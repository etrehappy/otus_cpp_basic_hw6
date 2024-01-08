#include "u_list.h"


u_list::u_list()
    : m_arr_size(NULL), m_start_node(nullptr), m_end_node(nullptr)
{  
    std::cout << "\n 1. Cоздан объект класса u_list для хранения элементов типа int в контейнере типа «Двунаправленный список».";
}

u_list::Node::Node() 
    : m_data(NULL), next(nullptr), prev(nullptr)  
{
    //std::cout << "\n Вызван конструктор Node";
}

u_list::Node::~Node()
{
    /*std::cout << "\n Вызван деструктор Node";*/
}


u_list::~u_list()
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
    /*std::cout << "\nОбъект list удалён деструктором ~u_list()";*/
}


void u_list::push_back(int value)
{
    ++m_arr_size;

    Node* new_end_node = new Node;

    if (m_arr_size == 1)
    {
        m_start_node = m_end_node = new_end_node;
        m_start_node->m_data = value;
    }
    else
    {        
        new_end_node->m_data = value;
        new_end_node->prev = m_end_node;       
        m_end_node->next = new_end_node;       
        m_end_node = new_end_node;
       
    }
}


int u_list::size() const
{
    return m_arr_size;
}


//@param pos > 0
void u_list::erase(int pos)
{

    Node* node = m_start_node;

    if (node == nullptr)
    {
        std::cout << "Первый элемент контейнера пустой.";
        return;
    }

    //Search the Node's pos in the container    
    for (int count_pos = 1; count_pos != pos; ++count_pos)
    {
        node = node->next;
    }

    //Change memory address of the container[pos-1]->next and the container[pos+1]->prev.
    node->prev->next = node->next;
    node->next->prev = node->prev;

    //Delete the old Node
    delete node;
    node = nullptr; 
    --m_arr_size;
}


//@param pos > 0
void u_list::insert(const int pos, const int value)
{
    if (pos < 1 || pos > m_arr_size)
    {
        std::cout << "\nError. Pos <= 0 OR pos > max container's size = " << m_arr_size;
        exit(1);
    }

    Node* old_node = m_start_node;
    Node* new_node = new Node;
    new_node->m_data = value;
   
    if (pos == 1) //Insert in the first pos
    {
        old_node->prev = m_start_node = new_node;
        new_node->next = old_node;
    }
    else    if (pos > 1)
    {
        //Search the Node's pos in the container
        old_node = m_start_node->next;
        for (int count_pos = 2; count_pos != pos; ++count_pos)
        {
            old_node = old_node->next;
        }

        old_node->prev->next = new_node; //Set new address for container[pos-1].next

        new_node->prev = old_node->prev;
        new_node->next = old_node;

        old_node->prev = new_node; //Set new address for container[pos+1].prev
    }
    else
    {
        delete new_node;
        new_node = nullptr;
        return;
    }

    ++m_arr_size;
}


std::ostream& operator<<(std::ostream& out, const u_list& rhs)
{    
    const u_list::Node* it = rhs.m_start_node;
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

//void u_list::test_print_container()
//{
//   Node* it = m_start_node;
//
//    if (it == nullptr)
//    {
//        std::cout << "\n";
//        std::cout << "Адрес элемента it\t" << it;
//        return;
//    }
//
//    do
//    {
//        std::cout << "\n";
//        std::cout << "Адрес it = " << it;
//        std::cout << ";\tЗначение it->prev = " << it->prev;
//        std::cout << ";\tЗначение it->next = " << it->next;
//        std::cout << ";\tЗначение it->m_data = " << it->m_data;
//
//        it = it->next;
//    } while (it != nullptr);
//}