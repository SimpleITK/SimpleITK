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
#ifndef __TransformCompare_h
#define __TransformCompare_h

#include <string>
#include <SimpleITKTestHarness.h>
#include <sitkImage.h>
#include <sitkTransform.h>


class TransformCompare
{

public:
  TransformCompare();

   bool Compare( const itk::simple::Transform &transform,
                 const itk::simple::Transform &baselineTransform,
                 const itk::simple::Image &fixedImage );

  bool Compare( const itk::simple::Transform &transform,
                const itk::simple::Image &baselineDisplacement );

  // Return the message from the previous image comparison.
  const std::string &GetMessage() const { return m_Message; }
  void SetTolerance ( double t ) { m_Tolerance = t; }
  double GetTolerance() const { return m_Tolerance; }

protected:
  std::string m_Message;
  double m_Tolerance;
};

#endif // __TransformCompare_h
