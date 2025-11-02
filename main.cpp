#include <array>
#include <iostream>
#include <span>
#include <vector>


void method(std::span<int const> const span)
{
    std::cout << "size: " <<
        span.size()
              << std::endl;
}

int main()
{
    std::vector<int> const customVector(/*n*/ 100, /*val*/ 0);
    method(std::span<int const>(customVector));
    std::array<int, 7> const customArray{0};
    method(std::span<int const>(customArray));

    method(customVector);
    method(customArray);

    method(std::span<int const>(customVector.data(), 8));

    method(std::span{customVector.cbegin(), customVector.size()});
    method(std::span{customVector.cbegin(), customVector.cend()});

    return 0;
}
