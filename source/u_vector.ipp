#include "u_vector.h"

     //  1       2       3        4     5       6       7        8       9      10
    //vec[0], vec[1], vec[2], vec[3], vec[4], vec[5], vec[6], vec[7], vec[8], vec[9]

template<typename T>
u_vector<T>::u_vector()
    : m_arr_size(NULL), m_arr(new T[m_arr_size]), m_capacity(NULL)
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
    const int old_size = m_arr_size;
    ++m_arr_size;

    if (m_capacity <= old_size)
    {
        double_capacity();
        new_container(old_size);
        fill(old_size, value);                
    }
    else if (m_capacity > old_size)
    {
        fill(old_size, value);
    } 
}

template<typename T>
int u_vector<T>::size() const
{
    return m_arr_size;
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
    for (int old_pos = pos - 1; old_pos < m_arr_size; old_pos++)
    {
        m_arr[old_pos] = m_arr[old_pos + 1];
    }    
    --m_arr_size;
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
    const int old_size = m_arr_size;
    const int new_size = ++m_arr_size;
    
    T* ptr_old = m_arr;

    if (m_capacity <= old_size)
    {
        double_capacity();
        
        m_arr = new T[new_size];

        fill(new_pos, new_size, value, ptr_old);

        delete[] ptr_old;
    }
    else if (m_capacity > old_size)
    {
        permutation(new_pos, new_size);
        fill(new_pos, value);
    }
}

template<typename T>
T& u_vector<T>::operator[](const int i)
{
    return m_arr[i];
}

template<typename T>
std::ostream& operator<<(std::ostream& out, u_vector<T>& rhs) 
{
    const int last = rhs.size() - 1; //for test: rhs.m_capacity - 1

    for (int i = 0; i < last; ++i) {
        out << rhs[i] << ", ";
    }
    out << rhs[last];
    return out;
}



template<typename T>
void u_vector<T>::new_container(const int old_size) {
    
    T* ptr_old = m_arr;
    m_arr = new T[m_capacity]{ NULL };

    for (int i = 0; i < old_size; i++)
    {
        m_arr[i] = ptr_old[i];   //There isn't problem with Warning C6386 here, because old_size = (m_arr_size - 1) 
    }
    delete[] ptr_old;
}


template<typename T>
void u_vector<T>::double_capacity()
{
    m_capacity = 2 * m_arr_size;
}

template<typename T>
void u_vector<T>::fill(int index, const T& value) //!!! delete?
{
    m_arr[index] = value;
}

template<typename T>
void u_vector<T>::fill(const int new_pos, const int new_size, const T& value, T* ptr_old) //!!! delete?
{ 
    for (int i = 0; i < new_size; i++)
    {
        if (i == new_pos)
            m_arr[i] = value;
        else if (i > new_pos)
            m_arr[i] = ptr_old[i - 1];
        else
            m_arr[i] = ptr_old[i];
    }
}

template<typename T>
void u_vector<T>::permutation(const int new_pos, const int new_size) 
{
    if (new_pos < new_size)
    {
        for (int j = new_size-1; j != new_pos; j--)
        {            
            m_arr[j] = m_arr [j-1];
        }        
    }
}

