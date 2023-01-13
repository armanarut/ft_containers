#pragma once

#include <memory>
#include "type_traits.hpp"

namespace ft
{
    template <class T>
    struct bidirectional_iterator
    {
        typedef std::bidirectional_iterator_tag                                 iterator_category;
        typedef typename ft::iterator<iterator_category, T>::value_type         value_type;
        typedef typename ft::iterator<iterator_category, T>::pointer            pointer;
        typedef typename ft::iterator<iterator_category, T>::reference          reference;
        typedef typename ft::iterator<iterator_category, T>::difference_type    difference_type;

        bidirectional_iterator():p(ft_nullptr) {}
        bidirectional_iterator(const pointer it):p(it) {}
        bidirectional_iterator(const bidirectional_iterator& other):p(other.p) {}
        bidirectional_iterator& operator=(const bidirectional_iterator& other) {
            p = other.p;
            return *this;}
        virtual ~bidirectional_iterator() {}

        operator bidirectional_iterator<const value_type> () const {
            return bidirectional_iterator<const value_type>(this->p);}

        pointer base() const {return this->p;}

        bidirectional_iterator&  operator++() {return (++p, *this);}
        bidirectional_iterator   operator++(int) {return bidirectional_iterator(p++);}
        bidirectional_iterator&  operator--() {return (--p, *this);}
        bidirectional_iterator   operator--(int) {return bidirectional_iterator(p--);}

        reference   operator*() {return *p;}
        pointer     operator->() {return p;}

    protected:
        pointer p;
    };

    template <class T>
    struct random_access_iterator: public bidirectional_iterator<T>
    {
        typedef std::random_access_iterator_tag                                 iterator_category;
        typedef typename ft::iterator<iterator_category, T>::value_type         value_type;
        typedef typename ft::iterator<iterator_category, T>::pointer            pointer;
        typedef typename ft::iterator<iterator_category, T>::reference          reference;
        typedef typename ft::iterator<iterator_category, T>::difference_type    difference_type;

        using ft::bidirectional_iterator<T>::p;

        random_access_iterator() {p = ft_nullptr;}
        random_access_iterator(const pointer it) {p = it;}
        random_access_iterator(const random_access_iterator& other) {p = other.p;}
        random_access_iterator& operator=(const random_access_iterator& other) {
            p = other.p;
            return *this;}
        virtual ~random_access_iterator() {}

        operator random_access_iterator<const value_type> () const {
            return random_access_iterator<const value_type>(this->p);}

        random_access_iterator&  operator++() {return (++p, *this);}
        random_access_iterator   operator++(int) {return random_access_iterator(p++);}
        random_access_iterator&  operator--() {return (--p, *this);}
        random_access_iterator   operator--(int) {return random_access_iterator(p--);}

        random_access_iterator   operator+(difference_type x) const {return random_access_iterator(p + x);}
        random_access_iterator   operator-(difference_type x) const {return random_access_iterator(p - x);}

        random_access_iterator&  operator+=(difference_type x) {p += x; return *this;}
        random_access_iterator&  operator-=(difference_type x) {p -= x; return *this;}

        reference   operator[](const difference_type x) {return *(p + x);}
    };

    template <class T>
        bool    operator==(const ft::bidirectional_iterator<T>& lhs, 
        const ft::bidirectional_iterator<T>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <class T, class U>
        bool    operator==(const ft::bidirectional_iterator<T>& lhs, 
        const ft::bidirectional_iterator<U>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <class T>
        bool    operator!=(const ft::bidirectional_iterator<T>& lhs, 
        const ft::bidirectional_iterator<T>& rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <class T, class U>
        bool    operator!=(const ft::bidirectional_iterator<T>& lhs, 
        const ft::bidirectional_iterator<U>& rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <class T>
        bool    operator>(const ft::bidirectional_iterator<T>& lhs, 
        const ft::bidirectional_iterator<T>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <class T, class U>
        bool    operator>(const ft::bidirectional_iterator<T>& lhs, 
        const ft::bidirectional_iterator<U>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <class T>
        bool    operator>=(const ft::bidirectional_iterator<T>& lhs, 
        const ft::bidirectional_iterator<T>& rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <class T, class U>
        bool    operator>=(const ft::bidirectional_iterator<T>& lhs, 
        const ft::bidirectional_iterator<U>& rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <class T>
        bool    operator<(const ft::bidirectional_iterator<T>& lhs, 
        const ft::bidirectional_iterator<T>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <class T, class U>
        bool    operator<(const ft::bidirectional_iterator<T>& lhs, 
        const ft::bidirectional_iterator<U>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <class T>
        bool    operator<=(const ft::bidirectional_iterator<T>& lhs, 
        const ft::bidirectional_iterator<T>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <class T, class U>
        bool    operator<=(const ft::bidirectional_iterator<T>& lhs, 
        const ft::bidirectional_iterator<U>& rhs)
    {
        return lhs.base() <= rhs.base();
    }
    
    template <class T>
        ft::random_access_iterator<T>
        operator+( typename ft::random_access_iterator<T>::difference_type x,
        ft::random_access_iterator<T> it)
    {
        return it + x;
    }

    template <class T>
        typename ft::random_access_iterator<T>::difference_type
        operator-(const ft::random_access_iterator<T>& lhs, 
        const ft::random_access_iterator<T>& rhs)
    {
        return lhs.base() - rhs.base();
    }

    template <class T, class U>
        typename ft::random_access_iterator<T>::difference_type
        operator-(const ft::random_access_iterator<T>& lhs, 
        const ft::random_access_iterator<U>& rhs)
    {
        return lhs.base() - rhs.base();
    }
}