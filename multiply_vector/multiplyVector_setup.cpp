#include "multiplyVector_setup.h"

auto print_vectors = [](std::vector<int> in, std::vector<int> out)
{
    std::cout << "Comparing vectors" << std::endl;
    for (size_t i = 0; i < in.size(); ++i)
        std::cout << std::setw(10) << in.at(i) << std::setw(10) << out.at(i) << std::endl;
};

void multiply_vector()
{
    /* inital setup the device and other stuff */
    InitialSetup SetUp("MultiplyVector.cl");
    auto context = SetUp.get_context();
    auto program = SetUp.get_program();
    auto device = SetUp.get_device();

    /* initial and show host data */
    const size_t size = 10;
    const int coef = 10;
    std::vector<int> inputVec(size);
    std::vector<int> outputVec(size);
    for (size_t i = 0; i < size; ++i) inputVec.at(i) = i;
    print_vectors(inputVec, outputVec);

    /* init device memory flags */
    auto readFlag = CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR;
    auto writeFlag = CL_MEM_WRITE_ONLY;

    /* creating buffer for data */
    cl::Buffer inputBuff(context, readFlag, sizeof(int) * size, inputVec.data());
    cl::Buffer outputBuff(context, writeFlag, sizeof(int) * size);

    /* reading the correct kernel */
    cl::Kernel kernel(program, "MultiplyVector");

    /* setting args for kernel function */
    kernel.setArg(0, inputBuff);
    kernel.setArg(1, outputBuff);
    kernel.setArg(2, sizeof(int), (void*)&coef);


    /* init command queue and run task on it */
    cl::CommandQueue queue(context, device);
    queue.enqueueWriteBuffer(inputBuff, CL_TRUE, 0, sizeof(int) * size, inputVec.data());
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(inputVec.size()));

    /* copy memory from device to host */
    queue.enqueueReadBuffer(outputBuff, true, 0, sizeof(int) * size, outputVec.data());
    cl::finish();

    /* execute the host */
    print_vectors(inputVec, outputVec);
}
