# gaussian_utils.py
# This utility file hides most of the Example-specific code. The main() routine
# now returns both the input and output SITK images so they can be displayed
# individually.
import sys
import SimpleITK
import matplotlib.pyplot as plt
sys.path.append('../../Examples/SimpleGaussian')
from SimpleGaussian import main

# Hard-coding a screen dpi of 96: calculating it appears to be difficult
SCREEN_DPI = 96


def plot_image(image: SimpleITK.Image):
    size_pixels = image.GetSize()

    nda = SimpleITK.GetArrayFromImage(image)
    plt.figure(figsize=(size_pixels[0] / SCREEN_DPI, size_pixels[1] / SCREEN_DPI))
    plt.axis('off')
    plt.imshow(nda, cmap='gray')


def run_gaussian():

    args = ['simple_gaussian',
            '../../docs/images/BrainProtonDensitySlice.png',
            2.0,
            '/tmp/gaussian_out.png',
            ]

    orig_image, out_image = main(args)
    return orig_image, out_image
