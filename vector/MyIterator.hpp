#ifndef MYITERATOR_HPP
# define MYITERATOR_HPP

#include <iterator>
#include <iostream>

namespace ft
{
	template <class T>
	class MyIterator: public std::iterator<std::random_access_iterator_tag, T>
	{
		public:
			MyIterator() {}
			MyIterator(T *x): _p(x) {}
			MyIterator(const MyIterator &x): _p(x._p) {}

			~MyIterator() {}

			MyIterator&	operator=(const MyIterator& x) {	_p = x._p;	return *this;	}
			bool		operator==(const MyIterator& x) {	return _p == x._p;	}
			bool		operator!=(const MyIterator& x) {	return _p != x._p;	}
			bool		operator>(const MyIterator& x) {	return _p > x._p;	}
			bool		operator<(const MyIterator& x) {	return _p < x._p;	}
			bool		operator>=(const MyIterator& x) {	return _p >= x._p;	}
			bool		operator<=(const MyIterator& x) {	return _p <= x._p;	}
			T&			operator*() {	return *_p;	}
			T*			operator->() {	return &operator*();	}

			MyIterator&	operator++() {	++_p; return *this;	}
			MyIterator	operator++(int) {
				MyIterator tmp(*this);
				++_p;
				return tmp;
			}
			MyIterator& operator--() {	--_p; return *this;	}
			MyIterator operator--(int) {
				MyIterator tmp(*this);
				--_p;
				return tmp;
			}

			MyIterator&	operator+=(int n) {	_p += n; return *this;	}
			MyIterator&	operator-=(int n) {	_p -= n; return *this;	}

			MyIterator	operator-(MyIterator &x) {	return _p - x._p;	}
			MyIterator	operator-(int n) {	return _p - n;	}

			MyIterator	operator+(int n) {	return (_p + n);	}
			template <class Iterator>
			friend Iterator	operator+(int n, Iterator &it);

			T&			operator[](int n) {	return *(_p + n);	}	


		private:
			T	*_p;

	};

	template <class Iterator>
	Iterator	operator+(int n, Iterator &it) {
		return (it.p + n);
	}
}

#endif