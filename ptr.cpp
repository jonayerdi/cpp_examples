#include <iostream> /* cout */
#include <string> /* string */
#include <memory> /* unique_ptr, make_unique */

using namespace std;

class MyClass 
{
private:
    string name;
public:
    MyClass(string name) {
        this->name = name;
        cout << *this << " constructor" << endl;
    }
    ~MyClass() {
        cout << *this << " destructor" << endl;
    }
    friend ostream& operator<<(ostream& os, const MyClass& obj) {
        os << "MyClass(" << obj.name << ")";
        return os;
    }
};

// Move function
void moveFunction(unique_ptr<MyClass> myObject) {
    cout << "moveFunction(" << *myObject << ")" << endl;
}

int main() {
    unique_ptr<MyClass> unique = make_unique<MyClass>("unique");
    moveFunction(std::move(unique));
    cout << "End of program" << endl;
}
