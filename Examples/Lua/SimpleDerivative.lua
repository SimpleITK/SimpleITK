
--=========================================================================
--
--  Copyright Insight Software Consortium
--
--  Licensed under the Apache License, Version 2.0 (the "License");
--  you may not use this file except in compliance with the License.
--  You may obtain a copy of the License at
--
--         http://www.apache.org/licenses/LICENSE-2.0.txt
--
--  Unless required by applicable law or agreed to in writing, software
--  distributed under the License is distributed on an "AS IS" BASIS,
--  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
--  See the License for the specific language governing permissions and
--  limitations under the License.
--
--=========================================================================

require "SimpleITK"

local sitk = {};
sitk = SimpleITK;

outfile = "sitk-lua-test.png";

-- parse the command line options
n = #arg;
for i=1,n do
  if ( (arg[i] == "--help")  or (arg[i] == "-h") ) then
    print ("Usage: SimpleDerivative.lua [--help|-h] [output_image]");
    os.exit();
  else
    outfile = arg[i];
  end
end

-- setup the parameters for the Gaussian source image
--   pixel dimensions of the Gaussian image image
size = sitk.VectorUInt32();
size:push_back(128);
size:push_back(128);

--   sigma of the Gaussian
sigma = sitk.VectorDouble();
sigma:push_back(32.0);
sigma:push_back(32.0);

--   center of the Gaussian
center = sitk.VectorDouble();
center:push_back(64.0);
center:push_back(64.0);

-- create Gaussian image
gauss = sitk.GaussianSource (sitk.sitkFloat32, size, sigma, center);

-- take the first derivative in the X direction of the Gaussian
deriv = sitk.Derivative(gauss);

-- rescale the intensities to [0, 255]
result = sitk.RescaleIntensity(deriv, 0, 255.0);

-- convert the float image pixels to unsigned char
result = sitk.Cast(result, sitk.sitkUInt8);

-- write the resulting image
sitk.WriteImage(result, outfile);

-- display the image via the Show function, which invokes ImageJ, by default.
if (os.getenv("SITK_NOSHOW") == nil) then
  sitk.Show(result);
end
