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
#ifndef __sitkImageFileWriter_h
#define __sitkImageFileWriter_h

#include "sitkMacro.h"
#include "sitkImage.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkIO.h"
#include "sitkProcessObject.h"

#include <memory>

namespace itk {
  namespace simple {

    /** \class ImageFileWriter
     * \brief Write out a SimpleITK image to the specified file location
     *
     * This writer tries to write the image out using the image's type to the
     * location specified in FileName. If writing fails, an ITK exception is
     * thrown.
     *
     * \sa itk::simple::WriteImage for the procedural interface
     */
    class SITKIO_EXPORT ImageFileWriter  :
      public ProcessObject
    {
    public:
      typedef ImageFileWriter Self;

      // function pointer type
      typedef Self& (Self::*MemberFunctionType)( const Image& );

      // list of pixel types supported
      typedef NonLabelPixelIDTypeList PixelIDTypeList;

      ImageFileWriter( void );

      /** Print ourselves to string */
      virtual std::string ToString() const;

      /** return user readable name fo the filter */
      virtual std::string GetName() const { return std::string("ImageFileWriter"); }

      /** \brief Enable compression if available for file type.
       *
       * These methods Set/Get/Toggle the UseCompression flag which
       * get's passed to image file's itk::ImageIO object. This is
       * only a request as not all file formatts support compression.
       * @{ */
      Self& SetUseCompression( bool UseCompression );
      bool GetUseCompression( void ) const;

      Self & UseCompressionOn( void ) { return this->SetUseCompression(true); }
      Self & UseCompressionOff( void ) { return this->SetUseCompression(false); }
      /** @} */

      Self& SetFileName ( std::string fileName );
      std::string GetFileName() const;

      Self& Execute ( const Image& );
      Self& Execute ( const Image& , const std::string &inFileName, bool inUseCompression );

    private:

      template <class T> Self& ExecuteInternal ( const Image& );

      bool m_UseCompression;
      std::string m_FileName;

      // friend to get access to executeInternal member
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;

      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;

    };

  SITKIO_EXPORT void WriteImage ( const Image& image, const std::string &fileName, bool useCompression=false );
  }
}

#endif
