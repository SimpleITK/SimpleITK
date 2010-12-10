#ifndef __sitkIndex_h
#define __sitkIndex_h

// sitk includes
#include "sitkMacro.h"

namespace itk
{
namespace simple
{

class Index
{

public:

  // Typedefs
  typedef Index              Self;
  typedef SmartPointer<Self> Pointer;
  typedef uint64_t           IndexValueType;

  // Constructors
  Index( IndexValueType x, IndexValueType y, IndexValueType z )
    {
    m_Index[0] = x;
    m_Index[1] = y;
    m_Index[2] = z;
    };

  // Get Component Methods
  IndexValueType GetX() { return m_Index[0]; };
  IndexValueType GetY() { return m_Index[1]; };
  IndexValueType GetZ() { return m_Index[2]; };

  // Set Component Methods
  Self& SetX( IndexValueType x ) { m_Index[0] = x; return *this; };
  Self& SetY( IndexValueType y ) { m_Index[1] = y; return *this; };
  Self& SetZ( IndexValueType z ) { m_Index[2] = z; return *this; };

  // [] operator (no bounds checking)
  IndexValueType & operator[](unsigned int dim)
  { return m_Index[dim]; }

  // Array of 3 values to hold the indices
  IndexValueType m_Index[3];

};  // end class Index


} // end namespace simple
} // end namespace itk


#endif
