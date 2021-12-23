#ifndef MAP_HPP
# define MAP_HPP
# include "../utils/utils.hpp"
# include "../utils/pair.hpp"
# include "RBT_Tree.hpp"


namespace ft
{
	template <	
				class key,
				class T,
				class Compare = std::less<key>,
				class Alloc = std::allocator<ft::pair<const key, T> >
			 >
		class Map {
			public:
				typedef				key																		key_type;
				typedef 			T																		mapped_type;
				typedef				ft::pair<const key_type, mapped_type>									value_type;
				typedef				Compare																	key_compare;
				typedef				Alloc																	allocator_type;
				typedef	typename	allocator_type::reference												reference;
				typedef	typename	allocator_type::const_reference											const_reference;
				typedef	typename	allocator_type::pointer													pointer;
				typedef	typename	allocator_type::const_pointer											const_pointer;
				typedef typename	ft::RBT<key, T, Compare, Alloc>::iterator				iterator;
				typedef typename	ft::RBT<key, T, Compare, Alloc>::const_iterator			const_iterator;
				typedef typename	ft::RBT<key, T, Compare, Alloc>::reverse_iterator		reverse_iterator;
				typedef typename	ft::RBT<key, T, Compare, Alloc>::const_reverse_iterator	const_reverse_iterator;
				typedef				std::ptrdiff_t															difference_type;
				typedef				size_t																	size_type;
				typedef				class value_compare: std::binary_function<value_type, value_type, bool>
				{
					friend class map;
					protected:
						Compare comp;
						value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
					public:
						typedef bool result_type;
						typedef value_type first_argument_type;
						typedef value_type second_argument_type;
						bool operator() (const value_type& x, const value_type& y) const
						{
							return comp(x.first, y.first);
						}
				}																							value_compare;

				/*
					* Contructors
				*/

				explicit Map 							(	const key_compare& comp = key_compare(),			// Empty
															const allocator_type& alloc = allocator_type()
							 							): _alloc(alloc), _compare(comp), _size(0) {}

				template <class InputIterator>
					Map 								(	InputIterator first, InputIterator last,			// Range
															const key_compare& comp = key_compare(),
															const allocator_type& alloc = allocator_type()
														): _compare(comp), _alloc(alloc), _size(0)
					{
						for (; first != last; first++)
						{
							ft::pair<key_type, mapped_type> tmp;
							tmp.first = first->first;
							tmp.second = first->second;
							insert(tmp);
						}
					}
				Map										(const Map& x)											// Copy
				{
					*this = x;
				}

				Map&									operator=(const Map& x)									// Assignement operator
				{
					m_tree = x.m_tree;
					_size = x._size;

					return *this;
				}
				
				/*
					* Destrucor
				*/
				~Map		() {	clear();	}

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
				const_reverse_iterator						rend() const {	return m_tree;	}



				/*
					* Capacity
				*/

				bool										empty() const {	return _size == 0;	}
				size_type									size() const {	return _size;	}
				size_type									max_size() const {	return _alloc.max_size();	}

				/*
					* Element access
				*/

				mapped_type&								operator[](const key_type& k)
				{
					ft::pair<key_type, mapped_type> tmp;
					tmp.first = k;
					tmp.second = 0;
					return m_tree.find(tmp)->data.second;
				}
				
				/*
					* Modifiers
				*/

				ft::pair<iterator, bool>					insert(const value_type val)
				{
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
						{
							ft::pair<key_type, mapped_type> tmp;
							tmp.first = first->first;
							tmp.second = first->second;
							insert(tmp);
						}
					}

				void										erase(iterator position)
				{
					bool ret = m_tree.erase(position->first);
					if (ret)
						_size--;
				}
				size_type									erase(const key_type& k)
				{
					ft::pair<key_type, mapped_type> tmp;
					tmp.first = k;
					tmp.second = 0;
					bool ret = m_tree.erase(tmp);
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
						keys[i] = first->first;

					for (size_type i = 0; i < old_size; i++)
						erase(keys[i]);
				}

				void										swap(Map& x)
				{
					m_tree = x.m_tree;
					_size = x._size;
				}

				void										clear()	{	erase(begin(), end());	}
				
				/*
					* Observers
				*/

				key_compare									key_comp() const {	return _compare;	}
				value_compare								value_comp() const {	return value_compare();	}

				/*
					* Operations
				*/
				
