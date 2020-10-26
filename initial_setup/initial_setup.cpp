#include "initial_setup.h"

cl::Program InitialSetup::create_program(const std::string& file)
{
    /* get platform */
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    auto platform = platforms.front();

    /* get device */
    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
    auto device = devices.front();

    /* read kernel data from file */
    std::ifstream kernelFile(file);
    std::string kernelString(std::istreambuf_iterator<char>(kernelFile), (std::istreambuf_iterator<char>()));
    auto kernelData = std::make_pair(kernelString.c_str(), kernelString.length() + 1);
    
    /* init object with kernel data */
    cl::Program::Sources sources(1, kernelData);

    /* create program and context */
    cl::Context context(device);
    cl::Program program(context, sources);

    /* create binary form of the program */
    program.build();

    return program;
}

InitialSetup::InitialSetup(const std::string& file)
{
    /* set all class fields */
    this->clBinaryProgram = create_program(file);
    this->clContext = clBinaryProgram.getInfo<CL_PROGRAM_CONTEXT>();
    this->clDevice = clBinaryProgram.getInfo<CL_PROGRAM_DEVICES>().front();
}

cl::Program InitialSetup::get_program()
{
    return this->clBinaryProgram;
}

cl::Context InitialSetup::get_context()
{
    return this->clContext;
}

cl::Device InitialSetup::get_device()
{
    return this->clDevice;
}

