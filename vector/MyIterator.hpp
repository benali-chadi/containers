#ifndef MYITERATOR_HPP
# define MYITERATOR_HPP

// #include <iterator>
#include <iostream>
#include <cstddef>

namespace ft
{

	template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
		struct iterator {
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	iterator_category;
		};

	template <class T>
	class MyIterator: public iterator<std::random_access_iterator_tag, T>
	{
		public:
			typedef typename iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename iterator<std::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename iterator<std::random_access_iterator_tag, T>::pointer				pointer;
			typedef typename iterator<std::random_access_iterator_tag, T>::reference			reference;
			typedef typename iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;

			MyIterator() {}
			MyIterator(pointer x): _p(x) {}
			MyIterator(const MyIterator &x): _p(x._p) {}

			~MyIterator() {}

			MyIterator&	operator=(const MyIterator& x) {	_p = x._p;	return *this;	}
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

			MyIterator&	operator+=(int n) {	_p += n; return *this;	}
			MyIterator&	operator-=(int n) {	_p -= n; return *this;	}

			MyIterator	operator-(MyIterator &x) {	return _p - x._p;	}
			MyIterator	operator-(int n) {	return _p - n;	}

			MyIterator	operator+(int n) {	return (_p + n);	}
			template <class Iterator>
			friend Iterator	operator+(int n, Iterator &it);

			reference	operator[](int n) {	return *(_p + n);	}	


		private:
			pointer _p;

	};

	template <class Iterator>
	Iterator	operator+(int n, Iterator &it) {
		return (it.p + n);
	}
}

#endif