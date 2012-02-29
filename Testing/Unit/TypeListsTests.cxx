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
#include "SimpleITKTestHarness.h"
#include <sitkPixelIDTypeLists.h>

class TypeListTest
  : public ::testing::Test
{
public:
  TypeListTest() {};
  struct CountPredicate
  {
    CountPredicate( void ) : count(0) {}

    template<class TType>
    void operator()( void )
      {
        ++count;
      }

    template<class TType1, class TType2>
    void operator()( void )
      {
        ++count;
      }

    template<class TType>
    void operator()( void ) const
      {
        ++count;
      }

    template<class TType1, class TType2>
    void operator()( void ) const
      {
        ++count;
        std::cout << typeid(TType1).name() << " " << typeid( TType2 ).name() << std::endl;
      }

    mutable int count;
  };

  CountPredicate pred;
  const CountPredicate constPred;
};


TEST_F(TypeListTest, Visit) {

  typedef typelist::MakeTypeList<int, char, void>::Type MyTypeList;

  typelist::Visit<MyTypeList> ListVisitor;
  ListVisitor( pred );
  ListVisitor( constPred );

  EXPECT_EQ( pred.count, 3 );
  EXPECT_EQ( constPred.count, 3 );

}

TEST_F(TypeListTest, DualVisit) {

  typedef typelist::MakeTypeList<int, char, short>::Type MyTypeList;

  typelist::DualVisit<MyTypeList,MyTypeList> ListVisitor;
  ListVisitor( pred );
  ListVisitor( constPred );

  EXPECT_EQ( pred.count, 9 );
  EXPECT_EQ( constPred.count, 9 );

}
