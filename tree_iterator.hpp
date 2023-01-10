#pragma once

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
        typedef T   value_type;

        RBnode*         parent;
        RBnode*         child[2];
        enum color_t    color;
        value_type      data;

        RBnode(){};
        RBnode(value_type data):data(data){};
    
        // RBnode& operator=(const RBnode& other)
        // {
        //     parent = other.parent;
        //     child[LEFT] = other.child[LEFT];
        //     child[RIGHT] = other.child[RIGHT];
        //     color = other.color;
        //     data = other.data;
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
        typedef RBnode<value_type>                                              node_type;
        typedef RBnode<const value_type>                                        const_node_type;
        typedef tree_iterator_map<U>                                            iterator;
        typedef tree_iterator_map<const U>                                      const_iterator;

        tree_iterator_map():_node(NULL) {}
        tree_iterator_map(node_type* it):_node(it) {}
        tree_iterator_map(const tree_iterator_map& other):_node(other.base()) {}
        tree_iterator_map& operator=(const tree_iterator_map& other) {
            _node = other.base();
            return *this;}
        virtual ~tree_iterator_map() {}

        operator const_iterator () const {
            return const_iterator(reinterpret_cast<const_node_type *>(_node));}

        node_type* base() const {return _node;}

        tree_iterator_map&  operator++()
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
                // if (_node != tmp->parent)
                    _node = tmp;
            }
            return *this;
        };

        tree_iterator_map   operator++(int)
        {
            tree_iterator_map last(*this);
            operator++();
            return last;
        };

        tree_iterator_map&  operator--()
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
                if (_node == tmp->parent && !_node->child[RIGHT] && !_node->child[LEFT])    // When _node is end()
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

        tree_iterator_map   operator--(int)
        {
            tree_iterator_map last(*this);
            operator--();
            return last;
        };

        reference   operator*() const {return _node->data;}
        pointer     operator->() const {return &_node->data;}



        bool		operator == ( tree_iterator_map const& t ) 		            {	return  _node == t._node;	};
		bool		operator != ( tree_iterator_map const& t )		            {	return  _node != t._node;	};
		bool		operator > ( tree_iterator_map const& t ) 		            {	return  _node > t._node;	};
		bool		operator <= ( tree_iterator_map const& t ) 		            {	return  _node <= t._node;	};
		bool		operator < ( tree_iterator_map const& t ) 		            {	return  _node < t._node;	};
		bool 	    operator >= ( tree_iterator_map const& t ) 		            {	return  _node >= t._node;	};

    protected:
        node_type* _node;
    };

    // template <class T>
    //     bool    operator==(const ft::tree_iterator_map<T>& lhs, 
    //     const ft::tree_iterator_map<T>& rhs)
    // {
    //     return lhs.base() == rhs.base();
    // }

    // template <class T, class U>
    //     bool    operator==(const ft::tree_iterator_map<T>& lhs, 
    //     const ft::tree_iterator_map<U>& rhs)
    // {
    //     return lhs.base() == rhs.base();
    // }

    // template <class T>
    //     bool    operator!=(const ft::tree_iterator_map<T>& lhs, 
    //     const ft::tree_iterator_map<T>& rhs)
    // {
    //     return lhs.base() != rhs.base();
    // }

    // template <class T, class U>
    //     bool    operator!=(const ft::tree_iterator_map<T>& lhs, 
    //     const ft::tree_iterator_map<U>& rhs)
    // {
    //     return lhs.base() != rhs.base();
    // }

    // template <class T>
    //     bool    operator>(const ft::tree_iterator_map<T>& lhs, 
    //     const ft::tree_iterator_map<T>& rhs)
    // {
    //     return lhs.base() < rhs.base();
    // }

    // template <class T, class U>
    //     bool    operator>(const ft::tree_iterator_map<T>& lhs, 
    //     const ft::tree_iterator_map<U>& rhs)
    // {
    //     return lhs.base() < rhs.base();
    // }

    // template <class T>
    //     bool    operator>=(const ft::tree_iterator_map<T>& lhs, 
    //     const ft::tree_iterator_map<T>& rhs)
    // {
    //     return lhs.base() <= rhs.base();
    // }

    // template <class T, class U>
    //     bool    operator>=(const ft::tree_iterator_map<T>& lhs, 
    //     const ft::tree_iterator_map<U>& rhs)
    // {
    //     return lhs.base() <= rhs.base();
    // }

    // template <class T>
    //     bool    operator<(const ft::tree_iterator_map<T>& lhs, 
    //     const ft::tree_iterator_map<T>& rhs)
    // {
    //     return lhs.base() > rhs.base();
    // }

    // template <class T, class U>
    //     bool    operator<(const ft::tree_iterator_map<T>& lhs, 
    //     const ft::tree_iterator_map<U>& rhs)
    // {
    //     return lhs.base() > rhs.base();
    // }

    // template <class T>
    //     bool    operator<=(const ft::tree_iterator_map<T>& lhs, 
    //     const ft::tree_iterator_map<T>& rhs)
    // {
    //     return lhs.base() >= rhs.base();
    // }

    // template <class T, class U>
    //     bool    operator<=(const ft::tree_iterator_map<T>& lhs, 
    //     const ft::tree_iterator_map<U>& rhs)
    // {
    //     return lhs.base() >= rhs.base();
    // }
    
}