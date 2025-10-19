#include <iostream>

int main()
{

#ifdef __CYGWIN__
    std::cout << "当前使用 Cygwin 编译！" << std::endl;
    std::cout << "Cygwin 版本检测通过" << std::endl;
#elif defined(__MINGW32__) || defined(__MINGW64__)
    std::cout << "当前使用 MinGW 编译！" << std::endl;
#else
    std::cout << "当前使用其他编译环境" << std::endl;
#endif

    std::cout << "Hello, World!" << std::endl;
    return 0;
}