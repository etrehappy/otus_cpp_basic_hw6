#include "u_forward_list.h"

u_forward_list::u_forward_list()
    : m_arr_size(NULL), m_start_node(nullptr), m_old_node(nullptr)
{
    std::cout << "\n 1. Cоздан объект класса u_forward_list для хранения элементов типа int в контейнере типа «Однонаправленный список».";
}

u_forward_list::Node::Node()
    : m_data(NULL), next(nullptr)
{
    //std::cout << "\n Вызван конструктор Node";
}

u_forward_list::Node::~Node()
{
   // std::cout << "\n Вызван деструктор Node";
}

u_forward_list::~u_forward_list()
{
    Node* it = m_start_node;
    Node* it_del = nullptr;

    if (it == nullptr)
    {
        std::cout << "\nПервый элемент контейнера пустой.";
        return;
    }

    for (; it != nullptr; )
    {
        it_del = it;
        it = it->next;

        delete it_del;
        it_del = nullptr;
    }
    //std::cout << "\nОбъект f_list удалён деструктором ~u_list()";
}

void u_forward_list::push_back(int value)
{
    ++m_arr_size;

    Node* new_node = new Node;
    new_node->m_data = value;

    if (m_arr_size == 1)   
        m_start_node = new_node;
    else      
        m_old_node->next = new_node;

    m_old_node = new_node;
}

int u_forward_list::size() const
{
    return m_arr_size;
}

//@param pos > 0
void u_forward_list::erase(int pos)
{   
    Node* node = m_start_node;
    Node* node_prev = nullptr;

    if (node == nullptr)
    {
        std::cout << "Первый элемент контейнера пустой.";
        return;
    }  

    //Search the Node's pos in the container    
    for (int count_pos = 1; count_pos != pos; ++count_pos)
    {
        node_prev = node;
        node = node->next;        
    }

    //Change memory address
    if (pos == 1)
    {
        node_prev = m_start_node;
        m_start_node = node_prev->next;
        goto size_count;
    }
    else if (node == nullptr) //check lust position
        node_prev->next = nullptr;
    else
        node_prev->next = node->next;  

    //Delete the old Node
    delete node;
    node = nullptr;

    size_count:
    --m_arr_size;
}

//@param pos > 0
void u_forward_list::insert(const int pos, const int value)
{
    if (pos < 1 || pos > m_arr_size)
    {
        std::cout << "\nError. Pos <= 0 OR pos > max container's size = " << m_arr_size;
        exit(1);
    }

    Node* node = m_start_node;
    Node* new_node = new Node;
    new_node->m_data = value;    

    if (pos == 1) //Insert in the first pos
    {
        m_start_node = new_node;
        new_node->next = node;
        goto size_count;
    }

    Node* node_prev = nullptr;
    node = m_start_node->next;
    for (int count_pos = 2; count_pos != pos; ++count_pos) //Search the Node's pos in the container
    {
        node_prev = node;
        node = node->next;
    }
    
    if (node == nullptr)  // check lust position
    {
        node_prev->next = new_node;
    }
    else
    { 
        node_prev->next = new_node; //Set new address for container[pos-1].next       
        new_node->next = node;
    }    

    size_count:
    ++m_arr_size;
}


std::ostream& operator<<(std::ostream& out, const u_forward_list& rhs)
{
    const u_forward_list::Node* it = rhs.m_start_node;
    for (; it->next != nullptr; ) {
        out << it->m_data << ", ";
        it = it->next;
    }

    if (it->next == nullptr)
    {
        out << it->m_data;
    }

    return out;
}