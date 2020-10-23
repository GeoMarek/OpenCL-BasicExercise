__kernel void MultiplyVector(
	__global int* out_arr, 
	__global const int* in_arr1,
	const int a
	)
{
	int id = get_global_id(0);
	out_arr[id] = a;
}
