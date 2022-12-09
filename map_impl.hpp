#pragma once

namespace ft
{

    template <class Key, class T, class Compare, class Alloc>
    template <class U>
    typename ft::map<Key, T, Compare, Alloc>::template bidirectional_iterator_map<U>&
        ft::map<Key, T, Compare, Alloc>::bidirectional_iterator_map<U>::operator++()
    {
        while (1)
        {
            if (p->right != _nil)
            {
                p = p->right;
                while (p->left != _nil)
                    p = p->left;
                break ;
            }
            else
            {
                while (p == p->parent->right)
                    p = p->parent;
                if (p->parent != p->parent->parent)
                    p = p->parent;
                else
                {
                while (p->right != _nil)
                    p = p->right;
                    return _nil;
                }
            }
        }
        return p;
    }

    template <class Key, class T, class Compare, class Alloc>
    template <class U>
    typename ft::map<Key, T, Compare, Alloc>::template bidirectional_iterator_map<U>
        ft::map<Key, T, Compare, Alloc>::bidirectional_iterator_map<U>::operator++(int)
    {


    }

    template <class Key, class T, class Compare, class Alloc>
    template <class U>
    typename ft::map<Key, T, Compare, Alloc>::template bidirectional_iterator_map<U>&
        ft::map<Key, T, Compare, Alloc>::bidirectional_iterator_map<U>::operator--()
    {


    }

    template <class Key, class T, class Compare, class Alloc>
    template <class U>
    typename ft::map<Key, T, Compare, Alloc>::template bidirectional_iterator_map<U>
        ft::map<Key, T, Compare, Alloc>::bidirectional_iterator_map<U>::operator--(int)
    {


    }

    template <class Key, class T, class Compare, class Alloc>
    ft::map<Key, T, Compare, Alloc>::map()
        :_alloc(allocator_type()),
        _comp(key_compare()),
        _nil(new_nil()),
        _node_root(_nil)
    {}

    template <class Key, class T, class Compare, class Alloc>
    ft::map<Key, T, Compare, Alloc>::map(const Compare& comp, const allocator_type& alloc)
        :_alloc(alloc),
        _comp(comp),
        _nil(new_nil()),
        _node_root(_nil)
    {}

    // template <class Key, class T, class Compare, class Alloc>
    // template <class InputIt>
    // ft::map<Key, T, Compare, Alloc>::map(InputIt first, InputIt last,
    //     const Compare& comp, const allocator_type& alloc)
    //     :_alloc(alloc),
    //     _comp(comp),
    //     _nil(new_nil()),
    //     _node_root(_nil)
    // {}

    template <class Key, class T, class Compare, class Alloc>
    ft::map<Key, T, Compare, Alloc>::~map()
    {
        delete _nil;
    }

    // template <class Key, class T, class Compare, class Alloc>
    // ft::map<Key, T, Compare, Alloc>&
    //     ft::map<Key, T, Compare, Alloc>::operator=(const map& other)
    // {



    //     return *this;
    // }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::allocator_type 
        ft::map<Key, T, Compare, Alloc>::get_allocator() const
    { return allocator_type(); }

    // template <class Key, class T, class Compare, class Alloc>
    // T&          ft::map<Key, T, Compare, Alloc>::at(const Key& key)
    // {

    // }

    // template <class Key, class T, class Compare, class Alloc>
    // const T&    ft::map<Key, T, Compare, Alloc>::at(const Key& key) const
    // {

    // }

    // template <class Key, class T, class Compare, class Alloc>
    // T&          ft::map<Key, T, Compare, Alloc>::operator[](const Key& key)
    // {
        
    // }

    /********************[Iterators]*******************/

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::iterator
        ft::map<Key, T, Compare, Alloc>::begin()
    {
        t_node<typename ft::map<Key, T, Compare, Alloc>::value_type>*   \
            tmp = _node_root;

        while (tmp->left != _nil)
            tmp = tmp->left;
        return iterator(tmp);
    }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::const_iterator
        ft::map<Key, T, Compare, Alloc>::begin() const
    {
        t_node<typename ft::map<Key, T, Compare, Alloc>::value_type>*   \
            tmp = _node_root;

        while (tmp->left != _nil)
            tmp = tmp->left;
        return const_iterator(tmp);
    }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::iterator
        ft::map<Key, T, Compare, Alloc>::end()
    { return iterator(_nil); }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::const_iterator
        ft::map<Key, T, Compare, Alloc>::end() const
    { return const_iterator(_nil); }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::reverse_iterator
        ft::map<Key, T, Compare, Alloc>::rbegin()
    { return reverse_iterator(this->end()); }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::const_reverse_iterator
        ft::map<Key, T, Compare, Alloc>::rbegin() const
    { return const_reverse_iterator(this->end()); }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::reverse_iterator
        ft::map<Key, T, Compare, Alloc>::rend()
    { return reverse_iterator(this->begin()); }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::const_reverse_iterator
        ft::map<Key, T, Compare, Alloc>::rend() const
    { return const_reverse_iterator(this->begin()); }

    /********************[Modifiers]*******************/

    template <class Key, class T, class Compare, class Alloc>
    ft::pair<typename ft::map<Key, T, Compare, Alloc>::iterator, bool>
        insert(const typename ft::map<Key, T, Compare, Alloc>::value_type& value)
    {
        typename ft::map<Key, T, Compare, Alloc>::node_type*  tmp = _node_root;
        bool    success = false;

        if (tmp == _nil)
        {
            _node_root = new_node(_nil, value);
            success = true;
        }
        while (!success)
        {
            if (tmp->data < value)
            {
                if (tmp->right != _nil)
                    tmp = tmp->right;
                else
                {
                    tmp->right = new_node(tmp, value);
                    success = true;
                }
            }
            else if (tmp->data != value)
            {
                if (tmp->left != _nil)
                    tmp = tmp->left;
                else
                {
                    tmp->left = new_node(tmp, value);
                    success = true;
                }
            }
            else break;
        }
        return ft::pair<iterator, bool>(iterator(tmp, success));
    }





    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::node_type*
        ft::map<Key, T, Compare, Alloc>::new_node(node_type* parent, value_type value)
    {
        node_type* new_node = new node_type;

        new_node->data = value;
        new_node->parent = parent;
        new_node->left = _nil;
        new_node->right = _nil;
        new_node->black = false;

        return new_node;
    }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::node_type*
        ft::map<Key, T, Compare, Alloc>::new_nil()
    {
        node_type*  new_node = node_type;

        new_node->parent = ft::ft_nullptr;
        new_node->left = ft::ft_nullptr;
        new_node->right = ft::ft_nullptr;
        new_node->black = true;

        return new_node;
    }
}