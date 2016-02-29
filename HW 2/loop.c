//Xiongfeng Jin
//504502689
//i'm using 2nd edition

//x in rdi, n in esi
//mask in edx, result in eax
//initial value result is 0
//initial value mask is 0
//test condition is whether mask is zero
//mask was updated by left shift by n
//result was updated by xor the mask & x

int loop(int x,int n){
	int result = 0;
	int mask;
	for (mask = 1;mask != 0;mask = mask << n)
	{
		result ^= mask & x;
	}
	return result;
}