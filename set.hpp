#pragma once

#include "RBtree.hpp"

namespace ft
{
    template<
        class Key,
        class Compare = std::less<Key>,
        class Alloc = std::allocator<Key>
    > class set
    {
    public:
        class                                                   value_compare;
        typedef Key                                             key_type;
        typedef Compare                                         key_compare;
        typedef Alloc                                           allocator_type;
        typedef typename allocator_type::value_type             value_type;
        typedef typename allocator_type::size_type              size_type;
        typedef typename allocator_type::difference_type        difference_type;
        typedef typename allocator_type::reference              reference;
        typedef typename allocator_type::const_reference        const_reference;
        typedef typename allocator_type::pointer                pointer;
        typedef typename allocator_type::const_pointer          const_pointer;
        typedef tree_iterator<const value_type>                 iterator;
        typedef tree_iterator<const value_type>                 const_iterator;
        typedef ft::reverse_iterator<iterator>                  reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;

        explicit    set(const Compare& comp = key_compare(),
                        const Alloc& alloc = allocator_type());
        template <class InputIt>
                    set(InputIt first, InputIt last,
                        const Compare& comp = key_compare(),
                        const Alloc& alloc = allocator_type());
                    set(const set& other);
                    ~set();

        set&        operator=( const set& other );

        allocator_type  get_allocator() const;

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
        bool        empty() const;
        size_type   max_size() const;

        /*********[Modifiers]*********/
        void        clear();
        ft::pair<iterator, bool>
                    insert(const value_type& value);
        iterator    insert( iterator position, const value_type& value );
        template< class InputIt >
            void    insert( InputIt first, InputIt last );
        iterator    erase (iterator position);
        iterator    erase (iterator first, iterator last);
        size_type   erase(const Key& key);
        void        swap (set& other);

        /*********[Lookup]*********/
        size_type                                   count(const Key& key) const;
        iterator                                    find(const Key& key);
        const_iterator                              find(const Key& key) const;
        ft::pair<iterator,iterator>                 equal_range(const Key& key);
        ft::pair<const_iterator,const_iterator>     equal_range(const Key& key) const;
        iterator                                    lower_bound( const Key& key );
        const_iterator                              lower_bound( const Key& key ) const;
        iterator                                    upper_bound( const Key& key );
        const_iterator                              upper_bound( const Key& key ) const;

        /*********[Observers]*********/
        key_compare     key_comp() const;
        value_compare   value_comp() const;

        class value_compare
        {
                friend class set;

            protected:
                Compare     comp;
                value_compare(Compare c):comp(c) {}

            public:
                value_compare():comp(Compare()){}

                bool operator()(const value_type& lhs, const value_type& rhs) const
                {
                    return comp(lhs, rhs);
                }
        };

    private:
        typedef RBnode<const value_type>                                  node_type;
        typedef RBtree<const value_type, value_compare, allocator_type>   tree_type;

        tree_type  _tree;
    };
}

#include "set_impl.hpp"