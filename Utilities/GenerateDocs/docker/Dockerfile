FROM ubuntu:16.04

RUN apt-get update && \
    apt-get install -y cmake cmake-curses-gui gcc g++ git python python-dev doxygen ninja-build gnuplot wget texlive-full

WORKDIR /tmp/
COPY ./cmd.sh /work/
RUN chmod o+rx /work/cmd.sh

ENTRYPOINT [ "bash", "-c", "groupadd -o -g $_GROUPID $_USER && useradd -m -o -g $_GROUPID $_USER -u $_USERID && su $_USER /work/cmd.sh" ]
