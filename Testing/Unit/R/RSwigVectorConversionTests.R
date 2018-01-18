## Test automatic conversion of C++ std::vector types
## Note that RPixelAccess tests all the options for numeric vectors
## being converted to R vectors, but it doesn't test conversion
## from R to C++
## Dicom example deals with std::vector<std::string> cases
## Some problems have occurred in the past due to references not being
## included specifically in the swig definitions.
library(SimpleITK)
options(warn=2)
img = Image(64, 64, "sitkFloat32")
img$SetOrigin(c(0.3,0.6))
img$SetSpacing(c(0.4,1.0))
p1<-c(0.1,0.1)

## This is a problem with swig and unsupported vector types
## Will need to address it.
## R to const std::vector< double > &point
## and std::vector< int64_t > to R
p1Indexes <-img$TransformPhysicalPointToIndex(p1)
sprintf("Point coordinates: %.1f %.1f Point indexes: %d %d",p1[1],p1[2],p1Indexes[1], p1Indexes[2])



# R to const std::vector< int64_t > &index)
# std::vector<double> to R
p2Location <- img$TransformIndexToPhysicalPoint(c(1,1))
print(p2Location)

# R to const std::vector<uint32_t>  &r
bd <- BinaryDilateImageFilter()
bd$SetKernelRadius(c(3,4))
# std::vector<uint32_t> to R
bd$GetKernelRadius()

# R to const std::vector<unsigned int> & Radius
bm <- BinaryMedianImageFilter()
bm$SetRadius(c(7,7))
# std::vector<unsigned int> to R
bm$GetRadius()

# R to std::vector<float>
st <- MultiLabelSTAPLEImageFilter()
st$SetPriorProbabilities(c(0.25, 0.25, 0.1))
# std::vector<float> to R
st$GetPriorProbabilities()

# R to const std::vector< std::string >
given_file_names <- c('1.dcm', '2.dcm')
reader <- ImageSeriesReader()
reader$SetFileNames(given_file_names)
reader_file_names <- c()
try(reader_file_names <- reader$GetFileNames(), silent=TRUE)
if(!identical(given_file_names, reader_file_names)) {
    cat("Problem with ImageSeriesReader::GetFileNames.\n")
    quit(save="no", status=1)
}
