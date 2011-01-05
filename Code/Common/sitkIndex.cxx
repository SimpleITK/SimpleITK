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


Index::Index( const itk::Index<2> &idx )
{
 m_Index[0] = idx[0];
 m_Index[1] = idx[1];
 m_Index[2] = 0;
 m_Dim = 2;
}

Index::Index( const itk::Index<3> &idx )
{
 m_Index[0] = idx[0];
 m_Index[1] = idx[1];
 m_Index[2] = idx[2];
 m_Dim = 3;
}

Index::IndexValueType Index::GetX() const { return m_Index[0]; }
Index::IndexValueType Index::GetY() const { return m_Index[1]; }
Index::IndexValueType Index::GetZ() const { return m_Index[2]; }

Index & Index::SetX( IndexValueType x ) { m_Index[0] = x; return *this; }
Index & Index::SetY( IndexValueType y ) { m_Index[1] = y; return *this; }
Index & Index::SetZ( IndexValueType z ) { m_Index[2] = z; return *this; }

unsigned int Index::GetDim() const { return m_Dim; }

Index::IndexValueType &
Index::operator[](unsigned int dim)
{
  return m_Index[dim];
}

const Index::IndexValueType &
Index::operator[](unsigned int dim) const
{
  return m_Index[dim];
}

bool Index::operator==(const Self & idx) const
{
  if (m_Index[0] == idx[0] &&
      m_Index[1] == idx[1] &&
      m_Index[2] == idx[2] &&
      m_Dim == idx.GetDim())
    {
    return true;
    }
  else
    {
    return false;
    }
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

std::string Index::ToString()
{
  std::ostringstream out;
  out << *this;
  return out.str();
}

std::ostream & operator<<(std::ostream & os, const Index & idx)
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
