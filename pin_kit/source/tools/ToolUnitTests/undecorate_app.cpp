/*
 * Copyright 2002-2019 Intel Corporation.
 * 
 * This software is provided to you as Sample Source Code as defined in the accompanying
 * End User License Agreement for the Intel(R) Software Development Products ("Agreement")
 * section 1.L.
 * 
 * This software and the related documents are provided as is, with no express or implied
 * warranties, other than those that are expressly stated in the License.
 */

/* This application does nothing
 * It is used only for checking symbol demangling feature
 */
#include <vector>
#include <string>
using std::vector;
using std::string;


class A
{
 public:
    void MyMethod1(const vector<int>& param1) {}
    void MyMethod2(string param2) {}
    void MyMethod3(string param3) const {}
};

template<class T> T MyMethod(T & arg) { return arg; }

template<class B> class MyMethod1 : public B
{
 public:
    MyMethod1() {}
};

void Foo()
{
    int i;
    volatile int *ip = (volatile int *)&i;

    *ip = 0;
}

// If you add new names, then update undecorate.cpp as well, so that it knows about them...
int main()
{
    A a;
    MyMethod1<A> goo;
    vector<int> v;
    v.push_back(1);

    a.MyMethod1(v);
    a.MyMethod2("MyString");
    a.MyMethod3("Foo");
    MyMethod(a);

    Foo();

    return 0;
}
