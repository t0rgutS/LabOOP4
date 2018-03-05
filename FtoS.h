#ifndef FTOS_H
#define FTOS_H

#include "iostream"

using namespace std;

class FloatString {
    string floatStr;
    int count, point;
    bool minus;
public:
    FloatString();

    FloatString(const FloatString &fs);

    int GetCount();

    friend istream &operator>>(istream &, FloatString &);

    friend ostream &operator<<(ostream &, FloatString &);

    void operator++(int);

    void operator+(const FloatString &fs1);

    friend FloatString operator+=(FloatString &fs1, const FloatString &fs2);
};

#endif
