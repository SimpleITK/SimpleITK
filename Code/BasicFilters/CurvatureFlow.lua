Filter = {
  name = 'CurvatureFlow',
  doc = 'Some global documentation',
  pixel_types = 'BasicPixelTypeList',
  members = {
    { name = 'TimeStep',
      type = 'double',
      default = '0.0',
      doc = 'Time step for curvature flow'
    };
    {
      name = 'NumberOfIterations';
      type = 'uint32_t';
      default = '5';
      doc = 'Number of iterations to run';
    };
  }
}

