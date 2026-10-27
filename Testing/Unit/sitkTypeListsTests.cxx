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
#include "SimpleITKTestHarness.h"
#include <sitkPixelIDTypeLists.h>
#include <itkImage.h>
#include <sitkDualMemberFunctionFactory.h>

#include <Ancillary/type_list2.h>

class TypeListTest : public ::testing::Test
{
public:
  TypeListTest() = default;
  ;
  struct CountPredicate
  {
    CountPredicate()
      : count(0)
    {}

    template <class TType>
    void
    operator()()
    {
      ++count;
    }

    template <class TType1, class TType2>
    void
    operator()()
    {
      ++count;
    }

    template <class TType>
    void
    operator()() const
    {
      ++count;
    }

    template <class TType1, class TType2>
    void
    operator()() const
    {
      ++count;
      std::cout << typeid(TType1).name() << " " << typeid(TType2).name() << std::endl;
    }

    mutable int count;
  };

  CountPredicate       pred;
  const CountPredicate constPred;
};


TEST_F(TypeListTest, typelist)
{
  using namespace typelist2;
  using t1 = typelist2::typelist<int, char>;

  static_assert(length<t1>::value == 2, "length check");
  static_assert(std::is_same<type_at<t1, 0>::type, int>::value, "idx");

  using t1t1 = typename append<t1, t1>::type;
  static_assert(length<t1t1>::value == 4, "append length check");

  using t11 = typename append<t1, int>::type;
  static_assert(length<t11>::value == 3, "append length check");

  using t12 = typename append<t1, double, float>::type;
  static_assert(length<t12>::value == 4, "append length check");

  using t1t1t1 = typename append<t1, t1, t1>::type;
  static_assert(length<t1t1t1>::value == 6, "append length check");

  using t1t1t1t1 = typename append<t1, t1, t1, t1>::type;
  static_assert(length<t1t1t1t1>::value == 8, "append length check");

  static_assert(index_of<t1, int>::value == 0, "OK");
  static_assert(index_of<t1, char>::value == 1, "OK");
  static_assert(index_of<t1, float>::value == -1, "OK");

  static_assert(has_type<t1, int>::value, "OK");
  static_assert(has_type<t1, char>::value, "OK");
  static_assert(has_type<t1, float>::value == false, "OK");
}


TEST_F(TypeListTest, typelist_visit)
{
  using t1 = typelist2::typelist<int, char, void>;

  typelist2::visit<t1> ListVisitor;
  ListVisitor(pred);
  ListVisitor(constPred);

  EXPECT_EQ(pred.count, 3);
  EXPECT_EQ(constPred.count, 3);
}


TEST_F(TypeListTest, typelist_dual_visit)
{
  using t1 = typelist2::typelist<int, char, short>;
  typelist2::dual_visit<t1, t1> DualVisitor;
  DualVisitor(pred);
  DualVisitor(constPred);

  EXPECT_EQ(pred.count, 9);
  EXPECT_EQ(constPred.count, 9);
}


TEST_F(TypeListTest, typelist_zip_visit)
{
  using t1 = typelist2::typelist<int, char, short>;
  using t2 = typelist2::typelist<float, double, long>;
  typelist2::zip_visit<t1, t2> ZipVisitor;
  ZipVisitor(pred);
  ZipVisitor(constPred);

  // Only the position-matched pairs are visited, not the 9 combinations.
  EXPECT_EQ(pred.count, 3);
  EXPECT_EQ(constPred.count, 3);
}


namespace
{
class DualFactoryProbe
{
public:
  using MemberFunctionType = int (DualFactoryProbe::*)();

  template <class TImageType1, class TImageType2>
  int
  DualExecuteInternal()
  {
    return 1;
  }
};
} // namespace


TEST(DualMemberFunctionFactory, RegisterMemberFunctionsZipped)
{
  namespace sitk = itk::simple;

  using Left = typelist2::typelist<sitk::BasicPixelID<float>, sitk::BasicPixelID<int8_t>>;
  using Right = typelist2::typelist<sitk::BasicPixelID<double>, sitk::BasicPixelID<int16_t>>;

  sitk::detail::DualMemberFunctionFactory<DualFactoryProbe::MemberFunctionType> factory;
  factory.RegisterMemberFunctionsZipped<Left, Right, 2>();

  DualFactoryProbe probe;
  EXPECT_TRUE(factory.HasMemberFunction(sitk::sitkFloat32, sitk::sitkFloat64, 2));
  EXPECT_TRUE(factory.HasMemberFunction(sitk::sitkInt8, sitk::sitkInt16, 2));
  EXPECT_EQ(1, factory.GetMemberFunction(sitk::sitkFloat32, sitk::sitkFloat64, 2, &probe)());

  // position-mismatched, same-type and other-dimension pairs are not registered
  EXPECT_FALSE(factory.HasMemberFunction(sitk::sitkFloat32, sitk::sitkInt16, 2));
  EXPECT_FALSE(factory.HasMemberFunction(sitk::sitkFloat32, sitk::sitkFloat32, 2));
  EXPECT_FALSE(factory.HasMemberFunction(sitk::sitkFloat32, sitk::sitkFloat64, 3));
  EXPECT_THROW(factory.GetMemberFunction(sitk::sitkFloat32, sitk::sitkInt16, 2, &probe), itk::simple::GenericException);
}


TEST(DualMemberFunctionFactory, RegisterMemberFunctionsSameTypeDimensionRange)
{
  namespace sitk = itk::simple;

  using List = typelist2::typelist<sitk::BasicPixelID<float>, sitk::BasicPixelID<int8_t>>;

  sitk::detail::DualMemberFunctionFactory<DualFactoryProbe::MemberFunctionType> factory;
  factory.RegisterMemberFunctions<List, 2, 3>();

  for (unsigned int dim : { 2u, 3u })
  {
    EXPECT_TRUE(factory.HasMemberFunction(sitk::sitkFloat32, sitk::sitkFloat32, dim));
    EXPECT_TRUE(factory.HasMemberFunction(sitk::sitkInt8, sitk::sitkInt8, dim));
    EXPECT_FALSE(factory.HasMemberFunction(sitk::sitkFloat32, sitk::sitkInt8, dim));
  }
}
