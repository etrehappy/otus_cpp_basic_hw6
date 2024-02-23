#pragma once
#include <iostream>

template<typename T>
class u_vector 
{
public:
    u_vector();
    u_vector(const u_vector<T>& rhs) = delete;
    u_vector& operator=(const u_vector<T>& rhs) = delete;
    u_vector(u_vector<T> &&rhs) noexcept; //доп. задание 3
    u_vector& operator=(u_vector<T>&& rhs) noexcept; //доп. задание 3
    virtual ~u_vector();

    void push_back(const T& value);
    int size() const;
    void erase(const int element_pos);
    void insert(const int pos, const T& value);

    struct iterator;
    iterator begin();
    iterator back();
    iterator end();

    T& operator[](int i) const;
    template<typename T>
    friend std::ostream& operator<<(std::ostream& out, u_vector<T>& rhs);

private:
    
    void double_capacity(); //доп. задание 1
    void new_container(const int old_size);
    void fill_new_arr(const int new_pos, const int new_size, const T& value, const T* ptr_old);
    void permutation(const int new_pos, const int new_size);
        
    int m_arr_size;
    T *m_arr;
    int m_capacity;
};

template<typename T>
struct u_vector<T>::iterator
{
public:
    iterator(T* p);

    T& operator*() const;
    iterator& operator++();
    friend bool operator!=(iterator& lhs, iterator& rhs) { 
        return lhs.m_iterator_ptr != rhs.m_iterator_ptr;
    }

    T& get() const;

private:
    T* m_iterator_ptr;
};


#include "u_vector.ipp"

