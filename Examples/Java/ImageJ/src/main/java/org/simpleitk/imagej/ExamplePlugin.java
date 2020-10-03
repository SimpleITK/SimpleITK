/*
 * To the extent possible under law, the ImageJ developers have waived
 * all copyright and related or neighboring rights to this tutorial code.
 *
 * See the CC0 1.0 Universal license for details:
 *     http://creativecommons.org/publicdomain/zero/1.0/
 */

package org.simpleitk.imagej;

import ij.IJ;
import ij.ImageJ;
import ij.ImagePlus;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;
import org.itk.simple.Image;
import org.itk.simple.SimpleITK;

public class ExamplePlugin implements PlugInFilter {

	/**
	 * We use this static method functional-programming style
	 * to wrap our image procressing algorithm: SimpleITKs
	 * implementation of Thresholding after Otsu et al. 1979.
	 *
	 * @param image input image (2D, single channel, grey scale)
	 * @return binary image
	 */
	public static ImagePlus process(ImagePlus image) {
		// convert image
		Image itk_image = SimpleITKUtilities.ijToITK(image);

		// process it
		Image itk_result = SimpleITK.otsuThreshold(itk_image);

		// convert back
		ImagePlus result = SimpleITKUtilities.itkToIJ(itk_result);

		return result;
	}


	/**
	 * This function is called by ImageJ when the user clicks
	 * the plugins menu item
	 *
	 * @param ip (unused)
	 */
	@Override
	public void run(ImageProcessor ip) {
		// retrieve current iamge from IamgeJ
		ImagePlus image = IJ.getImage();

		// process it
		ImagePlus result = process(image);

		result.show();
	}

	/**
	 * This function is called by ImageJ to figure out if this
	 * plugin can handle the given image.
	 *
	 * @param arg
	 * @param imp
	 * @return
	 */
	@Override
	public int setup(String arg, ImagePlus imp) {
		// define that this plugin can only process unsigned byte,
		// unsigned short and float images
		return DOES_8G | DOES_16 | DOES_32;
	}

	/**
	 * Main method for debugging
	 */
	public static void main(String[] args) throws Exception {

		// start ImageJ
		new ImageJ();

		// open the sample image
		ImagePlus image = IJ.openImage("src/main/resources/blobs.tif");

		// process it
		ImagePlus result = process(image);

		result.show();
	}

}
