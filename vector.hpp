#pragma once

#include "iterator.hpp"
#include <iostream>

namespace ft
{
    template<
        class T,
        class Alloc = std::allocator<T>
    > class vector
    {
    public:
        typedef T                                           value_type;
        typedef Alloc                                       allocator_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef ft::random_access_iterator<T>               iterator;
        typedef ft::random_access_iterator<const T>         const_iterator;
        typedef ft::reverse_iterator<iterator>              reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
        typedef typename allocator_type::difference_type    difference_type;
        typedef typename allocator_type::size_type          size_type;

        template <class InputIterator>
                    vector (InputIterator first, InputIterator last, 
                        const allocator_type& alloc = allocator_type());
        explicit    vector (const allocator_type& alloc = allocator_type());
        explicit    vector (size_type n, const value_type& val = value_type(),
                        const allocator_type& alloc = allocator_type());
                    vector (const vector& x);

        virtual     ~vector();

        vector&     operator=(const vector& x);

        allocator_type get_allocator() {return allocator_type();};

        /*********[Iterators]*********/
        iterator                begin();
        const_iterator          begin() const;
        iterator                end();
        const_iterator          end() const;
        reverse_iterator        rbegin();
        const_reverse_iterator  rbegin() const;
        reverse_iterator        rend();
        const_reverse_iterator  rend() const;

        /*********[Capacity]*********/
        size_type   size() const;
        size_type   max_size() const;
        void        resize (size_type n, value_type val = value_type());
        size_type   capacity() const;
        bool        empty() const;
        void        reserve (size_type n);

        /*********[Element access]*********/
        reference           operator[] (size_type n);
        const_reference     operator[] (size_type n) const;
        reference           at (size_type n);
        const_reference     at (size_type n) const;
        reference           front();
        const_reference     front() const;
        reference           back();
        const_reference     back() const;
        pointer             data();
        const_pointer       data() const;

        /*********[Modifiers]*********/
        template <class InputIterator>
            void    assign (InputIterator first, InputIterator last);
        void        assign (size_type n, const value_type& val);
        void        push_back(const_reference val);
        void        pop_back();
        iterator    insert (iterator position, const value_type& val);
        void        insert (iterator position, size_type n, const value_type& val);
        template <class InputIterator>
            void    insert (iterator position, InputIterator first, InputIterator last);
        iterator    erase (iterator position);
        iterator    erase (iterator first, iterator last);
        void        swap (vector& x);
        void        clear();

    protected:
        allocator_type  _alloc;
        pointer         _start;
        pointer         _capacity;
        pointer         _end;

        void        insert_do (iterator position, size_type n, const value_type& val, true_type);
        template <class InputIterator>
            void    insert_do (iterator position, InputIterator first, InputIterator last, false_type);
        template <class InputIterator>
            void    insert_do_select (iterator position, InputIterator first,
                        InputIterator last, ft::input_iterator_tag);
        template <class InputIterator>
            void    insert_do_select (iterator position, InputIterator first,
                        InputIterator last, std::input_iterator_tag);
        template <class InputIterator>
            void    insert_do_select (iterator position, InputIterator first,
                        InputIterator last, ft::forward_iterator_tag);
        template <class InputIterator>
            void    insert_do_select (iterator position, InputIterator first,
                        InputIterator last, std::forward_iterator_tag);
    };

    /********************[Non-Member functions]*******************/

    template <class T, class Alloc>
        bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>
        bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>
        bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>
        bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>
        bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>
        bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>
        void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
}

#include "vector_impl.hpp"
