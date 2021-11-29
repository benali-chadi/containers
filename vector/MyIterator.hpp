#ifndef MYITERATOR_HPP
# define MYITERATOR_HPP

#include <iterator>
namespace ft
{
template <class T>
class MyIterator: public std::iterator<std::random_access_iterator_tag, T>
{
	public:
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


	private:
		T	*_p;
		MyIterator() {}

};
}
#endif