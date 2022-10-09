#pragma once

#include <iostream>
#include <algorithm>
#include <queue>
#include <string>

#include "../sequence/sequence.hpp"
#include "../sequence/arraySequence.hpp"

using namespace std;

template <class T>
class Node
{
  public:
    T key;
    int height;
    Node<T>* left;
    Node<T>* right;

    Node()
    {
      height = 0;
      left = nullptr;
      right = nullptr;
    }

    Node(T data)
    {
      key = data;
      height = 1;
      left = nullptr;
      right = nullptr;
    }
};

template <class T>
class BinaryTree
{
  protected:
    Node<T>* root;
    int size;

    int get_height(Node<T>* node)
    {
      if (node) return node->height;
      return 0;
    }

    int get_bFactor(Node<T>* node)
    {
      return get_height(node->right) - get_height(node->left);
    }

    void fix_height(Node<T>* node)
    {
      int h_l = get_height(node->left);
      int h_r = get_height(node->right);
      node->height = max(h_l, h_r) + 1;
    }

    Node<T>* rotate_right(Node<T>* node)
    {
      Node<T>* rNode = node->left;
      node->left = rNode->right;
      rNode->right = node;

      fix_height(node);
      fix_height(rNode);

      return rNode;
    }

    Node<T>* rotate_left(Node<T>* node)
    {
      Node<T>* rNode = node->right;
      node->right = rNode->left;
      rNode->left = node;

      fix_height(node);
      fix_height(rNode);

      return rNode;
    }

    Node<T>* balance(Node<T>* node)
    {
      fix_height(node);
      if (get_bFactor(node) == 2)
      {
        if (get_bFactor(node->right) < 0) node->right = rotate_right(node->right);
        return rotate_left(node);
      }

      if (get_bFactor(node) == -2)
      {
        if (get_bFactor(node->left) > 0) node->left = rotate_left(node->left);
        return rotate_right(node);
      }

      return node;
    }

    Node<T>* insert(Node<T>* node, T data)
    {
      if (!node) return new Node<T>(data);

      if (data < node->key)
      {
        node->left = insert(node->left, data);
      }
      if (data > node->key)
      {
        node->right = insert(node->right, data);
      }

      return balance(node);
    }

    Node<T>* find_min(Node<T>* node)
    {
      if (node->left) return find_min(node->left);
      return node;
    }

    Node<T>* remove_min(Node<T>* node)
    {
      if (!node->left) return node->right;
      node->left = remove_min(node->left);
      return balance(node);
    }

    Node<T>* remove(Node<T>* node, T data)
    {
      if (!node) return nullptr;

      if (data < node->key)
      {
        node->left = remove(node->left, data);
      } else if (data > node->key) {
        node->right = remove(node->right, data);
      } else { // data = key
        Node<T>* left_cld = node->left;
        Node<T>* right_cld = node->right;
        delete node;
        if (!right_cld) return left_cld;
        Node<T>* min_node = find_min(right_cld);
        min_node->right = remove_min(right_cld);
        min_node->left = left_cld;
        return balance(min_node);
      }
      return balance(node);
    }

    void detour_to_queue(Node<T>* node, string type_detour, queue<T>* dQueue)
    {
      if (!node) return;
      for (int i = 0; i < 3; i++)
      {
        switch (type_detour[i])
        {
          case 'K':
          {
            dQueue->push(node->key);
            break;
          }
          case 'L':
          {
            detour_to_queue(node->left, type_detour, dQueue);
            break;
          }
          case 'P':
          {
            detour_to_queue(node->right, type_detour, dQueue);
            break;
          }
        }
      }
      return;
    }

    Node<T>* find_node(Node<T>* node, T key)
    {
      if (node->key == key) return node;
      if (key > node->key) return find_node(node->right, key);
      else return find_node(node->left, key);
    }

    bool subtree_detour(Node<T>* node, Node<T>* sub_node, bool res)
    {
      if (sub_node && (!node || sub_node->key != node->key)) return false;
      if (!sub_node) return res && true;
      res = subtree_detour(node->left, sub_node->left, res);
      res = subtree_detour(node->right, sub_node->right, res);
      return res;
    }

    Node<T>* get_root(BinaryTree<T>* tree)
    {
      return tree->root;
    }

  public:
    BinaryTree()
    {
      root = nullptr;
      size = 0;
    }

    Sequence<T>* GetSeq(string type_detour)
    {
      queue<T>* dQueue = new queue<T>();
      detour_to_queue(root, type_detour, dQueue);
      Sequence<T>* Seq = new ArraySequence<T>();

      while (!dQueue->empty())
      {
        Seq->Append(dQueue->front());
        dQueue->pop();
      }
      delete dQueue;      
      return Seq;
    }

    void print(string type_detour)
    {
      cout << endl << type_detour << ": ";
      queue<T>* dQueue = new queue<T>();
      detour_to_queue(root, type_detour, dQueue);

      while (!dQueue->empty())
      {
        cout << dQueue->front() << " ";
        dQueue->pop();
      }
      delete dQueue;

      cout << endl;
    }

    BinaryTree<T>* map(T (*func)(T key))
    {
      queue<T>* dQueue = new queue<T>();
      detour_to_queue(root, "KLP", dQueue);
      
      BinaryTree<T>* map_tree = new BinaryTree<T>();
      while (!dQueue->empty())
      {
        map_tree->add_key(func(dQueue->front()));
        dQueue->pop();
      }
      delete dQueue;

      return map_tree;
    }

    BinaryTree<T>* where(bool (*func)(T key))
    {
      queue<T>* dQueue = new queue<T>();
      detour_to_queue(root, "KLP", dQueue);

      BinaryTree<T>* where_tree = new BinaryTree<T>();
      while(!dQueue->empty())
      {
        if (func(dQueue->front())) where_tree->add_key(dQueue->front());
        dQueue->pop();
      }
      delete dQueue;

      return where_tree;
    }

    T reduce(T (*func)(T val1, T val2), T param)
    {
      queue<T>* dQueue = new queue<T>();
      detour_to_queue(root, "KLP", dQueue);

      T res = func(dQueue->front(), param);
      dQueue->pop();

      while(!dQueue->empty())
      {
        res = func (dQueue->front(), res);
        dQueue->pop();
      }

      delete dQueue;
      return res;
    }

    string string_save(string type_detour)
    {
      queue<T>* dQueue = new queue<T>();
      detour_to_queue(root, type_detour, dQueue);
      string save_str;

      while (!dQueue->empty())
      {
        save_str.append(to_string(dQueue->front()) + " ");
        dQueue->pop();
      }
      delete dQueue;

      return save_str;
    }

    BinaryTree<T>* get_subtree(T key)
    {
      queue<T>* dQueue = new queue<T>();
      detour_to_queue(find_node(root, key), "KLP", dQueue);

      BinaryTree<T>* subtree = new BinaryTree<T>();
      while (!dQueue->empty())
      {
        subtree->add_key(dQueue->front());
        dQueue->pop();
      }
      delete dQueue;

      return subtree;
    }

    bool check_subtree(BinaryTree<T>* sub_tree)
    {
      bool res = true;
      res = subtree_detour(find_node(root, sub_tree->root->key), sub_tree->root, res);
      return res;
    }

    void add_key(T data)
    {
      root = insert(root, data);
      size++;
      return;
    }

    void remove_key(T data)
    {
      root = remove(root, data);
      size--;
      return;
    }

};