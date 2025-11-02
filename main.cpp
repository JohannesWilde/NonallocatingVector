#include <cstdlib>
#include <iostream>
#include <span>
#include <vector>


void method(std::span<int, std::dynamic_extent> const span)
{
    std::cout << "bla: " <<
        span.size()
              << std::endl;
}

int main()
{
    std::vector<int> owningVector(/*n*/ 100, /*val*/ 0);
    method(std::span<int, std::dynamic_extent>(owningVector));
    return 0;
}
