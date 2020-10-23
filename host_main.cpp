#define CL_TARGET_OPENCL_VERSION 220
#include "helloWorld_setup.h"
#include "modifyVector_setup.h"

int main(int argc, char* argv[])
{
	//hello_world();
	modify_vector();

	std::cin.get();
	return 0;
}