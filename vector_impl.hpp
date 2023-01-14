#pragma once

namespace ft
{
    template <class T, class Allocator>
    vector<T, Allocator>::vector (const allocator_type& alloc)
        :
            _alloc(alloc),
            _start(ft::ft_nullptr),
            _capacity(ft::ft_nullptr),
            _end(ft::ft_nullptr) {}

    template <class T, class Allocator>
    vector<T, Allocator>::vector (size_type n, const value_type& val,
        const allocator_type& alloc)
        :
            _alloc(alloc),
            _start(ft::ft_nullptr),
            _capacity(ft::ft_nullptr),
            _end(ft::ft_nullptr)
    {
        insert(this->begin(), n, val);
    }

    template <class T, class Allocator>
    template <class InputIterator>
    vector<T, Allocator>::vector (InputIterator first, InputIterator last,
        const allocator_type& alloc)
        :
            _alloc(alloc),
            _start(ft::ft_nullptr),
            _capacity(ft::ft_nullptr),
            _end(ft::ft_nullptr)
    {
        insert(this->begin(), first, last);
    }

    template <class T, class Allocator>
    vector<T, Allocator>::vector (const vector& x)
        :
            _alloc(x._alloc),
            _start(ft::ft_nullptr),
            _capacity(ft::ft_nullptr),
            _end(ft::ft_nullptr) { *this = x; }

