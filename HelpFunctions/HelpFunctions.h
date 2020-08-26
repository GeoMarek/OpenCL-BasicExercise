#pragma once
#include <CL/cl.hpp>
#include <string>
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>

cl::Program CreateProgram(const std::string& file);
void WaitForEnter();
void RandomizeArray(std::vector<int>& vec, size_t size);
void PrintArray(char* text, std::vector<int> vec);

