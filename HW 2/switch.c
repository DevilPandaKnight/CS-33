//Xiongfeng Jin
//504502689
//i'm using 2nd edition

int switch_prob(int x,int n){
	int result = x;
	switch(n){
		case 50:
		case 52:
			result <<= 2;
			break;
		case 53:
			result >>= 2;
			break;
		case 54:
			result *= 3;
		case 55:
			result *= x;
		default:
			result += 10;
	}
	return result;
}