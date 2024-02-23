#pragma once
#include <iostream>

template<typename T>
class u_list
{
public:
    u_list();
    u_list(const u_list&) = delete;
    u_list& operator=(const u_list&) = delete;
    u_list(u_list&& rhs) noexcept; //доп. задание 3
    u_list& operator=(u_list&& rhs) noexcept; //доп. задание 3
    virtual ~u_list();

    void push_back(const T& value);
    int size() const;
    void erase(const int element_pos);
    void insert(const int pos, const int value);
    
    struct iterator;
    iterator begin();
    iterator back();
    iterator end();
    template<typename T>
    friend std::ostream& operator<<(std::ostream& out, u_list& rhs);    

private:

    struct Node;

    int m_arr_size;
    Node* m_start_node;    
    Node* m_end_node;
};

template<typename T>
struct u_list<T>::iterator
{
public:
    iterator(Node* p);

    int& operator*();
    iterator& operator++();
    friend bool operator!=(iterator& lhs, iterator& rhs)    {
            return lhs.m_iterator_ptr != rhs.m_iterator_ptr;
    }

    int& get();

private:    
    Node* m_iterator_ptr;
};

template<typename T>
struct u_list<T>::Node
{
    Node* next;
    Node* prev;
    int m_data;

    Node();    
    ~Node() = default;
};

#include "u_list.ipp"