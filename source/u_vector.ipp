#include "u_vector.h"

     //  1       2       3        4     5       6       7        8       9      10
    //vec[0], vec[1], vec[2], vec[3], vec[4], vec[5], vec[6], vec[7], vec[8], vec[9]

template<typename T>
u_vector<T>::u_vector()
    : m_arr_size(NULL), m_arr(new T[m_arr_size])
{
    std::cout << "\n 1. Cоздан объект шаблонного класса u_vector для хранения элементов размером " << sizeof(T) << " байта в последовательном контейнере.";
}

template<typename T>
u_vector<T>::u_vector(const u_vector<T>& rhs)
    : m_arr_size(rhs.m_arr_size), m_arr(new T[rhs.m_arr_size])
{
    for (size_t i = 0; i < m_arr_size; i++)
    {
        m_arr[i] = rhs.m_arr[i];
    }
    std::cout << "\nCall copy construcot u_vector(const u_vector<T>& rhs)";
}

template<typename T>
u_vector<T>::~u_vector()
{
    delete[] m_arr;
    /*std::cout << "\nОбъект vec удалён деструктором ~u_vector()"; */   
}

template<typename T>
void u_vector<T>::push_back(T value)
{  
    const int last = m_arr_size;   

    new_container(++m_arr_size, last);
    
    m_arr[last] = value; //There isn't problem with Warning C6386 here, because last = (m_arr_size - 1) 
}

template<typename T>
int u_vector<T>::size() const
{
    return m_arr_size;
}

template<typename T>
int u_vector<T>::size_memory() const
{
    return (m_arr_size)*sizeof(T); ///!!!
}

//@param pos > 0
template<typename T>
void u_vector<T>::erase(int pos)
{     
    if (pos == 0)
    {
        std::cout << "\nError. Pos is also > 0";
        exit(1);
    }

    //move position
    for (int new_pos = pos - 1; new_pos < m_arr_size; new_pos++)
    {
        m_arr[new_pos] = m_arr[new_pos + 1];
    }    
    const int new_size = --m_arr_size;
    m_arr[new_size] = NULL; // !!! если capasity больше, то не нужно.
    
    new_container(new_size, new_size);
}

//@param pos > 0
template<typename T> 
void u_vector<T>::insert(const int pos, const T& value)
{
    if (pos < 1 || pos > m_arr_size)
    {
        std::cout << "\nError. Pos <= 0 OR pos > max container's size = " << m_arr_size;
        exit(1);
    }

    const int new_pos = pos - 1;
    const int new_size = ++m_arr_size;

    T* ptr_old = m_arr;
    m_arr = new T[new_size];

    for (int i = 0; i < new_size; i++)
    {
        if (i == new_pos)
            m_arr[i] = value;
        else if (i > new_pos)
            m_arr[i] = ptr_old[i - 1];
        else
            m_arr[i] = ptr_old[i];
    }

    delete[] ptr_old;
}

template<typename T>
T& u_vector<T>::operator[](const int i)
{
    return m_arr[i];
}

template<typename T>
std::ostream& operator<<(std::ostream& out, u_vector<T>& rhs) 
{
    const int last = rhs.size() - 1;

    for (int i = 0; i < last; ++i) {
        out << rhs[i] << ", ";
    }
    out << rhs[last];
    return out;
}


template<typename T>
void u_vector<T>::new_container(const int new_size, const int max_size) {
    
    T* ptr_old = m_arr;
    m_arr = new T[new_size];

    for (int i = 0; i < max_size; i++)
    {
        m_arr[i] = ptr_old[i];
    }
    delete[] ptr_old;
}
