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
#ifndef sitkVectorArithmeticFunctors_hxx
#define sitkVectorArithmeticFunctors_hxx

#include "itkVariableLengthVector.h"

#include <cstddef>
#include <type_traits>
#include <vector>

namespace itk::simple
{

namespace Functor
{

namespace Detail
{

template <typename TPixel>
struct IsVectorPixel : std::false_type
{};

template <typename TComponent>
struct IsVectorPixel<itk::VariableLengthVector<TComponent>> : std::true_type
{};

template <typename TPixel>
struct ComponentOf
{
  using Type = TPixel;
};

template <typename TComponent>
struct ComponentOf<itk::VariableLengthVector<TComponent>>
{
  using Type = TComponent;
};

/** Component \c i of a vector pixel, or the value itself for a scalar pixel, which is
 * broadcast across all the components of the other operand. */
template <typename TComponent>
inline const TComponent &
GetComponent(const itk::VariableLengthVector<TComponent> & pixel, unsigned int i)
{
  return pixel[i];
}

template <typename TPixel>
inline const TPixel &
GetComponent(const TPixel & pixel, unsigned int)
{
  return pixel;
}

template <typename TInput1, typename TInput2>
inline unsigned int
GetNumberOfComponents(const TInput1 & input1, const TInput2 & input2)
{
  if constexpr (IsVectorPixel<TInput1>::value)
  {
    return input1.Size();
  }
  else
  {
    return input2.Size();
  }
}

/** Per thread storage for the components of one output pixel.
 *
 * The functor returns a non-owning vector referencing this storage, because ITK
 * copies the returned pixel into the output image. This avoids a heap allocation
 * for every pixel.
 */
template <typename TComponent>
inline TComponent *
GetScratch(std::size_t size)
{
  // Trivially constructed and destroyed, so the common path has no guard or cleanup code.
  thread_local TComponent * data = nullptr;
  thread_local std::size_t  capacity = 0;
  if (capacity < size)
  {
    // Only registered for destruction once memory is actually needed.
    thread_local std::vector<TComponent> storage;
    storage.resize(size);
    data = storage.data();
    capacity = size;
  }
  return data;
}

struct AddOperator
{
  template <typename TInput1, typename TInput2>
  static constexpr auto
  Apply(const TInput1 & a, const TInput2 & b)
  {
    return a + b;
  }
};

struct SubtractOperator
{
  template <typename TInput1, typename TInput2>
  static constexpr auto
  Apply(const TInput1 & a, const TInput2 & b)
  {
    return a - b;
  }
};

struct MultiplyOperator
{
  template <typename TInput1, typename TInput2>
  static constexpr auto
  Apply(const TInput1 & a, const TInput2 & b)
  {
    return a * b;
  }
};

} // namespace Detail


/** Applies an arithmetic operator to a pair of pixels.
 *
 * Each of the inputs may be a scalar or a vector pixel (itk::VariableLengthVector). Vector pixels
 * are processed per component, and a scalar is broadcast across the components of a vector. When
 * the output is a vector the result has the number of components of the vector input, which the
 * caller must ensure matches if both are vectors. For scalar pixels the result is
 * \c static_cast<TOutput>(Operator(a, b)), the same as the ITK functor.
 *
 * Instances are used concurrently by multiple threads.
 */
template <typename TOperator, typename TInput1, typename TInput2, typename TOutput>
class ArithmeticOperation
{
public:
  bool
  operator==(const ArithmeticOperation &) const
  {
    return true;
  }

  bool
  operator!=(const ArithmeticOperation &) const
  {
    return false;
  }

  inline TOutput
  operator()(const TInput1 & a, const TInput2 & b) const
  {
    if constexpr (Detail::IsVectorPixel<TOutput>::value)
    {
      using ComponentType = typename Detail::ComponentOf<TOutput>::Type;

      const unsigned int numberOfComponents = Detail::GetNumberOfComponents(a, b);
      ComponentType *    result = Detail::GetScratch<ComponentType>(numberOfComponents);
      for (unsigned int i = 0; i < numberOfComponents; ++i)
      {
        result[i] =
          static_cast<ComponentType>(TOperator::Apply(Detail::GetComponent(a, i), Detail::GetComponent(b, i)));
      }
      return TOutput(result, numberOfComponents, false);
    }
    else
    {
      return static_cast<TOutput>(TOperator::Apply(a, b));
    }
  }
};

/** a + b */
template <typename TInput1, typename TInput2, typename TOutput>
using Add = ArithmeticOperation<Detail::AddOperator, TInput1, TInput2, TOutput>;

/** a - b */
template <typename TInput1, typename TInput2, typename TOutput>
using Subtract = ArithmeticOperation<Detail::SubtractOperator, TInput1, TInput2, TOutput>;

/** a * b */
template <typename TInput1, typename TInput2, typename TOutput>
using Multiply = ArithmeticOperation<Detail::MultiplyOperator, TInput1, TInput2, TOutput>;

} // namespace Functor
} // namespace itk::simple

#endif
