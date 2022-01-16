#ifndef SET_HPP
# define SET_HPP

# include "../utils/utils.hpp"
# include "RBT_Tree_set.hpp"

namespace ft
{
	template <
				class T,
				class Compare = std::less<T>,
				class Alloc = std::allocator<T>
			 >
		class Set {
			public:
				typedef				T														key_type;
				typedef				T														value_type;
				typedef				Compare													key_compare;
				typedef				Compare													value_compare;
				typedef				Alloc													allocator_type;
				typedef	typename	allocator_type::reference								reference;
				typedef	typename	allocator_type::const_reference							const_reference;
				typedef	typename	allocator_type::pointer									pointer;
				typedef	typename	allocator_type::const_pointer							const_pointer;
				typedef	typename	ft::RBT_Set<T, Compare, Alloc>::iterator				iterator;
				typedef	typename	ft::RBT_Set<T, Compare, Alloc>::const_iterator			const_iterator;
				typedef	typename	ft::RBT_Set<T, Compare, Alloc>::reverse_iterator		reverse_iterator;
				typedef	typename	ft::RBT_Set<T, Compare, Alloc>::const_reverse_iterator	const_reverse_iterator;
				typedef				std::ptrdiff_t											difference_type;
				typedef				size_t													size_type;

				/*
					* Constructors
				*/

				explicit Set		(	const key_compare& comp = key_compare(),				// Empty
              							const allocator_type& alloc = allocator_type()
									): _alloc(alloc), _compare(comp), _size(0) {}
				
				template <class InputIterator>													// Range
					Set 			(	InputIterator first, InputIterator last,
										const key_compare& comp = key_compare(),
										const allocator_type& alloc = allocator_type()
									): _alloc(alloc), _compare(comp), _size(0)
					{
						for (; first != last; first++)
						{
							insert(*first);
						}
					}

				Set					(const Set& x) {	*this = x;	}							// Copy

				Set&				operator=(const Set& x)										// Assignement operator
				{
					_size = x._size;
					m_tree.deep_copy(x.m_tree);

					return *this;
				}

				/*
					* Destrucor
				*/

				~Set				() {	clear();	}

				/*
					* Iterators
				*/

				iterator									begin()	{	return m_tree.begin();	}
				const_iterator								begin() const {	return m_tree.begin();	}

				iterator									end() {	return m_tree.end();	}
				const_iterator								end() const {	return m_tree.end();	}

				reverse_iterator							rbegin() {	return m_tree.rbegin();	} 
				const_reverse_iterator						rbegin() const {	return m_tree.rbegin();	}

				reverse_iterator							rend() {	return m_tree.rend();	}
				const_reverse_iterator						rend() const {	return m_tree.rend();	}

				/*
					* Capacity
				*/

				bool										empty() const {	return _size == 0;	}
				size_type									size() const {	return _size;	}
				size_type									max_size() const {	return _alloc.max_size();	}

				/*
					* Modifiers
				*/

