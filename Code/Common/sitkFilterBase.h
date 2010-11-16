#ifndef __sitkFilterBase_h
#define __sitkFilterBase_h

namespace itk
{
namespace simple
{

class FilterBase
{
public:

  FilterBase( void ) {}
  virtual ~FilterBase( void ) {}

  template <typename TImageType>
  void Dispatch( typename TImageType::Pointer image )
    {
    }

protected:

private:

};

}
}


#endif //__sitkFilterBase_h
