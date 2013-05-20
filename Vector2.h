#ifndef STDLIB_H
#include <stdlib.h>
#endif
#ifndef VECTOR_H
#include <Vector.h>
#endif
using namespace std;

    template <typename T>
    my::vector<T>::vector() :size(0), capacity(1) {			//кидает 1 в случае ошибки
    try {
        p_vector = static_cast <T*> (::operator new (sizeof(T) * capacity));
            new(p_vector)T();
    } catch(std::bad_alloc &ba) {
            std::cerr << "bad_alloc caught: " << ba.what() << '\n';
            throw(ba);
    }
    }

    template <typename T>
    my::vector<T>::vector (const int  &_capacity): size(0), capacity(_capacity) {
        p_vector = static_cast <T*> (::operator new (sizeof(T) * _capacity));;
        for (int i = 0; i < _capacity; ++i) {
            new (p_vector + i) T();
        }
    }
    template <typename T>
    my::vector<T>::vector (my::vector<T> const &a) : size(a.size), capacity(a.capacity) {
        p_vector = static_cast <T*> (::operator new (sizeof(T) * capacity));
        for (int i = 0; i < a.size; ++i) {
            new (p_vector + i) T(a.p_vector[i]);
        }
    }

    template <typename T>
    my::vector<T>::~vector(){
        for (int i = 0; i < this->size; ++i){
            p_vector[i].~T();
        }
        delete[] (p_vector);
    }
    template <typename T>
    int my::vector<T>::push_back (T const &new_){ // кидает bad_alloc
        if (size == capacity) {
            T* placementMemory;
            try{
                placementMemory = static_cast <T*> (::operator new (sizeof(T) * capacity * 2));
            } catch (std::bad_alloc& ba) {
                 std::cerr << "bad_alloc caught: " << ba.what() << '\n';
                 throw(ba);
            }
            for (int i = 0; i < capacity; ++i) {
                 new (placementMemory+i) T(p_vector[i]) ;
                 p_vector[i].~T();
            }
            delete[] (p_vector);
            p_vector = placementMemory;
            capacity *= 2;
        }
        new (p_vector + size) T(new_) ;
        ++size;
        return 0;
    }

    template <typename T>
    const int& my::vector<T>::size_of_vector() const{
        return size;
    }

    template <typename T>
    void my::vector<T>::output () const
    {
        for (int i=0; i < size; ++i) {
            std::cout<<p_vector[i]<<" ";
        }
        std::cout<<std::endl;
        return;
    }


    template <typename T>
    T& my::vector<T>::operator [] (const int &pos) {
        if (pos >= size) {
            std::cerr<<"Не существует элемента с указанным номером!!!"<<std::endl;//Кидает строчку ,bad_index
            throw ("bad_index");
            return p_vector[0];
        }
        return p_vector[pos];
    }

    template <typename T>
    const T& my::vector<T>::operator [] (int pos) const {
        if (pos >= size) {
            std::cerr<<"Не существует элемента с указанным номером!!!"<<std::endl;//Кидает строчку ,bad_index
            throw ("bad_index");
            return p_vector[0];
        }
        return p_vector[pos];
    }

    template <typename T>
    my::vector<T>& my::vector<T>::operator = (const my::vector<T> & a) {
        size=a.size;
        capacity=a.capacity;
        delete[](p_vector);
        p_vector = static_cast <T*> (::operator new (sizeof(T) * capacity));
        for (int i = 0; i < a.size; ++i) {
            new (p_vector + i) T(a.p_vector[i]);
        }
        return *this;
    }

    template <typename T>
    bool my::vector<T>::operator == (my::vector<T> const&a) const {
        if (a.size == this -> size) {
            int i = 0;
            while (i < a.size) {
                if (a.p_vector [i] != this -> p_vector[i]) {
                    return false;
                }
                ++i;
            }
            return true;
        } else {
            return false;
        }
    }

    template <typename T>
    bool my::vector<T>::operator != (my::vector<T> const& a) const{
        return (!(*this == a));
    }



    my::vector<bool>::vector() :size(0), capacity(1) {
    try {
        p_vector = static_cast <char*> (::operator new (sizeof(char) * capacity));
        new (p_vector) char(255);
    } catch(std::bad_alloc &ba) {
            std::cerr << "bad_alloc caught: " << ba.what() << '\n';
            throw(ba);
    }
    }

    my::vector<bool>::vector(const int & _capacity): size(0), capacity(_capacity / sizeof(char)+1) {	//кидает 1 в случае неуспеха
        try{
            p_vector = static_cast <char*> (::operator new (sizeof(char) * capacity));
        } catch(std::bad_alloc& ba) {
            std::cerr << "bad_alloc caught: " << ba.what() << '\n';
            throw(ba);
        }
        for (int i = 0; i < capacity; ++i) {
            new(p_vector+i)char(255);
        }
    }

    my::vector<bool>::vector (my::vector<bool> const &a) : size(a.size), capacity(a.capacity) {
        p_vector = static_cast <char*> (::operator new (sizeof(char) * capacity));
        for (int i = 0; i < a.size; ++i) {
            new (p_vector + i) char(a.p_vector[i]);
        }
    }

    my::vector<bool>::~vector() {
        for (int i = 0; i < this->size; ++i) {
            ~p_vector[i];
        }
        delete[](p_vector);
    }

    int my::vector<bool>::push_back(bool const &new_){ //0 -успешное завершение, 1- неуспешное
        if ((size * 8) == capacity) {
            char* placementMemory;
            try{
                placementMemory = static_cast <char*> (::operator new (sizeof(char) * capacity * 2)) ;
            } catch (std::bad_alloc& ba) {
                std::cerr << "bad_alloc caught: " << ba.what() << '\n';
                throw(ba);
            }
            for (int i = 0; i < capacity; ++i) {
                new (placementMemory + i) char(p_vector[i]);
            }
            delete[] (p_vector);
            for (int i = capacity; i < 2 * capacity; ++i) {
                new(placementMemory + i) char(255);
            }
            p_vector = placementMemory;
            capacity *= 2;
        }
        if (new_ == false) {
            int pow_ = 8-1-(size % 8);
            p_vector[size / 8] =p_vector[size / 8] & (255 - (int)pow((float)2,(int)pow_));
        }
        ++size;
        return 0;
    }


    const int & my::vector<bool>::size_of_vector() const{
        return size;
    }

    void my::vector<bool>::output() const{
        int masc = 128;
        int j = 0;
        for (int i=0; i<size; ++i){
            if (masc == 0) {
                masc = 128;
                ++j;
            }
            int buf = p_vector[j] & masc;
            if (buf == 0) {
                std::cout<<0;
            } else {
                std::cout<<1;
            }
            masc = masc>>1;
        }
        std::cout<<"\n";
    }

    int my::vector<bool>::operator [] (const int & pos) {		//кидает строчку bad_index в случае неудачи
        char mask = pow((float)2, (int)(8 - pos));
        if (pos >= size) {
            std::cerr<<"Не существует элемента с указанным номером!!!"<<std::endl;//Кинуть исключение?
            throw ("bad_index");
            return p_vector[0];
        }
        int buf = p_vector[pos/8] & mask;
        if (buf > 0){
            return 1;
        } else {
            return 0;
        }
    }

    void  my::vector<bool>::set(const bool &_new, const int &pos){
        if (capacity * 8 < pos) {
            char* placementMemory;
            try{
                placementMemory = static_cast <char*> (::operator new (sizeof(char) * capacity * 2));
            } catch (std::bad_alloc& ba) {
                std::cerr << "bad_alloc caught: " << ba.what() << '\n';
                throw(ba);
            }
            for (int i = 0; i < capacity; ++i) {
                new (placementMemory + i) char (p_vector[i]);
            }
            delete[] (p_vector);
            for (int i = capacity; i < 2 * capacity; ++i) {
                    new (placementMemory + i) char (255);
            }
            p_vector = placementMemory;
            capacity *= 2;
        }
        if (size <= pos){
            size = pos + 1;
        }
        int pow_ = 8-1 -(pos % 8);
        int c=255 - (int)pow((float)2,(int)pow_);
        cout<<pos<<" "<<pow_<<" "<<c<<std::endl;
        if (_new == false){
            char ch = p_vector[pos / 8] & (255 - (int)pow((float)2,(int)pow_));
            this->p_vector[pos/8] = ch;
        }
        std::cout<<size<<"\n";
        return;
    }


     my::vector<bool>& my::vector<bool>::operator = (const my::vector<bool> & a){
        size=a.size;
        capacity=a.capacity;
        delete[](p_vector);
        p_vector = static_cast <char*> (::operator new (sizeof(char) * capacity));
        for (int i = 0; i < a.size; ++i) {
            new (p_vector + i) char(a.p_vector[i]);
        }
        return *this;
    }

    bool  my::vector<bool>::operator == (my::vector<bool> const&a) const{
        if (a.size == this -> size) {
            int i = 0;
            while (i < a.size) {
                if (a.p_vector [i] != this -> p_vector[i]) {
                    return false;
                }
                ++i;
            }
            return true;
        } else {
            return false;
        }
    }


    bool  my::vector<bool>::operator != (my::vector<bool> const& a) const{
        return (!(*this == a));
    }

