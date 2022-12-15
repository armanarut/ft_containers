#pragma once

#include "tree_iterator.hpp"
#include "pair.hpp"
#include <functional>

namespace ft
{
    template <class T, 
        class Compare = std::less<T>,
        class Alloc = std::allocator<T>
    > struct RBtree
    {
        typedef T                       value_type;
        typedef RBnode<value_type>      node_type;
        typedef Compare                 value_compare;
        typedef Alloc                   allocator_type;
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


        explicit    RBtree(const value_compare& comp,
                        const allocator_type& alloc)
            :_alloc(alloc),
            _comp(comp),
            _header(new_nil()) {};;
        ~RBtree() {delete _header;};

        RBtree& operator=(const RBtree& other);

        void        clear();

        ft::pair<iterator, bool>
                    insert(const value_type& value)
        {
            node_type*  root = _header->parent;
            bool    success = false;

            if (root == 0)
            {
                _header->parent = new_node(_header, value);
                root = _header->parent;
                success = true;
            }
            while (!success)
            {
                bool dir = _comp(*root->data, value);
                if (dir || root->data->first != value.first)
                {
                    if (root->child[dir] != 0)
                        root = root->child[dir];
                    else
                    {
                        root->child[dir] = new_node(root, value);
                        success = true;
                    }
                }
                else break;
            }
            return ft::make_pair(iterator(root), success);
        };

        iterator    insert( iterator position, const value_type& value );
        template< class InputIt >
            void    insert( InputIt first, InputIt last );
        iterator    erase (iterator position);
        iterator    erase (iterator first, iterator last);
        size_type   erase(const value_type& value);

    /********************[Iterators]*******************/

    iterator    begin()
    {
        node_type*  root = _header->parent;

        while (root->left)
            root = root->left;
        return iterator(root);
    }

    const_iterator  begin() const
    {
        node_type*  root = _header->parent;

        while (root->left)
            root = root->left;
        return const_iterator(root);
    }

    iterator    end()
    { return iterator(_header); }

    const_iterator  end() const
    { return const_iterator(_header); }

    reverse_iterator    rbegin()
    { return reverse_iterator(this->end()); }

    const_reverse_iterator  rbegin() const
    { return const_reverse_iterator(this->end()); }

    reverse_iterator    rend()
    { return reverse_iterator(this->begin()); }

    const_reverse_iterator  rend() const
    { return const_reverse_iterator(this->begin()); }

    iterator    find(const value_type& value)
    {
        node_type*  root = _header->parent;

        while (root)
        {
            bool dir = _comp(*root->data, value);
            if (dir || root->data->first != value.first)
            {
                if (root->child[dir])
                    root = root->child[dir];
                else break;
            }
            else return iterator(root);
        }
        return this->end();
    }

    const_iterator    find(const value_type& value) const
    {
        node_type*  root = _header->parent;

        while (root)
        {
            bool dir = _comp(*root->data, value);
            if (dir || root->data->first != value.first)
            {
                if (root->child[dir])
                    root = root->child[dir];
                else break;
            }
            else return const_iterator(root);
        }
        return this->end();
    }

    protected:
        allocator_type  _alloc;
        value_compare     _comp;
        node_type* _header;

        
        node_type*  new_node(node_type* parent, value_type value)
        {
            node_type* new_node = new node_type;

            new_node->data = _alloc.allocate(1);
            _alloc.construct(new_node->data, value);
            new_node->parent = parent;
            new_node->left = 0;
            new_node->right = 0;
            new_node->color = RED;
            return new_node;
        };

        node_type*  new_nil()
        {
            node_type*  new_node = new node_type;

            new_node->parent = 0;
            new_node->left = 0;
            new_node->right = 0;
            new_node->color = BLACK;

            return new_node;
        };
    };












}