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
#ifndef __sitkImageSeriesWriter_h
#define __sitkImageSeriesWriter_h

#include "sitkMacro.h"
#include "sitkImage.h"
#include "sitkProcessObject.h"
#include "sitkIO.h"
#include "sitkMemberFunctionFactory.h"

namespace itk {
  namespace simple {

    /** \class ImageSeriesWriter
     * \brief Writer series of image from a SimpleITK image
     *
     * \sa itk::simple::WriterImage for the procedural interface
     **/
    class SITKIO_EXPORT ImageSeriesWriter
      : public ProcessObject
    {
    public:
      typedef ImageSeriesWriter Self;

      ImageSeriesWriter();

      /** Print ourselves to string */
      virtual std::string ToString() const;

      /** return user readable name fo the filter */
      virtual std::string GetName() const { return std::string("ImageSeriesWriter"); }

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

      Self & SetFileNames ( const std::vector<std::string> &fileNames );
      const std::vector<std::string> &GetFileNames() const;


      Self & Execute( const Image& );
      Self & Execute( const Image &image, const std::vector<std::string> &inFileNames, bool inUseCompression );

    protected:

      template <class TImageType> Self &ExecuteInternal ( const Image& inImage );

    private:

      // function pointer type
      typedef Self& (Self::*MemberFunctionType)( const Image& );

      // friend to get access to executeInternal member
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;

      bool m_UseCompression;
      std::vector<std::string> m_FileNames;
    };

  SITKIO_EXPORT void WriteImage ( const Image & image, const std::vector<std::string> &fileNames, bool inUseCompression  );
  }
}

#endif
