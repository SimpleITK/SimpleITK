#!/usr/bin/env python


#    /files/some/path/stats/json

from __future__ import print_function
import requests
import json
import datetime

import pandas as pd
import numpy as np

import cartopy.crs as ccrs
import cartopy.feature as cf
import cartopy.io.shapereader as shpreader

import matplotlib.pyplot as plt
import matplotlib as mpl
import matplotlib.patches as mpatches

mpl.style.use('ggplot')


def get_sourceforge_stats(project,
                          start_date,
                          end_date=datetime.date.today(),
                          path="/"):

   """
   """

   # Get download statistics from SourceForge
   #
   # The API uses URLs very similar to the existing stats URLs. Here's an example:
   #    https://sourceforge.net/projects/openofficeorg.mirror/files/stats/json?start_date=2014-10-29&end_date=2014-11-04
   #
   # The url parameters start_date and end_date are required and must be
   # dates in YYYY-MM-DD format. To access project-wide stats, use
   #    /files/stats/json in the URL. To limit to a file or folder, use
   #    /files/some/path/stats/json

   print("start_date: {0}".format(start_date))
   query_url="https://sourceforge.net/projects/{0}/files/{1}/stats/json?start_date={2}&end_date={3}".format(project,
                                                                                                            path,
                                                                                                            start_date.isoformat(),
                                                                                                            end_date.isoformat())
   print("Query: \"{0}\"...".format(query_url))
   r = requests.get(query_url)

   if r.status_code == requests.codes.ok:
       return json.loads(r.text)
   else:
       r.raise_for_status()


#project="itk"
#path="itk"

project="simpleitk"
path="SimpleITK"
start_date=datetime.date(2013,1,1)
end_date=datetime.date.today() - datetime.timedelta(days=1)


# Load the JSON data into a nested dictionary structure
sf_json = get_sourceforge_stats(project,
                                start_date,
                                end_date,
                                path)


# Load the downloads over time into a Pandas Series
sf_dbym = pd.DataFrame(sf_json["downloads"])
sf_dbym.columns=["Date","Download Count"]
sf_dbym.set_index(sf_dbym.columns[0],inplace=True)
sf_dbym.index = pd.to_datetime(sf_dbym.index)

sf_dbym.plot(kind='area')
plt.title("SimpleITK SourceForge Downloads")
plt.ylabel("Downloads per Month")
plt.show()


# load the country, OS download counts into a DataFrame, from json
# the json field "oses_by_country" is a dict of countries indexing a dict of OSes and download
cbo_df = pd.DataFrame([v for (k,v) in sf_json["oses_by_country"].items()], index=sf_json["oses_by_country"].keys())
cbo_df.index.name="Country"
cbo_df.fillna(0,inplace=True)
cbo_df = cbo_df.astype(int)

# sort the data frame with the most popular country and OS at 0 (upper left)
cbo_df = cbo_df.loc[cbo_df.sum(axis=1).sort_values(ascending=False).index]
cbo_df = cbo_df[cbo_df.sum(axis=0).sort_values(ascending=False).index]
print(cbo_df)


# Graph OSes
# TODO: Combine OSes into a "Other" group
os_series= cbo_df.sum(axis=0).sort_values(ascending=False)
os_series.name = "OS"
os_series.plot(kind='pie',
               autopct='%1.1f%%',
               title="SourceForge Downloads by OS")
plt.show()


# Graph countries with pie Chart
total = cbo_df.sum(axis=1).sum()
percent = 0.80
bool_index = cbo_df.sum(axis=1).sort_values(ascending=False).cumsum()/total<percent
df = cbo_df.loc[bool_index].copy()
df.loc["Other"] = cbo_df.loc[~(bool_index)].sum(axis=0)
print(df)
df.sum(axis=1).plot(kind='pie',
            autopct='%1.1f%%',
            title="Downloads by Country")
plt.show();

#
# Cartography plot of downloads by country
#
c_series = cbo_df.sum(axis=1)
c_series = c_series.sort_values(ascending=False)
cmap = mpl.cm.OrRd

max_dl = float(c_series.max())
min_dl = float(c_series.min())

norm = mpl.colors.LogNorm(vmin=min_dl, vmax=max_dl)
total_users = c_series.sum()
shapename = 'admin_0_countries'
countries_shp = shpreader.natural_earth(resolution='110m', category='cultural', name=shapename)

