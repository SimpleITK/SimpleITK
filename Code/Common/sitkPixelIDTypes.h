#ifndef __sitkPixelIDTypes_h
#define __sitkPixelIDTypes_h


namespace itk
{

template <typename TPixelType, unsigned int VImageDimension> class Image;
template <typename TPixelType, unsigned int VImageDimension > class VectorImage;
template < typename TLabelObject > class LabelMap;
template < typename TLabelObject, unsigned int VImageDimension > class LabelObject;

namespace simple
{

/** This type is used as an identity for pixel of itk::Image type
 *
 * This is an empty type which is used for compile-time
 * meta-programming. It does not contain any information, an image
 * type can be converted to one of the PixelID types, and an PixelID
 * can be converted to a value. However, a run-time value can not be
 * converted to this compile time type.
 *
 * \sa PixelIDToImageType
 * \sa ImageTypeToPixelID
 * \sa ImageTypeToPixelIDValue
 * \sa PixelIDToPixelIDValue
 */
template <typename TPixelType>
struct BasicPixelID
{};


/** This type is used as an identity for pixel of itk::VectorImage type
 *
 * This is an empty type which is used for compile-time
 * meta-programming. It does not contain any information, an image
 * type can be converted to one of the PixelID types, and an PixelID
 * can be converted to a value. However, a run-time value can not be
 * converted to this compile time type.
 *
 * \sa PixelIDToImageType
 * \sa ImageTypeToPixelID
 * \sa ImageTypeToPixelIDValue
 * \sa PixelIDToPixelIDValue
 */
template <typename TPixelType>
struct VectorPixelID
{};


/** This type is used as an identity for pixel of itk::LabelMap type
 *
 * This is an empty type which is used for compile-time
 * meta-programming. It does not contain any information, an image
 * type can be converted to one of the PixelID types, and an PixelID
 * can be converted to a value. However, a run-time value can not be
 * converted to this compile time type.
 *
 * \sa PixelIDToImageType
 * \sa ImageTypeToPixelID
 * \sa ImageTypeToPixelIDValue
 * \sa PixelIDToPixelIDValue
 */
template <typename TPixelType>
struct LabelPixelID
{};

/** A meta-programming tool to query the "itk image type" if a PixelID
 * at compile type
 *
 * This structure contains one property,
 * PixelIDToImageType<T>::ImageType is the "itk image type" of the
 * pixel ID.
 *
 * \sa BasicPixelID
 * \sa VectorPixelID
 * \sa LabelPixelID
 * \sa ImageTypeToPixelIDValue
 *
 * @{ */
template <typename TPixelIDType, unsigned int VImageDimension> struct PixelIDToImageType;

template <typename TPixelType, unsigned int VImageDimension>
struct PixelIDToImageType< BasicPixelID<TPixelType> , VImageDimension >
{
  typedef itk::Image< TPixelType, VImageDimension > ImageType;
};

template <typename TVectorPixelType, unsigned int VImageDimension>
struct PixelIDToImageType< VectorPixelID< TVectorPixelType >, VImageDimension >
{
  typedef itk::VectorImage< TVectorPixelType, VImageDimension > ImageType;
};

template <typename TLabelType, unsigned int VImageDimension>
struct PixelIDToImageType< LabelPixelID< TLabelType >, VImageDimension >
{
  typedef itk::LabelMap< itk::LabelObject< TLabelType, VImageDimension > > ImageType;
};
/** @} */


/** A meta-programming tool to query the PixelID property of an "itk
 * image type" at compile type
 *
 * This structure contains one property,
 * ImageTypeToPixelID<T>::PixelIDType is the "itk image type" of the
 * pixel ID.
 *
 * \sa BasicPixelID
 * \sa VectorPixelID
 * \sa LabelPixelID
 * \sa ImageTypeToPixelIDValue
 *
 * @{ */
template <typename TImageType> struct ImageTypeToPixelID;

template <typename TPixelType, unsigned int VImageDimension>
struct ImageTypeToPixelID< itk::Image< TPixelType, VImageDimension> >
{
  typedef BasicPixelID<TPixelType > PixelIDType;
};

template <typename TPixelType, unsigned int VImageDimension>
struct ImageTypeToPixelID< itk::VectorImage< TPixelType, VImageDimension> >
{
  typedef VectorPixelID< TPixelType > PixelIDType;
};

template <typename TLabelType, unsigned int VImageDimension>
struct ImageTypeToPixelID< itk::LabelMap< itk::LabelObject< TLabelType, VImageDimension > > >
{
  typedef  LabelPixelID< TLabelType > PixelIDType;
};
/** @} */

}
}
#endif // _sitkPixelIDTypes_h
