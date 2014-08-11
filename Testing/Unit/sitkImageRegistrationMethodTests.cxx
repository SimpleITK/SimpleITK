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
#include <SimpleITKTestHarness.h>
#include <SimpleITK.h>

#include <stdint.h>
#include <memory>

namespace
{


class IterationUpdate
  : public itk::simple::Command
{
public:
  IterationUpdate( const itk::simple::ImageRegistrationMethod &m)
    : m_Method(m)
    {}

  virtual void Execute( )
    {
      // use sitk's output operator for std::vector etc..
      using itk::simple::operator<<;

      // stash the stream state
      std::ios  state(NULL);
      state.copyfmt(std::cout);
      std::cout << std::fixed << std::setfill(' ') << std::setprecision( 5 );
      std::cout << std::setw(3) << m_Method.GetOptimizerIteration();
      std::cout << " = " << std::setw(10) << m_Method.GetMetricValue();
      std::cout << " : " << m_Method.GetOptimizerPosition() << std::endl;

      std::cout.copyfmt(state);
    }

private:
  const itk::simple::ImageRegistrationMethod &m_Method;

};

}

//
//
//

TEST(Registration,ImageRegistrationMethod_Basic) {
  // This test is to perform some basic coverage of methods.

  namespace sitk = itk::simple;

  sitk::ImageRegistrationMethod registration;
  std::cout << registration.ToString();
}


//
// Fixture based tests
//

namespace sitk = itk::simple;

class sitkRegistrationMethodTest
  : public ::testing::Test
{
public:

  sitk::Image MakeDualGaussianBlobs(const std::vector<double> &pt0,
                                    const std::vector<double> &pt1,
                                    const std::vector<unsigned int> &size)
    {
       sitk::GaussianImageSource source1;
      source1.SetMean(pt0);
      source1.SetScale(1.0);

      std::vector<double> sigma;
      for(unsigned int i = 0; i < size.size(); ++i)
        {
        sigma.push_back(size[i]/10.0);
        }
      source1.SetSigma(sigma);
      source1.SetSize(size);
      source1.SetOutputPixelType(sitk::sitkFloat32);

      sitk::GaussianImageSource source2;
      source2.SetMean(pt1);
      source2.SetScale(-1.0);
      source2.SetSigma(sigma);
      source2.SetSize(size);
      source2.SetOutputPixelType(sitk::sitkFloat32);

      return sitk::Add(source1.Execute(), source2.Execute());
    }

protected:
  virtual void SetUp()
  {
    fixedBlobs = MakeDualGaussianBlobs(v2(64,64), v2(192,192), std::vector<unsigned int>(2,256));
    movingBlobs = MakeDualGaussianBlobs(v2(54,74), v2(192,192), std::vector<unsigned int>(2,256));
  }


  // virtual void TearDown() {}

  sitk::Image fixedBlobs;
  sitk::Image movingBlobs;

};


TEST_F(sitkRegistrationMethodTest, Transform_InPlaceOn)
{
  // This test is to check some excpetional cases for using masks
  sitk::ImageRegistrationMethod R;
  EXPECT_TRUE(R.GetInitialTransformInPlace());

  sitk::Image fixed = fixedBlobs;
  sitk::Image moving = fixedBlobs;

  double minStep=1e-4;
  unsigned int numberOfIterations=100;
  double relaxationFactor=0.5;
  double gradientMagnitudeTolerance = 1e-10;
  R.SetOptimizerAsRegularStepGradientDescent(1.0,
                                             minStep,
                                             numberOfIterations,
                                             relaxationFactor,
                                             gradientMagnitudeTolerance);

  R.SetInterpolator(sitk::sitkLinear);

  sitk::TranslationTransform tx(fixed.GetDimension());
  tx.SetOffset(v2(1.1,-2.2));
  R.SetInitialTransform(tx,false);
  EXPECT_TRUE(!R.GetInitialTransformInPlace());

  R.SetMetricAsMeanSquares();

  IterationUpdate cmd(R);
  R.AddCommand(sitk::sitkIterationEvent, cmd);

  sitk::Transform outTx = R.Execute(fixed,moving);

  EXPECT_VECTOR_DOUBLE_NEAR(v2(0.0,0.0), outTx.GetParameters(), 1e-4);
  // expect input not to be modified
  EXPECT_EQ(v2(1.1,-2.2), tx.GetParameters());

  // optimize in place this time
  R.SetInitialTransform(tx,true);
  EXPECT_TRUE(R.GetInitialTransformInPlace());
  outTx = R.Execute(fixed,moving);

  EXPECT_VECTOR_DOUBLE_NEAR(v2(0.0,0.0), outTx.GetParameters(), 1e-4);
  // expect input to have been modified
  EXPECT_VECTOR_DOUBLE_NEAR(v2(0.0,0.0), tx.GetParameters(), 1e-4);


}



