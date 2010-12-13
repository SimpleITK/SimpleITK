#include "sitkIndex.h"

namespace itk
{
namespace simple
{

Index::Index()
{
  m_Index[0] = 0;
  m_Index[1] = 0;
  m_Index[2] = 0;
  m_Dim = 2;
}

Index::Index( IndexValueType x, IndexValueType y )
{
  m_Index[0] = x;
  m_Index[1] = y;
  m_Index[2] = 0;
  m_Dim = 2;
}

Index::Index( IndexValueType x, IndexValueType y, IndexValueType z )
{
  m_Index[0] = x;
  m_Index[1] = y;
  m_Index[2] = z;
  m_Dim = 3;
}

Index::IndexValueType Index::GetX() const { return m_Index[0]; }
Index::IndexValueType Index::GetY() const { return m_Index[1]; }
Index::IndexValueType Index::GetZ() const { return m_Index[2]; }

Index & Index::SetX( IndexValueType x ) { m_Index[0] = x; return *this; };
Index & Index::SetY( IndexValueType y ) { m_Index[1] = y; return *this; };
Index & Index::SetZ( IndexValueType z ) { m_Index[2] = z; return *this; };

unsigned int Index::GetDim() const { return m_Dim; };

Index::IndexValueType &
Index::operator[](unsigned int dim)
{
  return m_Index[dim];
}

Index::operator itk::Index<2>()
{
  itk::Index<2> idx;
  idx[0] = m_Index[0];
  idx[1] = m_Index[1];
  return idx;
}

Index::operator itk::Index<3>()
{
  itk::Index<3> idx;
  idx[0] = m_Index[0];
  idx[1] = m_Index[1];
  idx[2] = m_Index[2];
  return idx;
}


std::ostream & operator<<(std::ostream & os, Index & idx)
{
  os << "[";
  for ( unsigned int i = 0; i + 1 < idx.GetDim(); ++i )
    {
    os << idx[i] << ", ";
    }
  if ( idx.GetDim() >= 1 )
    {
    os << idx[idx.GetDim() - 1];
    }
  os << "]";
  return os;
}


} // end namespace simple
} // end namespace itk
