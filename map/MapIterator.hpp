#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

# include "../utils/utils.hpp"

// 'ft::Map<int, char>::iterator' (aka 'MapIterator<node<int, char>, int, char, std::__1::less<int>, std::__1::allocator<ft::pair<const int, char> > >')
// 'ft::MapIterator<const ft::node<int, char>, int, char, std::__1::less<int>, std::__1::allocator<ft::pair<const int, char> > >::pointer' (aka 'const ft::node<int, char> *') for 1st argument


namespace ft
{
	template <class T1, class Compare, class Alloc>
		class RBT;
	template <class T, typename T1, class Compare, class Alloc>
	class MapIterator: public ft::iterator<std::bidirectional_iterator_tag, T>
	{
		public:
			typedef typename	iterator<std::bidirectional_iterator_tag, T1>::difference_type		difference_type;
			typedef typename	iterator<std::bidirectional_iterator_tag, T1>::value_type			value_type;
			typedef typename	iterator<std::bidirectional_iterator_tag, T1>::pointer				pointer;
			typedef typename	iterator<std::bidirectional_iterator_tag, T1>::reference			reference;
			typedef typename	iterator<std::bidirectional_iterator_tag, T1>::iterator_category	iterator_category;

			typedef 			T*																	m_pointer;


			// typedef	ft::RBT<key, T1, Compare> RBT;
			/*
				* Constructors
			*/

			MapIterator		() {}
			operator MapIterator<const T, const T1, Compare, Alloc>() {
    	        return MapIterator<const T, const T1, Compare, Alloc>(_p);
	        }
			MapIterator		(const MapIterator &x): _p(x._p)
			{
				m_pointer r = helper.get_root(_p);
				helper.set_root(r);
			}
			
			
			MapIterator		(m_pointer x): _p(x) {

				// pointer r = helper.get_root(_p);
				// if (x == r && (helper.in_order_pred(r) != r && helper.in_order_succ(r) != r))
				// 	_p = 0;
				helper.set_root(helper.get_root(x));
				// helper.set_root(r);
			}
			MapIterator		(m_pointer x, m_pointer root)
			{
				_p = x;
				helper.set_root(root);
			}

			MapIterator&	operator=(const MapIterator &x){ _p = x._p;	return *this;	}

			/*
				* Destructors
			*/

			~MapIterator		() {}

			/*
				* Operators
			*/

			bool			operator==(const MapIterator& x) {	return _p == x._p;	}
			bool			operator!=(const MapIterator& x) {	return _p != x._p;	}
			reference		&operator*() {	return _p->data;	}
			pointer			operator->() {	return &operator*();	}
			
			MapIterator&	operator++()
			{
				_p = helper.increment(_p);
				
				return *this;
			}
			MapIterator	operator++(int)
			{
				MapIterator tmp(*this);
				operator++();
				return tmp;
			}
			MapIterator&	operator--()
			{
				_p = helper.decrement(_p);
				
				return _p;	
			}
			MapIterator	operator--(int)
			{
				MapIterator tmp(this);
				operator--();
				return tmp;
			}

			// 	template <class T, typename key, typename T1, class Compare, class Alloc>


		
		private:
			m_pointer 						_p;
			ft::RBT< T1, Compare, Alloc>	helper;

	};
}

#endif