/*#ifndef STDLIB_H
#include <stdlib.h>
#endif
#ifndef VECTOR_H
#include "Vector.h"
#endif
using namespace std;

    template <typename T>
    my::vector<T>::vector() :size(0), capacity(1) {			//кидает 1 в случае ошибки
    try {
        p_vector = new T[1];
    } catch(std::bad_alloc) {
        std::cerr<<"Ошибка при выделении памяти"<<std::endl;
        throw (1);
    }
    }

    template <typename T>
    my::vector<T>::vector (int _capacity): size(0), capacity(_capacity) {
        p_vector = static_cast <T*> (::operator new (sizeof(T) * _capacity));;
        for (int i = 0; i < _capacity; ++i) {
            new (p_vector + i) T();
        }
    }
    template <typename T>
    my::vector<T>::vector (my::vector<T> const &a) : size(a.size), capacity(a.capacity) {
        p_vector = static_cast <T*> (::operator new (sizeof(T) * capacity));
        for (int i = 0; i < a.size; ++i) {
            new (p_vector + i) T(a.p_vector[i]);
        }
    }

    template <typename T>
    my::vector<T>::~vector(){
        delete[] (p_vector);
    }
    template <typename T>
    int my::vector<T>::push_back (T const new_){ //0 -успешное завершение, 1- неуспешное
        if (size == capacity) {
            T* placementMemory;
            try{
                placementMemory = new T [2 * capacity];
            } catch (std::bad_alloc& ba) {
                 std::cerr << "bad_alloc caught: " << ba.what() << '\n';
                 return 1;
            }
            for (int i = 0; i < capacity; ++i) {
                placementMemory[i] = p_vector[i];
                ~p_vector[i];
            }
            delete[] (p_vector);
            for (int i = capacity; i < 2 * capacity; ++i) {
                    placementMemory[i] = T();
            }
            p_vector = placementMemory;
            capacity *= 2;
        }
        p_vector[size] = new_;
        ++size;
        return 0;
    }

    template <typename T>
    const int& my::vector<T>::size_of_vector(){
        return size;
    }

    template <typename T>
    void my::vector<T>::output ()
    {
        for (int i=0; i < size; ++i) {
            std::cout<< p_vector[i]<<" ";
        }
        std::cout<<std::endl;
        return;
    }

    template <typename T>
    T& my::vector<T>::operator [] (int pos) {
        if (pos >= size) {
            std::cerr<<"Не существует элемента с указанным номером!!!"<<std::endl;//Кидает строчку ,bad_index
            throw ("bad_index");
            return p_vector[0];
        }
        return p_vector[pos];
    }

    template <typename T>
    const T& my::vector<T>::operator [] (int pos) const {
        if (pos >= size) {
            std::cerr<<"Не существует элемента с указанным номером!!!"<<std::endl;//Кидает строчку ,bad_index
            throw ("bad_index");
            return p_vector[0];
        }
        return p_vector[pos];
    }

    template <typename T>
    my::vector<T>& my::vector<T>::operator = (const my::vector<T> & a) {
        size=a.size;
        capacity=a.capacity;
        delete[](p_vector);
        p_vector = static_cast <T*> (::operator new (sizeof(T) * capacity));
        for (int i = 0; i < a.size; ++i) {
            new (p_vector + i) T(a.p_vector[i]);
        }
        return *this;
    }

    template <typename T>
    bool my::vector<T>::operator == (my::vector<T> const&a) {
        if (a.size == this -> size) {
            int i = 0;
            while (i < a.size) {
                if (a.p_vector [i] != this -> p_vector[i]) {
                    return false;
                }
                ++i;
            }
            return true;
        } else {
            return false;
        }
    }

    template <typename T>
    bool my::vector<T>::operator != (my::vector<T> const& a) {
        return (!(*this == a));
    }



    my::vector<bool>::vector() :size(0), capacity(1) {
    try {
        p_vector = new char[1];
    } catch(std::bad_alloc) {
        std::cerr<<"Ошибка при выделении памяти"<<std::endl;
    }
    }

    my::vector<bool>::vector(int _capacity): size(0), capacity(_capacity) {	//кидает 1 в случае неуспеха
        try{
         p_vector = new char [size];
        } catch(std::bad_alloc& ba) {
                 std::cerr << "bad_alloc caught: " << ba.what() << '\n';
                 throw (1);
        }
        for (int i = 0; i < _capacity; ++i) {
            p_vector [i] = 255;
        }
    }

    my::vector<bool>::vector (my::vector<bool> const &a) : size(a.size), capacity(a.capacity) {
        p_vector = static_cast <char*> (::operator new (sizeof(char) * capacity));
        for (int i = 0; i < a.size; ++i) {
            new (p_vector + i) char(a.p_vector[i]);
        }
    }

    my::vector<bool>::~vector() {
        delete[](p_vector);
    }

    int my::vector<bool>::push_back(bool const new_){ //0 -успешное завершение, 1- неуспешное
        if ((size * 8) == capacity) {
            char* placementMemory;
            try{
                placementMemory = new  char [2 * capacity] ;
            } catch (std::bad_alloc& ba) {
                 std::cerr << "bad_alloc caught: " << ba.what() << '\n';
                 return 1;
            }
            for (int i = 0; i < capacity; ++i) {
                placementMemory[i] = (char) p_vector[i];
            }
            delete[] (p_vector);
            for (int i = capacity; i < 2 * capacity; ++i) {
                    placementMemory[i] = 255;
            }
            p_vector = placementMemory;
            capacity *= 2;
        }
        if (new_ == false) {
            int pow_ = 8-1-(size % 8);
            p_vector[size / 8] =p_vector[size / 8] & (255 - (int)pow((float)2,(int)pow_));
        }
        ++size;
        return 0;
    }


    const int & my::vector<bool>::size_of_vector(){
        return size;
    }

    void my::vector<bool>::output(){
        int masc = 128;
        int j = 0;
        for (int i=0; i<size; ++i){
            if (masc == 0) {
                masc = 128;
                ++j;
            }
            int buf = p_vector[j] & masc;
            if (buf == 0) {
                std::cout<<0;
            } else {
                std::cout<<1;
            }
            masc = masc>>1;
        }
        std::cout<<"\n";
    }

    int my::vector<bool>::operator [] (int pos) {		//кидает строчку bad_index в случае неудачи
        char mask = pow((float)2, (int)(8 - pos));
        if (pos >= size) {
            std::cerr<<"Не существует элемента с указанным номером!!!"<<std::endl;//Кинуть исключение?
            throw ("bad_index");
            return p_vector[0];
        }
        int buf = p_vector[pos/8] & mask;
        if (buf > 0){
            return 1;
        } else {
            return 0;
        }
    }

    void  my::vector<bool>::set(bool _new, int pos){
        if (capacity * 8 < pos) {
            char* placementMemory;
            try{
                placementMemory = new char [2 * capacity];
            } catch (std::bad_alloc& ba) {
                 std::cerr << "bad_alloc caught: " << ba.what() << '\n';
                 return ;
            }
            for (int i = 0; i < capacity; ++i) {
                placementMemory[i] = (char) p_vector[i];
            }
            delete[] (p_vector);
            for (int i = capacity; i < 2 * capacity; ++i) {
                    placementMemory[i] = 255;
            }
            p_vector = placementMemory;
            capacity *= 2;
        }
        if (size <= pos){
            size = pos + 1;
        }
        int pow_ = 8-1 -(pos % 8);
        int c=255 - (int)pow((float)2,(int)pow_);
        cout<<pos<<" "<<pow_<<" "<<c<<std::endl;
        if (_new == false){
            char ch = p_vector[pos / 8] & (255 - (int)pow((float)2,(int)pow_));
            this->p_vector[pos/8] = ch;
        }
        std::cout<<size<<"\n";
        return;
    }


     my::vector<bool>& my::vector<bool>::operator = (const my::vector<bool> & a) {
        size=a.size;
        capacity=a.capacity;
        delete[](p_vector);
        p_vector = static_cast <char*> (::operator new (sizeof(char) * capacity));
        for (int i = 0; i < a.size; ++i) {
            new (p_vector + i) char(a.p_vector[i]);
        }
        return *this;
    }

    bool  my::vector<bool>::operator == (my::vector<bool> const&a) {
        if (a.size == this -> size) {
            int i = 0;
            while (i < a.size) {
                if (a.p_vector [i] != this -> p_vector[i]) {
                    return false;
                }
                ++i;
            }
            return true;
        } else {
            return false;
        }
    }


    bool  my::vector<bool>::operator != (my::vector<bool> const& a) {
        return (!(*this == a));
    }
*/
