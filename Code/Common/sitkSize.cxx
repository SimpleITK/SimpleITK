#include "sitkSize.h"

namespace itk
{
namespace simple
{

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
