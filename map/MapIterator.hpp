#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

# include "../utils/utils.hpp"

namespace ft
{
	template <class T1, class T2, class Compare, class Alloc>
		class RBT;
	template <class T, typename key, typename T1, class Compare, class Alloc>
	class MapIterator: public ft::iterator<std::bidirectional_iterator_tag, T>
	{
		public:
			typedef typename iterator<std::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef typename iterator<std::bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename iterator<std::bidirectional_iterator_tag, T>::pointer				pointer;
			typedef typename iterator<std::bidirectional_iterator_tag, T>::reference			reference;
			typedef typename iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;


			// typedef	ft::RBT<key, T1, Compare> RBT;
			/*
				* Constructors
			*/

			MapIterator		() {}
			MapIterator		(const MapIterator &x): _p(x._p)
			{
				pointer r = helper.get_root(_p);
				helper.set_root(r);
			}
			MapIterator		(pointer x): _p(x) {

				// pointer r = helper.get_root(_p);
				// if (x == r && (helper.in_order_pred(r) != r && helper.in_order_succ(r) != r))
				// 	_p = 0;
				helper.set_root(helper.get_root(x));
				// helper.set_root(r);
			}
			MapIterator		(pointer x, pointer root)
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
			reference		&operator*() {	return *_p;	}
			pointer			operator->() {	return &operator*();	}
			
			MapIterator&	operator++()
			{
				_p = helper.increment(_p);
				
				return *this;
			}
			MapIterator	operator++(int)
			{
				MapIterator tmp(*this);
				++(*this);
				return tmp;
			}
			MapIterator&	operator--()
			{
				_p = helper.decrement(_p);
				
				return *this;	
			}
			MapIterator	operator--(int)
			{
				MapIterator tmp(*this);
				--(*this);
				return tmp;
			}
		
		private:
			pointer _p;
			ft::RBT<key, T1, Compare, Alloc> helper;

	};
}

#endif