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
#ifndef sitkImage_h
#define sitkImage_h

#include "sitkCommon.h"
#include "sitkTemplateFunctions.h"
#include "sitkDetail.h"
#include "sitkPixelIDTokens.h"
#include "sitkEnableIf.h"

#include "nsstd/type_traits.h"
#include "nsstd/auto_ptr.h"

#include <vector>
#include <memory>

namespace itk
{

// Forward decalaration for pointer
class DataObject;

template<class T>
class SmartPointer;

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
  class SITKCommon_EXPORT Image
  {
  public:
    typedef Image              Self;

    virtual ~Image( );

    /** \brief Default constructor, creates an image of size 0 */
    Image( void );

    // copy constructor
    Image( const Image &img );
    Image& operator=( const Image &img );

    /** \brief Constructors for 2D, 3D an optionally 4D images where
     * pixel type and number of components can be specified.
     *
     * If the pixel type is a scalar or a label pixel type, then the
     * number of components must be specified as 0 or 1.
     *
     * If the pixel type is a vector pixel type, then the number of
     * components defaults to the image dimension, unless the
     * numberOfComponents is explicitly specified.
     *
     * Unlike the standard convention for Dimensional Vectors the size
     * parameter must be the exact dimension requesting. That is, it must be of
     * length 2 of a 2D image, 3 for a 3D image and 4 for a 4D image.
     * @{
     */
    Image( unsigned int width, unsigned int height, PixelIDValueEnum valueEnum  );
    Image( unsigned int width, unsigned int height, unsigned int depth, PixelIDValueEnum valueEnum );
    Image( const std::vector< unsigned int > &size, PixelIDValueEnum valueEnum, unsigned int numberOfComponents = 0 );
    /**@}*/


    /** \brief Construct an SimpleITK Image from an pointer to an ITK
     * image
     *
     * The SimpleITK image will add a reference to the underlying the
     * ITK image and hold a pointer to the image. If the image is
     * manipulated directly from the ITK interface, SimpleITK may be
     * unaware of it, and may cause complication related to aliasing
     * and SimpleITK copy on write policy.
     *
     * If simpleITK does not support the image type, a compile-time
     * error or assertion will fail.
     *
     * The ITK image must be fully buffered, and must have a zero
     * starting index for the Buffered/Largest regions.
     * @{
     */
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
    /**@}*/

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
    PixelIDValueEnum GetPixelID( void ) const;
    PixelIDValueType GetPixelIDValue( void ) const;

    unsigned int GetDimension( void ) const;

    /** \brief Get the number of components for each pixel
     *
     * For scalar images this methods returns 1. For vector images the
     * number of components for each pixel is returned.
     */
    unsigned int GetNumberOfComponentsPerPixel( void ) const;

    /** \brief Get the number of pixels in the image
     *
     * To Calculate the total number of values stored continuously for
     * the image's buffer, the NumberOfPixels should be multiplied by
     * NumberOfComponentsPerPixel in order to account for multiple
     * component images.
     *
     */
    uint64_t GetNumberOfPixels( void ) const;

    /** Get/Set the Origin
     * @{
     */
    std::vector< double > GetOrigin( void ) const;
    void SetOrigin( const std::vector< double > &origin );
    /** @} */

    /** Get/Set the Spacing
     * @{
     */
    std::vector< double > GetSpacing( void ) const;
    void SetSpacing( const std::vector< double > &spacing );
    /** @} */

    /** \brief Set/Get the Direction
     *
     * Internally, the Direction is represented by a matrix 2x2 for a
     * 2D and and 3x3 for a 3D image. The matrix is passed as a 1D
     * array in row-major form.
     * @{
     */
    std::vector< double > GetDirection() const;
    void SetDirection ( const std::vector< double > &direction );
    /** @} */

    /** Transform index to physical point */
    std::vector< double > TransformIndexToPhysicalPoint( const std::vector< int64_t > &index ) const;

    /** Transform physical point to index */
    std::vector< int64_t > TransformPhysicalPointToIndex( const std::vector< double >& point ) const;

    /** Transform physical point to continuous index */
    std::vector< double > TransformPhysicalPointToContinuousIndex( const std::vector< double >& point ) const;

    /** Transform continuous index to physical point */
    std::vector< double > TransformContinuousIndexToPhysicalPoint( const std::vector< double > &index) const;

