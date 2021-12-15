#ifndef VECTOR_HPP
# define VECTOR_HPP
#include <iostream>
#include <memory>
#include <algorithm>
#include "MyIterator.hpp"
#include "../utils/utils.hpp"
#include "../reverse_iterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class Vector
	{
		public:
			typedef				T										value_type;
			typedef 			Alloc									allocator_type;
			typedef typename	allocator_type::reference				reference;
			typedef typename	allocator_type::const_reference			const_reference;
			typedef typename	allocator_type::pointer					pointer;
			typedef typename	allocator_type::const_pointer			const_pointer;
			typedef				MyIterator<value_type>					iterator;
			typedef				MyIterator<const value_type>			const_iterator;
			typedef				ft::reverse_iterator<iterator>			reverse_iterator;
			typedef				ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef typename	std::ptrdiff_t							difference_type;
			typedef 			size_t									size_type;


			/*
				* Contructors
			*/

			explicit Vector	(const allocator_type& alloc = allocator_type()):			// Default
				_alloc(alloc), _size(0), _capacity(0) {	/*_arr = _alloc.allocate(0);*/	}
			explicit Vector	(size_type n, const value_type& val = value_type(), 		// Fill
							const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(n), _capacity(n)
			{
				_arr = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_arr + i, val);
			}
			template <class InputIterator>												// Range
				Vector		(
								InputIterator first, InputIterator last,
								const allocator_type& alloc = allocator_type(),
								typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator()
							): _alloc(alloc)
				{
					_capacity = last - first;
					_size = _capacity;
					_arr = _alloc.allocate(_capacity);
					for (int i = 0; first != last; first++, i++)
						_alloc.construct(_arr + i, *first);
				}
			Vector 			(const Vector& x): _size(0), _capacity(0)						//Copy
			{
				if (!x.size())
				{
					return	;
				}
				_capacity = x.size();
				_arr = _alloc.allocate(_capacity);
				*this = x;
			}

			Vector&	operator= (const Vector& x) {
				_size = 0;
				reallocate(x.size());

				for (size_type i = 0; i < x.size(); i++)
				{
					push_back(x._arr[i]);
				}
				return *this;
			}
			
			/*
				* Destructor
			*/

			~Vector() {	if (_capacity) _alloc.deallocate(_arr, _capacity);	};

			/*
				* Iterators
			*/
			
			iterator				begin() {	return iterator(_arr);	}
			const_iterator			begin() const {	return const_iterator(_arr);	}

			iterator				end() {	return iterator(_arr + _size);	}
			const_iterator			end() const {	return const_iterator(_arr + _size);	}

			reverse_iterator		rbegin() {	return reverse_iterator(_arr + _size);	}
			const_reverse_iterator	rbegin() const {	return const_reverse_iterator(_arr + _size);	}

			reverse_iterator 		rend() {	return reverse_iterator(_arr);	}
			const_reverse_iterator 	rend() const {	return const_reverse_iterator(_arr);	}

			// Reverse Iterator's functions

			/*
				* Capacity
			*/

			size_type				size() const {	return _size;	}
			size_type				max_size() const {	return _alloc.max_size();	}
			
			void					resize(size_type n, value_type val = value_type())
			{
				if (n < _size)
					_size = n;
				if (n > _capacity)
					reallocate(n);
				while (n > _size)
					push_back(val);
			}
			
			size_type				capacity() const {	return _capacity;	}
			bool					empty() const {	return _size == 0;	}
			
			void					reserve(size_type n)
			{
				if (n > max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				if (n > _capacity)
					reallocate(n);
			}

			/*
				* Element Access
			*/

			reference				operator[](size_type n)
			{
				return _arr[n];
			}
			const_reference			operator[](size_type n) const
			{
				return _arr[n];
			}

			reference				at(size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("vector");
				return _arr[n];
			}
			const_reference			at(size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("vector");
				return _arr[n];
			}

			reference				front() {	return _arr[0];	}
			const_reference			front() const {	return _arr[0];	}

			reference				back() {	return _arr[_size - 1];	}
			const_reference			back() const {	return _arr[_size - 1];	}

			/*
				* Modifiers
			*/

			template <class InputIterator>
				void				assign(InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
				{
					_size = 0;
					
					size_type len = last - first;
					if (len > _capacity)
						reallocate(len);
					for (; first != last; first++)
						push_back(*first);
				}
			void					assign(size_type n, const value_type& val)
			{
				_size = 0;
				
				if (n > _capacity)
					reallocate(n);
				while (n > _size)
					push_back(val);
			}

			void					push_back(const value_type& val)
			{
				if (_size + 1 > _capacity)
					reallocate();
				_size++;
				_alloc.construct(_arr + (_size - 1), val);
			}

			void					pop_back() {	_size--; _alloc.destroy(_arr + _size);	}

			iterator				insert(iterator position, const value_type& val) {
				size_type dist = std::distance(begin(), position);
			
				push_back(val);
				position = begin() + dist;
				iterator last = end() - 1; 
			
				for (; position != end() - 1; position++)
					std::swap(*position, *last);	
			
			
				return begin() + dist;
			}
			void					insert(iterator position, size_type n, const value_type& val)
			{
				size_type dist = std::distance(begin(), position);

				if (_size + n > _capacity)
				{
					if (n <= _size)
						reallocate();
					else
						reallocate(_size + n);
				}
				position = begin() + dist;

				Vector tmp(position, end());
				for (; n; position++, n--, dist++)
				{
					_alloc.construct(_arr + dist, val);
					_size++;
				}
				for (iterator it = tmp.begin(); it != tmp.end(); it++, dist++)
					_alloc.construct(_arr + dist, *it);
			}
			template <class InputIterator>
   				void 				insert (
										iterator position,
										InputIterator first,
										InputIterator last,
										typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator()
									)
				{
					size_type dist = std::distance(begin(), position);
					size_type range = std::distance(first, last);

					if (_size + range > _capacity)
					{
						if (range <= _size)
							reallocate();
						else
							reallocate(_size + range);
					}
					
					position = begin() + dist;
					Vector tmp(position, end());
					for (; first != last; first++, dist++)
					{
						_alloc.construct(_arr + dist, *first);
						_size++;
					}
					for (iterator it = tmp.begin(); it != tmp.end(); it++, dist++)
						_alloc.construct(_arr + dist, *it);
				}

			iterator 				erase(iterator position)
			{
				iterator initial_pos = position;

				for (; position != end() - 1; position++)
					std::swap(*position, *(position + 1));
				pop_back();
				return initial_pos;
			}

			iterator 				erase(iterator first, iterator last)
			{
				iterator ret = first;
				size_type dist = std::distance(begin(), first);
				if (last == end())
				{
					for (;first != last; first++, dist++)
					{
						_alloc.destroy(_arr + dist);
						_size--;
					}
				}
				else
				{
					size_type i = 0;
					for (; first != last; first++, dist++)
					{
						if ((last + i) < end())
							std::swap(*first, *(last + i));
						_alloc.destroy(_arr + dist);
						_size--;
					}
				}
				
				return ret;
			}

			void					swap(Vector& x)
			{
				pointer tmp = _arr;
				size_type len = _size;
				size_type cap = _capacity;

				_arr = x._arr;
				_size = x._size;
				_capacity = x._capacity;

				x._arr = tmp;
				x._size = len;
				x._capacity = cap;
			}

			void					clear()
			{
				while (_size > 0)
					pop_back();
			}

			/*
				* Allocator
			*/

			allocator_type			get_allocator() const {	return _alloc;	}

		private:
			value_type		*_arr;
			allocator_type	_alloc;
			size_type		_size;
			size_type		_capacity;

			void					reallocate(size_type n = 0)
			{
				if (n > max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				
				if (!_capacity)
				{
					_capacity = n ? n : 1;
					_arr = _alloc.allocate(_capacity);
					return ;
				}

				pointer		tmp = _arr;
				size_type	cap = _capacity;

				_capacity = n ? n : _capacity * 2;

				_arr = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_arr + i, tmp[i]);

				for (size_type i = 0; i < cap; i++)
					_alloc.destroy(tmp + i);
			}
	};

	/*
		* Non-member function overloads
	*/

	/*	Relational operators	*/

	template <class T, class Alloc>
		bool operator== (const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return false;
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}
	template <class T, class Alloc>
		bool operator!= (const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return true;
			return !operator==(lhs, rhs);
		}
	template <class T, class Alloc>
  		bool operator<  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}
	template <class T, class Alloc>
  		bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
		{
			return !operator<(rhs, lhs);
		}
	template <class T, class Alloc>
  		bool operator> (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
		{
			return operator<(rhs, lhs);
		}
	template <class T, class Alloc>
  		bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
		{
			return !operator<(lhs, rhs);
		}
	
	/*	swap	*/

	template <class T, class Alloc>
  		void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y) {	x.swap(y);	}
}

#endif
