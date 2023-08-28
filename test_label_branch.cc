#include <iostream>

int test_label() {
    int i = 0;
 inc:
    i = i + 1;

    if (i < 10)
        goto inc;

    return i;
}

int main(int argc, char *argv[])
{
    std::cout << test_label() << std::endl;
    return 0;
}
