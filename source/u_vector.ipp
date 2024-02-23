#include "u_vector.h"

//u_vector's конструкторы и деструктор

template<typename T>
u_vector<T>::u_vector()
    : m_arr_size(0), m_arr(nullptr), m_capacity(0)
{
    std::cout << "\n 1. Cоздан объект шаблонного класса u_vector для хранения элементов размером " << sizeof(T) << " байта в последовательном контейнере.";
}

template<typename T>
u_vector<T>::u_vector(u_vector<T>&& rhs) noexcept  //доп. задание 3
{
    m_arr = rhs.m_arr;
    m_arr_size = rhs.m_arr_size;
    m_capacity = rhs.m_capacity;
    
    rhs.m_arr = nullptr;
    rhs.m_arr_size = 0;
    rhs.m_capacity = 0;

    std::cout << "\n 1. Вызван конструктор перемещения u_vector(u_vector<T>&& rhs)";
}

template<typename T>
u_vector<T>& u_vector<T>::operator=(u_vector<T>&& rhs) noexcept  //доп. задание 3
{
    if (&rhs == this) 
        return *this;

    m_arr = rhs.m_arr;
    m_arr_size = rhs.m_arr_size;
    m_capacity = rhs.m_capacity;

    rhs.m_arr = nullptr;
    rhs.m_arr_size = 0;
    rhs.m_capacity = 0;

    std::cout << "\n 2. Вызван оператор присваивания перемещением operator=(u_vector<T>&& rhs)";
    
    return *this;
}

template<typename T>
u_vector<T>::~u_vector()
{
    delete[] m_arr;      
}



//u_vector's public и friend функции

template<typename T>
void u_vector<T>::push_back(const T& value)
{  
    const int old_size = m_arr_size;
    ++m_arr_size;

    if (m_capacity <= old_size)
    {
        double_capacity();          //доп. задание 1
        new_container(old_size);
        m_arr[old_size] = value;
    }
    else if (m_capacity > old_size)
    {
        m_arr[old_size] = value;
    } 
}

template<typename T>
int u_vector<T>::size() const
{
    return m_arr_size;
}

//@param element_pos > 0
template<typename T>
void u_vector<T>::erase(const int element_pos)
{   
    //проверяем позицию
    if (element_pos <= 0 || element_pos > m_arr_size)
    {
        std::cout << "\nError: erase element_pos <= 0 OR > max";
        exit(-1);
    }

    //смещаем элементы
    for (int pre_pos = element_pos - 1; pre_pos < m_arr_size; pre_pos++)
    {
        m_arr[pre_pos] = m_arr[pre_pos + 1];
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
    
    T* arr_old = m_arr;

    if (m_capacity <= old_size)
    {
        double_capacity();        
        m_arr = new T[new_size];
        fill_new_arr(new_pos, new_size, value, arr_old);

        delete[] arr_old;
    }
    else if (m_capacity > old_size)
    {
        permutation(new_pos, old_size);
        m_arr[new_pos] = value;
    }
}

template<typename T>
typename u_vector<T>::iterator u_vector<T>::begin()
{
    return iterator(m_arr);
}

template<typename T>
typename u_vector<T>::iterator u_vector<T>::back()
{
    return iterator(m_arr + m_arr_size - 1);
}

template<typename T>
typename u_vector<T>::iterator u_vector<T>::end()
{
    return iterator(m_arr + m_arr_size);
}


template<typename T>
T& u_vector<T>::operator[](int i) const
{
    return m_arr[i];
}

template<typename T>
std::ostream& operator<<(std::ostream& out, u_vector<T>& rhs)
{
    if (rhs.m_arr == nullptr)
    {
        out << "\nВектор не содержит элементов";
        return out;
    }

    auto last = rhs.back();
    
    for (auto it = rhs.begin(); it != last; ++it)  //доп. задание 4   
        out << *it << ", ";

    out << *last;
    return out;
}



//u_vector's private методы

template<typename T>
void u_vector<T>::double_capacity()
{
    m_capacity = 2 * m_arr_size;
}

template<typename T>
void u_vector<T>::new_container(const int old_size) {

    T* arr_old = m_arr;
    m_arr = new T[m_capacity]{ 0 };

    std::copy(arr_old, arr_old + old_size, m_arr); //Использую std::copy, потому что VS не нравится мой код ниже (Warning C6386)
    
    //for (int i = 0; i < old_size; i++) {
    //    m_arr[i] = ptr_old[i];   //Не должно быть проблем здесь, потому что old_size = (m_arr_size - 1) 
    //}
    delete[] arr_old;
}

template<typename T>
void u_vector<T>::fill_new_arr(const int new_pos, const int new_size, const T& value, const T* arr_old)
{ 
    for (int i = 0; i < new_size; i++)
    {
        if (i == new_pos)
            m_arr[i] = value; //вставить new value в new_pos
        else if (i > new_pos)
            m_arr[i] = arr_old[i - 1]; //вставка от места (new value + 1) до end
        else
            m_arr[i] = arr_old[i];  //вставка от 0 до new value 
    }
}

template<typename T>
void u_vector<T>::permutation(const int new_pos, int old_end)
{
    //меняем элемнты местами от end до new value
    for (; old_end != new_pos; old_end--)          
        m_arr[old_end] = m_arr [old_end-1];
}


//===========================================================================================================
//доп. задание 4   
//iterator's конструкторы и public методы

template<typename T>
u_vector<T>::iterator::iterator(T* p)
    : m_iterator_ptr(p)
{}

template<typename T>
T& u_vector<T>::iterator::operator*() const
{
    return *m_iterator_ptr;
}

template<typename T>
typename u_vector<T>::iterator& u_vector<T>::iterator::operator++()
{
    ++m_iterator_ptr;
    return *this;
}

template<typename T>
T& u_vector<T>::iterator::get() const
{
    return *m_iterator_ptr;
}