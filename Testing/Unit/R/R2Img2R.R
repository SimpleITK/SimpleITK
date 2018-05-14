## test that the transitions from R array to SimpleITK image and the
## other way round work as expected.

library(SimpleITK)

orig_arr <- array(0.0, dim=c(2,4,3))
orig_single_channel_img <- Image(c(2,4,3), "sitkFloat64")
orig_multi_channel_img <- Image(c(2,4), "sitkVectorFloat64", 3)

intensity_stat_filter <- StatisticsImageFilter()

# Get a single channel image
img <- as.image(orig_arr)
intensity_stat_filter$Execute(img - orig_single_channel_img)
if(intensity_stat_filter$GetSigma()!= 0 || intensity_stat_filter$GetMaximum()!=0)
{
  cat("Failure creating single channel image from array.\n")
  quit(save="no", status=1)
}

# Get the array back
if(!identical(orig_arr, as.array(img)))
{
  cat("Failure creating array from single channel image.\n")
  quit(save="no", status=1)
}


# Get a multi channel image
img <- as.image(orig_arr, isVector=TRUE)
diff_img <- img - orig_multi_channel_img
for(i in 1:img$GetDimension())
{
  intensity_stat_filter$Execute(VectorIndexSelectionCast(diff_img, i-1))
  if(intensity_stat_filter$GetSigma()!= 0 || intensity_stat_filter$GetMaximum()!=0)
  {
    cat("Failure creating multi channel image from array.\n")
    quit(save="no", status=1)
  }
}

# Get the array back
if(!identical(orig_arr, as.array(img)))
{
  cat("Failure creating array from single multi channel image.\n")
  quit(save="no", status=1)
}

quit(save="no", status=0)
