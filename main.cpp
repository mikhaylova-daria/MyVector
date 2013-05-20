
#ifndef STDLIB_H
#include <stdlib.h>
#endif
#ifndef VECTOR_H
#include "Vector.h"
#endif
#ifndef _IOSTREAM
        #include <iostream>
        #define  _IOSTREAM
#endif
using namespace std;

int main()
{
    my::vector<int> a;
    for (int i=0; i<4;++i) {
        int n;
        std::cin>>n;
        a.push_back(n);
    }
    my::vector<int> b(a);
    a.output();
    b.output();
    my::vector<int> c = b;
    c.output();
    my::vector<int> l(4);
    for (int i=0; i<4;++i) {
        int n;
        std::cin>>n;
        l.push_back(n);
    }
    l.output();

   my::vector<bool> g(30);
    for (int i=0; i<30; ++i){
        if (i % 2 == 0) {g.push_back(true);} else {
        g.push_back(false);
        }
    }
    g.output();
    my::vector<bool> h = g;
    cout << "@"<<(h == g)<<"@";
    h.set(true, 30);
    h.set(false,2);
    h.set(false, 3);
    cout<<"!!"<<h[2]<<"!!"<<h[3]<<"!!"<<h[30]<<endl;
    h.output();
    cout<< "@"<<(h != g)<<"@";
    cout<<h.size_of_vector();
    return 0;
}
