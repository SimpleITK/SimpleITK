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

#ifndef sitkMetaDataDictionaryCustomCast_hxx
#define sitkMetaDataDictionaryCustomCast_hxx
#include <vector>
#include <string>
#include <sstream>
#include <itkMetaDataDictionary.h>
#include <itkMetaDataObject.h>


namespace itk {
namespace simple {


//
// Custom Casts
//
namespace {
template<typename FilterType>
struct GetMetaDataKeysCustomCast
{
  static std::vector<std::string> CustomCast( const FilterType *f, int i)
    {
      const typename FilterType::DictionaryArrayType &mda = *f->GetMetaDataDictionaryArray();
      return mda.at(i)->GetKeys();
    }
};

template<typename FilterType>
struct HasMetaDataKeyCustomCast
{
  static bool CustomCast( const FilterType *f, int i, const std::string &k)
    {
      const typename FilterType::DictionaryArrayType &mda = *f->GetMetaDataDictionaryArray();
      return mda.at(i)->HasKey(k);
    }
};

struct GetMetaDataDictionaryCustomCast
{
  static std::string CustomCast( const MetaDataDictionary *md, const std::string &k)
    {
      std::string value;
      if (ExposeMetaData(*md, k, value))
        {
        return value;
        }

      std::ostringstream ss;
      md->Get(k)->Print(ss);
      return ss.str();
    }
};

template<typename FilterType>
struct GetMetaDataCustomCast
{
  static std::string CustomCast( const FilterType *f, int i, const std::string &k)
    {
      const typename FilterType::DictionaryArrayType &mda = *f->GetMetaDataDictionaryArray();

      return GetMetaDataDictionaryCustomCast::CustomCast(mda.at(i), k);

    }
};

}
}
}

#endif
