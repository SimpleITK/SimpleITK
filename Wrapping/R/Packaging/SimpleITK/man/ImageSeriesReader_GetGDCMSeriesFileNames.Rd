\name{ImageSeriesReader_GetGDCMSeriesFileNames}
\alias{ImageSeriesReader_GetGDCMSeriesFileNames}
\alias{ImageSeriesReader_GetGDCMSeriesIDs}

%- Also NEED an '\alias' for EACH other topic documented here.
\title{ImageSeriesReader_GetGDCMSeriesFileNames
}
\description{
Tools for dicom sorting.
}
\usage{
ImageSeriesReader_GetGDCMSeriesFileNames(...)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{\dots}{
directory	Set the directory that contains the DICOM data set.
recursive	Recursively parse the input directory.
seriesID	Set the name that identifies a particular series. Default value is an empty string which will return the file names associated with the first series found in the directory.
useSeriesDetails	Use additional series information such as ProtocolName and SeriesName to identify when a single SeriesUID contains multiple 3D volumes - as can occur with perfusion and DTI imaging.
loadSequences	Parse any sequences in the DICOM data set. Loading DICOM files is faster when sequences are not needed.
}
}
\details{
GetGDCMSeriesFileNames: Generate a sequence of filenames from a directory with a DICOM data set and a series ID.

This method generates a sequence of filenames whose filenames point to DICOM files. The data set may contain multiple series. The seriesID string is used to select a specific series. The ordering of the filenames is based on one of several strategies, which will read all images in the directory ( assuming there is only one study/series ).

GetGDCMSeriesIDs: Get all the seriesIDs from a DICOM data set.

These functions appear slightly differently (i.e. not accessible via the dollar
method) as they are static C++ methods.
}
\value{
vector of strings containing IDs or filenames.
}
