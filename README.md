[![DOI](https://zenodo.org/badge/21195/PavelKovalets/k52.svg)](https://zenodo.org/badge/latestdoi/21195/PavelKovalets/k52) [![Build Status](https://travis-ci.org/PavelKovalets/k52.svg?branch=develop)](https://travis-ci.org/PavelKovalets/k52)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/8569/badge.svg)](https://scan.coverity.com/projects/pavelkovalets-k52)
# Intro #

k52 is a set of c++ libraries aimed to facilitate scientific experiments
 in the fields of signal processing and sound analysis with the strong
 incline into OOP, flexibility and readability. 
It also provides the implementation of some optimization,
 classification and other methods, as well as set of handy tools
 to support parallel computing. Distributed under the [MIT License](https://github.com/PavelKovalets/k52/blob/develop/LICENSE).

# Quick start #

## Preparation ##

On both Linux and Windows you should install [git](https://git-scm.com/) and
 [clone k52 repository](https://help.github.com/articles/cloning-a-repository/).

For example you can create folder `e:\example\` and run following commands from command prompt:

```
$ cd "e:\example"
$ git clone git@github.com:PavelKovalets/k52.git
```

Now you will have `e:\example\k52` folder which contains k52 code. We will call it **the k52 root folder**.

## Windows and Visual Studio ##

**Prerequisites:** 

- [Visual Studio](https://www.visualstudio.com/en-us/products/visual-studio-community-vs.aspx) with c++ development tools
- [CMake](https://cmake.org/download/) installed

In this example we will use `e:\example` as a folder in which we will build k52. You can use any other folder path if you want.

**Hint:** However you should check that your full path doesn't contain spaces,
 otherwise some CMake code will fails (e.g. boost required headers will not be found)

**Steps:**

- Install [boost](http://www.boost.org/) dependency
 - Download latest boost version ( at the moment of writing it was [boost 1.61.0]( https://sourceforge.net/projects/boost/files/boost/1.61.0/ ) )
 - Extract it into `e:\example\`. After that you should have a folder `e:\example\boost_1_61_0\` with, apart of others, `bootstrap.bat` in it.
 - Add path into `k52.config` – corresponding line should be 
```CMake
set(BOOST_ROOT "e:\\example\\boost_1_61_0")
```

- Prepare the solution
 - Create a folder to build in - `e:\example\k52\build\`
 - Run CMake from this folder from command line 
 (you might need to add `/d` option for `cd` command if you are changing the drive e.g. from `c:\` to `e:\`):
```
$ cd "e:\example\k52\build"
$ cmake ..
```
 
- Build k52
 - Open the solution file which was created by CMake - `e:\example\k52\build\k52.sln`
 - Build the solution

This is the minimum set of steps to build k52.
However some parts of k52 will not be build. 
To get fully-functional version you need to make some additional steps.
After that you should re-run CMake to update the solution.

- Compile required boost libs
 - Just run following commands from boost folder - `e:\example\boost_1_61_0\`
```
$ bootstrap
$ .\b2 --with-test --with-thread --with-system --with-date_time
```
In case you have MPI installed on your system you can also add
 `--with-mpi --with-serialization` to compile k52 with MPI support,
 but this is more advanced case and usually not required.

- Install FFTW3 library
 - Download [precompiled dlls](http://www.fftw.org/install/windows.html)
 - Extract into `c:\example\fftw-3.3.5-dll32` - we will call it FFTW3 folder.
 
 - Only dynamic libs are precompiled. In order to link them from Visual C++,
 you need to create `.lib` "import libraries". 
 To do this run following commands from FFTW3 folder. 
 `lib` command must be available, so one option is to use
 [Developer Command Prompt for Visual Studio](https://msdn.microsoft.com/en-us/library/ms229859%28v=vs.110%29.aspx?f=255&MSPPError=-2147217396)
```
$ lib /def:libfftw3-3.def
$ lib /def:libfftw3f-3.def
$ lib /def:libfftw3l-3.def
```
 - Add path into `k52.config` – corresponding line should be 
```CMake
set(FFTW3_ROOT "C:\\example\\fftw-3.3.5-dll32")
```
 - Now everything will compile, but in oreder to run FFTW3-dependent code 
 (e.g. unit tests project) you need to reference dlls.
 You could either copy all dlls from FFTW3 folder to the folder with your `.exe` file
 or add it to `PATH` environment variable (in Visual Studio go to project properties (Alt+F7),
 under Debugging, find an Environment field and set it to `PATH=%PATH%;C:\example\fftw-3.3.5-dll32`).

## Linux steps ##

All you have to do is:

- Run `$./tools/bootstrap.sh` script from k52 root folder to install k52 dependencies
- Run `$./tools/build_k52_run_examples.sh` script from k52 root folder to build k52 and run its examples

## Other approaches to build using CMake ##

In case of CMake - aware IDE's you just need to open CMake file from k52 root folder and build it.

Else, from k52 root folder execute following commands using cmd:

```
$ mkdir build
$ cd build
$ cmake ..
```

This will create project files for your default compiler/IDE in `build` folder. You should check if there were no errors from ->-> K52 MESSAGE <-<-, if there are - try to fix them.

Now you have all the files that are necessary to build k52 in `build` folder.
- Visual Studio             -       find .sln file in `build` folder and run it.
- make                      -       execute `$ make` from `build` folder .

## Run tests ##

- Visual Studio             -       build `RUN_TESTS` project from `k52.sln` and see the output.
- make                      -       execute `$ make test` from `build` folder and see the output.

# Use k52 in other project #

k52 provides CMake config-file package during the install process.
It can be then used by other CMake project to easily use k52.

To do so first you have to run install `$ make install` (or build INSTALL project in VS).
After that you'll have `install` folder in k52 root folder,
 which contains all necessary files - config-file package, libs, headers.

After that you just need to link this config-file package in your project and use `find_package(k52 CONFIG)`.
Example CMake project file that uses such config-file package is following:

```CMake
cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME "test_project")
project(${PROJECT_NAME})

set(BOOST_ROOT "[your Boost root path here]")
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(k52 CONFIG REQUIRED HINTS "[your k52 install path here]")

include_directories(${k52_INCLUDE_DIRS})
link_directories(${k52_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${k52_LIBRARIES})
```

**Hint** You can take a look at the `tools/build_k52_run_examples.sh` script and try to run its commands
 one by one to get the complete picture of how to use k52.
 Or you can check to the `examples` folder which contains working examples of k52 usage.

# Detailed info #
 
## Libs description ##

- `common`                    -       helper classes, generic templates,
                                      patterns implementation, regularly-used functionality 
- `optimization`              -       implementation of various optimization methods
                                      for both discrete and continuous objective functions
- `dsp`                       -       implementation of various signal processing and
                                      sound analysis algorithms and methods
- `parallel`                  -       set of tools and helpers to support commonly-used
                                      parallel computing technologies (threads, MPI),
                                      with no or almost no set-up and infrastructural code required

##  Gitflow Workflow ##

k52 uses [Gitflow Workflow](https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow). We have following dedicated branches:
- `master` - stores the official release history. All commits here must be tagged with a release version number. 
- `develop` - serves as an integration branch for features.
- `coverity_scan` - serves as the source branch for the [static analisys tool](https://scan.coverity.com/projects/pavelkovalets-k52). `develop` should be merged into this branch from time to time to detect new defects, e.g. before creating new commit in `release` branch.
- other feature branches - the implimentation and bugfixes should be done in these branches. They are branched from `develop`, have names corresponding to the taks being implemented, and then merged back to `develop` when task is finished.

## Repository structure ##

The k52 root folder has following content:

### Folders ###

- `cmake`                         -       CMake external modules are loaded from this folder
- `configuration`                 -       contains CMake-specific configuration files,
                                          should not be edited unless required
- `examples`                      -       contains example projects of how k52 might be used
- `include`                       -       contains all k52 public headers
- `install`                       -       will be created on k52 install and contain all files
                                          necessary to use k52 in another project
- `src`                           -       contains all k52 private headers and source files
 - `common`                       -       lib source files
 - `dsp`                          -       lib source files
 - `optimization`                 -       lib source files
 - `parallel`                     -       lib source files
 - `unit_tests`                   -       unit tests for k52 libs
- `tools`                         -       set of useful scripts for k52 usage

### Files ###

- `k52.config`                          -       main configuration file for CMake system, normally
                                                should be edited by the end user to contain all the settings
                                                corresponding to the machine k52 is build on (like FFTW3_ROOT)
- `k52-config.cmake.in`                 -       template file for CMake fing_package support


- `tools/bootstrap.sh`                  -       linux shell script to setup all necessary environment
                                                to build k52, used in Vagrant box, but also could be
                                                used on any other system
- `tools/build_k52_run_examples.sh`     -       linux shell script to demonstrate the process of k52 build and usage;
                                                builds k52 to corresponding `tools_build` folders, installs it into `install` folder,
                                                builds k52 examples to corresponding `tools_build` folders and runs examples;
                                                can be used on Vagrant
- `tools/encoding.sh`                   -       linux shell script to check if all k52 source files have ASCII 7 bit encoding (only Latin symbols);
                                                outputs the name of files with different encoding, no output if encoding is ok
- `CMakeLists.txt`              -       root CMake file
- `LICENSE`                     -       file with license
- `README.md`                   -       &(*this)
- `Vagrantfile`                 -       file with Vagrant settings (see below how to use)
- `.gitattributes`              -       git settings, applied to the repository
- `.gitignore`                  -       used to exclude files from git tracking
- `.travis.yml`                 -       file with configuration for [Travis CI](https://travis-ci.org)

# Build system #

[CMake](https://cmake.org/), the cross-platform, open-source build system is used in k52, so you must install it to build k52.
While theoretically any platform supported by CMake will be ok, the tested are Windows and Linux.
[make](https://ru.wikipedia.org/wiki/Make) system is fully supported.

Following IDE might be helpful:

- [CLion (really good one, limited evaluation)](https://www.jetbrains.com/clion/ )
- [Visual Studio (not bad too, free)](https://www.visualstudio.com/en-us/products/visual-studio-express-vs.aspx)
- [KDevelop (free)](https://www.kdevelop.org/)
- [Eclipse CDT (free)](https://eclipse.org/cdt/)
 
# Using Vagrant box #

Vagrant is a handy tool that easily provides the environment on which k52 can be build:
- Install some virtualization provider (e.g. [VirtualBox](https://www.virtualbox.org/))
- Install [Vagrant](http://www.vagrantup.com/) and read about it 
- From project root (containing Vagrantfile) launch a console, create a vagrant VM, connect to the VM, and go to the project directory
```
$ vagrant up
$ vagrant ssh
$ cd /vagrant
```
- Now you can just make steps form Linux quick start example in your console.
 You do not need to install dependencies because Vagrant does it on start up.
- If any script from `tools` folder fails to run on Vagrant
 and you are using Windows host, try to temporary change 
 script file's EOL format to Linux (Vagrant use files directly).

# Known issues #

 - For Visual Studio there might be problems with libs 
(e.g. `cannot open file libboost_date_time-vc120-mt-gd-1_55.lib`).
Not completelly clear, is it a bug or feature, but according to
 http://www.boost.org/doc/libs/1_54_0/doc/html/thread/build.html 
it is fixed by compiling ALL dependant libs explicitly 
```
$ bjam --build-type=complete --with-thread --with-chrono --with-date_time)
```
