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
        typedef T                                                   value_type;
        typedef RBnode<value_type>                                  node_type;
        typedef Compare                                             value_compare;
        typedef typename Alloc::template rebind<node_type>::other   allocator_type;
        typedef typename allocator_type::size_type                  size_type;
        typedef typename allocator_type::difference_type            difference_type;
        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;
        typedef tree_iterator<value_type>                           iterator;
        typedef tree_iterator<const value_type>                     const_iterator;
        typedef ft::reverse_iterator<iterator>                      reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                const_reverse_iterator;


        explicit    RBtree(const value_compare& comp,
                        const allocator_type& alloc)
            :_alloc(alloc),
            _comp(comp),
            _header(new_nil()),
            _size(0) {};;

        ~RBtree()
        {
            this->clear();
            _alloc.deallocate(_header, 1);
        };

        RBtree& operator=(const RBtree& other)
        {
            this->clear();
            _alloc = other._alloc;
            _comp = other._comp;
            insert(other.begin(), other.end());
            return *this;
        };

        /********************[Modifiers]*******************/

        void    clear()
        {
            this->remove_node(_header->parent);
            _header->parent = NULL;
            _size = 0;
        }

        template< class InputIt >
        void    insert( InputIt first, InputIt last )
        {
            while (first != last)
            {
                insert(*first);
                ++first;
            }
        }

        ft::pair<iterator, bool>
                insert(const value_type& value)
        {
            node_type*  root = _header->parent;
            bool        success = false;

            if (root == 0)
            {
                _header->parent = new_node(_header, value);
                root = _header->parent;
                success = true;
            }
            while (!success)
            {
                bool dir = _comp(value, root->data);
                if (dir || _comp(root->data, value))
                {
                    if (root->child[1 - dir] != 0)
                        root = root->child[1 - dir];
                    else
                    {
                        root->child[1 - dir] = new_node(root, value);
                        root = root->child[1 - dir];
                        success = true;
                    }
                }
                else break;
            }
            if (success)
            {
                insert_fixup(root);
                ++_size;
            }
            return ft::make_pair(iterator(root), success);
        };

        void    swap (RBtree& other)
        {
            node_type*  tmp1 = _header;
            size_type   tmp2 = _size;

            _header = other._header;
            _size = other._size;
            other._header = tmp1;
            other._size = tmp2;
        }

        iterator    delete_node(node_type* z)
        {
            node_type*  y;
            node_type*  x;
            bool        color;

            if (z == _header)
                return this->end();
            y = z;
            color = y->color;
            if (!z->child[LEFT])
            {
                x = z->child[RIGHT];
                transplant(z, z->child[RIGHT]);
            }
            else if (!z->child[RIGHT])
            {
                x = z->child[LEFT];
                transplant(z, z->child[LEFT]);
            }
            else
            {
                y = min_node(z->child[RIGHT]);
                color = y->color;
                x = y->child[RIGHT];
                if (y->parent != z)
                {
                    transplant(y, y->child[RIGHT]);
                    y->child[RIGHT] = z->child[RIGHT];
                    if (y->child[RIGHT])
                        y->child[RIGHT]->parent = y;
                }
                transplant(z, y);
                y->child[LEFT] = z->child[LEFT];
                if (y->child[LEFT])
                    y->child[LEFT]->parent = y;
                y->color = z->color;
            }
            if (color == BLACK)
                delete_fixup(x);
            --_size;
            _alloc.destroy(z);
            _alloc.deallocate(z, 1);
            if (x)
                return iterator(x);
            else
                return this->end();
        }

        /********************[Iterators]*******************/

        iterator    begin()
        {
            node_type*  root = _header->parent;

            if (!root)
                return this->end();
            while (root->child[LEFT])
                root = root->child[LEFT];
            return iterator(root);
        }

        const_iterator  begin() const
        {
            node_type*  root = _header->parent;

            if (!root)
                return this->end();
            while (root->child[LEFT])
                root = root->child[LEFT];
            return iterator(root);
        }

        iterator    end()
        { return iterator(_header); }

        const_iterator  end() const
        { return iterator(_header); }

        reverse_iterator    rbegin()
        { return reverse_iterator(this->end()); }

        const_reverse_iterator  rbegin() const
        { return reverse_iterator(this->end()); }

        reverse_iterator    rend()
        { return reverse_iterator(this->begin()); }

        const_reverse_iterator  rend() const
        { return reverse_iterator(this->begin()); }

        /********************[Capacity]*******************/
        
        size_type   size() const
        {
            return _size;
        };

        bool    empty() const
        {
            return !_size;
        };

        size_type   max_size() const
        {
            return _alloc.max_size();
        }

        /********************[Lookup]*******************/

        iterator    find(const value_type& value)
        {
            node_type*  root = _header->parent;

            root = search_node(root, value);
            if (root)
                return iterator(root);
            else
                return this->end();
        }

        const_iterator    find(const value_type& value) const
        {
            node_type*  root = _header->parent;

            root = search_node(root, value);
            if (root)
                return iterator(root);
            else
                return this->end();
        }

        node_type*  lower_bound( const value_type& value ) const
        {
            node_type* node = _header->parent;
            node_type* lower = _header;

            while (node != 0)
            {
                if (!_comp(node->data, value))
                {
                    lower = node;
                    node = node->child[LEFT];
                }
                else
                    node = node->child[RIGHT];
            }
            return lower;
        }

        node_type*  upper_bound( const value_type& value ) const
        {
            node_type* node = _header->parent;
            node_type* lower = _header;

            while (node != 0)
            {
                if (_comp(value, node->data))
                {
                    lower = node;
                    node = node->child[LEFT];
                }
                else
                    node = node->child[RIGHT];
            }
            return lower;
        }

    protected:
        allocator_type          _alloc;
        value_compare           _comp;
        node_type*              _header;
        size_type               _size;

        #define RotateLeft(N)  rotate_dir(N, LEFT)
        #define RotateRight(N)  rotate_dir(N, RIGHT)

        void    insert_fixup(node_type* z)
        {
            while (z->parent->color == RED)
            {
                bool    dir = RIGHT;
                if (z->parent == z->parent->parent->child[LEFT])
                    dir = LEFT;
                node_type* y = z->parent->parent->child[1 - dir];
                if (y && y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->child[1 - dir])
                    {
                        z = z->parent;
                        rotate_dir(z, dir);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotate_dir(z->parent->parent, 1 - dir);
                }
            }
            _header->parent->color = BLACK;
        }

        void    delete_fixup(node_type* x)
        {
            while (x && x != _header->parent && x->color == BLACK)
            {
                bool    dir = RIGHT;
                if (x == x->parent->child[LEFT])
                    dir = LEFT;
                node_type* y = x->parent->child[1 - dir];

                if (y && y->color == RED)
                {
                    y->color = BLACK;
                    x->parent->color = RED;
                    rotate_dir(x->parent, dir);
                    x->parent->parent->color = RED;
                    y = x->parent->child[1 - dir];
                }
                if (y && (!y->child[dir] || y->child[dir]->color == BLACK)   \
                    && (!y->child[dir] || !y->child[1 - dir] || y->child[1 - dir]->color == BLACK))
                {
                    y->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (y && (!y->child[dir] || !y->child[1 - dir] || y->child[1 - dir]->color == BLACK))
                    {
                        y->child[dir]->color = BLACK;
                        y->color = RED;
                        rotate_dir(y, 1 - dir);
                        y = x->parent->child[1 - dir];
                    }
                    if (y)
                    {
                        y->color = x->parent->color;
                        y->child[1 - dir]->color = BLACK;
                    }
                    x->parent->color = BLACK;
                    if (x->parent->child[1 - dir])
                        rotate_dir(x->parent, dir);
                    x = _header->parent;
                }
            }
            if (x)
                x->color = BLACK;
        }

        void    rotate_dir(node_type* x, bool dir)
        {
            node_type*  y = x->child[1 - dir];
            x->child[1 - dir] = y->child[dir];
            if (y->child[dir])
                y->child[dir]->parent = x;
            y->parent = x->parent;
            if (x->parent == _header)
                _header->parent = y;
            else if (x == x->parent->child[dir])
                x->parent->child[dir] = y;
            else
                x->parent->child[1 - dir] = y;
            y->child[dir] = x;
            x->parent = y;
        };

        node_type*  search_node(node_type* x, const value_type& value) const
        {
            if (x && _comp(value, x->data))
                return search_node(x->child[LEFT], value);
            else if (x && _comp(x->data, value))
                return search_node(x->child[RIGHT], value);
            else
                return x;
        }

        void    transplant(node_type* u, node_type* v)
        {
            if (u == _header->parent)
                _header->parent = v;
            else if (u == u->parent->child[LEFT])
                u->parent->child[LEFT] = v;
            else
                u->parent->child[RIGHT] = v;
            if (v)
                v->parent = u->parent;
        }

        node_type* min_node(node_type* x)
        {
            while(x->child[LEFT])
                x = x->child[LEFT];
            return x;
        }

        node_type* max_node(node_type* x)
        {
            while(x->child[RIGHT])
                x = x->child[RIGHT];
            return x;
        }

        node_type*  new_node(node_type* parent, value_type value)
        {
            node_type* new_node = _alloc.allocate(1);
            _alloc.construct(new_node, node_type(value));
            
            new_node->parent = parent;
            new_node->child[LEFT] = 0;
            new_node->child[RIGHT] = 0;
            new_node->color = RED;
            return new_node;
        };

        node_type*  new_nil()
        {
            node_type* new_node = _alloc.allocate(1);

            new_node->parent = 0;
            new_node->child[LEFT] = 0;
            new_node->child[RIGHT] = 0;
            new_node->color = BLACK;

            return new_node;
        };

        void    remove_node(node_type* node)
        {
            if (!node)
                return ;
            if (node->child[LEFT])
                remove_node(node->child[LEFT]);
            if (node->child[RIGHT])
                remove_node(node->child[RIGHT]);
            _alloc.destroy(node);
            _alloc.deallocate(node, 1);
        };
    };
}