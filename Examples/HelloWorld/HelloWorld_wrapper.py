#!/usr/bin/env python

import SimpleITK as sitk
import matplotlib.pyplot as plt

import HelloWorld

# Hard-coding a screen dpi of 96: calculating it appears to be difficult
SCREEN_DPI = 96
image = HelloWorld.main()
size_pixels = image.GetSize()

nda = sitk.GetArrayFromImage(image)
plt.figure(figsize=(size_pixels[0] / SCREEN_DPI, size_pixels[1] / SCREEN_DPI))
plt.axis('off')
plt.imshow(nda, cmap='gray')
