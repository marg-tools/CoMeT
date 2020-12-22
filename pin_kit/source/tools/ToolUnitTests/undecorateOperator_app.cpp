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

/*
 * This test verifies that Pin doesn't crash when demangling a symbol name which
 * includes the "operator" keyword.
 * We expect Pin _not_ to identify "my_operator<int>" as the "operator<" keyword
 * and thus not to change the symbol name.
 */

/*
 * This is a template function, therefore the symbol name will include the string
 * "operator<". Pin should not corrupt this string.
 */
template<class T>
int my_operator(const T& src) {
    return src;
}

int main() {
    int a = my_operator<int>(0);
    return a;
}
