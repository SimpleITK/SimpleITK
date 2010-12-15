#ifndef _sitkPixelIDTokens_h
#define _sitkPixelIDTokens_h

#include "sitkPixelIDValues.h"

namespace itk
{
namespace simple
{


template <bool TValue>
struct InstantiatedToken {};

struct BasicPixelToken
  : InstantiatedToken<true>
{};

struct VectorPixelToken
  : InstantiatedToken<true>
{};

struct LabelPixelToken
  : InstantiatedToken<true>
{};

template <typename TPixelIDType>
struct PixelIDToToken
{
  typedef InstantiatedToken< (int)PixelIDToPixelIDValue<TPixelIDType>::Result != (int)sitkUnknown > Token;
};


template <typename TImageType>
struct ImageTypeToToken
{
  typedef typename PixelIDToToken< typename ImageTypeToPixelID<TImageType>::PixelIDType >::Token Token;
};


}
}

#endif // _sitkPixelIDTokens_h
