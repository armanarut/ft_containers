#pragma once

#include "iterator.hpp"

#define BLACK   0;
#define RED     1;

namespace ft
{
    template <typename T>
    struct t_node
    {
        typedef T   value_type;

        value_type* data;
        t_node*     parent;
        t_node*     left;
        t_node*     right;
        bool        color;
        bool        leaf;

        t_node& operator=(const t_node& other)
        {
            data = other.data;
            parent = other.parent;
            left = other.left;
            right = other.right;
            color = other.color;
            leaf = other.leaf;
            return *this;
        }
    };

    template <class U>
    struct tree_iterator_map
    {
        typedef bidirectional_iterator_tag                                      iterator_category;
        typedef typename ft::iterator<iterator_category, U>::value_type         value_type;
        typedef typename ft::iterator<iterator_category, U>::pointer            pointer;
        typedef typename ft::iterator<iterator_category, U>::reference          reference;
        typedef typename ft::iterator<iterator_category, U>::difference_type    difference_type;
        typedef t_node<value_type>                                                node_type;

        tree_iterator_map():_node(ft_nullptr) {}
        tree_iterator_map(node_type* it):_node(it) {}
        tree_iterator_map(const tree_iterator_map& other):_node(other._node) {}
        tree_iterator_map& operator=(const tree_iterator_map& other) {
            _node = other._node;
            return *this;}
        virtual ~tree_iterator_map() {}

        operator tree_iterator_map<const value_type> () const {
            return tree_iterator_map<const value_type>(this->_node);}

        pointer base() const {return this->_node;}

        tree_iterator_map&  operator++()
        {
        while (1)
        {
            if (_node->right->leaf)
            {
                _node = _node->right;
                while (_node->left->leaf)
                    _node = _node->left;
                break ;
            }
            else
            {
                while (_node == _node->parent->right)
                    _node = _node->parent;
                if (_node->parent != _node->parent->parent)
                    _node = _node->parent;
                else
                {
                while (_node->right->leaf)
                    _node = _node->right;
                    return _node->right;
                }
            }
        }
        return _node;
        }

        tree_iterator_map   operator++(int);
        tree_iterator_map&  operator--();
        tree_iterator_map   operator--(int);

        reference   operator*() {return *_node->data;}
        pointer     operator->() {return _node->data;}

    protected:
        node_type* _node;
    };
}