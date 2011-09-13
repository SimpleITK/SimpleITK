#ifndef __sitkImage_h
#define __sitkImage_h

#include "sitkMacro.h"
#include "sitkConfigure.h"
#include "sitkDetail.h"
#include "sitkPixelIDTokens.h"
#include "sitkEnableIf.h"


#ifndef SWIG
#ifdef SITK_HAS_STLTR1_TR1_TYPE_TRAITS
#include <tr1/type_traits>
#elif defined SITK_HAS_STLTR1_TYPE_TRAITS
#include <type_traits>
#else
#error "No system tr1 type traits available"
#endif
#endif

#include <vector>
#include <memory>
#include <stdint.h>

namespace itk
{

// Forward decalaration for pointer
class DataObject;

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
  {
  public:
    typedef Image              Self;

    virtual ~Image( );

    // copy constructor
    Image( const Image &img );
    Image& operator=( const Image &img );

    Image( unsigned int Width, unsigned int Height, PixelIDValueEnum ValueEnum );
    Image( unsigned int Width, unsigned int Height, unsigned int Depth, PixelIDValueEnum ValueEnum );

    template <typename TImageType>
    explicit Image( itk::SmartPointer<TImageType> image )
      : m_PimpleImage( NULL )
      {
        sitkStaticAssert( ImageTypeToPixelIDValue<TImageType>::Result != (int)sitkUnknown,
                          "invalid pixel type" );
        this->InternalInitialization<ImageTypeToPixelIDValue<TImageType>::Result, TImageType::ImageDimension>( image.GetPointer() );
      }

    template <typename TImageType>
    explicit Image( TImageType* image )
      : m_PimpleImage( NULL )
      {
        sitkStaticAssert( ImageTypeToPixelIDValue<TImageType>::Result != (int)sitkUnknown,
                          "invalid pixel type" );
        this->InternalInitialization<ImageTypeToPixelIDValue<TImageType>::Result, TImageType::ImageDimension>( image );
      }

    /** Get access to internal ITK data object.
     *
     * The return value should imediately be assigned to as
     * itk::SmartPointer.
     *
     * In many cases the value may need to be dynamically casted to
     * the the actual image type. The GetPixelIDValue() method should
     * return an PixelID which identifies the image type which the
     * DataObject points to.
     *
     * @{
     */
    itk::DataObject* GetITKBase( void );
    const itk::DataObject* GetITKBase( void ) const;
    /**@}*/

    // could return -1 if in valid

    PixelIDValueType GetPixelIDValue( void ) const;
    unsigned int GetDimension( void ) const;

    /** \brief Get the number of components for each pixel
     *
     * For scalar images this methods returns 1. For vector images the
     * number of components for each pixel is returned.
     */
    unsigned int GetNumberOfComponentsPerPixel( void ) const;

    /** Get/Set the Origin */
    std::vector< double > GetOrigin( void ) const;
    void SetOrigin( const std::vector< double > &origin );

    /** Get the Spacing */
    std::vector< double > GetSpacing( void ) const;
    void SetSpacing( const std::vector< double > &spacing );

    /** \brief Set/Get the Direction
     *
     * Internally, the Direction is represented by a matrix 2x2 for a
     * 2D and and 3x3 for a 3D image. The matrix is passed as a 1D
     * array in row-major form.
     */
    std::vector< double > GetDirection() const;
    void SetDirection ( const std::vector< double > &direction );

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

    /** \brief Get the value of a pixel
     *
     * Returns the value of a pixel for the given index. The index
     * follows standard SimpleITK conventions for it's length. The
     * correct method must be called for the underlying Image type,
     * otherwise an exception will be thrown.
     *
     * \param idx the zero based index into the image. It's length
     * must be at least the value of GetDimension(), additional
     * elements will be ignored. Boundary checking is performed on
     * idx, if it is out of bounds an exception will be thrown.
     *
     * \sa Image::GetPixelIDValue
     * @{
     */
    int8_t   GetPixelAsInt8( const std::vector<uint32_t> &idx) const;
    uint8_t  GetPixelAsUInt8( const std::vector<uint32_t> &idx) const;
    int16_t  GetPixelAsInt16( const std::vector<uint32_t> &idx ) const;
    uint16_t GetPixelAsUInt16( const std::vector<uint32_t> &idx ) const;
    int32_t  GetPixelAsInt32( const std::vector<uint32_t> &idx ) const;
    uint32_t GetPixelAsUInt32( const std::vector<uint32_t> &idx ) const;
    int32_t  GetPixelAsInt64( const std::vector<uint32_t> &idx ) const;
    uint32_t GetPixelAsUInt64( const std::vector<uint32_t> &idx ) const;
    float    GetPixelAsFloat( const std::vector<uint32_t> &idx ) const;
    double   GetPixelAsDouble(  const std::vector<uint32_t> &idx ) const;
    /* @} */

    /** \brief Set the value of a pixel
     *
     * Set the value of a pixel at the provided index. The index
     * follows standard SimpleITK conventions for it's length. The
     * correct method must be called which should match the underlying
     * image type, otherwise an exception will be thrown.
     *
     * \param idx the zero based index into the image. It's length
     * must be at least the value of GetDimension(), additional
     * elements will be ignored. Boundary checking is performed on
     * idx, if it is out of bounds an exception will be thrown.
     * \param v value to set the pixel to
     *
     * \sa Image::GetPixelIDValue
     * @{
     */
    void SetPixelAsInt8( const std::vector<uint32_t> &idx, int8_t v );
    void SetPixelAsUInt8( const std::vector<uint32_t> &idx, uint8_t v );
    void SetPixelAsInt16( const std::vector<uint32_t> &idx, int16_t v );
    void SetPixelAsUInt16( const std::vector<uint32_t> &idx, uint16_t v );
    void SetPixelAsInt32( const std::vector<uint32_t> &idx, int32_t v );
    void SetPixelAsUInt32( const std::vector<uint32_t> &idx, uint32_t v );
    void SetPixelAsInt64( const std::vector<uint32_t> &idx, int64_t v );
    void SetPixelAsUInt64( const std::vector<uint32_t> &idx, uint64_t v );
    void SetPixelAsFloat( const std::vector<uint32_t> &idx, float v );
    void SetPixelAsDouble( const std::vector<uint32_t> &idx, double v );
    /** @} */

   /** \brief Get a pointer to the image buffer
     * \warning this is dangerous
     *
     * The size of the buffer is the number of components*Xsize*Ysize
     * and then Zsize of a 3D image. The buffer should be accessed as
     * a 1-D array. For example a 3D image buffer should be accessed:
     * \code
     * uint8_t *buffer = img->GetBufferAsUInt8();
     * buffer[c + numComponents*(x+ xSize* (y*+ySize*z))]
     * \endcode
     *
     * The pointer to the buffer is not referenced
     * counted. Additionally, while this image is made unique before
     * returnign the pointer, additional copying and usage may
     * introduce unexpected aliasing.
     *
     * \sa Image::GetPixelIDValue
     * @{
     */
    int8_t   *GetBufferAsInt8( );
    uint8_t  *GetBufferAsUInt8( );
    int16_t  *GetBufferAsInt16( );
    uint16_t *GetBufferAsUInt16( );
    int32_t  *GetBufferAsInt32( );
    uint32_t *GetBufferAsUInt32( );
    int64_t  *GetBufferAsInt64( );
    uint64_t *GetBufferAsUInt64( );
    float    *GetBufferAsFloat( );
    double   *GetBufferAsDouble( );
    /* @} */


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

    void MakeUniqueForWrite( void );

    /** Method called by certain constructors to convert ITK images
     * into simpleITK ones.
     *
     * This is the single method which needs to be explicitly
     * instantiated to separate the internal ITK and Pimple image from
     * the external SimpleITK interface. Template parameters have been
     * choosen carefully to flexibly enable this.
     */
    template <int VPixelIDValue, unsigned int VImageDimension>
    void InternalInitialization( typename PixelIDToImageType<typename typelist::TypeAt<InstantiatedPixelIDTypeList,
                                                                                       VPixelIDValue>::Result,
                                                             VImageDimension>::ImageType *i );

  private:

    /** Dispatched from the InternalInitialization method. The enable
     * if idom is used here for method overloading. The second method
     * is for non-instantiated image, which turn into a void pointer
     * for the paramter. However, this second method should never be
     * executed.
     * @{
     */
    template<int VPixelIDValue, typename TImageType>
    typename DisableIf<std::tr1::is_same<TImageType, void>::value>::Type
    ConditionalInternalInitialization( TImageType *i);

    template<int VPixelIDValue, typename TImageType>
    typename EnableIf<std::tr1::is_same<TImageType, void>::value>::Type
    ConditionalInternalInitialization( TImageType *) { assert( false ); }
     /**@}*/

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
