#pragma once

#include "utils.hpp"
#include <cstddef>

namespace ft
{
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

    template <class Iter>
    struct iterator_traits
    {
        typedef typename Iter::difference_type      difference_type;
        typedef typename Iter::value_type           value_type;
        typedef typename Iter::pointer              pointer;
        typedef typename Iter::reference            reference;
        typedef typename Iter::iterator_category    iterator_category;
    };

    template <class T>
    struct iterator_traits<T*>
    {
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef ft::random_access_iterator_tag iterator_category;
    };

    template <class T>
    struct iterator_traits<const T*>
    {
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef const T*                        pointer;
        typedef const T&                        reference;
        typedef ft::random_access_iterator_tag iterator_category;
    };

	template <bool Cond,
			  class T = void >
	struct enable_if {};

	template <class T>
	struct enable_if<true, T>
	{ typedef T type; };

	template <class T, T v>
	struct integral_constant
	{
		typedef T						value_type;
		typedef integral_constant<T,v>	type;
	
		static const value_type		value = v;

		operator value_type() { return v; }
	};

	typedef integral_constant<bool,true>	true_type;
	typedef integral_constant<bool,false>	false_type;

	template <typename>
	struct is_integral:							false_type {};

	template <>
	struct is_integral<bool>:					true_type {};
	template <>
	struct is_integral<char>:					true_type {};
	template <>
	struct is_integral<signed char>:			true_type {};
	template <>
	struct is_integral<short int>:				true_type {};
	template <>
	struct is_integral<int>:					true_type {};
	template <>
	struct is_integral<long int>:				true_type {};
	template <>
	struct is_integral<unsigned char>:			true_type {};
	template <>
	struct is_integral<unsigned short int>:		true_type {};
	template <>
	struct is_integral<unsigned int>:			true_type {};
	template <>
	struct is_integral<unsigned long int>:		true_type {};

	template <>
	struct is_integral<const bool>:					true_type {};
	template <>
	struct is_integral<const char>:					true_type {};
	template <>
	struct is_integral<const signed char>:			true_type {};
	template <>
	struct is_integral<const short int>:			true_type {};
	template <>
	struct is_integral<const int>:					true_type {};
	template <>
	struct is_integral<const long int>:				true_type {};
	template <>
	struct is_integral<const unsigned char>:		true_type {};
	template <>
	struct is_integral<const unsigned short int>:   true_type {};
	template <>
	struct is_integral<const unsigned int>:			true_type {};
	template <>
	struct is_integral<const unsigned long int>:	true_type {};

	template <>
	struct is_integral<volatile bool>:					true_type {};
	template <>
	struct is_integral<volatile char>:					true_type {};
	template <>
	struct is_integral<volatile signed char>:			true_type {};
	template <>
	struct is_integral<volatile short int>:				true_type {};
	template <>
	struct is_integral<volatile int>:					true_type {};
	template <>
	struct is_integral<volatile long int>:				true_type {};
	template <>
	struct is_integral<volatile unsigned char>:			true_type {};
	template <>
	struct is_integral<volatile unsigned short int>:	true_type {};
	template <>
	struct is_integral<volatile unsigned int>:			true_type {};
	template <>
	struct is_integral<volatile unsigned long int>:		true_type {};

	template <>
	struct is_integral<const volatile bool>:				true_type {};
	template <>
	struct is_integral<const volatile char>:				true_type {};
	template <>
	struct is_integral<const volatile signed char>:			true_type {};
	template <>
	struct is_integral<const volatile short int>:			true_type {};
	template <>
	struct is_integral<const volatile int>:					true_type {};
	template <>
	struct is_integral<const volatile long int>:			true_type {};
	template <>
	struct is_integral<const volatile unsigned char>:		true_type {};
	template <>
	struct is_integral<const volatile unsigned short int>:	true_type {};
	template <>
	struct is_integral<const volatile unsigned int>:		true_type {};
	template <>
	struct is_integral<const volatile unsigned long int>:	true_type {};

