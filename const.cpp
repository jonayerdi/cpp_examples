#include <iostream>
#include <vector>

using namespace std;

double sum(const vector<double>& nums) 
{
    double sum {0.0};
    for(double n : nums) {
        sum += n;
    }
    return sum;
}

constexpr double square(double x) { return x*x; }

int main()
{
    vector<double> v { 1.2, 3.4, 4.5 };
    const double s1 = sum(v); // OK: evaluated at run time
    //constexpr double s2 = sum(v); // error : sum(v) not constant expression
    cout << s1 << endl;
    constexpr auto sq1 = square(1.3); // OK: evaluated at compile time
    const auto sq2 = square(v[1]); // OK: evaluated at run time
    cout << sq1 << endl;
    cout << sq2 << endl;
}
