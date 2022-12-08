#pragma once

#include <functional>
#include "pair.hpp"
#include "iterator.hpp"

namespace ft
{
    template<
        class Key,
        class T,
        class Compare = std::less<Key>,
        class Alloc = std::allocator<ft::pair<const Key, T> >
    > class map
    {
    public:
        typedef Key                                             key_type;
        typedef T                                               mapped_type;
        typedef Compare                                         key_compare;
        typedef Alloc                                           allocator_type;
        typedef typename allocator_type::value_type             value_type;
        typedef typename allocator_type::size_type              size_type;
        typedef typename allocator_type::difference_type        difference_type;
        typedef typename allocator_type::reference              reference;
        typedef typename allocator_type::const_reference        const_reference;
        typedef typename allocator_type::pointer                pointer;
        typedef typename allocator_type::const_pointer          const_pointer;
        typedef ft::bidirectional_iterator<value_type>          iterator;
        typedef ft::bidirectional_iterator<const value_type>    const_iterator;
        typedef ft::reverse_iterator<iterator>                  reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;






    private:

    };
}
