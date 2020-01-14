FROM ubuntu:14.04 as simpleitk-doxygen

RUN apt-get update && apt-get install -y \
  apt-utils \
  bison \
  build-essential \
  curl \
  flex \
  git \
  graphviz \
  ninja-build \
  doxygen \
  python \
  vim \
  && apt-get clean

# Install the latest CMake release
WORKDIR /tmp/
RUN curl  -L https://bootstrap.pypa.io/get-pip.py -o get-pip.py && \
    python get-pip.py && \
    pip install cmake

RUN git clone https://github.com/doxygen/doxygen.git && \
    ( cd doxygen && \
      git checkout Release_1_8_9_1 && \
      ./configure && \
      make -j$(nproc) && \
      make install) && \
    rm -rf ./doxygen

RUN git config --global url."https://github.com/InsightSoftwareConsortium/".insteadOf "https://itk.org/"

COPY run.sh /tmp

WORKDIR /work

ENTRYPOINT ["/tmp/run.sh"]
