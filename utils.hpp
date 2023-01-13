#pragma once

namespace ft
{
	struct ft_nullptr
	{
		template <class T>
		operator T *() const { return (0); }

		template <class C, class T>
		operator T C::*() const { return (0); }

	private:
		void	operator&() const;
	}ft_nullptr = {};

	template< class InputIt, class Distance >
	void advance(InputIt& it, Distance n)
	{
		while (n > 0)
        {
            --n;
            ++it;
        }
        while (n < 0)
        {
            ++n;
            --it;
        }
	}
}