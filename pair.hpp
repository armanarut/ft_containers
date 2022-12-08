#pragma once

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type	first;
		second_type	second;

		template <class U1, class U2>
			pair(const pair<U1, U2> &p);
			pair();
			pair(const first_type &a, const second_type &b);

		pair	&operator=(const pair &pr);
	};

	template <class T1, class T2>
		pair<T1, T2>	make_pair(T1 t, T2 u);
	template <class T1, class T2>
		bool			operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);
	template <class T1, class T2>
		bool			operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);
	template <class T1, class T2>
		bool			operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);
	template <class T1, class T2>
		bool			operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);
	template <class T1, class T2>
		bool			operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);
	template <class T1, class T2>
		bool			operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);
}

#include "pair_impl.hpp"