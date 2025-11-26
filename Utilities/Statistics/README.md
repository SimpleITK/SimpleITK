# SimpleITK Downloads Analysis

This directory contains two scripts for analyzing SimpleITK download statistics. One analyzes the binary downloads from GitHub, release artifacts, and the other analyzes PyPI downloads.

`Python` binaries are distributed via [PyPI](https://pypi.org/project/simpleitk/) and [conda-forge](https://anaconda.org/channels/conda-forge/packages/simpleitk/overview). Convenient snapshots of PyPI downloads for the past several months can be viewed on [pypistats](https://pypistats.org/packages/simpleitk) or [clickpy](https://clickpy.clickhouse.com/dashboard/simpleitk). Conda package download statistics can be viewed on the [conda-forge channel](https://anaconda.org/channels/conda-forge/packages/simpleitk/overview).

`Java` and `C#` binary packages are only available as GitHub release artifacts which requires using the `github_downloads_analysis` script to analyze their downloads.

`R` binary packages are not distributed. Instead an [installer](https://github.com/SimpleITK/SimpleITKRInstaller) which clones the SimpleITK repository and performs a local build is provided. There is no convenient way of tracking the number of repository clones associated with the `R` installer.

## Download analysis scripts

Run the two scripts using the [uv Python package and project manager](https://docs.astral.sh/uv/) without installing anything. This relies on inline script metadata per [PEP 723](https://peps.python.org/pep-0723/).

### GitHub release artifact downloads

The script `github_downloads_analysis` retrieves the artifact download statistics per release from GitHub, saves a csv output file `download_counts.csv` with the information and creates two figures in PDF format, bargraphs showing download counts per release categorized by programming language,
`download_counts_per_language.pdf` and operating system, `download_counts_per_os.pdf`.


Most common invocation:
```
uv run https://raw.githubusercontent.com/SimpleITK/SimpleITK/refs/heads/main/Utilities/Statistics/github_downloads_analysis.py --ignore_prereleases
```
One can include the pre-releases if desired or limit the analysis to a subset of releases by providing a regular expression. For example, all releases from the second major release family including pre-releases:
```
uv run https://raw.githubusercontent.com/SimpleITK/SimpleITK/refs/heads/main/Utilities/Statistics/github_downloads_analysis.py --version_expression "v2.*.*"
```

### PyPI monthly download analysis

The script `pypi_monthly_download_analysis` outputs two pdfs, `pypi_downloads_by_os`, a stacked per-month bar graph of downloads per operation system with an optional overlay of the SimpleITK releases. The second pdf `pypi_downloads_by_country` is a world map with color denoting the total downloads over the time period from each country. Two csv files are also produced, `pypi_downloads_by_os_stats` total downloads per OS and `pypi_downloads_by_country_stats` total downloads per country. Finally, an html file `pypi_downloads_by_country_animated` provides a per month view of downloads across the world. When looking at the world map of downloads, some locations are questionable. For example the couple of downloads from Antarctica (AQ) in 2024 and 2025, which were likely downloaded via [VPN](https://en.wikipedia.org/wiki/Virtual_private_network) from a more inhabited location.


Before running the analysis we need to obtain the PyPI download data. This requires a Google account as the PyPI download statistics dataset is hosted on Google BigQuery. The PyPI table schema describing the data is [available here](https://console.cloud.google.com/bigquery?p=bigquery-public-data&d=pypi&page=dataset&project=advance-stratum-298519&ws=!1m9!1m4!4m3!1sbigquery-public-data!2spypi!3ssimple_requests!1m3!3m2!1sbigquery-public-data!2spypi
).

To obtain download information for the past 5 years, sorted by month with columns titled "month", "operating_system", "python_version", "ci", "country_code", "download_count" run the following SQL query on [BigQuery](https://console.cloud.google.com/bigquery) (change the time interval to your needs):
```
SELECT
FORMAT_TIMESTAMP('%Y-%m', timestamp) as month,
details.system.name as operating_system,
REGEXP_EXTRACT(details.python, r"^([^\.]+\.[^\.]+)") as python_version,
details.ci as ci,
country_code,
COUNT(*) as download_count,
FROM `bigquery-public-data.pypi.file_downloads`
WHERE timestamp BETWEEN TIMESTAMP_ADD(CURRENT_TIMESTAMP(), INTERVAL -5 * 365 DAY) AND TIMESTAMP_ADD(CURRENT_TIMESTAMP(), INTERVAL -1 DAY)
AND file.project = "simpleitk"
GROUP BY
month, operating_system, python_version, country_code, ci
ORDER BY
month
```
Download the resulting csv for analysis.

Note that the country encoding in the csv is [ISO 3166-1 alpha-2](https://en.wikipedia.org/wiki/ISO_3166-1_alpha-2). To plot downloads using the `plotly.express.choropleth` function we need to denote the country using [ISO 3166-1 alpha-3](https://en.wikipedia.org/wiki/ISO_3166-1_alpha-3) or country name. To convert between the alpha-2 and country name or alpha-3 we use the [pycountry](https://github.com/pycountry/pycountry) package which provides us with the full country information (alpha-2, alpha-3, name, flag etc.).

Most common invocation:
```
uv run https://raw.githubusercontent.com/SimpleITK/SimpleITK/refs/heads/main/Utilities/Statistics/pypi_monthly_download_analysis.py big_query_results.csv --overlay_releases
```
