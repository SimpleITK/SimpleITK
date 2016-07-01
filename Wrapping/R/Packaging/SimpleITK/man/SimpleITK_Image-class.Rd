\name{_p_itk__simple__Image}
\Rdversion{1.1}
\docType{class}
\alias{_p_itk__simple__Image-class}
\alias{_p_itk__simple__Image}
\alias{SimpleITK_Image-class}
\alias{Image-class}
\alias{[,_p_itk__simple__Image-method}
\alias{[[,_p_itk__simple__Image-method}

\title{Class \code{"_p_itk__simple__Image"}}
\description{
The image class object used in SimpleITK. This object is a pointer to a C++ object
that contains the image voxel data and a range of meta data.

Classes in SimpleITK have methods accessible via '$' operator. These methods are used
to set and get class meta data.
}
\section{Image objecst}{
  Objects can be created by calls of the form

  \code{Image(xsize, ysize, zsize, 'sitkUInt8')},

  where 'sitkUInt8' defines the pixel type.

Most SimpleITK functions and filter classes also return images.

Images will often be saved in files and loaded using \code{im <- ReadImage(filename)}.

Arrays can be converted to images using \code{as.image}.
}

\section{Methods}{
  \describe{
    \item{[}{ The extract operator is used to perform image slicing in a
      similar fashion to array slicing, with indexes starting from 1.
      Standard slicing options are available, such as deleting using
      negative indexes or using logical indexes.

      There are some image specific conventions/differences, as follows.

      Using zero or empty indexes will raise an error:

      \code{im[c(), 1:3]}

      \code{im[1, 1:3, 0]}

      Slicing operations must produce constant voxel spacing in each
      dimension. i.e. subsampling must be uniform.

      Dropping a dimension (the default) is not always
      possible as SimpleITK images must be at least 2
      dimensional. Operations that request a 1D image will return a
      higher dimension image with some dimensions of size 1 and issue a
      warning.

      An R object (number or vector) will be return if the operation
      would otherwise result in an image with a single voxel.

      \code{im[1,2]}

      Array style assignment to image voxels is not yet supported.

    }
    \item{[[}{ The list access operator is used to extract an image
      component, such as the red channel from a colour image:

      \code{ red <- im[[1]] }
    }
    \item{Ops}{Arithmetic and logical operators are overloaded for
    images. Images are checked for consistency of spacing and spatial
    location.

    \code{ im1 * (im2 > 5) }

    Care may be required concerning pixel types - see the
    \code{\link{Cast}} function.
  }
  \item{Meta data methods are accessible using the '$' operator}{}
  \item{GetDimension}{Image dimension information

    \code{im$GetDimension()}

  }
  \item{GetNumberOfComponentsPerPixel}{}
  \item{SetOrigin/GetOrigin}{Image spatial origin meta data -

    \code{im$GetOrigin()}
  }
  \item{SetSpacing/GetSpacing}{Image voxel size meta data}
  \item{GetSize}{Image size meta data (dimensions in voxels)}
  \item{GetHeight/GetWidth/GetDepth}{Lengths of various image
    dimensions}
  \item{GetDirection/SetDirection}{Spatial transformation matrix}
  \item{TransformIndexToPhysicalPoint}{Spatial location from index}
  \item{TransformPhysicalPointToIndex}{Spatial location to index}
  \item{TransformPhysicalPointToContinuousIndex}{}
  \item{TransformContinuousIndexToPhysicalPoint}{}
  \item{CopyInformation}{Copy meta data information from another image}
  \item{GetPixel/SetPixel}{Pixel access methods - note indexing is
  C-style, starting from 0}
}
}
\references{
\url{https://itk.org/SimpleITKDoxygen/html/index.html}
}
