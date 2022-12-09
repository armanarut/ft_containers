#pragma once

namespace ft
{
	template <class T1, class T2>
	pair<T1, T2>::pair():
		first(),
		second() {}

	template <class T1, class T2>
	template <class U1, class U2>
	pair<T1, T2>::pair(const pair<U1, U2> &p)
	{
		this->first = p.first;
		this->second = p.second;
	}

	template <class T1, class T2>
	pair<T1, T2>::pair(const first_type &a, const second_type &b):
		first(a),
		second(b) {}

	template <class T1, class T2>
	pair<T1, T2>& pair<T1, T2>::operator=(const pair<T1, T2> &pr)
	{
		this->first = pr.first;
		this->second = pr.second;
		return *this;
	}

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 t, T2 u)
	{
		return pair<T1, T2>(t, u);
	}

	template <class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first == rhs.first && lhs.seccond == rhs.seccond);
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first < rhs.first || (rhs.first < lhs.first && lhs.seccond < rhs.seccond));
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs < rhs);
	}
}