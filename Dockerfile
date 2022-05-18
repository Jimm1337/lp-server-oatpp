# Target platform. # todo: SET TARGET PLATFORM
FROM debian:stable

# Update.
RUN apt update && apt upgrade -y

# Grab dependencies.
RUN apt install -y gcc g++ cmake ninja-build python3 python3-pip sqlite3
RUN pip install conan

# Add all project files to container.
ADD . /project

# Build.
WORKDIR /project
RUN mkdir sql

RUN cmake -DCMAKE_BUILD_TYPE=Debug  \
    -DCMAKE_MAKE_PROGRAM=ninja  \
    -DCMAKE_C_COMPILER=gcc  \
    -DCMAKE_CXX_COMPILER=g++  \
    -G Ninja  \
    -S .  \
    -B ./cmake-build-debug

RUN cmake -DCMAKE_BUILD_TYPE=Release  \
    -DCMAKE_MAKE_PROGRAM=ninja  \
    -DCMAKE_C_COMPILER=gcc  \
    -DCMAKE_CXX_COMPILER=g++  \
    -G Ninja  \
    -S .  \
    -B ./cmake-build-release

RUN cmake --build ./cmake-build-release --target lp-server-oatpp-exe
RUN cmake --build ./cmake-build-release --target lp-server-oatpp-test

RUN cmake --build ./cmake-build-debug --target lp-server-oatpp-exe
RUN cmake --build ./cmake-build-debug --target lp-server-oatpp-test
