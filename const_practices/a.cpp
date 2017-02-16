#include "common.h"
#include <string>

// 默认只在当前文件中生效，其他文件中可以定义同名const int，互不影响
const int a = 10;
// 需要在多个文件中都生效，用extern关键字
extern const int b = 10;

// const 类型变量可以用函数动态初始化
const int c = func_c();

// const 类型变量动态初始化函数返回值可以做隐式类型转换
const int d = func_d();

// 注意：并不是所有时候都可以默认转换的
//const char f = func_f();

int func_c(){
	printf("init const int c by func_c \n");
	return 15;
}

double func_d(){
	printf("init const int c by func_d return double type variable\n");
	return 1005.5;
}

void func_e(){
	// 函数内定义的const只在函数被调用的时候才完成定义和初始化的过程。
	const int e = func_c();
	printf("func_e\te=%d\n", e);
}

std::string func_f(){
	return "aaa";
}

void func_a(){
	printf("func_a\ta=%d\n", a);
	printf("func_a\tb=%d\n", b);
	printf("func_a\tc=%d\n", c);
	printf("func_a\td=%d\n", d);
	// 在函数中定义的 const 变量只在函数作用域中生效
	// printf("func_a\td=%d\n", e);
}

int main(){
	// const 变量会先初始化
	printf("call main function\n");
	func_a();	
	func_b();
	func_e();
	return 0;
}
