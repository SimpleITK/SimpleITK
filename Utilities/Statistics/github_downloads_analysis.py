# =========================================================================
#
#  Copyright NumFOCUS
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0.txt
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
# =========================================================================

#
# Provide inline script metadata per PEP 723 (https://peps.python.org/pep-0723/)
# /// script
# requires-python = "==3.12"
# dependencies = [
#   "requests",
#   "pandas",
#   "matplotlib"
# ]
# ///

import argparse
import pandas as pd
import re
import sys
import os
import requests
from typing import Dict, List, Optional
import matplotlib.pyplot as plt

"""
This script retrieves release download statistics from github.com/SimpleITK/SimpleITK
and generates a csv output file "download_counts.csv" and two figures in PDF format,
bargraphs showing download counts per release categorized by programming language,
"download_counts_per_language.pdf" and operating system, "download_counts_per_os.pdf".

Usage (without explicitly creating a virtual environment or installing dependencies):
Run the script using the uv (https://docs.astral.sh/uv/) tool as follows:
uv run downloads_analysis.py
"""


def retrieve_all_releases(repo: str, token: Optional[str] = None) -> List[Dict]:
    """
    Retrieve all releases from the specified GitHub repository.

    Args:
        repo (str): GitHub repository using 'owner/repo' format.
        token (Optional[str]): GitHub personal access token for authentication.
            Provides higher rate limits (requests/hour) and access
            to private repositories.

    Returns:
        list: List of release dictionaries. Relevant keys are 'tag_name',
              'prerelease', and 'assets'. Assets is a list of dictionaries with
              the relevant keywords being 'name' and 'download_count'.
    """
    headers = {}
    maximum_value_per_page = 100  # max value according to GitHub API documentation
    if token:
        headers["Authorization"] = f"token {token}"

    releases = []
    page = 1
    while True:
        url = f"https://api.github.com/repos/{repo}/releases?page={page}&per_page={maximum_value_per_page}"
        response = requests.get(url, headers=headers)
        response.raise_for_status()
        page_releases = response.json()
        if not page_releases:
            break
        releases.extend(page_releases)
        page += 1
    return releases


def analyze_releases(
    releases: List[Dict],
    asset_classpatterns: Dict[str, re.Pattern],
    combined_classes: List[Dict[str, List[str]]],
) -> None:
    """
    Analyze the release data and compute download statistics.
    Args:
        releases (List[Dict]): List of release dictionaries as retrieved from GitHub API.
        asset_classpatterns (Dict[str, re.Pattern]): Dictionary mapping asset class names
                                                    to compiled regular expression patterns
                                                    for matching asset filenames.
        combined_classes (List[Dict[str, List[str]]]): List of dictionaries defining
                                                       broader combined classes. Each dictionary
                                                       maps a combined class name to a list
                                                       of asset class names to combine. The
                                                       asset class names that are combined
                                                       are the values from asset_classpatterns.keys().
    """
    # Get the relevant information from the releases list of dictionaries
    # and compute the download statistics for the broader/combined categories
    class_stats_per_release = {}
    published_at = []
    for r in releases:
        published_at.append(r["published_at"])
        class_stats_per_release[r["tag_name"]] = dict(
            zip(asset_classpatterns.keys(), [0] * len(asset_classpatterns))
        )
        for a in r["assets"]:
            for class_str in asset_classpatterns.keys():
                if asset_classpatterns[class_str].match(a["name"]):
                    class_stats_per_release[r["tag_name"]][class_str] += a[
                        "download_count"
                    ]
    df = pd.DataFrame.from_dict(class_stats_per_release, orient="index")
    df = df.reset_index().rename(columns={"index": "release_tag"})
    df["published_at"] = pd.to_datetime(published_at)
    df = df.sort_values("published_at")

    for combined_class in combined_classes:
        for k, v in combined_class.items():
            if all(item in df.columns for item in v):
                df[k] = df[v].apply(lambda x: x.sum(), axis=1)
    return df


def plot_datetime_spaced_stacked_barchart(
    df: pd.DataFrame,
    date_time_column: str,
    tick_label_column: str,
    title: str,
    xlabel: str,
    ylabel: str,
    bar_width=20,
    colormap=plt.cm.tab10.colors,
    figsize=(12, 6),
):
    """
    Create a stacked bar chart with bars positioned according to datetime values. All other columns
    are assumed to be the data series to plot.
    Args:
        df (pd.DataFrame): DataFrame containing the data to plot. The column specified by date_time_column
                           should contain datetime values.
        date_time_column (str): Name of the column containing datetime values for x-axis positions.
        tick_label_column (str): Name of the column containing string labels for x-axis ticks.
        title (str): Title of the plot.
        xlabel (str): Label for the x-axis.
        ylabel (str): Label for the y-axis.
        bar_width (int, optional): Width of the bars in days. Defaults to 20.
        colormap (list, optional): List of colors for the bars. Defaults to plt.cm.tab10.colors.
        figsize (tuple, optional): Figure size. Defaults to (12, 6).
    Returns:
        fig, ax: Matplotlib figure and axis objects.
    """
    fig, ax = plt.subplots(figsize=figsize)

    x_positions = df[date_time_column]
    # Plot stacked bars at actual date positions
    bottom = None
    colors = colormap
    for i, col in enumerate(
        df.columns.difference([date_time_column, tick_label_column])
    ):
        if bottom is None:
            ax.bar(x_positions, df[col], width=bar_width, label=col, color=colors[i])
            bottom = df[col].values
        else:
            ax.bar(
                x_positions,
                df[col],
                width=bar_width,
                bottom=bottom,
                label=col,
                color=colors[i],
            )
            bottom = bottom + df[col].values

    # Set x-axis tick positions and labels
    ax.set_xticks(x_positions)
    ax.set_xticklabels(df[tick_label_column], rotation=90, ha="center")

    ax.set_title(title)
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)
    ax.legend()
    plt.tight_layout()
    return fig, ax


