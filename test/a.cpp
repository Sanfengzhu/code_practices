#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <bitset>  


void BinaryBitset(int n)  
{  
	std::cout << std::bitset<sizeof(int)*8>(n) << std::endl;  
}  


int main(){
	int a = 755;
	int b = 1<<9;
	BinaryBitset(a);
	BinaryBitset(b);
	BinaryBitset(a | b);
	return 0;
}
