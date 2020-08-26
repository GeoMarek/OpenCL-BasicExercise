# OpenCL-BasicExercise

A collection of basic programs written as part of OpenCL learning in C++. 

In the *HelpFunctions* folder there are files containing helpful functions, e.g.

- void RandomizeArray(vector\<int> vec, size_t size) or 
- cl::Program CreateProgram(const string& file)

The *KernelFile* folder contains files with source code written in OpenCL C.  Host-running programs have been converted into functions and saved in the *KernelPrograms.cpp* file.  They can be called in the *host.cpp* file.

1. Hello World
2. Modify every second vector element
3. Linear multiplication of the vector i.e. A = x*B
