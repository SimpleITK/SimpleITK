#ifndef __sitkIndex_h
#define __sitkIndex_h

// sitk includes
#include "sitkMacro.h"

// itk includes
#include "itkIndex.h"

namespace itk
{
namespace simple
{

class Index
{

public:

  // Typedefs
  typedef Index              Self;
  typedef size_t             IndexValueType;

  //
  // Constructors
  //
  Index( IndexValueType x, IndexValueType y );
  Index( IndexValueType x, IndexValueType y, IndexValueType z );
  explicit Index( const itk::Index<2> &idx );
  explicit Index( const itk::Index<3> &idx );

  //
  // Methods
  //

  // Get Component Methods
  IndexValueType GetX() const;
  IndexValueType GetY() const;
  IndexValueType GetZ() const;

  // Set Component Methods
  Self& SetX( IndexValueType x );
  Self& SetY( IndexValueType y );
  Self& SetZ( IndexValueType z );

  // Get dimensionality
  unsigned int GetDim() const;


  //
  // Operators
  //

  // [] operator (no bounds checking)
  IndexValueType & operator[](unsigned int dim);

  // Cast operator for itk::Index<2>
  operator itk::Index<2>();

  // Cast operator for itk::Index<3>
  operator itk::Index<3>();

private:

  // Not Implemented
  Index();

  // The dimensionality of the index
  unsigned int m_Dim;

  // Array of 3 values to hold the indices
  IndexValueType m_Index[3];

};  // end class Index


// << operator for printing
std::ostream & operator<<(std::ostream & os, Index & idx);


} // end namespace simple
} // end namespace itk


#endif
