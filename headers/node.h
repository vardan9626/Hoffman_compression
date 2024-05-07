//
// Created by vardan on 5/7/24.
//

#ifndef COMPRESSOR_NODE_H
#define COMPRESSOR_NODE_H

#endif //COMPRESSOR_NODE_H
#include "headers.h"

struct node
{
    node *left;
    node *right;
    bool isEnd = false;
    char alp;
    long long val = 0;
    node(char alphabet, int value, bool end = 1, node *left_ptr = nullptr, node *right_ptr = nullptr)
    {
        this->alp = alphabet;
        this->isEnd = end;
        this->left = left_ptr;
        this->right = right_ptr;
        this->val = value;
    }
};

struct Comparator
{
    bool operator()(node *a, node *b)
    {
        return a->val > b->val;
    }
};
