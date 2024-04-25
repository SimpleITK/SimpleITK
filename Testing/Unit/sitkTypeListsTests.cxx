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