plt.figure(figsize=(14,8))
ax = plt.axes(projection=ccrs.Robinson() )
ax.add_feature(cf.BORDERS)
ax.add_feature(cf.COASTLINE)
#ax.add_feature(cf.OCEAN)
#ax.add_feature(cf.LAND)

hdl_dict = dict()

for country in shpreader.Reader(countries_shp).records():
    name = country.attributes['name_long']
    if name in c_series:
        num_users = c_series[name]
        hdl = ax.add_geometries(country.geometry, ccrs.PlateCarree(),
                               facecolor=cmap(norm(num_users),alpha=True))
        hdl_dict[name] = hdl

# Add ColorBar
sm = plt.cm.ScalarMappable(cmap=cmap,norm=norm)
sm._A = [] # WHAT? DANGER
plt.colorbar(sm,ax=ax)
plt.title("Source Forge Downloads by Country\n{0} to {1}".format(start_date, end_date))

# Add Legend
cnt = (cbo_df.sum(axis=1).sort_values(ascending=False).cumsum()/total < percent).sum()

p = [ mpatches.Patch(color=cmap(norm(v)), label="{0} ({1})".format(k,v)) for (k,v) in c_series[0:cnt].iteritems()]
plt.legend(handles=p,
           loc=3, fancybox=True)
plt.savefig("{0}_CountriesCarto_{1}_{2}.pdf".format(project,start_date, end_date), format='pdf')
plt.show()

##################################################
#
# PyPI Download Statistics - via Google BigData Query
#
#
"""
SELECT
  STRFTIME_UTC_USEC(timestamp, "%Y-%m") AS yyyymm,
  COUNT(*) as download_count
FROM
  TABLE_DATE_RANGE(
    [the-psf:pypi.downloads],
    DATE_ADD(CURRENT_TIMESTAMP(), -12, "month"),
    CURRENT_TIMESTAMP()
  )
WHERE
  file.project = 'simpleitk' and details.installer.name != 'bandersnatch'
GROUP BY
  yyyymm, file.version
ORDER BY
  yyyymm DESC, download_count DESC, file.version DESC
LIMIT 100
"""
#
##################################################

df = pd.read_csv("psf-pypi-downloads-simpleitk-query.csv")
print(df)

# Load query results into a data frame
df["yyyymm"] = pd.to_datetime(df["yyyymm"], format=("%Y-%m") )
if "file_version" in df.columns:
   df = df.pivot(index='yyyymm', columns='file_version', values='download_count')
   df.columns.name = "Version"
else:
   df.set_index('yyyymm', inplace=True)


df.fillna(0,inplace=True)
df = df.astype(int)
df.sort_index(ascending=False,inplace=True)

print(df)
print("Total PyPI Downloads: {0}".format(df.sum(axis=1).sum()))

# Plot the PyPI downloads of different versions
df.plot(kind="area",
           title="SimpleITK PyPI Downloads")
plt.ylabel("Downloads per Month")
plt.show()

# Create Series for PyPI downloads by time
s = df.sum(axis=1)
s.name= "PyPI Download Count"
s.index.name="Date"

# Manually enter dates of tags
tags = pd.Series({"2017-04-05":"v1.0.0",
                  "2016-07-27":"v0.10.0",
                  "2015-09-25":"v0.9.1",
                  "2015-05-12":"v0.9.0",
                  "2014-12-19":"v0.8.1",
                  "2014-03-08":"v0.8.0",
                  "2013-11-21":"v0.7.1",
                  "2013-09-30":"v0.7.0",
                  "2013-02-01":"v0.6.0"})
tags.index = pd.to_datetime(tags.index)
tags.name = "Releases"


#
# Combine SourceForge and PyPI download statistics into Total Downloads
#
combined_df = pd.concat([sf_dbym,pd.DataFrame(s)],axis=1)
combined_df.columns = ["Source Forge Downloads", combined_df.columns[1]]

plt.figure(figsize=(8,10))
ax = combined_df.plot(kind="area")

i = 1
for (date,tag) in tags.iteritems():
    #ax.plot(date, 0, 'o')
    ax.annotate(tag,(date,800), horizontalalignment='left', verticalalignment='center', rotation=90)
    i = i +1

plt.title("SimpleITK Downloads");
plt.ylabel("Downloads per Month")

plt.savefig("{0}_Downloads_{1}_{2}.pdf".format(project,start_date, end_date), format='pdf')
plt.show()
