#pragma once

#include <string>
#include <exception>
#include <stdexcept>

using namespace std;
// Как быть в ситуации с 2-мя нодами

template <typename T>
class List_Node
{
  public:
    T key;
    List_Node<T>* next;

    List_Node() {next = nullptr;}
    List_Node(T key) {this->key = key, next = nullptr;}
};

template <typename T>
class LinkedList
{
  private:
    List_Node<T>* root;
    int size;

    void CheckEmpty() const
    {
      if (size == 0)  
        throw out_of_range("IndexOutOfRange: Empty list");
    }

    void CheckValidIndex(int index) const
    {
      if (index < 0 || index >= size)
        throw out_of_range("IndexOutOfRange(" + to_string(index) + ")");
    }

  public:
    // конструкторы/деструкторы
    LinkedList()
    {
      size = 0;
      root = nullptr;
    }

    LinkedList(T* items, int count)
    {
      size = count;
      root = new List_Node<T>(items[0]);

      List_Node<T>* ptr = root;
      for (int i = 1; i <= count - 1; i++)
      {
        ptr->next = new List_Node<T>(items[i]);
        ptr = ptr->next;
      }
    }

    LinkedList(const LinkedList<T>& list)
    {
      size = list.size;
      root = new List_Node<T>(list.root->key);

      List_Node<T>* ThisPtr = root;
      List_Node<T>* OtherPtr = list.root;
      
      while(OtherPtr->next)
      {
        ThisPtr->next = new List_Node<T>(OtherPtr->next->key);
        ThisPtr = ThisPtr->next;
        OtherPtr = OtherPtr->next;
      }
    }

    ~LinkedList()
    {
      List_Node<T>* ptr = root;
      
      while (ptr)
      {
        List_Node<T>* tmp = ptr;
        ptr = ptr->next;
        delete tmp;
      }
    }

    // декомпозиция
    T GetFirst() const 
    {
      CheckEmpty();
      return root->key;
    }

    T GetLast() const
    {
      CheckEmpty();
      List_Node<T>* ptr = root;

      while (ptr->next) ptr = ptr->next;
      return ptr->key;
    }

    T Get(int index) const
    {
      CheckEmpty();
      CheckValidIndex(index);

      List_Node<T>* ptr = root;
      for (int i = 0; i < index; ptr = ptr->next, i++);
      return ptr->key;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex) const
    {
      CheckEmpty();
      CheckValidIndex(startIndex);
      CheckValidIndex(endIndex);

      LinkedList<T>* Res = new LinkedList<T>();
      List_Node<T>* ptr = root;
      for (int i = 0; i < startIndex; ptr = ptr->next, i++);

      for (int i = startIndex; i < endIndex; i++)
      {
        Res->Append(ptr->key);
        ptr = ptr->next;
      }

      return Res;
    }

    int GetLength() const {return size;}

    // операции
    void Append(T item)
    {
      if (size == 0)
      {
        root = new List_Node<T>(item);
        size++;
        return;
      }

      List_Node<T>* ptr = root;
      while (ptr->next) ptr = ptr->next;
      ptr->next = new List_Node<T>(item);
      size++;
    }

    void Prepend(T item)
    {
      if (size == 0)
      {
        root = new List_Node<T>(item);
        size++;
        return;
      }

      List_Node<T>* tmp = root;
      root = new List_Node<T>(item);
      root->next = tmp;
      size++;
    }

    void InsertAt(int index, T item)
    {
      CheckEmpty();
      CheckValidIndex(index);

      List_Node<T>* ptr;
      for (int i = 0; i < index; ptr = ptr->next, i++);

      List_Node<T>* tmp = ptr->next;
      ptr->next = new List_Node<T>(item);
      ptr->next->next = tmp;
    }

    void Set(int index, T item)
    {
      CheckEmpty();
      CheckValidIndex(index);

      List_Node<T>* ptr = root;
      for (int i = 0; i < index; ptr = ptr->next, i++);
      ptr->key = item;
    }
};