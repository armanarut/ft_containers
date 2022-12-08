#pragma once

namespace ft
{
    template <class T, class Container>
    ft::stack<T, Container>::stack(const Container& cont)
        :c(cont) {}

    template <class T, class Container>
    ft::stack<T, Container>::stack( const stack& other )
        :c(other.c) {}

    template <class T, class Container>
    ft::stack<T, Container>::~stack()
    {}

    template <class T, class Container>
    ft::stack<T, Container>&
        ft::stack<T, Container>::operator=(const stack<T, Container>& other)
    {
        c = other.c;
        return *this;
    }

    /********************[Element access]*******************/

    template <class T, class Container>
    typename ft::stack<T, Container>::reference
        ft::stack<T, Container>::top()
    {
        return c.back();
    }

    template <class T, class Container>
    typename ft::stack<T, Container>::const_reference
        ft::stack<T, Container>::top() const
    {
        return c.back();
    }

    /********************[Capacity]*******************/
    
    template <class T, class Container>
    bool ft::stack<T, Container>::empty() const
    {
        return c.empty();
    }

    template <class T, class Container>
    typename ft::stack<T, Container>::size_type
        ft::stack<T, Container>::size() const
    {
        return c.size();
    }

    /********************[Modifiers]*******************/
    
    template <class T, class Container>
    void ft::stack<T, Container>::push(const value_type& value)
    {
        c.push_back(value);
    }

    template <class T, class Container>
    void ft::stack<T, Container>::pop()
    {
        c.pop_back();
    }

    /********************[Non-Member functions]*******************/

    template <class T, class Container>
        bool operator== (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
    {
        if (lhs.size() != rhs.size()) return false;
        return ft::equal(lhs.c.begin(), lhs.c.end(), rhs.c.begin());
    }

    template <class T, class Container>
        bool operator!= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Container>
        bool operator<  (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
    {
        return ft::lexicographical_compare(lhs.c.begin(), lhs.c.end(), rhs.c.begin(), rhs.c.end());
    }

    template <class T, class Container>
        bool operator<= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
    {
        return !(rhs < lhs);
    }

    template <class T, class Container>
        bool operator>  (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
    {
        return rhs < lhs;
    }

    template <class T, class Container>
        bool operator>= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
    {
        return !(lhs < rhs);
    }

}