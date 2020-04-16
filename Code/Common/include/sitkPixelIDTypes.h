/*=========================================================================
*
*  Copyright NumFOCUS
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
#ifndef sitkPixelIDTypes_h
#define sitkPixelIDTypes_h


namespace itk
{

template <unsigned int VImageDimension> class ImageBase;
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
  using ImageType = itk::Image< TPixelType, VImageDimension >;
};

template <typename TVectorPixelType, unsigned int VImageDimension>
struct PixelIDToImageType< VectorPixelID< TVectorPixelType >, VImageDimension >
{
  using ImageType = itk::VectorImage< TVectorPixelType, VImageDimension >;
};

template <typename TLabelType, unsigned int VImageDimension>
struct PixelIDToImageType< LabelPixelID< TLabelType >, VImageDimension >
{
  using ImageType = itk::LabelMap< itk::LabelObject< TLabelType, VImageDimension > >;
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
  using PixelIDType = BasicPixelID<TPixelType >;
};

template <typename TPixelType, unsigned int VImageDimension>
struct ImageTypeToPixelID< itk::VectorImage< TPixelType, VImageDimension> >
{
  using PixelIDType = VectorPixelID< TPixelType >;
};

template <typename TLabelType, unsigned int VImageDimension>
struct ImageTypeToPixelID< itk::LabelMap< itk::LabelObject< TLabelType, VImageDimension > > >
{
  using PixelIDType = LabelPixelID< TLabelType >;
};
/** @} */

}
}
#endif // _sitkPixelIDTypes_h
