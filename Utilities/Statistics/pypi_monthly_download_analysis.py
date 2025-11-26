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
# requires-python = ">=3.11"
# dependencies = [
#     "pandas>=2.0.0",
#     "matplotlib>=3.7.0",
#     "requests>=2.31.0",
#     "pycountry>=24.6.1",
#     "plotly>=5.17.0",
#     "kaleido>=1.2.0",
# ]
# ///

from datetime import datetime
from pathlib import Path
import argparse
import sys
import pathlib
from typing import Optional, List, Dict, Union
import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
import pandas as pd
import requests
import pycountry
import plotly.express as px


def csv_path(path, required_columns={}):
    """
    Define the csv_path type for use with argparse. Checks
    that the given path string is a path to a csv file and that the
    header of the csv file contains the required columns.
    """
    p = pathlib.Path(path)
    required_columns = set(required_columns)
    if p.is_file():
        try:  # only read the csv header
            expected_columns_exist = required_columns.issubset(
                set(pd.read_csv(path, nrows=0).columns.tolist())
            )
            if expected_columns_exist:
                return p
            else:
                raise argparse.ArgumentTypeError(
                    f"Invalid argument ({path}), does not contain all expected columns."
                )
        except UnicodeDecodeError:
            raise argparse.ArgumentTypeError(
                f"Invalid argument ({path}), not a csv file."
            )
    else:
        raise argparse.ArgumentTypeError(f"Invalid argument ({path}), not a file.")


def retrieve_official_releases_and_dates(
    repo: str = "SimpleITK/SimpleITK", token: Optional[str] = None
) -> List[Dict]:
    """
    Retrieve all releases from the specified GitHub repository.

    Args:
        repo (str): GitHub repository using 'owner/repo' format.
        token (Optional[str]): GitHub personal access token for authentication.
            Provides higher rate limits (requests/hour) and access
            to private repositories.

    Returns:
        pd.DataFrame: DataFrame with columns 'version', and 'date'
        for official release versions (no pre-releases or drafts).
    """
    headers = {}
    maximum_value_per_page = 100  # max value according to GitHub API documentation
    if token:
        headers["Authorization"] = f"token {token}"

    all_releases = []
    page = 1
    while True:
        url = f"https://api.github.com/repos/{repo}/releases?page={page}&per_page={maximum_value_per_page}"
        response = requests.get(url, headers=headers)
        response.raise_for_status()
        page_releases = response.json()
        if not page_releases:
            break
        all_releases.extend(page_releases)
        page += 1
    # Get the version without the 'v' prefix and the published date
    releases = []
    for release in all_releases:
        if not release["prerelease"] and not release["draft"]:
            releases.append(
                {
                    "version": release["tag_name"].lstrip("v"),
                    "date": datetime.strptime(
                        release["published_at"], "%Y-%m-%dT%H:%M:%SZ"
                    ),
                }
            )
    return pd.DataFrame(releases)


