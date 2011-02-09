#ifndef __sitkImage_h
#define __sitkImage_h

#include "sitkMacro.h"

#include "sitkDetail.h"
#include "sitkPixelIDTokens.h"
#include "sitkPixelContainer.h"
#include "sitkNonCopyable.h"
#include "itkDataObject.h"

#include <memory>

namespace itk
{
namespace simple
{

  // This is the foward declaration of a class used internally to the
  // Image class, but the actually interface is not exposed to simple
  // ITK. A pointer to the implementation is used as per the pimple
  // idiom.
  class PimpleImageBase;

  /** \class Image
   * \brief The main Image class for SimpleITK
   */
  class Image
    : public LightObject,
      protected NonCopyable
  {
  public:
    typedef Image              Self;
    typedef SmartPointer<Self> Pointer;

    virtual ~Image( );

    Image( uint64_t Width, uint64_t Height, PixelIDValueEnum ValueEnum );
    Image( uint64_t Width, uint64_t Height, uint64_t Depth, PixelIDValueEnum ValueEnum );

    template <typename TImageType>
    explicit Image( itk::SmartPointer<TImageType> image )
      : m_PimpleImage( NULL )
      { this->InternalInitialization( image.GetPointer() ); }

    template <typename TImageType>
    explicit Image( TImageType* image )
      : m_PimpleImage( NULL )
      { this->InternalInitialization( image ); }

    itk::DataObject::Pointer GetImageBase( void );
    itk::DataObject::ConstPointer GetImageBase( void ) const;

    // could return -1 if in valid
    PixelIDValueType GetPixelIDValue( void ) const;

    unsigned int GetDimension( void ) const;

    /** Get/Set the Origin */
    std::vector< double > GetOrigin( void );
    void SetOrigin( std::vector< double > );

    /** Get the Spacing */
    std::vector< double > GetSpacing( void );
    void SetSpacing( std::vector< double > );

    /** Transform index to physical point */
    std::vector< double > TransformIndexToPhysicalPoint( std::vector< unsigned int > );

    /** Transform physical point to index */
    std::vector< unsigned int > TransformPhysicalPointToIndex( std::vector< double > );

    uint64_t GetHeight( void );
    uint64_t GetWidth( void );
    uint64_t GetDepth( void );


    std::string GetPixelIDTypeAsString( void ) const;
    std::string ToString( void );

    typedef AllPixelIDTypeList PixelIDTypeList;
    typedef void (Self::*MemberFunctionType)( uint64_t Width, uint64_t Height, uint64_t Depth );

    PixelContainer::Pointer GetPixelContainer();

    /** Method called my certain constructors to convert ITK images
     * into simpleITK ones.
     */
    template <typename TImageType>
    void InternalInitialization( TImageType * );


  protected:

    /** \brief Methods called by the constructor to allocate and initialize
     * an image.
     *
     * This method internally utlizes the member function factory to
     * dispatch to methods instantiated on the image of the pixel ID
     */
    void Allocate ( uint64_t Width, uint64_t Height, uint64_t Depth, PixelIDValueEnum ValueEnum );

    /** \brief Dispatched methods for allocating images
     *
     * The enable if idiom is used here to enable different methods
     * for different pixel/image types.
     *
     * @{
     */
    template<class TImageType>
    typename EnableIf<IsBasic<TImageType>::Value>::Type
    AllocateInternal ( uint64_t Width, uint64_t Height, uint64_t Depth );

    template<class TImageType>
    typename EnableIf<IsVector<TImageType>::Value>::Type
    AllocateInternal ( uint64_t Width, uint64_t Height, uint64_t Depth );

    template<class TImageType>
    typename EnableIf<IsLabel<TImageType>::Value>::Type
    AllocateInternal ( uint64_t Width, uint64_t Height, uint64_t Depth );
    /**@}*/

    typedef detail::AllocateMemberFunctionAddressor<MemberFunctionType> AllocateAddressor;
    friend struct detail::AllocateMemberFunctionAddressor<MemberFunctionType>;


    /** \brief Do not call this method
     *
     * The purpose of this methods is to implicitly instantiate the
     * templated constructors of this class.
     */
    void __ImplicitInstantiate( void );

  private:

    PimpleImageBase *m_PimpleImage;
  };

}
}

#endif
