#include "SimpleITKTestHarness.h"
#include <sitkPixelIDTypeLists.h>

class TypeListTest
  : public ::testing::Test
{
public:
  struct CountPredicate
  {
    CountPredicate( void ) : count(0) {}

    template<class TType>
    void operator()( TType t )
      {
        ++count;
        std::cout << " check " << count;
      }

    int count;
  };

  CountPredicate pred;
};


TEST_F(TypeListTest, ForEach_0) {

  typedef typelist::MakeTypeList<>::Type MyTypeList;

  typelist::ForEach<MyTypeList> ListVisitor;
  ListVisitor( pred );

  EXPECT_EQ( pred.count, 0 );
}
