#ifndef VECTOR_HPP
# define VECTOR_HPP
#include <iostream>
#include <memory>
#include <algorithm>
#include "MyIterator.hpp"
namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef				T								value_type;
			typedef 			Alloc							allocator_type;
			typedef 			size_t							size_type;
			typedef typename	allocator_type::reference		reference;
			typedef typename	allocator_type::const_reference	const_reference;
			typedef typename	allocator_type::pointer			pointer;
			typedef typename	allocator_type::const_pointer	const_pointer;
			typedef				MyIterator<value_type>			iterator;
			typedef				MyIterator<const value_type>	const_iterator;
			
			/*
				* Contructors
			*/

			explicit vector	(const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(0), _capacity(0) {	_arr = _alloc.allocate(0);	}
			explicit vector	(size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(n), _capacity(n)
			{
				_arr = _alloc.allocate(n);
				for (int i = 0; i < n; i++)
					_arr[i] = val;
			}
			// template <class InputIterator>
			// 	vector		(InputIterator first, InputIterator last,
			// 				const allocator_type& alloc = allocator_type()): _alloc(alloc) // initialize _size and _capacity
			// 	{
			// 		// Fill _arr by iterating
			// 	}
			vector 			(const vector& x) {
				// Copy x's element in my array
				// initialize _size, _capacity and _alloc
			}

			vector&	operator= (const vector& x) {
				// copy size, capacity and x's elements
			}
			
			/*
				* Destructor
			*/

			~vector() {};

			/*
				* Iterators
			*/
			
			iterator		begin()
			{
				return iterator(_arr);
			}
			const_iterator	begin() const
			{
				return const_iterator(_arr);
			}

			iterator		end()
			{
				return iterator(_arr + _size);
			}
			const_iterator	end() const
			{
				return const_iterator(_arr + _size);
			}

			/*
				* Capacity
			*/

			size_type		size() const {	return _size;	}
			size_type		max_size() const {	return _alloc.max_size();	}
			
			void			resize(size_type n, value_type val = value_type())
			{
				if (n < _size)
				{
					// erase _arr's element untill _size == n
				}
				else if (n > _size)
				{
					if (n > _capacity)
					{
						// REALOCATION
							// - save current _arr elems in a tmp
							// - copy the tmp elems in the realocated _arr
					}
					// insert val in _arr until _size == n
				}
			}
			
			size_type		capacity() const {	return _capacity;	}
			bool			empty() const {	return _size == 0;	}
			
			void			reserve(size_type n)
			{
				if (n > max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				if (n > _capacity)
				{
					_capacity = n;
					// reallocate to n
				}
			}

			/*
				* Element Access
			*/

			reference		operator[] (size_type n)
			{
				return _arr[n];
			}
			const_reference	operator[] (size_type n) const
			{
				return _arr[n];
			}

			reference		at (size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("vector");
				return _arr[n];
			}
			const_reference	at (size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("vector");
				return _arr[n];
			}

			reference		front()
			{
				return _arr[0];
			}
			const_reference	front() const
			{
				return _arr[0];
			}

			reference		back()
			{
				return _arr[_size - 1];
			}
			const_reference	back() const
			{
				return _arr[_size - 1];
			}

			/*
				* Modifiers
			*/

			template <class InputIterator>
				void		assign (InputIterator first, InputIterator last)
				{
					// assign with Iterator
				}
			void			assign (size_type n, const value_type& val)
			{
				// Erase the existing elements
				// insert val n times, change the size accordinglly
				// if -and only if- the new vector size surpasses the current vector capacity.
					// REALOCATION
			}

			void			push_back(const value_type& val)
			{
				_size++;
				if (_size > _capacity)
				{
					reallocate();
				}
				_arr[_size - 1] = val;
			}

			void			pop_back()
			{
				_size--;
				// erase the lase element
			}

			// insert

			// erase

			void			swap(vector& x)
			{
				// swap the elements from x to the current _arr
				// all iterators, references and pointers must remain valid
				// The capacity is also swaped
			}

			void			clear()
			{
				// remove all elements from the array
				// size = 0
			}

			/*
				* Allocator
			*/

			allocator_type	get_allocator() const {	return _alloc;	}

		private:
			value_type		*_arr;
			allocator_type	_alloc;
			size_type		_size;
			size_type		_capacity;

			void			reallocate()
			{
				value_type *tmp = std::move(_arr);
				// value_type *tmp = _arr;

				if (_capacity)
					_capacity *= 2;
				else
					_capacity = 1;

				_arr = _alloc.allocate(_capacity);
				_arr = std::move(tmp);
				// _arr = tmp;
			}
	};
}

#endif
