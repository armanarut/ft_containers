#pragma once

namespace ft
{
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
    ft::map<Key, T, Compare, Alloc>::map(const map& other)
        :_alloc(other.alloc),
        _comp(ft_nullptr),
        _nil(ft_nullptr),
        _node_root(ft_nullptr) {*this = other;}

    template <class Key, class T, class Compare, class Alloc>
    ft::map<Key, T, Compare, Alloc>::~map()
    {
        delete _nil;
    }

    template <class Key, class T, class Compare, class Alloc>
    ft::map<Key, T, Compare, Alloc>&
        ft::map<Key, T, Compare, Alloc>::operator=(const map& other)
    {
        //**********clear nodes here

        _alloc = other._alloc;
        _comp = other._comp;
        _nil = other._nil;
        _node_root = other._node_root;
    
        return *this;
    }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::allocator_type 
        ft::map<Key, T, Compare, Alloc>::get_allocator() const
    { return allocator_type(); }

    /********************[Element access]*******************/

    template <class Key, class T, class Compare, class Alloc>
    T&          ft::map<Key, T, Compare, Alloc>::at(const Key& key)
    {
        typename ft::map<Key, T, Compare, Alloc>::iterator it = this->find(key);

        if (it == this->end())
            throw (std::out_of_range("map"));
        return it->data->second;
    }

    template <class Key, class T, class Compare, class Alloc>
    const T&    ft::map<Key, T, Compare, Alloc>::at(const Key& key) const
    {
        typename ft::map<Key, T, Compare, Alloc>::const_iterator it = this->find(key);

        if (it == this->end())
            throw (std::out_of_range("map"));
        return it->data->second;
    }

    template <class Key, class T, class Compare, class Alloc>
    T&          ft::map<Key, T, Compare, Alloc>::operator[](const Key& key)
    {
        typename ft::map<Key, T, Compare, Alloc>::iterator it = this->find(key);

        if (it == this->end())
            return insert(ft::make_pair(key, T())).first->second;
        return it->data->second;
    }

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

    // template <class Key, class T, class Compare, class Alloc>
    // void    ft::map<Key, T, Compare, Alloc>::clear()
    // {
        
    // }

