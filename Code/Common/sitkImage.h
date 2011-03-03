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
    : protected NonCopyable
  {
  public:
    typedef Image              Self;

    virtual ~Image( );

    Image( unsigned int Width, unsigned int Height, PixelIDValueEnum ValueEnum );
    Image( unsigned int Width, unsigned int Height, unsigned int Depth, PixelIDValueEnum ValueEnum );

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
    std::vector< double > GetOrigin( void ) const;
    void SetOrigin( const std::vector< double > &origin );

    /** Get the Spacing */
    std::vector< double > GetSpacing( void ) const;
    void SetSpacing( const std::vector< double > &spacing );

    /** Transform index to physical point */
    std::vector< double > TransformIndexToPhysicalPoint( const std::vector< int64_t > &index ) const;

    /** Transform physical point to index */
    std::vector< int64_t > TransformPhysicalPointToIndex( const std::vector< double >& point ) const;

    std::vector< unsigned int > GetSize( void ) const;

    unsigned int GetHeight( void ) const;
    unsigned int GetWidth( void ) const;
    unsigned int GetDepth( void ) const;


    std::string GetPixelIDTypeAsString( void ) const;
    std::string ToString( void ) const;
    ::itk::simple::PixelContainer* GetPixelContainer();

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
    void Allocate ( unsigned int Width, unsigned int Height, unsigned int Depth, PixelIDValueEnum ValueEnum );

    /** \brief Dispatched methods for allocating images
     *
     * The enable if idiom is used here to enable different methods
     * for different pixel/image types.
     *
     * @{
     */
    template<class TImageType>
    typename EnableIf<IsBasic<TImageType>::Value>::Type
    AllocateInternal ( unsigned int Width, unsigned int Height, unsigned int Depth );

    template<class TImageType>
    typename EnableIf<IsVector<TImageType>::Value>::Type
    AllocateInternal ( unsigned int Width, unsigned int Height, unsigned int Depth );

    template<class TImageType>
    typename EnableIf<IsLabel<TImageType>::Value>::Type
    AllocateInternal ( unsigned int Width, unsigned int Height, unsigned int Depth );
    /**@}*/


    /** \brief Do not call this method
     *
     * The purpose of this methods is to implicitly instantiate the
     * templated constructors of this class.
     */
    void __ImplicitInstantiate( void );

  private:


// SWIG does not appear to process private classes correctly
#ifndef SWIG

    /** An addressor of AllocateInternal to be utilized with
     * registering member functions with the factory.
     */
    template < class TMemberFunctionPointer >
    struct AllocateMemberFunctionAddressor
    {
      typedef typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType ObjectType;

      template< typename TImageType >
      TMemberFunctionPointer operator() ( void ) const
      {
        return &ObjectType::template AllocateInternal< TImageType >;
      }
    };

#endif
    PimpleImageBase *m_PimpleImage;
  };

}
}

#endif