    template <class T, class Allocator>
    vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& x)
    {
        if (&x == this)
            return *this;
        if (this->capacity())
        {
            this->clear();
            _alloc.deallocate(_start, this->capacity());
            _capacity = _end;
        }
        _alloc = x._alloc;
        this->assign(x.begin(), x.end());
        return *this;
    }

    template <class T, class Allocator>
    vector<T, Allocator>::~vector ()
    {
        if (this->capacity())
        {
            this->clear();
            _alloc.deallocate(_start, this->capacity());
        }
    }
    /********************[Iterators]*******************/

    template <class T, class Allocator>
    typename vector<T, Allocator>::iterator
        vector<T, Allocator>::begin()
    {
        return iterator(_start);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_iterator
        vector<T, Allocator>::begin() const
    {
        return const_iterator(_start);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::iterator
        vector<T, Allocator>::end()
    {
        return iterator(_end);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_iterator
        vector<T, Allocator>::end() const
    {
        return const_iterator(_end);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::reverse_iterator
        vector<T, Allocator>::rbegin()
    {
        return reverse_iterator(this->end());
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_reverse_iterator
        vector<T, Allocator>::rbegin() const
    {
        return const_reverse_iterator(this->end());
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::reverse_iterator
        vector<T, Allocator>::rend()
    {
        return reverse_iterator(this->begin());
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_reverse_iterator
        vector<T, Allocator>::rend() const
    {
        return const_reverse_iterator(this->begin());
    }

    /********************[Capacity]*******************/

    template <class T, class Allocator>
    typename vector<T, Allocator>::size_type
        vector<T, Allocator>::size() const
    {
        return _end - _start;
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::size_type
        vector<T, Allocator>::max_size() const
    {
        return allocator_type().max_size();
    }

    template <class T, class Allocator>
    void    vector<T, Allocator>::resize (size_type n, value_type val)
    {
        if (n >= this->max_size())
            throw (std::length_error("vector"));
        if (this->size() > n)
            for (size_type i = this->size(); i != n; i--)
                _alloc.destroy(--_end);
        else if (this->size() < n)
        {
            if (this->capacity() <= n)
            {
                size_type new_size = this->empty() ? n: (this->capacity() * 2 <= n) ? (this->size() + n): this->capacity() * 2;
                if (new_size > this->max_size())
                    new_size = this->max_size();
                reserve(new_size);
            }
            insert(this->end(), n - this->size(), val);
        }
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::size_type
        vector<T, Allocator>::capacity() const
    {
        return _capacity - _start;
    }

    template <class T, class Allocator>
    bool    vector<T, Allocator>::empty() const
    {
        return this->size() ? false: true;
    }

    template <class T, class Allocator>
    void    vector<T, Allocator>::reserve (size_type n)
    {
        if (n >= this->max_size())
            throw (std::length_error("vector"));
        else if (n > capacity())
        {
            pointer new_start = _alloc.allocate(n);
            pointer new_end = new_start;

            for (pointer it = _start; it != _end; it++)
                _alloc.construct(new_end++, *it);
            if (this->capacity())
            {
                this->clear();
                _alloc.deallocate(_start, this->capacity());
            }
            _start = new_start;
            _end = new_end;
            _capacity = _start + n;
        }
    }

    /********************[Element access]*******************/

    template <class T, class Allocator>
    typename vector<T, Allocator>::reference
        vector<T, Allocator>::operator[] (size_type n)
    {
        if (n > this->size())
            throw (std::out_of_range("vector"));
        return *(_start + n);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_reference
        vector<T, Allocator>::operator[] (size_type n) const
    {
        if (n > this->size())
            throw (std::out_of_range("vector"));
        return *(_start + n);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::reference
        vector<T, Allocator>::at (size_type n)
    {
        if (n >= this->size())
            throw (std::out_of_range("vector"));
        return *(_start + n);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_reference
        vector<T, Allocator>::at (size_type n) const
    {
        if (n >= this->size())
            throw (std::out_of_range("vector"));
        return *(_start + n);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::reference
        vector<T, Allocator>::front()
    {
        return *_start;
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_reference
        vector<T, Allocator>::front() const
    {
        return *_start;
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::reference
        vector<T, Allocator>::back()
    {
        if (_start == _end)
            return *_end;
        return *(_end - 1);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_reference
        vector<T, Allocator>::back() const
    {
        if (_start == _end)
            return *_end;
        return *(_end - 1);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::pointer
        vector<T, Allocator>::data()
    {
        return _start;
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_pointer
        vector<T, Allocator>::data() const
    {
        return _start;
    }

    /********************[Modifiers]*******************/

    template <class T, class Allocator>
    template <class InputIterator>
    void    vector<T, Allocator>::assign (InputIterator first, InputIterator last)
    {
        this->clear();
        this->insert(this->begin(), first, last);
    }

    template <class T, class Allocator>
    void vector<T, Allocator>::assign (size_type n, const value_type& val)
    {
        this->clear();
        this->insert(this->begin(), n, val);
    }

    template <class T, class Allocator>
    void    vector<T, Allocator>::push_back(const_reference val)
    {
        this->insert(this->end(), val);
    }

    template <class T, class Allocator>
    void    vector<T, Allocator>::pop_back()
    {
        if (_start != _end)
            _alloc.destroy(--_end);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::iterator    
        vector<T, Allocator>::insert (iterator position, const value_type& val)
    {
        size_type pos = ft::distance(begin(), position);
        size_type m = ft::distance(position, this->end());
        if (_capacity == _end)
        {
            size_type new_size = this->empty() ? 1: (this->size() <= 1) ? (this->size() + 1): this->capacity() * 2;
            if (new_size > this->max_size())
                new_size = this->max_size();
            reserve(new_size);
        }
        for (size_type i = 1; i <= m; i++)
        {
            _alloc.construct(_end + 1 - i, *(_end - i));
            _alloc.destroy(_end - i);
        }
        _alloc.construct(_end++ - m, val);
        return this->begin() + pos;
    }

    template <class T, class Allocator>
    void    vector<T, Allocator>::insert (iterator position,
        size_type n, const value_type& val)
    {
        insert_do(position, n, val, true_type());
    }


    template <class T, class Allocator>
    template <class InputIterator>
    void    vector<T, Allocator>::insert (iterator position,
        InputIterator first, InputIterator last)
    {
        typedef typename ft::is_integral<InputIterator>::type is_inter;
        insert_do(position, first, last, is_inter());
    }

    template <class T, class Allocator>
    void    vector<T, Allocator>::insert_do (iterator position,
        size_type n, const value_type& val, true_type)
    {
        if (n >= this->max_size())
            throw (std::length_error("vector::insert"));
        size_type m = ft::distance(position, this->end());

        if (_capacity < _end + n)
        {
            size_type new_size = this->empty() ? n: (this->size() <= n) ? (this->size() + n): this->capacity() * 2;
            if (new_size > this->max_size())
                new_size = this->max_size();
            reserve(new_size);
        }
        pointer old_end = _end;
        for (size_type i = 1; i <= m; i++)
        {
            if (_end + n - i < old_end)
                _alloc.destroy(_end + n - i);
            _alloc.construct(_end + n - i, *(_end - i));
        }
        try
        {
            while (n--)
            {
                if (_end - m < old_end)
                    _alloc.destroy(_end - m);
                _alloc.construct(_end++ - m, val);
            }
        }
        catch(...)
        {
            _end += n;
            this->clear();
            _alloc.deallocate(_start, this->capacity());
            _capacity = _start;
            throw;
        }
    }

    template <class T, class Allocator>
    template <class InputIterator>
    void    vector<T, Allocator>::insert_do (iterator position,
        InputIterator first, InputIterator last, false_type)
    {
        typedef typename iterator_traits<InputIterator>::iterator_category category;
        insert_do_select(position, first, last, category());

    }

    template <class T, class Allocator>
    template <class InputIterator>
    void    vector<T, Allocator>::insert_do_select (iterator position,
        InputIterator first, InputIterator last, std::input_iterator_tag)
    {
        size_type begin_size = ft::distance(this->begin(), position);
        pointer old_start = _start;
        pointer old_end = _end;
        size_type old_capacity = this->capacity();

        _start = ft::ft_nullptr;
        _end = ft::ft_nullptr;
        _capacity = ft::ft_nullptr;
        this->insert(this->begin(), iterator(old_start), iterator(old_start + begin_size));
        while (first != last)
        {
            this->push_back(*first);
            first++;
        }
        this->insert(this->end(), iterator(old_start + begin_size), iterator(old_end));
        if (old_capacity)
        {
            while (old_end != old_start)
                _alloc.destroy(--old_end);
            _alloc.deallocate(old_start, old_capacity);
        }
    }

    template <class T, class Allocator>
    template <class InputIterator>
    void    vector<T, Allocator>::insert_do_select (iterator position,
        InputIterator first, InputIterator last, std::forward_iterator_tag)
    {
        size_type n = ft::distance(first, last);
        size_type m = ft::distance(position, this->end());

        if (_capacity < _end + n)
        {
            size_type new_size = this->empty() ? n: (this->size() <= n) ? (this->size() + n): this->capacity() * 2;
            if (new_size > this->max_size())
                new_size = this->max_size();
            reserve(new_size);
        }
        pointer old_end = _end;
        for (size_type i = 1; i <= m; i++)
        {
            if (_end + n - i < old_end)
                _alloc.destroy(_end + n - i);
            _alloc.construct(_end + n - i, *(_end - i));
        }
        try
        {
            while (n--)
            {
                if (_end - m < old_end)
                    _alloc.destroy(_end - m);
                _alloc.construct(_end - m , *first);
                _end++;
                first++;
            }
        }
        catch(...)
        {
            _end += n;
            this->clear();
            _alloc.deallocate(_start, this->capacity());
            _capacity = _start;
            throw;
        }
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::iterator
        vector<T, Allocator>::erase (iterator position)
    {
        size_type m = ft::distance(position, this->end());

        if (!m)
            return position;
        while (--m)
        {
            _alloc.destroy(_end - 1 - m);
            _alloc.construct(_end - 1 - m, *(_end - m));
        }
        _alloc.destroy(--_end);
        return (position);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::iterator
        vector<T, Allocator>::erase (iterator first, iterator last)
    {
        size_type n = ft::distance(first, last);
        size_type m = ft::distance(last, this->end());

        if (n == 0)
            return first;
        for (;m;m--)
        {
            _alloc.destroy(_end - n - m);
            _alloc.construct(_end - n - m, *(_end - m));
        }
        while (n--)
            _alloc.destroy(--_end);
        return first;
    }

    template <class T, class Allocator>
    void    vector<T, Allocator>::swap (vector& x)
    {
        pointer tmp;

        tmp = x._start;
        x._start = this->_start;
        this->_start = tmp;
        tmp = x._end;
        x._end = this->_end;
        this->_end = tmp;
        tmp = x._capacity;
        x._capacity = this->_capacity;
        this->_capacity = tmp;
    }

    template <class T, class Allocator>
    void    vector<T, Allocator>::clear()
    {
        while(_end != _start)
            _alloc.destroy(--_end);
    }

    /********************[Non-Member functions]*******************/

    template <class T, class Alloc>
        bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (lhs.size() != rhs.size()) return false;
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class T, class Alloc>
        bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Alloc>
        bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
        bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(rhs < lhs);
    }

    template <class T, class Alloc>
        bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return rhs < lhs;
    }

    template <class T, class Alloc>
        bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs < rhs);
    }

    template <class T, class Alloc>
        void swap (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs)
    {
        ft::vector<T, Alloc> tmp;
        tmp.swap(lhs);
        lhs.swap(rhs);
        rhs.swap(tmp);
    }
}