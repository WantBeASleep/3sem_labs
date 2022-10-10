#pragma once

#include <algorithm>

#include "../../sequence.hpp"

using namespace std;

template <typename T>
class Node
{
  public:
    T key;
    int height;
    Node<T>* left, *right;

    Node(T key) 
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
  private:
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

    Node<T>* Insert(Node<T>* node, T data)
    {
      if (!node)
      {
        size++;
        return new Node<T>(data);
      }

      if (data < node->key)
      {
        node->left = Insert(node->left, data);
      }
      if (data > node->key)
      {
        node->right = Insert(node->right, data);
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

    Node<T>* Remove(Node<T>* node, T k)
    {
      if (!node) return nullptr;
      
      if (k < node->key) node->left = Remove(node->left, k);
      else if (k > node->key) node->right = Remove(node->right, k);
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
      AVLTree() {root = nullptr; size = 0;}
      ~AVLTree() {while (root) root = Remove(root, root->key);}
      
      void Append(T key) {root = Insert(root, key);}

      Sequence<T>* GetSequence() const
      {
        Sequence<T>* Seq = new ArraySequence<T>();
        Seq_LKP(Seq, root);
        return Seq;
      }

};