def main():
    parser = argparse.ArgumentParser(
        description="Analyze SimpleITK GitHub release download statistics",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument(
        "--version_expression",
        default="v\\d+\\.\\d+\\.\\d+",  # All non draft releases
        help="Regular expression denoting which git tags to analyze"
        + '(e.g. "v2\\.\\d+\\.\\d+" denoting all releases under major version 2)',
    )
    parser.add_argument("--ignore_prereleases", action="store_true")

    # If used in a GitHub Action, set the token as environment variable
    # env:
    #  GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
    parser.add_argument(
        "--token",
        help="GitHub personal access token",
        default=os.environ.get("GITHUB_TOKEN"),
    )

    args = parser.parse_args()

    try:
        all_releases = retrieve_all_releases("SimpleITK/SimpleITK", args.token)

        # Prior to SimpleITK release 1.0.0 assets (binary distributions) were not uploaded to GitHub
        pre_1_0_pattern = re.compile(r"v?0\.\d+\.\d+")
        all_releases = [
            r for r in all_releases if not pre_1_0_pattern.match(r["tag_name"])
        ]

        # filter the releases based on version and whether to include prerelease
        # or ignore them
        pattern = re.compile(args.version_expression)
        filtered_releases = [r for r in all_releases if pattern.match(r["tag_name"])]
        if args.ignore_prereleases:
            filtered_releases = [r for r in filtered_releases if not r["prerelease"]]

        if not filtered_releases:
            print("No releases found matching the specified criteria.")
            return 1
        # Define asset classes language_os using the file naming patterns
        asset_classpatterns = {
            "python_windows": re.compile(r".*cp\d+.*win.*whl", re.IGNORECASE),
            "python_macos": re.compile(r".*cp\d+.*macosx.*whl", re.IGNORECASE),
            "python_linux": re.compile(r".*cp\d+.*linux.*whl", re.IGNORECASE),
            "csharp_windows": re.compile(r".*CSharp.*win.*\.zip", re.IGNORECASE),
            "csharp_macos": re.compile(r".*CSharp.*macosx.*\.zip", re.IGNORECASE),
            "csharp_linux": re.compile(r".*CSharp.*linux.*\.zip", re.IGNORECASE),
            "java_windows": re.compile(r".*Java.*win.*\.zip", re.IGNORECASE),
            "java_macos": re.compile(r".*Java.*macosx.*\.zip", re.IGNORECASE),
            "java_linux": re.compile(r".*Java.*linux.*\.zip", re.IGNORECASE),
            "source_code": re.compile(r".*source.*\.zip", re.IGNORECASE),
        }
        # Combine asset classes into broader categories, language
        # or os based
        combined_language_classes = {
            "python": ["python_windows", "python_macos", "python_linux"],
            "csharp": ["csharp_windows", "csharp_macos", "csharp_linux"],
            "java": ["java_windows", "java_macos", "java_linux"],
        }
        combined_os_classes = {
            "windows": ["python_windows", "csharp_windows", "java_windows"],
            "macos": ["python_macos", "csharp_macos", "java_macos"],
            "linux": ["python_linux", "csharp_linux", "java_linux"],
        }

        df = analyze_releases(
            filtered_releases,
            asset_classpatterns,
            [combined_language_classes, combined_os_classes],
        )
        df.to_csv("download_counts.csv", index=False)

        fig, _ = plot_datetime_spaced_stacked_barchart(
            df[
                ["published_at", "release_tag"] + list(combined_language_classes.keys())
            ],
            date_time_column="published_at",
            tick_label_column="release_tag",
            title="Downloads per Release by Language",
            xlabel="Release",
            ylabel="Download Count",
        )
        fig.savefig("download_counts_per_language.pdf", dpi=300, bbox_inches="tight")

        fig, _ = plot_datetime_spaced_stacked_barchart(
            df[["published_at", "release_tag"] + list(combined_os_classes.keys())],
            date_time_column="published_at",
            tick_label_column="release_tag",
            title="Downloads per Release by OS",
            xlabel="Release",
            ylabel="Download Count",
        )
        fig.savefig("download_counts_per_os.pdf", dpi=300, bbox_inches="tight")
        return 0

    except Exception as e:
        print(f"Fatal error: {e}")
        return 1


if __name__ == "__main__":
    sys.exit(main())
