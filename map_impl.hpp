#pragma once

namespace ft
{
    template <class Key, class T, class Compare, class Alloc>
    ft::map<Key, T, Compare, Alloc>::map(const Compare& comp, const allocator_type& alloc)
        :_tree(comp, alloc)
    {}

    template <class Key, class T, class Compare, class Alloc>
    template <class InputIt>
    ft::map<Key, T, Compare, Alloc>::map(InputIt first, InputIt last,
        const Compare& comp, const allocator_type& alloc)
        :_tree(comp, alloc)
    {
        insert(first, last);
    }

    template <class Key, class T, class Compare, class Alloc>
    ft::map<Key, T, Compare, Alloc>::map(const map& other)
        :_tree(ft_nullptr) {*this = other;}

    template <class Key, class T, class Compare, class Alloc>
    ft::map<Key, T, Compare, Alloc>::~map()
    {}

    template <class Key, class T, class Compare, class Alloc>
    ft::map<Key, T, Compare, Alloc>&
        ft::map<Key, T, Compare, Alloc>::operator=(const map& other)
    {
        _tree = other._tree;
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
        return it->second;
    }

    template <class Key, class T, class Compare, class Alloc>
    const T&    ft::map<Key, T, Compare, Alloc>::at(const Key& key) const
    {
        typename ft::map<Key, T, Compare, Alloc>::const_iterator it = this->find(key);

        if (it == this->end())
            throw (std::out_of_range("map"));
        return it->second;
    }

    template <class Key, class T, class Compare, class Alloc>
    T&          ft::map<Key, T, Compare, Alloc>::operator[](const Key& key)
    {
        typename ft::map<Key, T, Compare, Alloc>::iterator it = this->find(key);

        if (it == this->end())
            return insert(ft::make_pair(key, T())).first->second;
        return it->second;
    }

    /********************[Iterators]*******************/

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::iterator
        ft::map<Key, T, Compare, Alloc>::begin()
    {
        return _tree.begin();
    }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::const_iterator
        ft::map<Key, T, Compare, Alloc>::begin() const
    {
        return _tree.begin();
    }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::iterator
        ft::map<Key, T, Compare, Alloc>::end()
    { return _tree.end(); }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::const_iterator
        ft::map<Key, T, Compare, Alloc>::end() const
    { return _tree.end(); }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::reverse_iterator
        ft::map<Key, T, Compare, Alloc>::rbegin()
    { return _tree.rbegin(); }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::const_reverse_iterator
        ft::map<Key, T, Compare, Alloc>::rbegin() const
    { return _tree.rbegin(); }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::reverse_iterator
        ft::map<Key, T, Compare, Alloc>::rend()
    { return _tree.rend(); }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::const_reverse_iterator
        ft::map<Key, T, Compare, Alloc>::rend() const
    { return _tree.rend(); }

    /********************[Capacity]*******************/

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::size_type
        ft::map<Key, T, Compare, Alloc>::size() const
    {
        return _tree.size();
    }

    template <class Key, class T, class Compare, class Alloc>
    bool    ft::map<Key, T, Compare, Alloc>::empty() const
    {
        return _tree.empty();
    }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::size_type
        ft::map<Key, T, Compare, Alloc>::max_size() const
    {
        return _tree.max_size();
    }

    /********************[Modifiers]*******************/

    template <class Key, class T, class Compare, class Alloc>
    void    ft::map<Key, T, Compare, Alloc>::clear()
    {
        /*****************************************************************************************************/
    }

    template <class Key, class T, class Compare, class Alloc>
    ft::pair<typename ft::map<Key, T, Compare, Alloc>::iterator, bool>
        ft::map<Key, T, Compare, Alloc>::insert(const typename ft::map<Key, T, Compare, Alloc>::value_type& value)
    {
        return _tree.insert(value);
    }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::iterator
         ft::map<Key, T, Compare, Alloc>::insert( iterator position,
        const value_type& value )
    {
        (void)position;
        ft::pair<typename ft::map<Key, T, Compare, Alloc>::iterator, bool> it = insert(value);
        return it->first;
    }

    template <class Key, class T, class Compare, class Alloc>
    template< class InputIt >
    void    ft::map<Key, T, Compare, Alloc>::insert( InputIt first, InputIt last )
    {
        while (first != last)
        {
            insert(*first);
            ++first;
        }
    }

    template <class Key, class T, class Compare, class Alloc>
    void    ft::map<Key, T, Compare, Alloc>::erase (iterator position)
    {
        return _tree.delete_node(position.base());
    }

    template <class Key, class T, class Compare, class Alloc>
    void    ft::map<Key, T, Compare, Alloc>::erase (iterator first, iterator last)
    {
        node_type* it;
        while (first != last)
        {
            it = _tree.delete_node(first.base());
            ++first;
        }
        return it;
    }
    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::size_type
        ft::map<Key, T, Compare, Alloc>::erase(const Key& key)
    {
        iterator it = find(key);
        if (it == end())
            return 0;
        else
            erase(it);
        return 1;
    }

    template <class Key, class T, class Compare, class Alloc>
    void    ft::map<Key, T, Compare, Alloc>::swap (map& other)
    {
        typename ft::map<Key, T, Compare, Alloc>::tree_type buff = _tree;
        _tree = other._tree;
        other._tree = buff;
    }

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
        return _tree.find(get_value_type(key));
    }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::const_iterator
        ft::map<Key, T, Compare, Alloc>::find(const Key& key) const
    {
        return _tree.find(get_value_type(key));
    }

    template <class Key, class T, class Compare, class Alloc>
    ft::pair<typename ft::map<Key, T, Compare, Alloc>::iterator,
        typename ft::map<Key, T, Compare, Alloc>::iterator>
        ft::map<Key, T, Compare, Alloc>::equal_range(const Key& key)
    {
        return _tree.equal_range(get_value_type(key));
    }

    template <class Key, class T, class Compare, class Alloc>
    ft::pair<typename ft::map<Key, T, Compare, Alloc>::const_iterator,
        typename ft::map<Key, T, Compare, Alloc>::const_iterator>
        ft::map<Key, T, Compare, Alloc>::equal_range(const Key& key) const
    {
        return _tree.equal_range(get_value_type(key));
    }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::iterator
        ft::map<Key, T, Compare, Alloc>::lower_bound( const Key& key )
    {
        return _tree.lower_bound(get_value_type(key));
    }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::const_iterator
        ft::map<Key, T, Compare, Alloc>::lower_bound( const Key& key ) const
    {
        return _tree.lower_bound(get_value_type(key));
    }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::iterator
        ft::map<Key, T, Compare, Alloc>::upper_bound( const Key& key )
    {
        return _tree.upper_bound(get_value_type(key));
    }

    template <class Key, class T, class Compare, class Alloc>
    typename ft::map<Key, T, Compare, Alloc>::const_iterator
        ft::map<Key, T, Compare, Alloc>::upper_bound( const Key& key ) const
    {
        return _tree.upper_bound(get_value_type(key));
    }

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