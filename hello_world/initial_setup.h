#pragma once
#include <CL/cl.hpp>
#include <string>
#include <fstream>

class InitialSetup 
{
private:
	/* 
	 * Create cl:Program built object based on
	 * kernel file pass by argument.
	 * @param const std::string&	- path to kernel file
	 * @return cl::Program			- program to run task on device
	*/
	cl::Program create_program(const std::string& file);
public:
	/* 
	* Constructor for InitialSetup clas
	* @param const std::string&	- path to kernel file 
	*/
	InitialSetup(const std::string& file);
	/* 
	* Getters for all fields
	*/
	cl::Program get_program();
	cl::Context get_context();
	cl::Device get_device();
private:
	/* binary form of cl::Program */
	cl::Program clBinaryProgram;
	/* context in which takss will be executed */
	cl::Context clContext;
	/* device on which tasks will be executed */
	cl::Device clDevice;


};
