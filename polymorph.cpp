#include <iostream>

using namespace std;

class Base
{
private:
    int x;
protected:
    int y;
public:
    int z;

    Base(int x, int y, int z) : x{x}, y{y}, z{z} {}
    virtual int pureVirtualFn() = 0;
    virtual int virtualFn() {
        return x + y + z;
    }
    int nonVirtualFn() {
        return x + y + z;
    }
};

class Derived1 : public Base
{
public:
    Derived1(int x, int y, int z) : Base(x, y, z) {}
    int pureVirtualFn() {
        return y - z;
    }
    int virtualFn() {
        return y - z;
    }
    int nonVirtualFn() {
        return y - z;
    }
};

class Derived2 : public Base
{
public:
    Derived2(int x, int y, int z) : Base(x, y, z) {}
    int pureVirtualFn() {
        return z - y;
    }
    int nonVirtualFn() {
        return z - y;
    }
};

int main() {
    // Base b{1,2,3}; // cannot instantiate abstract class
    Derived1 d1{1,2,3};
    Derived2 d2{1,2,3};
    Base& d1b = d1;
    Base& d2b = d2;
    cout << "Derived1 " << "pureVirtualFn " << d1.pureVirtualFn() << endl;
    cout << "Derived1(Base) " << "pureVirtualFn " << d1b.pureVirtualFn() << endl;
    cout << "Derived1 " << "virtualFn " << d1.virtualFn() << endl;
    cout << "Derived1(Base) " << "virtualFn " << d1b.virtualFn() << endl;
    cout << "Derived1 " << "nonVirtualFn " << d1.nonVirtualFn() << endl;
    cout << "Derived1(Base) " << "nonVirtualFn " << d1b.nonVirtualFn() << endl;
    cout << "Derived2 " << "pureVirtualFn " << d2.pureVirtualFn() << endl;
    cout << "Derived2(Base) " << "pureVirtualFn " << d2b.pureVirtualFn() << endl;
    cout << "Derived2 " << "virtualFn " << d2.virtualFn() << endl;
    cout << "Derived2(Base) " << "virtualFn " << d2b.virtualFn() << endl;
    cout << "Derived2 " << "nonVirtualFn " << d2.nonVirtualFn() << endl;
    cout << "Derived2(Base) " << "nonVirtualFn " << d2b.nonVirtualFn() << endl;
}
