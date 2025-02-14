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

   ```shell
   pacman -S mingw-w64-x86_64-toolchain
   pacman -S mingw-w64-x86_64-cmake
   ln -s /mingw64/bin/mingw32-make.exe /mingw64/bin/make.exe
   ```
   If you installed MSYS2 in C:\msys64, your compiler, make and cmake are installed in C:\msys64\mingw64\bin. Add this directory to the beginning of the environment variable PATH.

   Install gmp-devel, which is required by symengine. 
   ```shell
   pacman -S gmp-devel
   ```

   From now on, you do NOT need the mingw64 command line anymore. You can use the windows command line or poweshell to compile and install the code. 

   Go to the root folder of symengine, open the command line terminal, and run:

   ```shell
   mkdir build
   cd build
   cmake -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX=c:\msys64\mingw64 ..
   make
   make install
   ```
   The above commends will install symengine to c:\msys64\ming64. To avoid -G "MinGW Makefiles" in the command line, you can create an environment variable CMAKE_GENERATOR and set its value as  "MinGW Makefiles". It sets the default generator to be MinGW Makefiles for cmake. 
   
   1.2 **Compile SDA**
   
   Go to the SDA folder and run the following commands.
   
   ```shell
   mkdir build
   cd build
   cmake .. -G "MinGW Makefiles"
   make
   make install
   ```
   
   The above commends will install the SDA lib to c:\msys64\ming64. 
   
   1.3 **compile the examples**
   
   `cmake --build . --target build-examples`
   
   The example source files locate in the folder `examples`. The executables are compiled and save in `build/bin/examples`. 
   
   1.4 **Compile the tests**
   
   `cmake --build . --target build-tests`
   
   An executable `run_tests` will be created in `build/bin/tests`.   
   
   The tests depend on [*Catch2*]([GitHub - catchorg/Catch2: A modern, C++-native, test framework for unit-tests, TDD and BDD - using C++14, C++17 and later (C++11 support is in v2.x branch, and C++03 on the Catch1.x branch)](https://github.com/catchorg/Catch2)) version 2.3.16, which is a header only test framework for C++. 


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
