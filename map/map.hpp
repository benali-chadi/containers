#ifndef MAP_HPP
# define MAP_HPP
# include "../utils/utils.hpp"
# include "../utils/pair.hpp"
# include "RBT_Tree.hpp"


namespace ft
{
	template <	class key,
				class T,
				class Compare = std::less<key>,
				class Alloc = std::allocator<ft::pair<const key, T> >
			>
		class Map {
			public:
				typedef				key																key_type;
				typedef 			T																mapped_type;
				typedef				pair<const key_type, mapped_type>								value_type;
				typedef				Compare															key_compare;
				typedef				Alloc															allocator_type;
				typedef	typename	allocator_type::reference										reference;
				typedef	typename	allocator_type::const_reference									const_reference;
				typedef	typename	allocator_type::pointer											pointer;
				typedef	typename	allocator_type::const_pointer									const_pointer;
				typedef typename	ft::RBT<key_type, mapped_type, Compare>::iterator				iterator;
				typedef typename	ft::RBT<key_type, mapped_type, Compare>::const_iterator			const_iterator;
				typedef typename	ft::RBT<key_type, mapped_type, Compare>::reverse_iterator		reverse_iterator;
				typedef typename	ft::RBT<key_type, mapped_type, Compare>::const_reverse_iterator	const_reverse_iterator;
				typedef				std::ptrdiff_t													difference_type;
				typedef				size_t															size_type;

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
					return m_tree.search_to_erase(k)->second;
				}
				
				/*
					* Modifiers
				*/

				ft::pair<iterator, bool>	insert(const value_type& val)
				{
					// iterator					tmp;
					// tmp->first = val.first;
					// tmp->second = val.second;
					// std::cout << "tmp first = " << tmp->first;
					ft::pair<iterator, bool>	ret = m_tree.insert(val);
					std::cout << "ok\n";
					
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
					for (; first != last; first++)
						erase(first);
				}
				
				

			private:
				Alloc									_alloc;
				key_compare								_compare;
				size_type								_size;
				ft::RBT<key_type, mapped_type, Compare>	m_tree;
		};
}

#endif