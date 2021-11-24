#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <memory>
#include <algorithm>

template <class T, class Alloc = std::allocator<T> >
class vector
{
	public:
		typedef	T			value_type;
		typedef Alloc		allocator_type;
		typedef size_t		size_type;
		typedef typename	allocator_type::reference		reference
		typedef typename	allocator_type::const_reference	const_reference
		typedef typename	allocator_type::pointer			pointer
		typedef typename	allocator_type::const_pointer	const_pointer
		
		/*
			* Contructors
		*/

		explicit vector	(const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(0), _capacity(0) {	_arr = _alloc.allocate(0);	}
		explicit vector	(size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type): _alloc(alloc), _size(n), _capacity(n)
		{
			_arr = _alloc.allocate(n);
		}
		template <class std::InputIterator>
			vector		(InputIterator first, InputIterator last,
						const allocator_type& alloc = allocator_type): _alloc(alloc) // initialize _size and _capacity
			{
				// Fill _arr by iterating
			}
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

		~vector();

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
						// - destory and reallocate _arr to _capacity * 2
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
				throw std::length_error();
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
				throw std::out_of_range();
			return _arr[n];
		}
		const_reference	at (size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range();
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
				// REALOCATION
			}
			_arr[_size - 1] = val;
		}

		void			pop_back()
		{
			_size--;
			// erase the lase element
		}

		

	private:
		value_type		*_arr;
		allocator_type	_alloc;
		size_type		_size;
		size_type		_capacity;
};

#endif