    template <
        class Category,
        class T,
        class Distance = ptrdiff_t,
        class Pointer = T*,
        class Reference = T&
    > struct iterator {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			first1++;
			first2++;
		}
		return true;
	}

	template <class InputIterator>
    typename iterator_traits<InputIterator>::difference_type
		distance(InputIterator first, InputIterator last)
    {
        typename iterator_traits<InputIterator>::difference_type n = 0;

        for ( ; first != last; ++first)
            ++n;
		return n;
    }

    template <class Iter>
    struct reverse_iterator
    {
        typedef Iter                                                    iterator_type;
        typedef typename ft::iterator_traits<Iter>::iterator_category   iterator_category;
        typedef typename ft::iterator_traits<Iter>::value_type          value_type;
        typedef typename ft::iterator_traits<Iter>::pointer             pointer;
        typedef typename ft::iterator_traits<Iter>::reference           reference;
        typedef typename ft::iterator_traits<Iter>::difference_type     difference_type;

        reverse_iterator():p() {}
        reverse_iterator(Iter it):p(it) {}
        reverse_iterator(const pointer it):p(iterator_type(it)) {}
        reverse_iterator(const reverse_iterator& other):p(other.p) {}
        template <class Iterator>
            reverse_iterator(const reverse_iterator<Iterator>& other):p(other.base()) {}

        template <class Iterator>
            reverse_iterator& operator=(const reverse_iterator<Iterator>& other) {
            p = other.base();
            return *this;}

        reverse_iterator& operator=(const reverse_iterator& other) {
            p = other.p;
            return *this;}

        virtual ~reverse_iterator() {}

        Iter base() const {return this->p;}

        reverse_iterator&  operator++() {return (--p, *this);}
        reverse_iterator   operator++(int) {return reverse_iterator(p--);}
        reverse_iterator&  operator--() {return (++p, *this);}
        reverse_iterator   operator--(int) {return reverse_iterator(p++);}

        reverse_iterator   operator+(difference_type x) const {return reverse_iterator(p - x);}
        reverse_iterator   operator-(difference_type x) const {return reverse_iterator(p + x);}

        reverse_iterator&  operator+=(difference_type x) {p -= x; return *this;}
        reverse_iterator&  operator-=(difference_type x) {p += x; return *this;}

        reference   operator*() {return *(p.base() - 1);}
        pointer     operator->() {return (p.base() - 1);}
        reference   operator[](const difference_type x) {return *(p - x - 1);}

    protected:
        Iter p;
    };

    template <class T>
        bool    operator==(const ft::reverse_iterator<T>& lhs, 
        const ft::reverse_iterator<T>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <class T, class U>
        bool    operator==(const ft::reverse_iterator<T>& lhs, 
        const ft::reverse_iterator<U>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <class T>
        bool    operator!=(const ft::reverse_iterator<T>& lhs, 
        const ft::reverse_iterator<T>& rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <class T, class U>
        bool    operator!=(const ft::reverse_iterator<T>& lhs, 
        const ft::reverse_iterator<U>& rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <class T>
        bool    operator>(const ft::reverse_iterator<T>& lhs, 
        const ft::reverse_iterator<T>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <class T, class U>
        bool    operator>(const ft::reverse_iterator<T>& lhs, 
        const ft::reverse_iterator<U>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <class T>
        bool    operator>=(const ft::reverse_iterator<T>& lhs, 
        const ft::reverse_iterator<T>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <class T, class U>
        bool    operator>=(const ft::reverse_iterator<T>& lhs, 
        const ft::reverse_iterator<U>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <class T>
        bool    operator<(const ft::reverse_iterator<T>& lhs, 
        const ft::reverse_iterator<T>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <class T, class U>
        bool    operator<(const ft::reverse_iterator<T>& lhs, 
        const ft::reverse_iterator<U>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <class T>
        bool    operator<=(const ft::reverse_iterator<T>& lhs, 
        const ft::reverse_iterator<T>& rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <class T, class U>
        bool    operator<=(const ft::reverse_iterator<T>& lhs, 
        const ft::reverse_iterator<U>& rhs)
    {
        return lhs.base() >= rhs.base();
    }
    
    template <class T>
        ft::reverse_iterator<T>
        operator+( typename ft::reverse_iterator<T>::difference_type x,
        ft::reverse_iterator<T> it)
    {
        return (it + x);
    }

    template <class T>
        typename ft::reverse_iterator<T>::difference_type
        operator-(const ft::reverse_iterator<T>& lhs, 
        const ft::reverse_iterator<T>& rhs)
    {
        return rhs.base() - lhs.base();
    }

    template <class T, class U>
        typename ft::reverse_iterator<T>::difference_type
        operator-(const ft::reverse_iterator<T>& lhs, 
        const ft::reverse_iterator<U>& rhs)
    {
        return rhs.base() - lhs.base();
    }
}