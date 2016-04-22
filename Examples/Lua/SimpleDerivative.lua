
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

local sitk = {}
sitk = SimpleITK

outfile = "sitk-lua-test.png"

if #arg>0 then
  outfile = arg[1]
end

size = sitk.VectorUInt32();
size:push_back(128);
size:push_back(128);

sigma = sitk.VectorDouble();
sigma:push_back(32.0);
sigma:push_back(32.0);

center = sitk.VectorDouble();
center:push_back(64.0);
center:push_back(64.0);

gauss = sitk.GaussianSource (sitk.sitkFloat32, size, sigma, center);

deriv = sitk.Derivative(gauss);

result = sitk.RescaleIntensity(deriv, 0, 255.0);

result = sitk.Cast(result, sitk.sitkUInt8);

sitk.WriteImage(result, outfile);
