#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <class T>
using ELEM=vector<T>;

template <class T>
using VEC=vector<ELEM<T>>;

template <class T>
using action_t = T (*) (int);

template <class T>
using pred_t = bool (*) (T);

template <class T>
using map_t = T (*) (T,T);


template <class T>
void printElem(const ELEM<T>& elems) {
    int n=elems.size(); 
    if(n<2) {
        for(int i=0; i<n; ++i) {
            cout << elems[i];
        }
    } else {
        cout << "(";
        for(int i=0; i<n; ++i) {
            cout << elems[i];
            if(i!=n-1)
                cout << " ";
        }
        cout << ")";
    }
}

template <class T>
void initVec(VEC<T>& my_vector, const ELEM<T>& elements) {
    for(const T& e : elements) {
        ELEM<T> curr{e};
        my_vector.push_back(curr);
    }    
}

template <class T>
void printVec(const VEC<T>& my_vector) {
    cout << "[ ";
    int n=my_vector.size(); 
    for(int i=0; i<n; ++i) {
        printElem(my_vector[i]);
        if(i!=n-1)
            cout << ",";
        cout << " ";
    }
    cout << "]" << endl;
}

// note: that the intended use is for vectors of the
//       same size.
template<class T>
VEC<T> zip(VEC<T> vec1, VEC<T> vec2) {
    VEC<T> ans;
    int n=vec1.size();
    for(int i=0; i<n; ++i) {
        ELEM<T> curr;
        int m=vec1[i].size();
        for(int j=0; j<m; ++j) {
            curr.push_back(vec1[i][j]);
        }
        for(int j=0; j<m; ++j) {
            curr.push_back(vec2[i][j]);
        }
        ans.push_back(curr);
    } 
    return ans;
}

int f(int n) {
    return n*n;
}

template<class T>
VEC<T> generate(int n, T(*func)(T)) {
    VEC<T> ans;
    for(int i=0; i<n; ++i) {
        ELEM<T> curr;
        int element=func(i);
        curr.push_back(element);
        ans.push_back(curr);
    }
    return ans;
}

bool g(int arg) {
    return arg>0;
}

template<class T, class U> 
VEC<T> filter(VEC<T> my_vector, U(*func)(T)) {
    VEC<T> ans; 
    for(const auto elements : my_vector) {
        ELEM<T> curr;
        for(const auto e : elements) {
            if(func(e)) 
                curr.push_back(e);
        }
        if(!curr.empty())
            ans.push_back(curr);
    }
    return ans;
}

int h(int arg) {
    return arg>0;
}

template<class T, class U>
VEC<T> map(VEC<T> my_vector, U(*func)(T)) {    
    VEC<T> ans;
    for(const auto elements : my_vector) {
        ELEM<T> curr;
        for(const auto e : elements) {
            int result=func(e);
            curr.push_back(result);
        }
        ans.push_back(curr);
    }
    return ans;
}

template<class T>
T k(ELEM<T> a, T b) {
    return a[0]+b; 
}

template<class T> 
ELEM<T> reduce(VEC<T> my_vector, T(*operation)(ELEM<T>, T), ELEM<T> starting_val) {
    ELEM<T> result=starting_val;
    for(const auto elements : my_vector) {
        for(const auto e : elements) {
            T curr=operation(result, e);
            result.clear();
            result.push_back(curr);
        }
    }
    return result;
}


int main() {

    VEC<int> v;
    initVec(v, ELEM<int>{1,2,3,4});
    VEC<int> w;
    initVec(w, ELEM<int>{-1,3,-3,4});
    printVec(v);
    cout << string(10, '*') << endl;
    printVec(w);
    cout << string(10, '*') << endl;
    VEC<int> z=zip(v, w);
    printVec(z); 
    cout << string(10, '*') << endl;
    VEC<int> x=zip(z, z);
    printVec(x);
    cout << string(10, '*') << endl;
    VEC<int> a=generate(10, f);
    printVec(a);
    VEC<int> y=filter(w, g);
    printVec(y);
    VEC<int> u=map(w,h);
    printVec(u);
    ELEM<int> e=reduce(u,k,ELEM<int>{0});
    printElem(e); cout << endl;

    cout << string(10, '$') << endl;
    VEC<string> ws;
    initVec(ws, ELEM<string>{"hello", "there", "franco", "carlacci"});
    printVec(ws);
    ELEM<string> es=reduce(ws, k, ELEM<string>{""});
    printElem(es); cout << endl;

    VEC<char> wc;
    initVec(wc, ELEM<char>{'a', 'b', 'c', 'd'});
    cout << string(10, '$') << endl;
    printVec(wc);
    ELEM<char> ec=reduce(wc, k, ELEM<char>{' '});
    cout << endl << string(10, '$') << endl;
    printElem(ec); cout << endl;

    return 0;
}
