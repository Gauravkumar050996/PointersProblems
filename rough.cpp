#include <iostream>
#include <cstddef>


using namespace std;

//void f(int) { cout << "f(int) called\n"; }
void f(char*) { cout << "f(char*) called\n"; }
//void f(std::nullptr_t) { cout << "f(nullptr_t) called\n"; }

int main() {
    // 0 is an integer literal. It selects f(int).
    f(0); // f(int)

    // NULL is a macro. In C++ it is usually defined as 0, so it behaves like integer 0.
    // This will typically call f(int).
    //f(NULL); // likely f(int)

    // nullptr is a prvalue of type std::nullptr_t and picks the nullptr overload.
    f(nullptr); // f(nullptr_t)

    // You can force a pointer overload by casting 0/NULL to a pointer type.
    f((char*)0); // f(char*)

    return 0;
}
