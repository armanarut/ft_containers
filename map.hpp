#pragma once

#include "RBtree.hpp"

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
        class                                                   value_compare;
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
        typedef tree_iterator_map<value_type>                   iterator;
        typedef tree_iterator_map<const value_type>             const_iterator;
        typedef ft::reverse_iterator<iterator>                  reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;

        explicit    map(const Compare& comp = key_compare(),
                        const allocator_type& alloc = allocator_type());
        template <class InputIt>
                    map(InputIt first, InputIt last,
                        const Compare& comp = Compare(),
                        const allocator_type& alloc = allocator_type());
                    map(const map& other);
                    ~map();

        map&        operator=( const map& other );

        allocator_type  get_allocator() const;

        /*********[Element access]*********/
        T&          at(const Key& key);
        const T&    at(const Key& key) const;
        T&          operator[](const Key& key);

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
        void        swap (map& other);

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
        key_compare             key_comp() const;
        value_compare  value_comp() const;

        class value_compare
        {
            friend class map;

        protected:
            Compare     comp;
            value_compare(Compare c):comp(c) {}

        public:
            bool operator()(const value_type& lhs, const value_type& rhs) const
            {
                return comp(lhs.first, rhs.first);
            }
        };

    private:
        typedef RBnode<value_type>                                  node_type;
        typedef RBtree<value_type, value_compare, allocator_type>   tree_type;

        tree_type  _tree;

        value_type get_value_type(const Key& key);
    };
}

#include "map_impl.hpp"