    template <class Key, class T, class Compare, class Alloc>
    ft::pair<typename ft::map<Key, T, Compare, Alloc>::iterator, bool>
        ft::map<Key, T, Compare, Alloc>::insert(const typename ft::map<Key, T, Compare, Alloc>::value_type& value)
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
            if (*tmp->data < value)
            {
                if (tmp->right != _nil)
                    tmp = tmp->right;
                else
                {
                    tmp->right = new_node(tmp, value);
                    success = true;
                }
            }
            else if (tmp->data->first != value.first)
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
        return ft::pair<iterator, bool>(iterator(tmp), success);
    }


    // template <class Key, class T, class Compare, class Alloc>
    // typename ft::map<Key, T, Compare, Alloc>::iterator
    //      ft::map<Key, T, Compare, Alloc>::insert( iterator position,
    //     const value_type& value )
    // {

    // }


    // template <class Key, class T, class Compare, class Alloc>
    // template< class InputIt >
    // void    ft::map<Key, T, Compare, Alloc>::insert( InputIt first, InputIt last )
    // {

    // }
    // template <class Key, class T, class Compare, class Alloc>
    // typename ft::map<Key, T, Compare, Alloc>::iterator
    //     ft::map<Key, T, Compare, Alloc>::erase (iterator position)
    // {
        
    // }
    // template <class Key, class T, class Compare, class Alloc>
    // typename ft::map<Key, T, Compare, Alloc>::iterator
    //     ft::map<Key, T, Compare, Alloc>::erase (iterator first, iterator last)
    // {

    // }
    // template <class Key, class T, class Compare, class Alloc>
    // typename ft::map<Key, T, Compare, Alloc>::size_type
    //     ft::map<Key, T, Compare, Alloc>::erase(const Key& key)
    // {
        
    // }
    // template <class Key, class T, class Compare, class Alloc>
    // void    ft::map<Key, T, Compare, Alloc>::swap (map& other)
    // {

    // }

    /********************[Lookup]*******************/

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::size_type
        ft::map<Key, T, Compare, Alloc>::count(const Key& key) const
    {
        typename ft::map<Key, T, Compare, Alloc>::iterator it = this->find(key);

        return (it != this->end());
    }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::iterator
        ft::map<Key, T, Compare, Alloc>::find(const Key& key)
    {
        typename ft::map<Key, T, Compare, Alloc>::node_type*  tmp = _node_root;

        while (tmp != _nil)
        {
            if (tmp->data->first < key)
            {
                if (tmp->right != _nil)
                    tmp = tmp->right;
                else break;
            }
            else if (tmp->data->first != key)
            {
                if (tmp->left != _nil)
                    tmp = tmp->left;
                else break;
            }
            else return iterator(tmp);
        }
        return this->end();
    }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::const_iterator
        ft::map<Key, T, Compare, Alloc>::find(const Key& key) const
    {
        typename ft::map<Key, T, Compare, Alloc>::node_type*  tmp = _node_root;

        while (tmp != _nil)
        {
            if (tmp->data->first < key)
            {
                if (tmp->right != _nil)
                    tmp = tmp->right;
                else break;
            }
            else if (tmp->data->first != key)
            {
                if (tmp->left != _nil)
                    tmp = tmp->left;
                else break;
            }
            else return const_iterator(tmp);
        }
        return this->end();
    }

    // template <class Key, class T, class Compare, class Alloc>
    // ft::pair<typename ft::map<Key, T, Compare, Alloc>::iterator,
    //     typename ft::map<Key, T, Compare, Alloc>::iterator>
    //     ft::map<Key, T, Compare, Alloc>::equal_range(const Key& key)
    // {

    // }
    // template <class Key, class T, class Compare, class Alloc>
    // ft::pair<typename ft::map<Key, T, Compare, Alloc>::const_iterator,
    //     typename ft::map<Key, T, Compare, Alloc>::const_iterator>
    //     ft::map<Key, T, Compare, Alloc>::equal_range(const Key& key) const
    // {

    // }
    // template <class Key, class T, class Compare, class Alloc>
    // typename ft::map<Key, T, Compare, Alloc>::iterator
    //     ft::map<Key, T, Compare, Alloc>::lower_bound( const Key& key )
    // {
        
    // }
    // template <class Key, class T, class Compare, class Alloc>
    // typename ft::map<Key, T, Compare, Alloc>::const_iterator
    //     ft::map<Key, T, Compare, Alloc>::lower_bound( const Key& key ) const
    // {

    // }
    // template <class Key, class T, class Compare, class Alloc>
    // typename ft::map<Key, T, Compare, Alloc>::iterator
    //     ft::map<Key, T, Compare, Alloc>::upper_bound( const Key& key )
    // {

    // }
    // template <class Key, class T, class Compare, class Alloc>
    // typename ft::map<Key, T, Compare, Alloc>::const_iterator
    //     ft::map<Key, T, Compare, Alloc>::upper_bound( const Key& key ) const
    // {

    // }

    /********************[Observers]*******************/

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::key_compare
        ft::map<Key, T, Compare, Alloc>::key_comp() const
    { return key_compare(); }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::value_compare
        ft::map<Key, T, Compare, Alloc>::value_comp() const
    {
        return value_compare(typename ft::map<Key, T, Compare, Alloc>::key_compare());
    }

    /********************[Private functions]*******************/

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::node_type*
        ft::map<Key, T, Compare, Alloc>::new_node(node_type* parent, value_type value)
    {
        node_type* new_node = new node_type;

        new_node->data = _alloc.allocate(1);
        _alloc.construct(new_node->data, value);
        new_node->parent = parent;
        new_node->left = _nil;
        new_node->right = _nil;
        new_node->color = RED;
        new_node->leaf = true;
        return new_node;
    }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::node_type*
        ft::map<Key, T, Compare, Alloc>::new_nil()
    {
        node_type*  new_node = new node_type;

        new_node->data = ft::ft_nullptr;
        new_node->parent = ft::ft_nullptr;
        new_node->left = ft::ft_nullptr;
        new_node->right = ft::ft_nullptr;
        new_node->color = BLACK;
        new_node->color = false;

        return new_node;
    }

    /********************[Non-Member functions]*******************/

    template <class Key, class T, class Compare, class Alloc>
    bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
        const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
        const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return !(lhs == rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
       const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
        const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return !(rhs < lhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
       const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return rhs < lhs;
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
        const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return !(lhs < rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    void swap( ft::map<Key,T,Compare,Alloc>& lhs,
           ft::map<Key,T,Compare,Alloc>& rhs )
    {
        ft::map<Key, T, Compare, Alloc> tmp(lhs);
        lhs = rhs;
        rhs = tmp;
    }
}