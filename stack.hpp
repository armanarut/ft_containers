#pragma once

#include "vector.hpp"

namespace ft
{
    template <
        class T,
        class Container = ft::vector<T>
    > class stack
    {
    public:
        typedef Container                              container_type;
        typedef typename Container::value_type         value_type;
        typedef typename Container::size_type          size_type;
        typedef typename Container::reference          reference;
        typedef typename Container::const_reference    const_reference;

        explicit    stack(const Container& cont = Container());
                    stack(const stack& other);
                    ~stack();

        stack&      operator=(const stack& other);

        /*********[Element access]*********/
        reference       top();
        const_reference top() const;

        /*********[Capacity]*********/
        bool        empty() const;
        size_type   size() const;

        /*********[Modifiers]*********/
        void    push(const value_type& value);
        void    pop();

    protected:
        Container   c;
    };
}

#include "stack_impl.hpp"