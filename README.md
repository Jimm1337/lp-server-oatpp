# lp-server-oatpp
[![GitHub license](https://img.shields.io/github/license/Jimm1337/lp-server-oatpp?color=blue)](https://github.com/Jimm1337/lp-server-oatpp/blob/master/LICENSE)

C++20 REST API with gpio and sqlite integration. Targets RaspberryPi 4B.

## Features
- SQLite3
- gpiod
- swagger

## Build guide
### 1. Install Docker
See [Install Docker Engine on Debian](https://docs.docker.com/engine/install/debian/).
### 2. Build
```shell
$ docker build . --tag lp-server-oatpp 
```

## Run
### - Debug
```shell
$ docker run --privileged -it -p 8000:8000 lp-server-oatpp /project/cmake-build-debug/bin/lp-server-oatpp-exe
```
### - Release
```shell
$ docker run --privileged -it -p 8000:8000 lp-server-oatpp /project/cmake-build-release/bin/lp-server-oatpp-exe
```
### - Test
```shell
$ docker run --privileged -it -p 8000:8000 lp-server-oatpp /project/cmake-build-debug/bin/lp-server-oatpp-test
```

## Before you contribute
### 1. Install clang-format
See [clang-format Stackoverflow](https://stackoverflow.com/questions/20756924/how-can-i-install-clang-format-in-ubuntu).
### 2. Format code
```shell
$ clang-format -i ./src/**/*.cpp
$ clang-format -i ./src/**/*.hpp
$ clang-format -i ./test/**/*.cpp
$ clang-format -i ./test/**/*.hpp
```

## Todo:
#### CI/CD
- coverity-scan
- Codecov
- Travis
- AppVeyor