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
				typedef typename	ft::RBT<key_type, mapped_type, Compare, Alloc>::iterator				iterator;
				typedef typename	ft::RBT<key_type, mapped_type, Compare, Alloc>::const_iterator			const_iterator;
				typedef typename	ft::RBT<key_type, mapped_type, Compare, Alloc>::reverse_iterator		reverse_iterator;
				typedef typename	ft::RBT<key_type, mapped_type, Compare, Alloc>::const_reverse_iterator	const_reverse_iterator;
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

				explicit Map 				(	const key_compare& comp = key_compare(),			// Empty
												const allocator_type& alloc = allocator_type()
							 				): _alloc(alloc), _compare(comp), _size(0) {}

				template <class InputIterator>
					Map 					(	InputIterator first, InputIterator last,			// Range
												const key_compare& comp = key_compare(),
												const allocator_type& alloc = allocator_type()
											): _compare(comp), _alloc(alloc), _size(0)
					{
						for (; first != last; first++)
						{
							value_type tmp;
							tmp.first = first->first;
							tmp.second = first->second;
							insert(tmp);
						}
					}
				Map							(const Map& x)											// Copy
				{
					*this = x;
				}

				Map&						operator=(const Map& x)									// Assignement operator
				{
					m_tree = x.m_tree;
					_size = x._size;

					return *this;
				}
				
				/*
					* Destrucor
				*/
				~Map		() {}

				/*
					* Iterators
				*/

				iterator					begin()	{	return m_tree.begin();	}
				const_iterator				begin() const {	return m_tree.begin();	}

				iterator					end() {	return m_tree.end();	}
				const_iterator				end() const {	return m_tree.end();	}

				reverse_iterator			rbegin() {	return m_tree.rbegin();	} 
				const_reverse_iterator		rbegin() const {	return m_tree.rbegin();	}

				reverse_iterator			rend() {	return m_tree.rend();	}
				const_reverse_iterator		rend() const {	return m_tree;	}



				/*
					* Capacity
				*/

				bool						empty() const {	return _size == 0;	}
				size_type					size() const {	return _size;	}
				size_type					max_size() const {	return _alloc.max_size();	}

				/*
					* Element access
				*/

				mapped_type&				operator[](const key_type& k)
				{
					return m_tree.find(k)->second;
				}
				
				/*
					* Modifiers
				*/

				ft::pair<iterator, bool>	insert(const value_type val)
				{
					ft::pair<iterator, bool>	ret = m_tree.insert(val);
					
					if (ret.second)
						_size++;
					
					return ret;
				}
				iterator					insert(iterator position, const value_type& val)
				{
					
					
					ft::pair<iterator, bool>	ret = insert(val);
					position = ret.first;

					return position;
				}
				template <class InputIterator>
					void					insert(InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
					{
						for (; first != last; first++)
						{
							value_type tmp;
							tmp.first = first->first;
							tmp.second = first->second;
							insert(tmp);
						}
					}

				void						erase(iterator position)
				{
					bool ret = m_tree.erase(position->first);
					if (ret)
						_size--;
				}
				void						erase(const key_type& k)
				{
					bool ret = m_tree.erase(k);
					if (ret)
						_size--;
				}
				void						erase(iterator first, iterator last)
				{
					key_type	keys[_size];
					size_type	old_size = _size;

					// Geting keys
					for (size_type i = 0; first != last; first++, i++)
						keys[i] = first->first;

					for (size_type i = 0; i < old_size; i++)
					{
						std::cout << keys[i] << std::endl;
						erase(keys[i]);
					}
				}


				// swap

				void						clear()	{	erase(begin(), end());	}
				
				/*
					* Observers
				*/

				key_compare					key_comp() const {	return _compare;	}
				value_compare				value_comp() const {	return value_compare();	}

				/*
					* Operations
				*/
				
				iterator					find(const key_type& k) {	return m_tree.find(k);	}
				const_iterator				find(const key_type& k) const {	return m_tree.find(k);	}

				size_type					count(const key_type& k)
				{
					if (find(k))
						return 1;
					return 0;
				}

			private:
				Alloc											_alloc;
				key_compare										_compare;
				size_type										_size;
				ft::RBT<key_type, mapped_type, Compare, Alloc>	m_tree;
		};
}

#endif