TEST_F(sitkRegistrationMethodTest, Mask_Test0)
{
  // This test is to check some excpetional cases for using masks
  sitk::ImageRegistrationMethod R;

  R.SetOptimizerAsGradientDescent(1.0, 100);

  R.SetInterpolator(sitk::sitkLinear);


  sitk::TranslationTransform tx(fixedBlobs.GetDimension());
  R.SetInitialTransform(tx);

  // wrong dimension should produce error
  R.SetMetricFixedMask(sitk::Image(100,100,100,sitk::sitkUInt8));

  EXPECT_THROW(R.Execute(fixedBlobs,movingBlobs), sitk::GenericException);

  R.SetMetricFixedMask(sitk::Image());
  // wrong dimension should produce error
  R.SetMetricMovingMask(sitk::Image(100,100,100,sitk::sitkUInt8));

  EXPECT_THROW(R.Execute(fixedBlobs,movingBlobs), sitk::GenericException);
}


TEST_F(sitkRegistrationMethodTest, Mask_Test1)
{
  // This test is to check that the metric masks have the correct
  // effect.

  sitk::ImageRegistrationMethod R;

  double learningRate=2.0;
  double minStep=1e-7;
  unsigned int numberOfIterations=100;
  double relaxationFactor=0.5;
  double gradientMagnitudeTolerance=1e-8;
  R.SetOptimizerAsRegularStepGradientDescent(learningRate,
                                             minStep,
                                             numberOfIterations,
                                             relaxationFactor,
                                             gradientMagnitudeTolerance );
  R.SetInterpolator(sitk::sitkLinear);


  sitk::TranslationTransform tx(fixedBlobs.GetDimension());
  R.SetInitialTransform(tx);

  R.SetMetricAsCorrelation();
  R.SetMetricFixedMask(sitk::Cast(sitk::Greater(fixedBlobs,0),sitk::sitkFloat32));

  IterationUpdate cmd(R);
  R.AddCommand(sitk::sitkIterationEvent, cmd);

  sitk::Transform outTx = R.Execute(fixedBlobs,movingBlobs);

  EXPECT_VECTOR_DOUBLE_NEAR(v2(-10,10), outTx.GetParameters(), 1e-4);
}


TEST_F(sitkRegistrationMethodTest, Mask_Test2)
{
  // This test is to check that the metric masks have the correct
  // effect.

  sitk::ImageRegistrationMethod R;

  double learningRate=1.0;
  double minStep=1e-7;
  unsigned int numberOfIterations=100;
  double relaxationFactor=0.5;
  double gradientMagnitudeTolerance=1e-8;
  R.SetOptimizerAsRegularStepGradientDescent(learningRate,
                                             minStep,
                                             numberOfIterations,
                                             relaxationFactor,
                                             gradientMagnitudeTolerance );
  R.SetInterpolator(sitk::sitkLinear);


  sitk::TranslationTransform tx(fixedBlobs.GetDimension());
  tx.SetOffset(v2(120,99));
  R.SetInitialTransform(tx);

  R.SetMetricAsCorrelation();
  R.SetMetricFixedMask(sitk::Greater(fixedBlobs,0));
  R.SetMetricMovingMask(sitk::Less(movingBlobs,0));

  IterationUpdate cmd(R);
  R.AddCommand(sitk::sitkIterationEvent, cmd);

  sitk::Transform outTx = R.Execute(fixedBlobs,movingBlobs);

  EXPECT_VECTOR_DOUBLE_NEAR(v2(128.0,128.0), outTx.GetParameters(), 1e-3);
}