				ft::pair<iterator, bool>					insert(const value_type val)
				{
					// std::cout << "val = " << val << std::endl;
					ft::pair<iterator, bool>	ret = m_tree.insert(val);

					if (ret.second)
						_size++;

					return ret;
				}
				iterator									insert(iterator position, const value_type& val)
				{
					ft::pair<iterator, bool>	ret = insert(val);
					position = ret.first;

					return position;
				}
				template <class InputIterator>
					void									insert(InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
					{
						for (; first != last; first++)
							insert(*first);
					}

				void										erase(iterator position) {	erase(*position);	}
				size_type									erase(const value_type& k)
				{
					bool ret = m_tree.erase(k);
					if (ret)
					{
						_size--;
						return 1;
					}
					return 0;
				}
				void										erase(iterator first, iterator last)
				{
					key_type	keys[_size];
					size_type	old_size = _size;

					for (size_type i = 0; first != last; first++, i++)
						keys[i] = *first;

					for (size_type i = 0; i < old_size; i++)
						erase(keys[i]);
				}

				void 										swap (Set& x)
				{
					Set	tmp;

					tmp.m_tree = m_tree;
					tmp._size = _size;
					tmp._compare = _compare;
					tmp._alloc = _alloc;
					
					m_tree = x.m_tree;
					_size = x._size;
					_compare = x._compare;
					_alloc = x._alloc;
					
					x.m_tree = tmp.m_tree;
					x._size = tmp._size;
					x._compare = tmp._compare;
					x._alloc = tmp._alloc;

					tmp.m_tree.set_root(0);
				}

				void										clear()
				{
					m_tree.delete_tree();
					_size = 0;
				}

				/*
					* Observers
				*/

				key_compare									key_comp() const {	return _compare;	}
				value_compare								value_comp() const {	return _compare;	}

				/*
					* Operations
				*/
				
				iterator									find(const value_type& k) const {	return iterator(&m_tree.find(k)->data, (Node *)m_tree.get_root2());	}

				size_type									count(const value_type& k) const
				{
					if (m_tree.contains(k))
						return 1;
					return 0;
				}

				iterator									lower_bound(const value_type& k) const
				{
					ft::pair<const_iterator, bool> ret = m_tree.search(k);

					if ((const_iterator)ret.first != end())
						return iterator((value_type *)&(*ret.first), (Node *)m_tree.get_root2());
					return iterator(0, (Node *)m_tree.get_root2());
				}

				iterator									upper_bound(const value_type& k) const
				{
					ft::pair<const_iterator, bool> ret = m_tree.search_for_upper_bound(k);

					if (ret.second)
						return iterator((value_type *)&(*ret.first), (Node *)m_tree.get_root2());

					return iterator(0, (Node *)m_tree.get_root2());
				}

				pair<iterator,iterator>             equal_range (const value_type& k) const
				{
					ft::pair<const_iterator, bool> ret = m_tree.search(k);

					if ((const_iterator)ret.first != end() && !ret.second)
						return ft::make_pair(iterator((value_type *)&(*ret.first), (Node *)m_tree.get_root2()), iterator((value_type *)&(*(++ret.first)), (Node *)m_tree.get_root2()));
					if (ret.second)
						return ft::make_pair(iterator((value_type *)&(*ret.first), (Node *)m_tree.get_root2()), iterator((value_type *)&(*ret.first), (Node *)m_tree.get_root2()));

					return ft::make_pair(iterator(0, (Node *)m_tree.get_root2()), iterator(0, (Node *)m_tree.get_root2()));
				}

				/*
					* Allocator
				*/

				allocator_type						get_allocator() const {	return _alloc;	}

			private:
				typedef ft::RBT_Set<T, Compare, Alloc>			RBT;
				typedef typename RBT::Node						Node;
				Alloc											_alloc;
				key_compare										_compare;
				size_type										_size;
				RBT												m_tree;
				
		};

		template < class T, class Compare, class Alloc >
			bool	operator==(	const Set<  T, Compare, Alloc>& lhs,
								const Set<  T, Compare, Alloc>& rhs)
			{
				if (lhs.size() != rhs.size())
					return false;
				return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
			}
		template< class T, class Compare, class Alloc >
			bool	operator!=(	const Set< T, Compare,Alloc>& lhs,
								const Set< T, Compare,Alloc>& rhs)
			{
				if (lhs.size() != rhs.size())
					return true;
				return !operator==(lhs, rhs);
			}
		template< class T, class Compare, class Alloc >
			bool	operator<(	const Set< T, Compare,Alloc>& lhs,
								const Set< T, Compare,Alloc>& rhs)
			{
				return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), lhs.value_comp());
			}
		template< class T, class Compare, class Alloc >
			bool	operator<=(	const Set< T, Compare,Alloc>& lhs,
								const Set< T, Compare,Alloc>& rhs)
		{
			return !operator<(rhs, lhs);
		}
		template< class T, class Compare, class Alloc >
			bool	operator>(	const Set< T, Compare,Alloc>& lhs,
								const Set< T, Compare,Alloc>& rhs)
			{
				return operator<(rhs, lhs);
			}
		template< class T, class Compare, class Alloc >
			bool	operator>=(	const Set< T, Compare,Alloc>& lhs,
								const Set< T, Compare,Alloc>& rhs)
			{
				return !operator<(lhs, rhs);
			}

		template< class T, class Compare, class Alloc >
			void swap( Set< T, Compare,Alloc>& lhs,
					Set< T, Compare,Alloc>& rhs )
			{
				lhs.swap(rhs);
			}
}

#endif