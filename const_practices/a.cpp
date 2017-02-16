#include "common.h"

// 默认只在当前文件中生效，其他文件中可以定义同名const int，互不影响
const int a = 10;
// 需要在多个文件中都生效，用extern关键字
extern const int b = 10;

void func_a(){
	printf("func_a\ta=%d\n", a);
	printf("func_a\tb=%d\n", b);
}

int main(){
	func_a();	
	func_b();
	return 0;
}
