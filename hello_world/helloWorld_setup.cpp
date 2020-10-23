#include "helloWorld_setup.h"
#include <iostream>

void hello_world()
{
    /* inital setup the device and other stuff */
    InitialSetup SetUp("HelloWorld.cl");
    auto context = SetUp.get_context();
    auto program = SetUp.get_program();
    auto device = SetUp.get_device();

    /* initial host buffer */
    char hostBuffer[16];

    /* creating buffer for data */
    cl::Buffer memoryBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(hostBuffer));

    /* reading the correct kernel */
    cl::Kernel kernel(program, "HelloWorld");

    /* setting args for kernel function */
    kernel.setArg(0, memoryBuffer);

    /* init command queue and run task on it */
    cl::CommandQueue queue(context, device);
    queue.enqueueTask(kernel);

    /* copy memory from device to host */
    queue.enqueueReadBuffer(memoryBuffer, true, 0, sizeof(hostBuffer), hostBuffer);

    /* execute the host */
    std::cout << hostBuffer;
}
