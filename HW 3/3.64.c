//Xiongfeng Jin
//504502689
//2nd edition

//1. the word_sum function returns the struct str2, which is 8 byte big, but the return register eax has only 4 byte big. so the eax must contains the address of the struct which we return. therefore
//8(%ebp) is the address of the variable "result"
//12(%ebp) is s1.a
//16(%ebp) is s1.p


//2. the 20 bytes are for the 2 struct s1 and s2
//so the top 8 bytes is s2.sum and s2.diff
//and following it is s1.a and s1.p
//and the bottom byte is the address of s2

//3. when passing an struct to a function, we push the value in the struct to the stack
//it like each member in struct is an argument

//we store the address of the struct from the caller function to stack
//when we return, we just write the value to the struct from the caller's function
//by using the address in the stack