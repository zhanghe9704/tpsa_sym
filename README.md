# SDA - Symbolic DA/TPSA Lib in C++

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/zhanghe9704/tpsa/blob/master/LICENSE.md)

## About this code

This code allows users to do symbolic computations using  Differential Algebra (DA), also called Truncated Power Series Algebra (TPSA), in C++. This code is developed based on the numerical DA/TPSA lib,  [*cppTPSA/pyTPSA*](https://github.com/zhanghe9704/tpsa), and the symbolic computation lib, [*SymEngine*](https://github.com/symengine/symengine). The algorithms for DA/TPSA computation in this lib are exactly the same with those in  [*cppTPSA/pyTPSA*](https://github.com/zhanghe9704/tpsa), but they are implemented on symbols rather than numbers. Currently, symbolic calculation with complex numbers is not supported. It could be added in the future version, should a desire exist. 

For users who are not familar with TPSA and DA, please refer to chapter 8 in [*Lecture Notes on Special Topics in Accelerator Physics*](http://inspirehep.net/record/595287/files/slac-pub-9574.pdf)  by  Prof. Alex Chao  and chapter 2 in [*Modern Map Methods in Particle Beam Physics*](http://bt.pa.msu.edu/cgi-bin/display.pl?name=AIEP108book) by Prof. Martin Berz. It may also be helpful to play with the numerical DA/TPSA lib [*cppTPSA/pyTPSA*](https://github.com/zhanghe9704/tpsa) first. 


Popular mathematical operators and functions have been overloaded for the symbolic DA vector data type. 

Math operator overloaded: (SDA - Symbolic DA vector)

| Left hand | Operator | Right hand | Left hand | Operator | Right hand |
| :-------: | :------: | :--------: | :-------: | :------: | :--------: |
|    SDA    |    +     |    SDA     |    SDA    |    /     |   double   |
|  double   |    +     |    SDA     |  double   |    /     |    SDA     |
|    SDA    |    +     |   double   |    SDA    |    =     |    SDA     |
|           |    +     |    SDA     |    SDA    |    =     |   double   |
|    SDA    |    -     |    SDA     |    SDA    |    +=    |    SDA     |
|    SDA    |    -     |   double   |    SDA    |    +=    |   double   |
|  double   |    -     |    SDA     |    SDA    |    -=    |    SDA     |
|           |    -     |    SDA     |    SDA    |    -=    |   double   |
|    SDA    |    *     |    SDA     |    SDA    |    *=    |    SDA     |
|    SDA    |    *     |   double   |    SDA    |    *=    |   double   |
|  double   |    *     |    SDA     |    SDA    |    /=    |    SDA     |
|    SDA    |    /     |    SDA     |    SDA    |    /=    |   double   |

Math functions overloaded:

- sqrt
- exp
- log
- sin
- cos
- tan
- asin
- acos
- atan
- sinh
- cosh
- tanh
- pow
- erf 
  
More information on the code is available in [this doxygen document](https://zhanghe9704.github.io/tpsa_sym/doc/doxygen/html/index.html).


## How to compile
You will need a C++ compiler that supports C++ 14 standard. You also need to install [SymEngine](https://github.com/symengine/symengine) before compiling this code. In the following, we will explain how to install SymEngine and compile SDA lib. 

### Linux ###
The author compiled the code in Ubuntu 20.04 and Ubuntu 22.04 as follows. 
1. **Install SymEngine**

   `conda install symengine -c conda-forge`

   To make sure cmake can find SymEngine, add the its install directory to `LD_LIBRARY_PATH` by 

   `export LD_LIBRARY_PATH=/PATH/TO/SYMENGINE/lib:$LD_LIBRARY_PATH`

   The author installed SymEngine by micromamba. By default, it is installed to `home/MyUserName/micromamba/pkgs/symengine-0.12.0-h7298f4c_2/`. 

2. **Compile the SDA lib**

Clone this repository. Inside the root folder, use the following commands to compile it. 

```shell
mkdir build
cd build
cmake ..
make
sudo make install  # To install the SDA lib
```

The `make` command will generate a shared lib `libsymtpsa.so` and a static lib `libsymtpsa.a`. By default, the two libs will be installed to `/usr/local/lib` and the header file `sda.h`  will be installed to `/usr/local/include`/ 

3. **Compile the examples**
   
   `make examples`

   The example source files locate in the folder `examples`. The executables are compiled and save in `build/bin/examples`. 

4. **Compile the tests**
   
   `make tests`

   An executable `run_tests` will be created in `build/bin/tests`.   
   
   The tests depend on [*Catch2*]([GitHub - catchorg/Catch2: A modern, C++-native, test framework for unit-tests, TDD and BDD - using C++14, C++17 and later (C++11 support is in v2.x branch, and C++03 on the Catch1.x branch)](https://github.com/catchorg/Catch2)) version 2.3.16, which is a header only test framework for C++. 

### Windows 11 ###

The simplest way to compile SDA in Windows is to use WSL2 and compile it as in Linux. But if a library that runs in the native Windows environment is desired, try to compile in the following way. 

1. **Compile with GNU compilers**

   To compile SDA using GNU compilers, we need to compile SymEngine from source code first. We can do it using MSYS2. 

   1.1 **Compile SymEngine from source code**

   Clone the SymEngine repo from Github.
   `git clone git@github.com:symengine/symengine.git`

   Install MSYS2 and then open MSYS2 MINGW64 terminal.  If necessary, install the compiling tools. (May have already been installed.)

   `pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake`

   Make sure `gcc`, `g++`, `mingw32-make`, and `cmake` are callable from the  terminal. Close the terminal and reopen it. 

   In the MSYS2 MINGW64 terminal, go to the SymEngine folder. Windows partitions are mounted under the root in MSYS2. For example, go to `/d/symengine` for `D:\symengine`. Use the following command to compile SymEngine. 

   ```shell
   mkdir build
   cd build
   cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
   mingw32-make
   ```

   This will build a static lib of SymEngine. For dynamic/shared lib, use the following command to configure cmake.

   `cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=YES`

   To install SymEngine to the default folder, run MSYS2 MINGW64 as administrator and go back to the above folder. 

   `mingw32-make install`

    SymEngine will be installed to ` C:/Program Files (x86)/symengine/`

   1.2 **Compile SDA**

   Go to the SDA folder and run the following commands.

   ```shell
   mkdir build
   cd build
   cmake .. -G "MinGW Makefiles"
   mingw32-make
   ```

   1.3 **compile the examples**

   `make examples`

   The example source files locate in the folder `examples`. The executables are compiled and save in `build/bin/examples`. 

   1.4 **Compile the tests**

   `make tests`

   An executable `run_tests` will be created in `build/bin/tests`.   

   The tests depend on [*Catch2*]([GitHub - catchorg/Catch2: A modern, C++-native, test framework for unit-tests, TDD and BDD - using C++14, C++17 and later (C++11 support is in v2.x branch, and C++03 on the Catch1.x branch)](https://github.com/catchorg/Catch2)) version 2.3.16, which is a header only test framework for C++. 

   1.5 **Before you run any executables**

   The dynamic libs of *symengine* and *gmp* may be needed to run the executables. To make sure they can be found, add their directories to the environmental variable *Path*. If compiled as above, the directories are

   `C:\Program Files (x86)\symengine\bin`

   `C:\msys64\mingw64\bin`


2. **Compile with Microsoft compiler and Visual Studio IDE**

   If SymEngine is installed through conda-forge using 

   `conda install symengine -c conda-forge`

   the SymEngine lib was compiled by Microsoft compiler. SDA has to be compiled by Microsoft compiler, too. Open SDA fold with conda terminal and run the following commands.

   ```shell
   mkdir build
   cd build
   cmake -G "Visual Studio 16 2019" -A x64 ..
   ```

    Visual Studio projects will be generated. Then you can open those projects to compile the SDA, the examples, and the tests. You may want to change some settings inside the projects. However, the author is not familar with Visual Studio and cannot provide further help. 

### macOS ###
Sorry! The author has never used macOS and hence cannot provide an instruction. However, if you can install SymEngine following its instruction successfully, compiling SDA lib is expected to be as straightforward as in Linux. 


### Known issues ###

When running tests in Linux (tested in Ubuntu 20.04/22.04), a "segmentation fault" error will be reported after passing all the tests. The does not happen when running the tests on Windows, and in Linux it does not happen when I used the lib in other programs. There might be conflict in the way how CATCH2 and this SDA lib manage the memory.     

## Guidelines for Third-Party Contributions, Issue Reporting, and Support

See [here](https://zhanghe9704.github.io/tpsa_sym/contributing.html).

## Acknowledgement

**This work is supported by the U.S. Department of Energy, Office of Science, Office of Nuclear Physics under contract DE-AC05-06OR23177.**



## Contact

Contact the author by hezhang.AT.jlab.org. 
