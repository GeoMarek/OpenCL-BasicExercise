#include "KernelPrograms.h"


void ModifyVector()
{
    // read device and init context
    auto program = CreateProgram("ModifyVector.cl");
    auto context = program.getInfo<CL_PROGRAM_CONTEXT>();
    auto devices = program.getInfo<CL_PROGRAM_DEVICES>();
    auto& device = devices.front();

    // init source data
    std::vector<int> vec(20);
    std::fill(vec.begin(), vec.end(), 1);
    PrintArray("Before:", vec);

    // init buff flags
    auto in_flags = CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR;
    auto out_flags = CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY;

    // alloc memory in GPU
    cl::Buffer in_Buff(context, in_flags, sizeof(int) * vec.size(), vec.data());
    cl::Buffer out_Buff(context, out_flags, sizeof(int) * vec.size());

    // init kernel
    cl::Kernel kernel(program, "ModifyVector");
    kernel.setArg(0, in_Buff);
    kernel.setArg(1, out_Buff);

    // init queue
    cl::CommandQueue queue(context, device);

    // run kernel
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(vec.size()));

    // read from buffer
    queue.enqueueReadBuffer(out_Buff, true, 0, sizeof(int) * vec.size(), vec.data());

    // finish
    cl::finish();
    PrintArray("After:", vec);
}

void LinearVectorCombination()
{
    // prepare program, context, device
    auto program = CreateProgram("LinearVectorCombination.cl");
    auto context = program.getInfo<CL_PROGRAM_CONTEXT>();
    auto devices = program.getInfo<CL_PROGRAM_DEVICES>();
    auto device = devices.front();

    // prepare host data
    unsigned int vec_size = 16;
    const int coef = 10;

    std::vector<int> output; 
    output.resize(vec_size);
    std::fill(output.begin(), output.end(), 1);

    std::vector<int> host_vector;
    RandomizeArray(host_vector, vec_size);

    PrintArray("Input", host_vector);
    PrintArray("Out before", output);

    // create buffer
    auto read_only = CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR;
    auto write_only = CL_MEM_WRITE_ONLY;
    cl::Buffer buff_in(context, read_only, sizeof(int) * vec_size, host_vector.data());
    cl::Buffer buff_out(context, write_only, sizeof(int) * vec_size);

    // read kernel source
    cl::Kernel kernel(program, "LinearVectorCombination");
    kernel.setArg(0, buff_out);
    kernel.setArg(1, buff_in);
    kernel.setArg(2, sizeof(int), (void*)&coef);

    // create command queue
    cl::CommandQueue queue(context, device);
    queue.enqueueWriteBuffer(buff_in, CL_TRUE, 0, sizeof(int) * vec_size, host_vector.data());
    
    // run kernel
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(vec_size));

    // read from buff
    queue.enqueueReadBuffer(buff_out, true, 0, sizeof(int) * vec_size, output.data());
    
    // finish
    cl::finish(); 
    PrintArray("After", output);
}

void HelloWorld()
{
    auto program = CreateProgram("HelloWorld.cl");
    auto context = program.getInfo<CL_PROGRAM_CONTEXT>();
    auto devices = program.getInfo<CL_PROGRAM_DEVICES>();
    auto device = devices.front();

    char buff[16];
    cl::Buffer memBuff(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(buff));
    cl::Kernel kernel(program, "HelloWorld");
    kernel.setArg(0, memBuff);

    cl::CommandQueue queue(context, device);
    queue.enqueueTask(kernel);
    queue.enqueueReadBuffer(memBuff, true, 0, sizeof(buff), buff);
    std::cout << buff;
}


