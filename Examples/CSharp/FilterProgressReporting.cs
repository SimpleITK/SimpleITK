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

using System;
using itk.simple;

namespace itk.simple.examples {

//! [csharp director command]
  class MyCommand : Command {

    private ProcessObject m_ProcessObject;

    public MyCommand(ProcessObject po){
      m_ProcessObject = po;
    }

    public override void Execute() {
      Console.WriteLine("{0} Progress: {1:0.00}", m_ProcessObject.GetName(), m_ProcessObject.GetProgress() );
    }
  }
//! [csharp director command]

  class FilterProgressReporting {

    static void Main(string[] args) {
      try {
        if (args.Length < 3) {
          Console.WriteLine("Usage: {0} <input> <variance> <output>", args[0]);
          return;
        }
        // Read input image
        ImageFileReader reader = new ImageFileReader();
        reader.SetFileName(args[0]);
        Image image = reader.Execute();

        // Execute Gaussian smoothing filter
        DiscreteGaussianImageFilter filter = new DiscreteGaussianImageFilter();
        filter.SetVariance(Double.Parse(args[1]));

        MyCommand cmd = new MyCommand(filter);
        filter.AddCommand(EventEnum.sitkProgressEvent, cmd);

        image = filter.Execute(image);

        // Write output image
        ImageFileWriter writer = new ImageFileWriter();
        writer.SetFileName(args[2]);
        writer.Execute(image);

      } catch (Exception ex) {
        Console.WriteLine(ex);
      }
    }
  }
}
