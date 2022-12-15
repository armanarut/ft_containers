#pragma once

#include "type_traits.hpp"

namespace ft
{
    enum color_t {BLACK, RED};
    #define LEFT  0
    #define RIGHT 1
    #define left  child[LEFT]
    #define right child[RIGHT]
    #define CHILD_DIR(N) ( N == (N->parent)->right ? RIGHT : LEFT )

    template <typename T>
    struct RBnode
    {
        typedef T   value_type;

        RBnode*         parent;
        RBnode*         child[2];
        enum color_t    color;
        value_type*     data;

        // RBnode& operator=(const RBnode& other)
        // {
        //     data = other.data;
        //     parent = other.parent;
        //     left = other.left;
        //     right = other.right;
        //     color = other.color;
        //     leaf = other.leaf;
        //     return *this;
        // }
    };

    template <class U>
    struct tree_iterator_map
    {
        typedef bidirectional_iterator_tag                                      iterator_category;
        typedef typename ft::iterator<iterator_category, U>::value_type         value_type;
        typedef typename ft::iterator<iterator_category, U>::pointer            pointer;
        typedef typename ft::iterator<iterator_category, U>::reference          reference;
        typedef typename ft::iterator<iterator_category, U>::difference_type    difference_type;
        typedef RBnode<value_type>                                                node_type;

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
            if (_node->right)
            {
                _node = _node->right;
                while (_node->left)
                    _node = _node->left;
            }
            else
            {
                node_type*  tmp = _node->parent;
                while (_node == tmp->right)
                {
                    _node = tmp;
                    tmp = _node->parent;
                }
                _node = tmp;
                if (_node->parent == tmp->parent)
                {
                    while (_node->right)
                        _node = _node->right;
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