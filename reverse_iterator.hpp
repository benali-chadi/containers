#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include <iostream>
#include <cstddef>

namespace ft {
	template <class Iterator>
		class iterator_traits {
			typedef typename Iterator::diffrence_type		diffrence_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
		};
	template <class T>
		class iterator_traits<T*> {
			typedef ptrdiff_t					diffrence_type;
			typedef T							value_type;
			typedef T*							pointer;
			typedef T&							reference;
			typedef random_access_iterator_tag	iterator_category;
		};
	
	template <class T>
		class iterator_traits<const T*> {
			typedef ptrdiff_t					diffrence_type;
			typedef T							value_type;
			typedef const T*							pointer;
			typedef const T&							reference;
			typedef random_access_iterator_tag	iterator_category;
		};
	

	template <class Iterator>
		class reverse_iterator {
			public:
				typedef 			Iterator										iterator_type;
				typedef typename	iterator_traits<Iterator>::iterator_category	iterator_category;
				typedef typename	iterator_traits<Iterator>::value_type			value_type;
				typedef typename	iterator_traits<Iterator>::diffrence_type		diffrence_type;
				typedef typename	iterator_traits<Iterator>::pointer				pointer;
				typedef typename	iterator_traits<Iterator>::reference			reference;

				reverse_iterator () {}
				explicit reverse_iterator (iterator_type it) {	_iter = it - 1;	}
				template <class Iter>
					reverse_iterator (const reverse_iterator<Iter>& rev_it)
					{
						*this = rev_it;
					}
				
				iterator_type 		base() const {	return _iter;	}

				reference			operator*() const {	return *_iter;	}
				reverse_iterator	operator+(diffrence_type n) const {	return _iter - n;	}
				reverse_iterator	operator-(diffrence_type n) const {	return _iter + n;	}
				pointer				operator->() const {	return &(operator*());	}
				reference			operator[](diffrence_type n) const {	return *(_iter - n);	}
				reverse_iterator&	operator+=(diffrence_type n) {	_iter -= n; return *this;	}
				reverse_iterator&	operator-=(diffrence_type n) {	_iter += n; return *this;	}

				reverse_iterator&	operator++() {	--_iter; return *this;	}
				reverse_iterator	operator++(int)
				{
					reverse_iterator tmp = *this;
					++(*this);
					return tmp;
				}

				reverse_iterator&	operator--() {	++_iter; return *this;	}
				reverse_iterator	operator--(int)
				{
					reverse_iterator tmp = *this;
					--(*this);
					return tmp;
				}




			private:
				iterator_type _iter;
		};
}

#endif