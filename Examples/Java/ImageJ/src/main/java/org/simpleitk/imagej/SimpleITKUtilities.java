package org.simpleitk.imagej;

import ij.IJ;
import ij.ImagePlus;
import ij.gui.NewImage;
import ij.plugin.Duplicator;
import net.haesleinhuepf.clij.coremem.interop.JNAInterop;
import net.haesleinhuepf.clij.coremem.offheap.OffHeapMemory;
import org.itk.simple.*;

class SimpleITKUtilities {
    /**
     * Convert a SimpleITK image to an ImageJ image
     *
     * @param image 2D ITK image
     * @return 2D ImageJ image
     */
    public static ImagePlus itkToIJ(Image image) {
        long bytesPerPixel = 0;

        // determine memory size
        long length = image.getWidth() * image.getHeight();
        if (image.getDimension() == 3) {
            length = length * image.getDepth();
        }

        ImagePlus buffer = null;
        long pointer = 0;

        // for simplicity, we only convert 32-bit float images
        image = SimpleITK.cast(image, PixelIDValueEnum.sitkFloat32);
        bytesPerPixel = 4;

        // retrieve pointer
        SWIGTYPE_p_float bufferAsFloat = image.getBufferAsFloat();
        pointer = SWIG_FLOAT.getPointer(bufferAsFloat);

        // create empty image
        buffer = NewImage.createFloatImage("image", (int)image.getWidth(), (int)image.getHeight(), 1, NewImage.FILL_BLACK);

        // wrap pointer
        OffHeapMemory offHeapMemory = OffHeapMemory.wrapPointer(JNAInterop.getJNAPointer(pointer), length * bytesPerPixel);

        // copy pixels
        offHeapMemory.copyTo((float[])buffer.getProcessor().getPixels());

        return buffer;
    }

    /**
     * Convert an image from ImageJ to SimpleITK
     *
     * @param input 2D ImageJ image of type 8, 16 or 32 bit
     * @return 2D ITK image
     */
    public static Image ijToITK(ImagePlus input) {
        long bytesPerPixel = 4;
        long length = input.getWidth() * input.getHeight() * input.getNSlices();

        // for simplicity, we only convert 32-bit float images
        if (input.getBitDepth() != 32) {
            input = new Duplicator().run(input);
            IJ.run(input, "32-bit", "");
        }

        // create a new image
        Image image = new Image(input.getWidth(), input.getHeight(), PixelIDValueEnum.sitkFloat32);

        // retrieve its pointer
        SWIGTYPE_p_float bufferAsFloat = image.getBufferAsFloat();
        long pointer = SWIG_FLOAT.getPointer(bufferAsFloat);

        // wrap pointer
        OffHeapMemory offHeapMemory = OffHeapMemory.wrapPointer(JNAInterop.getJNAPointer(pointer), length * bytesPerPixel);

        // copy pixels
        offHeapMemory.copyFrom((float[])input.getProcessor().getPixels());
        return image;
    }

    // workaround class
    static class SWIG_FLOAT extends SWIGTYPE_p_float {
        public static long getPointer(SWIGTYPE_p_float t) {
            return SWIGTYPE_p_float.getCPtr(t);
        }
    }
}
