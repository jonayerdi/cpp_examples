#include <iostream>
#include <complex>

void basic() 
{
    double d1 {2.5}, d2 {4.3};
    std::cout << d1 << "*" << d2 << "=" << d1*d2 << std::endl;
}

void complex() 
{
    std::complex<double> z1 = {2};
    std::complex<double> z2 = {1.4,1.2};
    std::cout << z1*z2 << std::endl;
}

void initializers()
{
    auto x = true;
    static_cast<void>(x);
    //int a = 1.2; // warning : floating-point to integer conversion
    //int b {0.2}; // error : floating-point to integer conversion
}

int main()
{
    basic();
    complex();
}
