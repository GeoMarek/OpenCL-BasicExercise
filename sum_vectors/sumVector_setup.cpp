#include "sumVector_setup.h"

void sum_vector(float* hostInput1, float* hostInput2, float* hostOutput, const uint32_t size)
{
	/* setup program, device and context */
	InitialSetup SetUp("SumVector.cl");
	auto context = SetUp.get_context();
	auto program = SetUp.get_program();
	auto device = SetUp.get_device();

	/* create  buffers in device memory */
	cl::Buffer bufferInput1(context, CL_MEM_READ_ONLY, size * sizeof(float));
	cl::Buffer bufferInput2(context, CL_MEM_READ_ONLY, size * sizeof(float));
	cl::Buffer bufferOutput(context, CL_MEM_WRITE_ONLY, size * sizeof(float));

	/* creating command queue */
	cl::CommandQueue queue(context, device, 0, 0);

	/* sending host data to device */
	queue.enqueueWriteBuffer(bufferInput1, true, 0, size * sizeof(size), (void*)hostInput1);
	queue.enqueueWriteBuffer(bufferInput2, true, 0, size * sizeof(size), (void*)hostInput2);

	/* reading the kernel */
	cl::Kernel kernel(program, "sum_vector");
	
	/* set kernel arguments */
	kernel.setArg(0, bufferInput1);
	kernel.setArg(1, bufferInput2);
	kernel.setArg(2, bufferOutput);
	kernel.setArg(3, sizeof(size), (void*)&size);

	/* setting range in device */
	cl::Event event;
	queue.enqueueNDRangeKernel(kernel, cl::NullRange, 
		cl::NDRange(size, 1), cl::NullRange, NULL, &event);
	event.wait();
	
	/* reading data from device */
	queue.enqueueReadBuffer(bufferOutput, true, 0, size * sizeof(float), (void*)hostOutput);

}
