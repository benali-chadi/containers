#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include <iostream>
#include <cstddef>
#include "utils.hpp"

namespace ft {
	template <class Iterator>
		class iterator_traits {
			public:
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
		};
	template <class T>
		class iterator_traits<T*> {
			public:
			typedef ptrdiff_t						difference_type;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef std::random_access_iterator_tag	iterator_category;
		};
	
	template <class T>
		class iterator_traits<const T*> {
			public:
			typedef ptrdiff_t						difference_type;
			typedef T								value_type;
			typedef const T*						pointer;
			typedef const T&						reference;
			typedef std::random_access_iterator_tag	iterator_category;
		};
	

	template <class Iterator>
		class reverse_iterator {
			public:
				typedef 			Iterator										iterator_type;
				typedef typename	iterator_traits<Iterator>::iterator_category	iterator_category;
				typedef typename	iterator_traits<Iterator>::value_type			value_type;
				typedef typename	iterator_traits<Iterator>::difference_type		difference_type;
				typedef typename	iterator_traits<Iterator>::pointer				pointer;
				typedef typename	iterator_traits<Iterator>::reference			reference;

				reverse_iterator () {}
				explicit reverse_iterator (iterator_type it): _iter(it) {}

				template <class Iter>
					reverse_iterator (const reverse_iterator<Iter>& rev_it) {	_iter = rev_it.base();	}
				
				iterator_type 		base() const {	return _iter;	}

				reverse_iterator	operator+(difference_type n) const
				{
					iterator_type tmp = _iter;
					return reverse_iterator(tmp - n);
				}
				reverse_iterator	operator-(difference_type n) const 
				{
					iterator_type tmp = _iter;
					return reverse_iterator(tmp + n);
				}
				reference			operator*() const {
					iterator_type tmp = _iter;
					--tmp;
					return *(tmp);
				}
				pointer				operator->() const {	return &(operator*());	}
				reference			operator[](difference_type n) const {	return *(base() - (n + 1));	}
				reverse_iterator&	operator+=(difference_type n) {	_iter -= n; return *this;	}
				reverse_iterator&	operator-=(difference_type n) {	_iter += n; return *this;	}

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

				// operator reverse_iterator<const iterator_type>() {
				// 	return reverse_iterator<const iterator_type>(_iter);
				// }

			private:
				iterator_type _iter;
		};

	/*
		* Non-member function overloads
	*/

	/*	Relational operators	*/

	template <class Iterator>
		bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return lhs.base() == rhs.base();
		}
	template <class Iterator>
		bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return lhs.base() != rhs.base();
		}
	template <class Iterator>
  		bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return rhs.base() < lhs.base();
		}
	template <class Iterator>
  		bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return rhs.base() <= lhs.base();
		}
	template <class Iterator>
  		bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return rhs.base() > lhs.base();
		}
	template <class Iterator>
  		bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return rhs.base() >= lhs.base();
		}
	
	/*	Operators	*/

	template <class Iterator>
		reverse_iterator<Iterator> operator+ (
				typename reverse_iterator<Iterator>::difference_type n,
				const reverse_iterator<Iterator>& rev_it)
		{
			return reverse_iterator<Iterator>(rev_it + n);
		}
	
	template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type operator- (
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
		{
			typename reverse_iterator<Iterator>::iterator_type tmp1 = lhs.base();
			typename reverse_iterator<Iterator>::iterator_type tmp2 = rhs.base();
			return (tmp2 - tmp1);
		}
}

#endif