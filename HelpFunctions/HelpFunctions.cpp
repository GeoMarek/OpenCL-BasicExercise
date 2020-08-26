#include "HelpFunctions.h"



cl::Program CreateProgram(const std::string& file)
{
    {
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);
        
        auto platform = platforms.front();
        std::vector<cl::Device> devices;
        platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
        
        auto device = devices.front();

        std::ifstream kernelFile(file);
        std::string kernelSource(std::istreambuf_iterator<char>(kernelFile), (std::istreambuf_iterator<char>()));

        cl::Program::Sources sources(1, std::make_pair(kernelSource.c_str(), kernelSource.length() + 1));
        
        cl::Context context(device);
        cl::Program program(context, sources);

        program.build();
        return program;
    }
}


void WaitForEnter()
{
    std::cout << "\nPress enter to end\n";
    std::cin.get();
}


void PrintArray(char* text, std::vector<int> vec)
{
    std::cout << text << std::endl;
    for (auto& it : vec)
    {
        std::cout << std::left << std::setw(4) << it;
    }
    std::cout << std::endl;
}


void RandomizeArray(std::vector<int>& vec, size_t size)
{
    for (size_t i = 0; i < size; ++i) vec.push_back(i);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));
}


