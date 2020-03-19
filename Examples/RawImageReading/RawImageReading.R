#=========================================================================
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
#=========================================================================
# Run with:
#
# Rscript --vanilla RawImageReading.R raw_file_name sitk_pixel_type image_size
#
# where sitk_pixel_type is string representing the pixel type (e.g. sitkUInt16, sitkFloat32)
# and image size is the number of pixels per dimension [x,y,...] (e.g. 204 204)

library(SimpleITK)

#' Read a raw binary scalar image.
#'
#' @param binary_file_name (str): Raw, binary image file content.
#' @param image_size (tuple like): Size of image (e.g. [2048,2048])
#' @param sitk_pixel_type (SimpleITK pixel type: Pixel type of data (e.g. sitk.sitkUInt16).
#' @param image_spacing (tuple like): Optional image spacing, if none given assumed to be [1]*dim.
#' @param image_origin (tuple like): Optional image origin, if none given assumed to be [0]*dim.
#' @param big_endian (bool): Optional byte order indicator, if True big endian, else little endian.
#'
#' @return SimpleITK image.
read_raw<-function(binary_file_name, image_size, sitk_pixel_type, image_spacing=NULL,
                   image_origin=NULL, big_endian=FALSE)
{
    PIXEL_TYPE <- list("sitkUInt8" = "MET_UCHAR",
                       "sitkInt8" = "MET_CHAR",
                       "sitkUInt16" = "MET_USHORT",
                       "sitkInt16" = "MET_SHORT",
                       "sitkUInt32" = "MET_UINT",
                       "sitkInt32" = "MET_INT",
                       "sitkUInt64" = "MET_ULONG_LONG",
                       "sitkInt64" = "MET_LONG_LONG",
                       "sitkFloat32" = "MET_FLOAT",
                       "sitkFloat64" = "MET_DOUBLE")
    direction_cosine <- list("1 0 0 1", "1 0 0 0 1 0 0 0 1", "1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1")
    dim <- length(image_size)
    header <- c("ObjectType = Image\n",
                paste0("NDims = ",toString(dim),"\n"),
                paste0("DimSize = ", paste(image_size, collapse = " "), "\n"),
                paste0("ElementSpacing = ", paste((if (!is.null(image_spacing)) image_spacing else rep(1,dim)), collapse = " "), "\n"),
                paste0("Offset = ", paste(if (!is.null(image_origin)) image_origin else rep(0,dim), collapse = " "), "\n"),
                paste0("TransformMatrix = ", direction_cosine[dim-1], "\n"),
                paste0("ElementType = ", PIXEL_TYPE[sitk_pixel_type], "\n"),
                "BinaryData = True\n",
                paste0("BinaryDataByteOrderMSB = ", if (big_endian==FALSE) "False" else "True", "\n"),
                paste0("ElementDataFile = ", normalizePath(binary_file_name), "\n")) # ElementDataFile must be the last entry in the header

    fname <- tempfile(fileext = ".mhd") #generate temp file name
    writeLines(header, con=fname) #create and write to file
    img <- ReadImage(fname)
    file.remove(fname) #immediatly remove tempfile, otherwise it is automatically removed at the end of the R session
    return(img)
}

args <- commandArgs( TRUE )

if (length(args) < 6) {
   write("Usage arguments: <raw_file_name> <out_file_name> <big_endian false|true> <sitk_pixel_type> <image_size>", stderr())
   quit(save="no", status=1)
}

# Read the image using both big and little endian
image <- tryCatch(read_raw(binary_file_name=args[[1]], image_size=tail(args,-4), sitk_pixel_type=args[[4]], big_endian=as.logical(args[3])),
                                warning = function(err) {
                                    message(err)
                                    quit(save="no", status=1)
                                }
                               )

WriteImage(image, args[[2]])

if (exists("SITK_NOSHOW", mode="environment")) {
   Show(image, "little endian")
}

quit(save="no", status=0)
