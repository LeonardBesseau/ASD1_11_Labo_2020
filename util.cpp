#include <iostream>
using std::cout;
using std::endl;

#include <stdexcept>

#include "util.h"

C::C(int i) : value(i), throws(0) {
    cout << " C(" << value << ") ";
}

C::C(const C& c) : value(c.value), throws(c.throws) {
    if(throws == 2) throw std::exception();
    else{
        cout << " CP(" << value << ") ";
        ++throws;
    }

}

C& C::operator= (const C& other) {
    if(throws) throw std::exception();
    value = other.value;
    throws = other.throws;
    cout << " =(" << value << ") ";
    return *this;
}

void C::enableException() { throws = true; }

C::~C() {
    cout << " D(" << value << ") ";
}

std::ostream& operator<<(std::ostream& s, const C& c) {
    s << c.value;
    return s;
}

bool C::operator==(const C &rhs) const {
    return value == rhs.value &&
           throws == rhs.throws;
}

bool C::operator!=(const C &rhs) const {
    return !(rhs == *this);
}

bool C::operator<(const C &rhs) const {
    if (value < rhs.value)
        return true;
    if (rhs.value < value)
        return false;
    return throws < rhs.throws;
}

bool C::operator>(const C &rhs) const {
    return rhs < *this;
}

bool C::operator<=(const C &rhs) const {
    return !(rhs < *this);
}

bool C::operator>=(const C &rhs) const {
    return !(*this < rhs);
}

C::C(int i, int throws):  value(i), throws(throws){}
