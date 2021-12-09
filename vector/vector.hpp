#ifndef VECTOR_HPP
# define VECTOR_HPP
#include <iostream>
#include <memory>
#include <algorithm>
#include "MyIterator.hpp"
#include "../utils.hpp"
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
				_alloc(alloc), _size(0), _capacity(0) {	_arr = _alloc.allocate(0);	}
			explicit Vector	(size_type n, const value_type& val = value_type(), 		// Fill
							const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(n), _capacity(n)
			{
				_arr = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					_arr[i] = val;
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
					{
						_arr[i] = *first;
					}
				}
			Vector 			(const Vector& x)											//Copy
			{
				_capacity = 0;
				_arr = _alloc.allocate(0);
				*this = x;
			}

			Vector&	operator= (const Vector& x) {
				_size = 0;
				_capacity = _capacity < x.size() ? x.size() : _capacity; 

				for (size_type i = 0; i < x.size(); i++)
					push_back(x._arr[i]);
				return *this;
			}
			
			/*
				* Destructor
			*/

			~Vector() {	_alloc.deallocate(_arr, _capacity);	};

			/*
				* Iterators
			*/
			
			iterator				begin() {	return iterator(_arr);	}
			const_iterator			begin() const {	return const_iterator(_arr);	}

			iterator				end() {	return iterator(_arr + _size);	}
			const_iterator			end() const {	return const_iterator(_arr + _size);	}

			reverse_iterator		rbegin() {	return reverse_iterator(end());	}
			const_reverse_iterator	rbegin() const {	return const_reverse_iterator(end());	}

			reverse_iterator 		rend() {	return reverse_iterator(begin());	}
			const_reverse_iterator 	rend() const {	return const_reverse_iterator(begin());	}

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
					for (; first != last; first++)
						push_back(*first);
				}
			void					assign(size_type n, const value_type& val)
			{
				_size = 0;
				while (n > _size)
					push_back(val);
			}

			void					push_back(const value_type& val)
			{
				_size++;
				if (_size > _capacity)
					reallocate();
				_arr[_size - 1] = val;
			}

			void					pop_back() {	_size--; _alloc.destroy(_arr + _size);	}

			iterator				insert(iterator position, const value_type& val) {	put_val(position, val);	return position;	}
			void					insert(iterator position, size_type n, const value_type& val)
			{
				size_type total_size = _size + n;
				while (total_size > _size)
					put_val(position, val);
			}
			template <class InputIterator>
   				void 				insert (
										iterator position,
										InputIterator first,
										InputIterator last,
										typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator()
									)
				{
					for (; first != last; first++, position++)
						put_val(position, *first);
				}

			iterator 				erase(iterator position)
			{
				erase_one(position);
				return position;
			}

			iterator 				erase(iterator first, iterator last)
			{
				iterator ret = first;
				for (; first != last; last--)
				{
					erase_one(first);
				}
				return first;
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

			void					reallocate(int n = 0)
			{
				value_type *tmp = new value_type[_size];
				std::copy(_arr, _arr + _size, tmp);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_arr + i);

				if (n)
					_capacity = n;
				else if (_capacity)
					_capacity *= 2;
				else
					_capacity = 1;

				_arr = _alloc.allocate(_capacity);
				std::copy(tmp, tmp + _size, _arr);
				delete [] tmp;
			}

			void					put_val(iterator pos, T val)
			{
				push_back(val);
				iterator last = end() - 1; 
				for (; pos != end() - 1; pos++)
					std::swap(*pos, *last);
			}

			void					erase_one(iterator pos)
			{
				for (; pos != _arr + _size; pos++)
					std::swap(*pos, *(pos + 1));
				pop_back();
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
