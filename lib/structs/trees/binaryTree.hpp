#pragma once
#include <algorithm>
#include "../sequence/sequence.hpp"
#include "../sequence/arraySequence.hpp"

using namespace std;

template <typename T>
class Node
{
  public:
    T key;
    int height;
    Node<T> *left, *right;

    Node(T const &key) 
    {
      this->key = key;
      height = 1;
      left = nullptr;
      right = nullptr;
    }

};

template <typename T>
class AVLTree
{
  protected:
    Node<T>* root;
    int size;
        
    int GetHeight(Node<T>* ptr) const {return ptr?ptr->height:0;}

    int GetBFactor(Node<T>* ptr) const {return ptr->right - ptr->left;}

    void FixHeight(Node<T>* ptr)
    {
      int H_L = GetHeight(ptr->left);
      int H_R = GetHeight(ptr->right);
      ptr->height = max(H_L, H_R) + 1;
    }

    Node<T>* RotateRight(Node<T>* node)
    {
      Node<T>* R_Node = node->left;
      node->left = R_Node->right;
      R_Node->right = node;

      FixHeight(node);
      FixHeight(R_Node);

      return R_Node;
    }

    Node<T>* RotateLeft(Node<T>* node)
    {
      Node<T>* R_Node = node->right;
      node->right = R_Node->left;
      R_Node->left = node;

      FixHeight(node);
      FixHeight(R_Node);

      return R_Node;
    }

    Node<T>* Balance(Node<T>* node)
    {
      FixHeight(node);
      if (GetBFactor(node) == 2)
      {
        if (GetBFactor(node->right) < 0) node->right = RotateRight(node->right);
        return RotateLeft(node);
      }

      if (GetBFactor(node) == -2)
      {
        if (GetBFactor(node->left) > 0) node->left = RotateLeft(node->left);
        return RotateRight(node);
      }

      return node;
    }

    Node<T>* Insert(Node<T>* node, T const &key)
    {
      if (!node)
      {
        size++;
        return new Node<T>(key);
      }

      if (key < node->key)
      {
        node->left = Insert(node->left, key);
      }
      if (key > node->key)
      {
        node->right = Insert(node->right, key);
      }

      return Balance(node);
    }

    Node<T>* FindMin(Node<T>* node) const {return node->left?FindMin(node->left):node;}

    Node<T>* RemoveMin(Node<T>* node)
    {
      if (!node->left) return node->right;
      node->left = RemoveMin(node->left);
      return Balance(node);
    }

    Node<T>* RemovePrivate(Node<T>* node, T const &key)
    {
      if (!node) return nullptr;
      
      if (node->key > key) node->left = RemovePrivate(node->left, key);
      else if (node->key < key) node->right = RemovePrivate(node->right, key);
      else
      {
        Node<T>* LeftSubTr = node->left;
        Node<T>* RightSubTr = node->right;
        delete node;
        size--;
        if (!RightSubTr) return LeftSubTr;
        Node<T>* MinNode = FindMin(RightSubTr);
        MinNode->right = RemoveMin(RightSubTr);
        MinNode->left = LeftSubTr;
        return Balance(MinNode);
      }

      return Balance(node);
    }

    void Seq_LKP(Sequence<T>* Seq, Node<T>* node) const
    {
      if (!node) return;
      Seq_LKP(Seq, node->left);
      Seq->Append(node->key);
      Seq_LKP(Seq, node->right);
    }

    public:
      AVLTree(bool (*cmp)(const T& val1, const T& val2)) {root = nullptr; size = 0;}
      ~AVLTree() {while (root) root = RemovePrivate(root, root->key);}
      
      int GetCount() const {return size;}
      
      Sequence<T>* GetSequence() const
      {
        Sequence<T>* Seq = new ArraySequence<T>();
        Seq_LKP(Seq, root);
        return Seq;
      }

      void Add(T const &key) {root = Insert(root, key);}

      void Remove(T const &key) {root = RemovePrivate(root, key);}
            
};