#include "modifyVector_setup.h"


/* lambda function to print std::vector<int> */
auto print = [](std::vector<int> vec, char* info) 
{
    std::cout << info << std::endl;
    for (auto& it : vec)
    {
        std::cout << std::left << std::setw(4) << it;
    }
    std::cout << std::endl;
};

void modify_vector()
{
    /* inital setup the device and other stuff */
    InitialSetup SetUp("ModifyVector.cl");
    auto context = SetUp.get_context();
    auto program = SetUp.get_program();
    auto device = SetUp.get_device();

    /* initial and show host data */
    std::vector<int> vec(20);
    //std::fill(vec.begin(), vec.end(), );
    print(vec, "Before");
 
    /* init device memory flags */
    auto in_flags = CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR;
    auto out_flags = CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY;

    /* creating buffer for data */
    cl::Buffer in_Buff(context, in_flags, sizeof(int) * vec.size(), vec.data());
    cl::Buffer out_Buff(context, out_flags, sizeof(int) * vec.size());

    /* reading the correct kernel */
    cl::Kernel kernel(program, "ModifyVector");

    /* setting args for kernel function */
    kernel.setArg(0, in_Buff);
    kernel.setArg(1, out_Buff);

    /* init command queue and run task on it */
    cl::CommandQueue queue(context, device);
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(vec.size()));

    /* copy memory from device to host */
    queue.enqueueReadBuffer(out_Buff, true, 0, sizeof(int) * vec.size(), vec.data());
    cl::finish();

    /* execute the host */
    print(vec, "After");
}
