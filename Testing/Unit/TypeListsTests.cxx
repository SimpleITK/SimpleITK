#include "SimpleITKTestHarness.h"

#include <SimpleITK.h>

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
