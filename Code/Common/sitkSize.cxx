#include "sitkSize.h"

namespace itk
{
namespace simple
{

Size::Size()
{
  m_Index[0] = 0;
  m_Index[1] = 0;
  m_Index[2] = 0;
  m_Dim = 2;
}

Size::Size( SizeValueType x, SizeValueType y )
{
  m_Index[0] = x;
  m_Index[1] = y;
  m_Index[2] = 0;
  m_Dim = 2;
}

Size::Size( SizeValueType x, SizeValueType y, SizeValueType z )
{
  m_Index[0] = x;
  m_Index[1] = y;
  m_Index[2] = z;
  m_Dim = 3;
}


Size::Size( const itk::Size<2> &idx )
{
 m_Index[0] = idx[0];
 m_Index[1] = idx[1];
 m_Index[2] = 0;
 m_Dim = 2;
}

Size::Size( const itk::Size<3> &idx )
{
 m_Index[0] = idx[0];
 m_Index[1] = idx[1];
 m_Index[2] = idx[2];
 m_Dim = 3;
}

Size::operator itk::Size<2>()
{
  itk::Size<2> idx;
  idx[0] = m_Index[0];
  idx[1] = m_Index[1];
  return idx;
}

Size::operator itk::Size<3>()
{
  itk::Size<3> idx;
  idx[0] = m_Index[0];
  idx[1] = m_Index[1];
  idx[2] = m_Index[2];
  return idx;
}

} // end namespace itk
} // end namespace simple
