/*=========================================================================
*
*  Copyright Insight Software Consortium
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/
#ifndef __sitkImageReaderBase_h
#define __sitkImageReaderBase_h

#include "sitkProcessObject.h"
#include "sitkPixelIDValues.h"
#include "sitkIO.h"

namespace itk {

// Forward decalaration for pointer
class ImageIOBase;

template<class T>
class SmartPointer;

  namespace simple {

    /** \class ImageReaderBase
     * \brief An abract base class for image readers
     *
     */
    class SITKIO_EXPORT ImageReaderBase :
      public ProcessObject
    {
    public:
      typedef ImageReaderBase Self;

      ImageReaderBase();
      // The destructor will be implicitly declared as public.

      /** \brief Set/Get The output PixelType of the image.
       *
       * By default the value is sitkUnknown, which enable the output
       * pixel type to be same as the file. If the pixel type is
       * specified then the itk::ConvertPixelBuffer will be used to
       * convert the pixels.
       * @{
       */
      Self& SetOutputPixelType( PixelIDValueEnum pixelID );
      PixelIDValueEnum GetOutputPixelType( void ) const;
      /* @} */

      virtual Image Execute() = 0;

      virtual std::string ToString() const;

    protected:


      void GetPixelIDFromImageIO( const std::string &fileName,
                                  PixelIDValueType &outPixelType,
                                  unsigned int & outDimensions);

      unsigned int GetDimensionFromImageIO( const std::string &fileName, unsigned int i);

    private:

      PixelIDValueType ExecuteInternalReadScalar( int componentType );

      PixelIDValueType ExecuteInternalReadVector( int componentType );

      PixelIDValueType ExecuteInternalReadComplex( int componentType );

      itk::SmartPointer<ImageIOBase> GetImageIOBase(const std::string &fileName);

      PixelIDValueEnum m_OutputPixelType;

    };
  }
}


#endif // __sitkImageReaderBase_h
