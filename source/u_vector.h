#pragma once
#include <iostream>

template<typename T>
class u_vector 
{
public:
    u_vector();
    u_vector(const u_vector<T>& rhs);
    ~u_vector();

    void push_back(T value);
    int size() const;
    void erase(int pos);
    void insert(const int pos, const T& value);

    T& operator[](const int i);
    
    template<typename T>
    friend std::ostream& operator<<(std::ostream& out, u_vector<T>& rhs);   

private:
    
    void double_capacity(); //extra 1
    void new_container(const int old_size);
    void fill(int index, const T& value);
    void fill(const int new_pos, const int new_size, const T& value, T* ptr_old); 
    void permutation(const int new_pos, const int new_size);

    int m_arr_size;
    T *m_arr;
    int m_capacity;
};

#include "u_vector.ipp"