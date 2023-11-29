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
    int size_memory() const;
    void erase(int pos);
    void insert(const int pos, const T& value);

    T& operator[](const int i);
    
    template<typename T>
    friend std::ostream& operator<<(std::ostream& out, u_vector<T>& rhs);   

private:
    
    void new_container(const int new_size, const int max_size);
    
    int m_arr_size;
    T *m_arr;
};

#include "u_vector.ipp"