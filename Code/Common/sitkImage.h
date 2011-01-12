#ifndef __sitkImage_h
#define __sitkImage_h

#include "sitkMacro.h"

#include "sitkPixelIDTypeLists.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkPixelContainer.h"

namespace itk
{
  namespace simple
  {

    class Image : public LightObject {
    public:
      typedef Image              Self;
      typedef SmartPointer<Self> Pointer;

      Image( uint64_t Width, uint64_t Height, PixelIDValueEnum ValueEnum );
      Image( uint64_t Width, uint64_t Height, uint64_t Depth, PixelIDValueEnum ValueEnum );


      template <typename TImageType>
      Image( itk::SmartPointer<TImageType> image );

      template <typename TImageType>
      Image( TImageType* image );

      itk::DataObject::Pointer GetImageBase( void );
      itk::DataObject::ConstPointer GetImageBase( void ) const;

      // could return -1 if in valid
      PixelIDValueType GetPixelIDValue( void ) const;

      unsigned int GetDimension( void ) const;

      uint64_t GetHeight( void );
      uint64_t GetWidth( void );
      uint64_t GetDepth( void );


      std::string GetPixelIDTypeAsString( void ) const;
      std::string ToString( void );

      typedef BasicPixelIDTypeList PixelIDTypeList;
      typedef void (Self::*MemberFunctionType)( uint64_t Width, uint64_t Height, uint64_t Depth );

      PixelContainer::Pointer GetPixelContainer();

    protected:

      void Allocate ( uint64_t Width, uint64_t Height, uint64_t Depth, PixelIDValueEnum ValueEnum );
      template<class TImageType> void AllocateInternal ( uint64_t Width, uint64_t Height, uint64_t Depth );
      friend struct detail::AllocateMemberFunctionAddressor<MemberFunctionType>;
      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType, detail::AllocateMemberFunctionAddressor<MemberFunctionType> > > m_AllocateMemberFactory;

    private:

      // Copying is not supported
      Image &operator=( const Image & ); // Not implemented
      // For some reason, SWIG gets a little confused here, so don't let it see this code.
#ifndef SWIG

      /// We utilize the private implementation ( or PImple)
      /// programming idiom to modify the behavior of the simple image
      /// class based on the different image types.
      ///
      /// This class is designed to be utilize to have trivial copy,
      /// and assignment operators
      class PimpleImageBase
      {
      public:
        virtual ~PimpleImageBase( void ) {};

        virtual PixelIDValueType GetPixelIDValue(void) = 0;
        virtual unsigned int GetDimension( void ) = 0;

        virtual PimpleImageBase *Clone(void) const = 0;
        virtual itk::DataObject::Pointer GetDataBase( void ) = 0;
        virtual itk::DataObject::ConstPointer GetDataBase( void ) const = 0;

        virtual uint64_t GetWidth( void ) const { return this->GetSize( 0 ); }
        virtual uint64_t GetHeight( void ) const { return this->GetSize( 1 ); }
        virtual uint64_t GetDepth( void ) const { return this->GetSize( 2 ); }

        virtual uint64_t GetSize( unsigned int dimension ) const = 0;
        virtual std::string ToString() const = 0;

        virtual PixelContainer::Pointer GetPixelContainer() = 0;
      };

      // utilize std::auto_ptr to perform automatic deletion on deconstruction
      std::auto_ptr< PimpleImageBase > m_PimpleImage;

#endif
    };
  }
}


#endif
