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
				typedef				key									key_type;
				typedef 			T									mapped_type;
				typedef				pair<const key_type, mapped_type>	value_type;
				typedef				Compare								key_compare;
				typedef				Alloc								allocator_type;
				typedef	typename	allocator_type::reference			reference;
				typedef	typename	allocator_type::const_reference		const_reference;
				typedef	typename	allocator_type::pointer				pointer;
				typedef	typename	allocator_type::const_pointer		const_pointer;
				// iterator
				// const_iterator
				// reverse_iterator
				// const_reverse_iterator
				// diffrence_type
				typedef	size_t								size_type;

				/*
					* Contructors
				*/

				explicit map 				(	const key_compare& comp = key_compare(),			// Empty
												const allocator_type& alloc = allocator_type()
							 				): _compare(comp), _alloc(alloc), _size(0) {}

				template <class InputIterator>
					map 					(	InputIterator first, InputIterator last,			// Range
												const key_compare& comp = key_compare(),
												const allocator_type& alloc = allocator_type()
											): _compare(comp), _alloc(alloc), _size(0)
					{
						// iterators
					}
				map							(const map& x)											// Copy
				{
					*this = x;
				}

				map&						operator=(const map& x)									// Assignement operator
				{
					m_tree = x.m_tree;
					_size = x._size;

					return *this;
				}
				
				/*
					* Destrucor
				*/
				~map		() {}

				/*
					* Iterators
				*/



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

				}
				
				/*
					* Modifiers
				*/

				ft::pair<iterator, bool>	insert(const value_type& val)
				{
					bool	ret = m_tree.insert(val);
					// implement return type
				}
				iterator					insert(iterator position, const value_type& val)
				{

				}
				template <class InputIterator>
					void					insert(InputIterator first, InputIterator last)
					{

					}
				

			private:
				Alloc											_alloc;
				key_compare										_compare;
				size_type										_size;
				ft::RBT_Tree<key_type, mapped_type, _compare>	m_tree;
		};
}

#endif