    std::vector< unsigned int > GetSize( void ) const;

    unsigned int GetHeight( void ) const;
    unsigned int GetWidth( void ) const;
    unsigned int GetDepth( void ) const;


    /** \brief Copy common meta-data from an image to this one.
     *
     * Copies the Origin, Spacing, and Direction from the source image
     * to this image. The meta-data dictionary is \b not copied.
     *
     * It is required for the source Image's dimension and size to
     * match, this image's attributes, otherwise an exception will be
     * generated.
     *
     */
    void CopyInformation( const Image &srcImage );

    /** \brief get a vector of keys in from the meta-data dictionary
     *
     * Returns a vector of keys to the key/value entries in the
     * image's meta-data dictionary. Iterate through with these keys
     * to get the values.
     */
    std::vector<std::string> GetMetaDataKeys( void ) const;

    /** \brief Query the meta-data dictionary for the existence of a key.
     */
    bool HasMetaDataKey( const std::string &key ) const;

    /** \brief Get the value of a meta-data dictionary entry as a string.
     *
     * If the key is not in the dictionary then an exception is
     * thrown.
     *
     * string types in the dictionary are returned as their native
     * strings. Other types are printed to string before returning.
     */
    std::string GetMetaData( const std::string &key ) const;

    /** \brief Set an entry in the meta-data dictionary.
     *
     * Replaces or creates an entry in the image's meta-data dictionary.
     */
    void SetMetaData( const std::string &key, const std::string &value);

    /** \brief Remove an entry from the meta-data dictionary.
     *
     * Returns true, when the value exists in the dictionary and is
     * removed, false otherwise.
     */
    bool EraseMetaData( const std::string &key );

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
    int64_t  GetPixelAsInt64( const std::vector<uint32_t> &idx ) const;
    uint64_t GetPixelAsUInt64( const std::vector<uint32_t> &idx ) const;
    float    GetPixelAsFloat( const std::vector<uint32_t> &idx ) const;
    double   GetPixelAsDouble(  const std::vector<uint32_t> &idx ) const;

    std::vector<int8_t>   GetPixelAsVectorInt8( const std::vector<uint32_t> &idx) const;
    std::vector<uint8_t>  GetPixelAsVectorUInt8( const std::vector<uint32_t> &idx) const;
    std::vector<int16_t> GetPixelAsVectorInt16( const std::vector<uint32_t> &idx ) const;
    std::vector<uint16_t> GetPixelAsVectorUInt16( const std::vector<uint32_t> &idx ) const;
    std::vector<int32_t>  GetPixelAsVectorInt32( const std::vector<uint32_t> &idx ) const;
    std::vector<uint32_t> GetPixelAsVectorUInt32( const std::vector<uint32_t> &idx ) const;
    std::vector<int64_t>  GetPixelAsVectorInt64( const std::vector<uint32_t> &idx ) const;
    std::vector<uint64_t> GetPixelAsVectorUInt64( const std::vector<uint32_t> &idx ) const;
    std::vector<float>    GetPixelAsVectorFloat32( const std::vector<uint32_t> &idx ) const;
    std::vector<double>   GetPixelAsVectorFloat64( const std::vector<uint32_t> &idx ) const;

    std::complex<float>  GetPixelAsComplexFloat32( const std::vector<uint32_t> &idx ) const;
    std::complex<double> GetPixelAsComplexFloat64( const std::vector<uint32_t> &idx ) const;
    /** @} */

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

    void SetPixelAsVectorInt8( const std::vector<uint32_t> &idx, const std::vector<int8_t> &v );
    void SetPixelAsVectorUInt8( const std::vector<uint32_t> &idx, const std::vector<uint8_t> &v );
    void SetPixelAsVectorInt16( const std::vector<uint32_t> &idx, const std::vector<int16_t> &v );
    void SetPixelAsVectorUInt16( const std::vector<uint32_t> &idx, const std::vector<uint16_t> &v );
    void SetPixelAsVectorInt32( const std::vector<uint32_t> &idx, const std::vector<int32_t> &v );
    void SetPixelAsVectorUInt32( const std::vector<uint32_t> &idx, const std::vector<uint32_t> &v );
    void SetPixelAsVectorInt64( const std::vector<uint32_t> &idx, const std::vector<int64_t> &v );
    void SetPixelAsVectorUInt64( const std::vector<uint32_t> &idx, const std::vector<uint64_t> &v );
    void SetPixelAsVectorFloat32( const std::vector<uint32_t> &idx, const std::vector<float> &v );
    void SetPixelAsVectorFloat64( const std::vector<uint32_t> &idx, const std::vector<double> &v );

