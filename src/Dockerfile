FROM ubuntu
RUN apt update && apt install gcc g++ make cmake libgtest-dev valgrind build-essential libsubunit-dev -y
RUN cd /usr/src/googletest && cmake CMakeLists.txt && make
WORKDIR /home
COPY . /home

ENTRYPOINT ["sh", "valgrisha.sh"]
