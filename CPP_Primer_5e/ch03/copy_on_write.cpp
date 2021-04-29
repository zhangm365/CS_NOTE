
// 引用计数 & 写时复制
#include <iostream>
#include <string>
using namespace std;
 
int main(int argc, char **argv)
{
	string sa = "Copy on write";
	string sb = sa;
	string sc = sb;
	printf("sa char buffer address: %p\n", sa.c_str());
	printf("sb char buffer address: %p\n", sb.c_str());
	printf("sc char buffer address: %p\n", sc.c_str());
 
	sc = "Now writing...";
	printf("After writing sc:\n");
	printf("sa char buffer address: %p\n", sa.c_str());
	printf("sb char buffer address: %p\n", sb.c_str());
	printf("sc char buffer address: %p\n", sc.c_str());
 
	return 0;
}