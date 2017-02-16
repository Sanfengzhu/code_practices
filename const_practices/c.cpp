#include "common.h"

void func_c_a(){
	/* 变量 */
	// 非常量的是否有初始值随意
	int ia;
	int ib = 1;

	/* 常量 */
	// 常量类型必须有个默认的初始值
	// const int ic0;
	const int ic = ib;
	// 常量初始化以后不能妄图改变其值
	// ic++; error
	
	// 时刻记住引用不是对象，引用就是个别称 
	const int &rc = ic;
	// rc++; error

	/* 指向常量的指针 */
	// 指向常量的指针，由右向左读，首先是cp指针，指向的是int类型，再看是个常量。
	// 引用rc就是ic的别名
	const int *cp = &rc;
	const int ic1 = 3;
	// 指向常量的指针，不是说它自己不能变，是说它指的那个东西不能通过它变
	// (*cp)++; // error: 妄图改变ic的值
	cp = &ic1;  // 指向一个新的常量，完全没问题。
	
	// 指向一个新的变量，也没问题。这时候变量ia还是可以变化的，
	// 只是cp以为ia是常量，不会通过自己来改变ia
	cp = &ia;
	ia = 12;
	// *cp = 13;
	
	/* 常量指针 */
	// 从右向左读，首先是个常量（隐含得初始化，其之后不能变），然后是指针，这个指针指向了int
	// 也就是指向int类型的常量指针
	int *const icp = &ia;
	// int *const icp1; // error: 没有初始化
	// icp++;// error: 不能再赋值
	(*icp)++; // 指向的int类型随意变
	// 不要用指向变量的指针，指向一个常量。
	// int *const icp2 = &ic; // error
	// 但是指向常量的常量指针可以指向变量
	const int *const icp2 = &ia;
	// 虽然有一个指向常量的常量指针，指向变量ia，但是并不影响变量ia通过其他渠道来改变。
	ia=15;
	printf("%d\n", *icp2);
}