def pypi_monthly_downloads_country_report(
    df: pd.DataFrame, figure_title: str, output_file_name: Union[Path, str]
):

    # drop entries with no country code and unknown country codes
    dropped_downloads = df[df["country_code"].isna()]["download_count"].sum()
    df = df.dropna(subset=["country_code"])

    country_information = df["country_code"].apply(
        lambda code: pycountry.countries.get(alpha_2=code)
    )
    dropped_downloads += df[country_information.isna()]["download_count"].sum()
    unknown_country_codes = (df["country_code"][country_information.isna()]).unique()
    df = df[country_information.notna()]
    df["country_code"] = country_information[country_information.notna()].apply(
        lambda country: country.alpha_3
    )
    unknown_country_codes_str = ", ".join(unknown_country_codes)
    if unknown_country_codes_str:
        unknown_country_codes_str = "(" + unknown_country_codes_str + ")"
    print(
        f"Dropping {dropped_downloads} downloads with unknown or missing country codes {unknown_country_codes_str}."
    )

    # Group by month and country code, keeping the time dimension for animation
    monthly_country_downloads = (
        df.groupby(["month", "country_code"])["download_count"].sum().reset_index()
    )

    # Sort by month to ensure proper animation sequence
    monthly_country_downloads = monthly_country_downloads.sort_values("month")

    # Create animated choropleth map
    fig = px.choropleth(
        monthly_country_downloads,
        locations="country_code",
        locationmode="ISO-3",
        color="download_count",
        hover_data={"download_count": ":,.0f", "country_code": False, "month": True},
        animation_frame="month",
        color_continuous_scale="Viridis",
        title=f"{figure_title} - Monthly Animation",
        labels={"download_count": "Downloads", "month": "Month"},
        range_color=[0, monthly_country_downloads["download_count"].max()],
    )

    fig.update_layout(
        title_font_size=16,
        font_size=12,
        width=1200,
        height=700,
        geo=dict(
            showframe=False, showcoastlines=True, projection_type="equirectangular"
        ),
    )

    # Customize animation settings
    fig.update_layout(
        updatemenus=[
            {
                "type": "buttons",
                "showactive": False,
                "buttons": [
                    {
                        "label": "Play",
                        "method": "animate",
                        "args": [
                            None,
                            {
                                "frame": {"duration": 1000, "redraw": True},
                                "transition": {"duration": 300},
                                "fromcurrent": True,
                            },
                        ],
                    },
                    {
                        "label": "Pause",
                        "method": "animate",
                        "args": [
                            [None],
                            {
                                "frame": {"duration": 0, "redraw": False},
                                "mode": "immediate",
                                "transition": {"duration": 0},
                            },
                        ],
                    },
                ],
            }
        ],
        sliders=[
            {
                "steps": [
                    {
                        "args": [
                            [month],
                            {
                                "frame": {"duration": 0, "redraw": True},
                                "mode": "immediate",
                            },
                        ],
                        "label": month,
                        "method": "animate",
                    }
                    for month in sorted(monthly_country_downloads["month"].unique())
                ],
                "active": 0,
                "transition": {"duration": 300},
                "x": 0.1,
                "len": 0.9,
            }
        ],
    )

    # Save animated HTML
    html_file = output_file_name.replace(".pdf", "_animated.html")
    fig.write_html(html_file)

    # Create static aggregate map (total downloads across all months)
    total_country_downloads = (
        monthly_country_downloads.groupby("country_code")["download_count"]
        .sum()
        .reset_index()
    )

    # Add country names for hover information
    total_country_downloads["country_name"] = total_country_downloads[
        "country_code"
    ].apply(lambda code: pycountry.countries.get(alpha_3=code).name)

    # Create static choropleth for total downloads
    fig_static = px.choropleth(
        total_country_downloads,
        locations="country_code",
        locationmode="ISO-3",
        color="download_count",
        hover_name="country_name",
        hover_data={"download_count": ":,.0f", "country_code": False},
        color_continuous_scale="Viridis",
        title=f"{figure_title} - Total Downloads {monthly_country_downloads['month'].min()} to {monthly_country_downloads['month'].max()}",
        labels={"download_count": "Total Downloads"},
    )

    fig_static.update_layout(
        title_font_size=16,
        font_size=12,
        width=1200,
        height=700,
        geo=dict(
            showframe=False, showcoastlines=True, projection_type="equirectangular"
        ),
    )

    fig_static.write_image(output_file_name)

    # Save country summary stats to CSV
    country_totals = total_country_downloads.sort_values(
        "download_count", ascending=False
    )
    total_downloads = country_totals["download_count"].sum()
    percentage_multiplier = 100 / total_downloads
    country_stats_data = [
        {
            "country": row["country_name"],
            "count": row["download_count"],
            "percentage": int(round(row["download_count"] * percentage_multiplier)),
        }
        for _, row in country_totals.iterrows()
    ]
    country_stats_df = pd.DataFrame(country_stats_data)
    csv_file = output_file_name.replace(".pdf", "_stats.csv")
    country_stats_df.to_csv(csv_file, index=False)