				iterator									find(const key_type& k) {
					ft::pair<key_type, mapped_type> tmp;
					tmp.first = k;
					tmp.second = 0;

					return m_tree.find(tmp);
				}
				const_iterator								find(const key_type& k) const {
					ft::pair<key_type, mapped_type> tmp;
					tmp.first = k;
					tmp.second = 0;
	
					return m_tree.find(k);
				}

				size_type									count(const key_type& k)
				{
					if (find(k))
						return 1;
					return 0;
				}

				iterator									lower_bound(const key_type& k)
				{
					for (iterator first = begin(); first != end(); first++)
					{
						if (first->data.first >= k)
							return first;
					}
					return &(*(begin())) + 1;
				}
				const_iterator								lower_bound (const key_type& k) const
				{
					for (const_iterator first = begin(); first != end(); first++)
					{
						if (first->data.first >= k)
							return first;
					}
					return &(*(begin())) + 1;
				}

				iterator									upper_bound(const key_type& k)
				{
					for (iterator first = begin(); first != end(); first++)
					{
						if (first->data.first > k)
							return first;
					}
					return &(*(begin())) + 1;
				}
				const_iterator								upper_bound (const key_type& k) const
				{
					for (const_iterator first = begin(); first != end(); first++)
					{
						if (first->data.first > k)
							return first;
					}
					return &(*(begin())) + 1;
				}

				ft::pair<const_iterator, const_iterator>	equal_range(const key_type& k) const
				{
					ft::pair<const_iterator, const_iterator> ret;
					for (const_iterator first = begin(); first != end(); first++)
					{
						if (first->data.first == k)
						{
							ret.first = first;
							first++;
							ret.second = first;
							return ret;
						}
						if (first->data.first > k)
						{
							ret.first = first;
							ret.second = first;
							return ret;
						}
					}
					return ft::make_pair(&(*(begin())) + 1, &(*(begin())) + 1);
				}

				pair<iterator,iterator>             equal_range (const key_type& k)
				{
					ft::pair<iterator, iterator> ret;
					for (iterator first = begin(); first != end(); first++)
					{
						if (first->data.first == k)
						{
							ret.first = first;
							first++;
							ret.second = first != end() ? first : ret.first;
							return ret;
						}
						if (first->data.first > k)
						{
							ret.first = first;
							ret.second = first;
							return ret;
						}
					}
					return ft::make_pair(&(*(begin())) + 1, &(*(begin())) + 1);
				}

				/*
					* Allocator
				*/

				allocator_type						get_allocator() const {	return _alloc;	}

			private:
				Alloc											_alloc;
				key_compare										_compare;
				size_type										_size;
				ft::RBT<key, T, Compare, Alloc>				m_tree;
		};

		/*
			* Non-member function overloads
		*/

		template < class Key, class T, class Compare, class Alloc >
			bool	operator==(	const Map<Key, T, Compare, Alloc> lhs,
								const Map<Key, T, Compare, Alloc> rhs)
			{
				if (lhs.size() != rhs.size())
					return false;
				return ft::map_equal(lhs.begin(), lhs.end(), rhs.begin());
			}
		template< class Key, class T, class Compare, class Alloc >
			bool	operator!=(	const Map<Key,T,Compare,Alloc>& lhs,
								const Map<Key,T,Compare,Alloc>& rhs)
			{
				if (lhs.size() != rhs.size())
					return true;
				return !operator==(lhs, rhs);
			}
		template< class Key, class T, class Compare, class Alloc >
			bool	operator<(	const Map<Key,T,Compare,Alloc>& lhs,
								const Map<Key,T,Compare,Alloc>& rhs)
			{
				return ft::map_lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
			}
		template< class Key, class T, class Compare, class Alloc >
			bool	operator<=(	const Map<Key,T,Compare,Alloc>& lhs,
								const Map<Key,T,Compare,Alloc>& rhs)
		{
			return !operator<(rhs, lhs);
		}
		template< class Key, class T, class Compare, class Alloc >
			bool	operator>(	const Map<Key,T,Compare,Alloc>& lhs,
								const Map<Key,T,Compare,Alloc>& rhs)
			{
				return operator<(rhs, lhs);
			}
		template< class Key, class T, class Compare, class Alloc >
			bool	operator>=(	const Map<Key,T,Compare,Alloc>& lhs,
								const Map<Key,T,Compare,Alloc>& rhs)
			{
				return !operator<(lhs, rhs);
			}
		

}

#endif