    void SetPixelAsComplexFloat32( const std::vector<uint32_t> &idx, const std::complex<float> v );
    void SetPixelAsComplexFloat64( const std::vector<uint32_t> &idx, const std::complex<double> v );

    /** @} */

   /** \brief Get a pointer to the image buffer
     * \warning this is dangerous
     *
     * The size of the buffer is the number of components*Xsize*Ysize
     * and then Zsize of a 3D image. The buffer should be accessed as
     * a 1-D array. For example a 3D image buffer should be accessed:
     * \code
     * uint8_t *buffer = img->GetBufferAsUInt8();
     * buffer[c + numComponents*(x+xSize*(y+ySize*z))]
     * \endcode
     *
     * The pointer to the buffer is not referenced
     * counted. Additionally, while this image is made unique before
     * returnign the pointer, additional copying and usage may
     * introduce unexpected aliasing.
     *
     * The correct method for the current pixel type of the image must
     * be called or else an exception will be generated. For vector
     * pixel types the type of the component of the vector must be called.
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

    const int8_t   *GetBufferAsInt8( ) const;
    const uint8_t  *GetBufferAsUInt8( ) const;
    const int16_t  *GetBufferAsInt16( ) const;
    const uint16_t *GetBufferAsUInt16( ) const;
    const int32_t  *GetBufferAsInt32( ) const;
    const uint32_t *GetBufferAsUInt32( ) const;
    const int64_t  *GetBufferAsInt64( ) const;
    const uint64_t *GetBufferAsUInt64( ) const;
    const float    *GetBufferAsFloat( ) const;
    const double   *GetBufferAsDouble( ) const;
    /** @} */


    /** \brief Performs actually coping if needed to make object unique.
     *
     * The Image class by default performs lazy coping and
     * assignment. This method make sure that coping actually happens
     * to the itk::Image pointed to is only pointed to by this object.
     */
    void MakeUnique( void );

  protected:

    /** \brief Methods called by the constructor to allocate and initialize
     * an image.
     *
     * This method internally utlizes the member function factory to
     * dispatch to methods instantiated on the image of the pixel ID
     */
    void Allocate ( unsigned int width, unsigned int height, unsigned int depth, unsigned int dim4, PixelIDValueEnum valueEnum, unsigned int numberOfComponents );

    /** \brief Dispatched methods for allocating images
     *
     * The enable if idiom is used here to enable different methods
     * for different pixel/image types.
     *
     * @{
     */
    template<class TImageType>
    typename EnableIf<IsBasic<TImageType>::Value>::Type
    AllocateInternal ( unsigned int width, unsigned int height, unsigned int depth, unsigned int dim4, unsigned int numberOfComponents );

    template<class TImageType>
    typename EnableIf<IsVector<TImageType>::Value>::Type
    AllocateInternal ( unsigned int width, unsigned int height, unsigned int depth, unsigned int dim4, unsigned int numberOfComponents );

    template<class TImageType>
    typename EnableIf<IsLabel<TImageType>::Value>::Type
    AllocateInternal ( unsigned int width, unsigned int height, unsigned int depth, unsigned int dim4, unsigned int numberOfComponents );
    /**@}*/


  private:

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

    /** Dispatched from the InternalInitialization method. The enable
     * if idiom is used here for method overloading. The second method
     * is for non-instantiated image, which turn into a void pointer
     * for the paramter. However, this second method should never be
     * executed.
     * @{
     */
    template<int VPixelIDValue, typename TImageType>
    typename DisableIf<nsstd::is_same<TImageType, void>::value>::Type
    ConditionalInternalInitialization( TImageType *i);

    template<int VPixelIDValue, typename TImageType>
    typename EnableIf<nsstd::is_same<TImageType, void>::value>::Type
    ConditionalInternalInitialization( TImageType *) { assert( false ); }
     /**@}*/

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

    PimpleImageBase *m_PimpleImage;
  };

}
}

#endif