def pypi_monthly_downloads_os_report(
    df: pd.DataFrame,
    figure_title: str,
    output_file_name: Union[Path, str],
    overlay_releases: bool,
):
    """
    Generate a stacked bar chart of monthly PyPI downloads by operating system.
    Optionally overlay official SimpleITK releases on the plot. File format is determined
    by the extension of output_file_name.
    Args:
        df (pd.DataFrame): DataFrame containing PyPI download data with columns "month", "operating_system", and "download_count".
        figure_title (str): Title for the figure.
        output_file_name (Union[Path, str]): Path to save the output figure.
        overlay_releases (bool): Whether to overlay official SimpleITK releases on the plot.

    """
    # Group by month and operating_system, summing download counts
    monthly_os_downloads = (
        df.groupby(["month", "operating_system"])["download_count"]
        .sum()
        .unstack(fill_value=0)
    )

    # Clean up the operating system categories - handle NaN and empty values
    monthly_os_downloads.columns = [
        col if pd.notna(col) and col != "" else "Unknown"
        for col in monthly_os_downloads.columns
    ]

    # Sort columns for consistent display (put common OS first)
    os_order = []
    for os_name in ["Linux", "Windows", "Darwin", "Unknown"]:
        if os_name in monthly_os_downloads.columns:
            os_order.append(os_name)
    # Add any other OS that might exist
    for col in monthly_os_downloads.columns:
        if col not in os_order:
            os_order.append(col)
    monthly_os_downloads = monthly_os_downloads[os_order]

    # Filter to only plot Windows, Linux, and Darwin
    plot_os = ["Linux", "Windows", "Darwin"]
    monthly_os_downloads_plot = monthly_os_downloads[
        [col for col in plot_os if col in monthly_os_downloads.columns]
    ]

    # Create the stacked bar chart
    fig, ax = plt.subplots(figsize=(14, 8))
    monthly_os_downloads_plot.plot(kind="bar", stacked=True, ax=ax, colormap="tab10")

    # Customize the plot
    ax.set_xlabel("Month", fontsize=12, fontweight="bold")
    ax.set_ylabel("Download Count", fontsize=12, fontweight="bold")
    ax.set_title(
        figure_title,
        fontsize=14,
        fontweight="bold",
    )

    # Add custom legend entry for toolkit releases
    handles, labels = ax.get_legend_handles_labels()
    if overlay_releases:
        releases_df = retrieve_official_releases_and_dates()
        release_information_color = "green"

        month_labels = monthly_os_downloads_plot.index.tolist()
        for _, release in releases_df.iterrows():
            release_month = release["date"].strftime("%Y-%m")
            # only plot releases that are within the data range
            if release_month in month_labels:
                # Find the numeric x-position for this month
                x_position = month_labels.index(release_month)
                # plot vertical line in background, zorder=0
                ax.axvline(
                    x=x_position, color=release_information_color, linestyle="--", linewidth=1.5, zorder=0
                )
                # Add version label at the top
                y_max = ax.get_ylim()[1]
                ax.text(
                    x_position,
                    y_max * 0.98,
                    release["version"],
                    rotation=90,
                    verticalalignment="top",
                    horizontalalignment="right",
                    fontsize=8,
                    color=release_information_color,
                    fontweight="bold",
                )

        handles.append(
            Line2D([0], [0], color=release_information_color, linestyle="--", linewidth=1.5, alpha=0.7)
        )
        labels.append("Toolkit Release")
    ax.legend(
        handles,
        labels,
        title="Operating System",
        bbox_to_anchor=(1.05, 1),
        loc="upper left",
    )

    ax.grid(axis="y", alpha=0.3)
    month_tick_spacing = 4
    ax.set_xticks(range(0, len(monthly_os_downloads_plot.index), month_tick_spacing))

    # Rotate x-axis labels for better readability
    plt.xticks(rotation=90, ha="center")

    # Adjust layout to prevent label cutoff
    plt.tight_layout()

    plt.savefig(output_file_name, dpi=300, bbox_inches="tight")

    # Save OS summary stats to CSV
    os_totals = monthly_os_downloads.sum().sort_values(ascending=False)
    percentage_multiplier = 100 / os_totals.sum()
    os_stats_data = [
        {
            "os_name": os_name,
            "count": count,
            "percentage": int(round(count * percentage_multiplier)),
        }
        for os_name, count in os_totals.items()
    ]
    os_stats_df = pd.DataFrame(os_stats_data)
    csv_file = output_file_name.replace(".pdf", "_stats.csv")
    os_stats_df.to_csv(csv_file, index=False)


def main():

    parser = argparse.ArgumentParser(
        description="Plot SimpleITK PyPI download information (by operating system and by country)",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument(
        "pypi_data_file",
        type=lambda x: csv_path(
            x,
            required_columns={
                "month",
                "operating_system",
                "ci",
                "download_count",
                "python_version",
                "country_code",
            },
        ),
        help="Path to the CSV file containing PyPI download data",
    )
    parser.add_argument(
        "--overlay_releases",
        action="store_true",
        help="Overlay SimpleITK releases on the download plot",
    )
    parser.add_argument(
        "--exclude_ci",
        action="store_true",
        help="Exclude CI downloads from the analysis",
    )
    args = parser.parse_args()

    df = pd.read_csv(args.pypi_data_file)
    # Exclude all downloads where 'ci' is empty, False, or NaN
    if args.exclude_ci:
        df = df[df["ci"] != True]

    os_figure_title = "SimpleITK PyPI Downloads by Operating System"
    country_figure_title = "SimpleITK PyPI Downloads by Country"
    if args.exclude_ci:
        os_figure_title += " (excluding CI)"
        country_figure_title += " (excluding CI)"

    # The output file extension determines the format
    pypi_monthly_downloads_os_report(
        df,
        figure_title=os_figure_title,
        output_file_name="pypi_downloads_by_os.pdf",
        overlay_releases=args.overlay_releases,
    )

    pypi_monthly_downloads_country_report(
        df,
        figure_title=country_figure_title,
        output_file_name="pypi_downloads_by_country.pdf",
    )


if __name__ == "__main__":
    sys.exit(main())
