#ifndef VECTOR_H
#define VECTOR_H
    #ifndef _IOSTREAM
        #include <iostream>
        #define  _IOSTREAM
    #endif
    #ifndef _NEW
        #include <new>
        #define  _NEW
    #endif
    #ifndef MATH_H
        #include <math.h>
        #define MATH_H
    #endif
    namespace  my {
    template <typename T> class vector;
    template <> class my::vector<bool>;
    }

    template <typename T> class my::vector
    {
        T *p_vector;
        int  size;
        int capacity;
    public:
        vector();
        vector (int const & _capacity);
        vector (vector const &a);
        ~vector();
        int push_back (T const & new_);
        const int &size_of_vector() const;
        void output () const;
        T &operator [] (const int &pos);
        const T &operator [] (const int &pos) const;
        my::vector<T> &operator = (my::vector<T> const& a);
        bool operator == (my::vector<T> const&a) const;
        bool operator != (my::vector<T> const& a) const;
        };

    template <> class my::vector<bool>{
        char* p_vector;
        int  size;
        int capacity;


    public:
        struct get{
        char* p_vector;
        char mask;
        int pos;
        void operator =(bool _new){
            if (_new == false){
                char ch = p_vector[pos / 8] & (255 - mask);
                this->p_vector[pos/8] = ch;
            } else {
                char ch = p_vector[pos / 8] | mask;
                this->p_vector[pos/8] = ch;
            }
            return;
        }
        };
        vector() ;
        vector(const int & _capacity);
        vector (vector const &a);
        ~vector();
        int push_back(bool const &new_);
        int size_of_vector() const;
        void output() const;
        get operator [] (const int &pos);
        bool operator [] (const int &pos) const;
        //int operator [] (const int &pos);
        void set(const bool &_new, const int &pos);
        my::vector<bool> &operator = (my::vector<bool> const& a);
        bool operator == (my::vector<bool> const&a) const;
        bool operator != (my::vector<bool> const& a)const;
    };
    #include "Vector2.h"
#endif
