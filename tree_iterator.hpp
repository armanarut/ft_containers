#pragma once

#include <memory>
#include "type_traits.hpp"

namespace ft
{
    enum color_t {BLACK, RED};
    #define LEFT  0
    #define RIGHT 1
    #define CHILD_DIR(N) ( N == (N->parent)->right ? RIGHT : LEFT )

    template <typename T>
    struct RBnode
    {
        typedef T       value_type;

        RBnode*         parent;
        RBnode*         child[2];
        enum color_t    color;
        value_type      data;

        RBnode():data(0){};
        RBnode(value_type data):data(data){};
    };

    template <class U>
    struct tree_iterator
    {
        typedef std::bidirectional_iterator_tag                                 iterator_category;
        typedef typename ft::iterator<iterator_category, U>::value_type         value_type;
        typedef typename ft::iterator<iterator_category, U>::pointer            pointer;
        typedef typename ft::iterator<iterator_category, U>::reference          reference;
        typedef typename ft::iterator<iterator_category, U>::difference_type    difference_type;
        typedef RBnode<value_type>                                              node_type;
        typedef RBnode<const value_type>                                        const_node_type;
        typedef tree_iterator<U>                                                iterator;
        typedef tree_iterator<const U>                                          const_iterator;

        tree_iterator():_node(NULL) {}
        tree_iterator(node_type* it):_node(it) {}
        tree_iterator(const tree_iterator& other):_node(other.base()) {}

        virtual     ~tree_iterator() {}

        tree_iterator&  operator=(const tree_iterator& other)
        {
            _node = other.base();
            return *this;
        }

        operator const_iterator () const
        { return const_iterator(reinterpret_cast<const_node_type *>(_node)); }

        node_type*      base() const
        { return _node; }

        tree_iterator&  operator++()
        {
            if (_node->child[RIGHT])
            {
                _node = _node->child[RIGHT];
                while (_node->child[LEFT])
                    _node = _node->child[LEFT];
            }
            else
            {
                node_type*  tmp = _node->parent;
                while (_node == tmp->child[RIGHT])
                {
                    _node = tmp;
                    tmp = _node->parent;
                }
                _node = tmp;
            }
            return *this;
        };

        tree_iterator   operator++(int)
        {
            tree_iterator last(*this);
            operator++();
            return last;
        };

        tree_iterator&  operator--()
        {
            if (_node->child[LEFT])
            {
                _node = _node->child[LEFT];
                while (_node->child[RIGHT])
                    _node = _node->child[RIGHT];
            }
            else
            {
                node_type*  tmp = _node->parent;
                if (_node == tmp->parent && !_node->child[RIGHT] && !_node->child[LEFT])
                {
                    _node = tmp;
                    while (_node->child[RIGHT])
                        _node = _node->child[RIGHT];
                }
                else
                {
                    while (_node == tmp->child[LEFT])
                    {
                        _node = tmp;
                        tmp = _node->parent;
                    }
                    if (_node != tmp->parent)
                        _node = tmp;
                }
            }
            return *this;
        };

        tree_iterator   operator--(int)
        {
            tree_iterator   last(*this);
            operator--();
            return last;
        };

        reference   operator*() const   { return _node->data; }
        pointer     operator->() const  { return &_node->data; }

        bool    operator == ( tree_iterator const& t )  { return  _node == t._node; };
		bool	operator != ( tree_iterator const& t )  { return  _node != t._node; };
		bool	operator > ( tree_iterator const& t )   { return  _node > t._node; };
		bool	operator <= ( tree_iterator const& t )  { return  _node <= t._node; };
		bool	operator < ( tree_iterator const& t )   { return  _node < t._node; };
		bool    operator >= ( tree_iterator const& t )  { return  _node >= t._node; };

    protected:
        node_type*  _node;
    };

    template <class T>
        bool    operator==(const ft::tree_iterator<T>& lhs, 
        const ft::tree_iterator<const T>& rhs)
    { return *lhs == *rhs; }

    template <class T>
        bool    operator!=(const ft::tree_iterator<T>& lhs, 
        const ft::tree_iterator<const T>& rhs)
    { return *lhs != *rhs; }

    template <class T>
        bool    operator>(const ft::tree_iterator<T>& lhs, 
        const ft::tree_iterator<const T>& rhs)
    { return *lhs < *rhs; }

    template <class T>
        bool    operator>=(const ft::tree_iterator<T>& lhs, 
        const ft::tree_iterator<const T>& rhs)
    { return *lhs <= *rhs; }

    template <class T>
        bool    operator<(const ft::tree_iterator<T>& lhs, 
        const ft::tree_iterator<const T>& rhs)
    { return *lhs > *rhs; }

    template <class T>
        bool    operator<=(const ft::tree_iterator<T>& lhs, 
        const ft::tree_iterator<const T>& rhs)
    { return *lhs >= *rhs; }
}