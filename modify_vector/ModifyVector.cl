__kernel void ModifyVector(__global int* input, __global int* output)
{
	int id = get_global_id(0);
	
	if (id & 1)
	{	
		output[get_global_id(0)] = 0xFF;
	}
	else
	{
		output[get_global_id(0)] = id;
	}
}