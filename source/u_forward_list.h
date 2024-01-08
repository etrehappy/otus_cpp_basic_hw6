#pragma once
#include <iostream>

class u_forward_list
{
public:
    u_forward_list();
    ~u_forward_list();

    void push_back(int value);
    int size() const;
    void erase(int pos);
    void insert(const int pos, const int value);

    friend std::ostream& operator<<(std::ostream& out, const u_forward_list& rhs);    

private:

    struct Node
    {
        Node* next;
        int m_data;

        Node();
        Node(const Node& rhs_node) = default;
        Node& operator=(const Node& rhs_node) = delete;
        ~Node();
    };

    int m_arr_size;
    Node* m_start_node;
    Node* m_old_node;
};

