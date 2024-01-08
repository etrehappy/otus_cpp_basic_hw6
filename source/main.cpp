#include "main.h"


template<typename T>
void print(int number, u_vector<T>& vec)
{
    std::cout << "\n " << number <<". Содержимое контейнера vec: " << vec;
}

void print(int number, const u_list& f_list)
{
    std::cout << "\n " << number << ". Содержимое контейнера f_list: " << f_list;
}

void check_u_vector()
{
    u_vector<int> vec;

    const int size_vec = 10;
    for (int i = 0; i < size_vec; i++)
    {
        vec.push_back(i);
    }

    std::cout << "\n 2. В контейнер vec добавлено " << size_vec << " элементов.";
    print(3, vec);
    std::cout << "\n 4. Размер контейнера: " << vec.size();

    vec.erase(3);
    vec.erase(4);
    vec.erase(5);

    std::cout << "\n 5. Из контейнера удалены 3, 5 и 7 элементы.";
    print(6, vec);    

    vec.insert(1, 10);

    std::cout << "\n 7. Добавлен элемент 10 в начало контейнера.";
    print(8, vec);    

    vec.insert(5, 20);

    std::cout << "\n 9. Добавлен элемент 20 в середину контейнера.";
    print(10, vec);

    vec.push_back(30); // !!! insert

    std::cout << "\n 11. Добавлен элемент 30 в конец контейнера.";
    print(12, vec);    
}

void check_u_forward_list()
{
    u_list list;

    const int size_f_list = 10;
    for (int i = 0; i < size_f_list; i++)
    {
        list.push_back(i);
    }
    std::cout << "\n 2. В контейнер list добавлено " << size_f_list << " элементов.";
    print(3, list);
    std::cout << "\n 4. Размер контейнера: " << list.size();

    list.erase(3);
    list.erase(4);
    list.erase(5);
    std::cout << "\n 5. Из контейнера удалены 3, 5 и 7 элементы.";
    print(6, list);

    list.insert(1, 10);
    std::cout << "\n 7. Добавлен элемент 10 в начало контейнера.";
    print(8, list);


    list.insert(5, 20);
    std::cout << "\n 9. Добавлен элемент 20 в середину контейнера.";
    print(10, list);

    list.push_back(30);
    std::cout << "\n 11. Добавлен элемент 30 в конец контейнера.";
    print(12, list);
}

int main() 
{ 
    setlocale(LC_ALL, "Russian");
   
    check_u_vector();

    std::cout << "\n\n===============================================\n";

    check_u_forward_list();    
           
    return 0;
}