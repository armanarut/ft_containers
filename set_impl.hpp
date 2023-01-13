#pragma once

namespace ft
{
    template <class Key, class Compare, class Alloc>
    ft::set<Key, Compare, Alloc>::set(const Compare& comp, const Alloc& alloc)
        :_tree(comp, alloc)
    {}

    template <class Key, class Compare, class Alloc>
    template <class InputIt>
    ft::set<Key, Compare, Alloc>::set(InputIt first, InputIt last,
        const Compare& comp, const Alloc& alloc)
        :_tree(comp, alloc)
    { insert(first, last); }

    template <class Key, class Compare, class Alloc>
    ft::set<Key, Compare, Alloc>::set(const set& other)
        :_tree(Compare(), Alloc())
    { *this = other; }

    template <class Key, class Compare, class Alloc>
    ft::set<Key, Compare, Alloc>::~set()
    {}

    template <class Key, class Compare, class Alloc>
    ft::set<Key, Compare, Alloc>&
        ft::set<Key, Compare, Alloc>::operator=(const set& other)
    {
        _tree = other._tree;
        return *this;
    }

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::allocator_type 
        ft::set<Key, Compare, Alloc>::get_allocator() const
    { return allocator_type(); }

    /********************[Iterators]*******************/

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::iterator
        ft::set<Key, Compare, Alloc>::begin()
    { return _tree.begin(); }

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::const_iterator
        ft::set<Key, Compare, Alloc>::begin() const
    { return _tree.begin(); }

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::iterator
        ft::set<Key, Compare, Alloc>::end()
    { return _tree.end(); }

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::const_iterator
        ft::set<Key, Compare, Alloc>::end() const
    { return _tree.end(); }

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::reverse_iterator
        ft::set<Key, Compare, Alloc>::rbegin()
    { return _tree.rbegin(); }

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::const_reverse_iterator
        ft::set<Key, Compare, Alloc>::rbegin() const
    { return _tree.rbegin(); }

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::reverse_iterator
        ft::set<Key, Compare, Alloc>::rend()
    { return _tree.rend(); }

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::const_reverse_iterator
        ft::set<Key, Compare, Alloc>::rend() const
    { return _tree.rend(); }

    /********************[Capacity]*******************/

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::size_type
        ft::set<Key, Compare, Alloc>::size() const
    { return _tree.size(); }

    template <class Key, class Compare, class Alloc>
    bool    ft::set<Key, Compare, Alloc>::empty() const
    { return _tree.empty(); }

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::size_type
        ft::set<Key, Compare, Alloc>::max_size() const
    { return _tree.max_size(); }

    /********************[Modifiers]*******************/

    template <class Key, class Compare, class Alloc>
    void    ft::set<Key, Compare, Alloc>::clear()
    { _tree.clear(); }

    template <class Key, class Compare, class Alloc>
    ft::pair<typename ft::set<Key, Compare, Alloc>::iterator, bool>
        ft::set<Key, Compare, Alloc>::insert(const typename ft::set<Key, Compare, Alloc>::value_type& value)
    { return _tree.insert(value); }

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::iterator
         ft::set<Key, Compare, Alloc>::insert( iterator position,
        const value_type& value )
    {
        (void)position;
        ft::pair<typename ft::set<Key, Compare, Alloc>::iterator, bool> it = insert(value);
        return it.first;
    }

    template <class Key, class Compare, class Alloc>
    template< class InputIt >
    void    ft::set<Key, Compare, Alloc>::insert( InputIt first, InputIt last )
    {
        while (first != last)
        {
            insert(*first);
            ++first;
        }
    }

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::iterator
        ft::set<Key, Compare, Alloc>::erase (iterator position)
    {
        if (position != this->end())
            return _tree.delete_node(position.base());
        return position;
    }

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::iterator
        ft::set<Key, Compare, Alloc>::erase (iterator first, iterator last)
    {
        iterator it;

        while (first != last)
        {
            it = first++;
            _tree.delete_node(it.base());
        }
        return first;
    }
    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::size_type
        ft::set<Key, Compare, Alloc>::erase(const Key& key)
    {
        iterator it = find(key);
        if (it == end())
            return 0;
        else
            erase(it);
        return 1;
    }

