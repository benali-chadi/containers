#ifndef MYITERATOR_HPP
# define MYITERATOR_HPP

// #include <iterator>
#include "../utils/utils.hpp"
#include <iostream>
#include <cstddef>

namespace ft
{
	template <class T>
	class MyIterator: public ft::iterator<std::random_access_iterator_tag, T>
	{
		public:
			typedef typename iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename iterator<std::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename iterator<std::random_access_iterator_tag, T>::pointer				pointer;
			typedef typename iterator<std::random_access_iterator_tag, T>::reference			reference;
			typedef typename iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;

			/*
				* Constructors
			*/

			MyIterator	() {}
			MyIterator	(const MyIterator &x): _p(x._p) {}
			MyIterator	(pointer x): _p(x) {}

			MyIterator&	operator=(const MyIterator& x) {	_p = x._p;	return *this;	}
			
			/*
				* Destructors
			*/

			~MyIterator	() {}

			/*
				* Operators
			*/
			
			operator MyIterator<const T> () const { return MyIterator<const T>(_p); }
			bool		operator==(const MyIterator& x) {	return _p == x._p;	}
			bool		operator!=(const MyIterator& x) {	return _p != x._p;	}
			bool		operator>(const MyIterator& x) {	return _p > x._p;	}
			bool		operator<(const MyIterator& x) {	return _p < x._p;	}
			bool		operator>=(const MyIterator& x) {	return _p >= x._p;	}
			bool		operator<=(const MyIterator& x) {	return _p <= x._p;	}
			reference	operator*() {	return *_p;	}
			pointer		operator->() {	return &operator*();	}

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

			MyIterator&	operator+=(difference_type n) {	_p += n; return *this;	}
			MyIterator&	operator-=(difference_type n) {	_p -= n; return *this;	}

			difference_type	operator-(MyIterator &x) {	;return _p - x._p;	}
			MyIterator	operator-(difference_type n) {	return _p - n;	}

			MyIterator	operator+(difference_type n) {	return (_p + n);	}

			reference	operator[](difference_type n) {	return *(_p + n);	}	


		private:
			pointer _p;

	};

	template <class T>
		MyIterator<T>	operator+(
					typename MyIterator<T>::difference_type n,
					MyIterator<T> &it
					)
		{
			return it + n;
		}
}

#endif