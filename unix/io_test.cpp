#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    std::ifstream is("pid.c");
    while (is.good()) {
        std::string l;
        std::getline(is, l, '\t');
        std::cout << l << " " << l.size() << " " << l.empty() << std::endl;
    }
    int out = atoi("2147483648");
    assert(out < 0);
    std::cout << out << std::endl;
    is.close();
    return 0;
}
