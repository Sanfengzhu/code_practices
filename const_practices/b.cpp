#include "common.h"

const int a = 12; // 只在当前文件有效，定义并且必须初始化

//extern const int b = 12; //error 重定义
extern const int b; // 只需要再声明一次即可

void func_b(){
	printf("func_b\ta=%d\n", a);
	printf("func_b\tb=%d\n", b);
}