    template <class Key, class Compare, class Alloc>
    void    ft::set<Key, Compare, Alloc>::swap (set& other)
    { _tree.swap(other._tree); }

    /********************[Lookup]*******************/

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::size_type
        ft::set<Key, Compare, Alloc>::count(const Key& key) const
    { return (this->find(key) != this->end()); }

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::iterator
        ft::set<Key, Compare, Alloc>::find(const Key& key)
    { return _tree.find(key); }

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::const_iterator
        ft::set<Key, Compare, Alloc>::find(const Key& key) const
    { return _tree.find(key); }

    template <class Key, class Compare, class Alloc>
    ft::pair<typename ft::set<Key, Compare, Alloc>::iterator,
        typename ft::set<Key, Compare, Alloc>::iterator>
        ft::set<Key, Compare, Alloc>::equal_range(const Key& key)
    { return _tree.equal_range(key); }

    template <class Key, class Compare, class Alloc>
    ft::pair<typename ft::set<Key, Compare, Alloc>::const_iterator,
        typename ft::set<Key, Compare, Alloc>::const_iterator>
        ft::set<Key, Compare, Alloc>::equal_range(const Key& key) const
    { return _tree.equal_range(key); }

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::iterator
        ft::set<Key, Compare, Alloc>::lower_bound( const Key& key )
    { return _tree.lower_bound(key); }

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::const_iterator
        ft::set<Key, Compare, Alloc>::lower_bound( const Key& key ) const
    { return _tree.lower_bound(key); }

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::iterator
        ft::set<Key, Compare, Alloc>::upper_bound( const Key& key )
    { return _tree.upper_bound(key); }

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::const_iterator
        ft::set<Key, Compare, Alloc>::upper_bound( const Key& key ) const
    { return _tree.upper_bound(key); }

    /********************[Observers]*******************/

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::key_compare
        ft::set<Key, Compare, Alloc>::key_comp() const
    { return key_compare(); }

    template <class Key, class Compare, class Alloc>
    typename ft::set<Key, Compare, Alloc>::value_compare
        ft::set<Key, Compare, Alloc>::value_comp() const
    { return value_compare(typename ft::set<Key, Compare, Alloc>::key_compare()); }

    /********************[Non-Member functions]*******************/

    template <class Key, class Compare, class Alloc>
    bool operator==( const ft::set<Key, Compare, Alloc>& lhs,
        const ft::set<Key, Compare, Alloc>& rhs )
    {
        if ( lhs.size() != rhs.size() ) return false;
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class Key, class Compare, class Alloc>
    bool operator!=( const ft::set<Key, Compare, Alloc>& lhs,
        const ft::set<Key, Compare, Alloc>& rhs )
    { return !(lhs == rhs); }

    template <class Key, class Compare, class Alloc>
    bool operator<( const ft::set<Key, Compare, Alloc>& lhs,
       const ft::set<Key, Compare, Alloc>& rhs )
    { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

    template <class Key, class Compare, class Alloc>
    bool operator<=( const ft::set<Key, Compare, Alloc>& lhs,
        const ft::set<Key, Compare, Alloc>& rhs )
    { return !(rhs < lhs); }

    template <class Key, class Compare, class Alloc>
    bool operator>( const ft::set<Key, Compare, Alloc>& lhs,
       const ft::set<Key, Compare, Alloc>& rhs )
    { return rhs < lhs; }

    template <class Key, class Compare, class Alloc>
    bool operator>=( const ft::set<Key, Compare, Alloc>& lhs,
        const ft::set<Key, Compare, Alloc>& rhs )
    { return !(lhs < rhs); }

    template <class Key, class Compare, class Alloc>
    void swap( ft::set<Key, Compare, Alloc>& lhs,
           ft::set<Key, Compare, Alloc>& rhs )
    {
        ft::set<Key, Compare, Alloc> tmp(lhs);
        lhs = rhs;
        rhs = tmp;
    }
}