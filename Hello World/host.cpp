
#define CL_TARGET_OPENCL_VERSION 220
#include <CL/cl.hpp>
#include <fstream>
#include<string>
#include<iostream>

int main()
{
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);
	cl::Platform platform = platforms.at(0);
	std::vector<cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
	auto device = devices.front();
	std::ifstream helloWorldFile("HelloWorld.cl");
	std::string src(std::istreambuf_iterator<char>(helloWorldFile), (std::istreambuf_iterator<char>()));
	
	cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1));

	cl::Context context(device);
	cl::Program program(context, sources);

	auto err = program.build();

	char buff[16];
	cl::Buffer memBuff(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(buff));
	cl::Kernel kernel(program, "HelloWorld", &err);
	kernel.setArg(0, memBuff);

	cl::CommandQueue queue(context, device);
	queue.enqueueTask(kernel);
	queue.enqueueReadBuffer(memBuff, true, 0, sizeof(buff), buff);
	std::cout << buff;
	std::cin.get();

	return 0;
}