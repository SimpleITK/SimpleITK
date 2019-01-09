FROM ubuntu:16.04

RUN apt-get update && \
    apt-get install -y cmake cmake-curses-gui gcc g++ git python python-dev doxygen ninja-build gnuplot wget texlive-full

WORKDIR /tmp/
COPY ./cmd.sh /work/bin/
COPY ./entrypoint.sh /work/bin/
RUN chmod o+rx /work/bin/*.sh


ENTRYPOINT ["/work/bin/entrypoint.sh"]
CMD ["/work/bin/cmd.sh"]
