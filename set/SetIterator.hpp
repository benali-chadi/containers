#ifndef SETITERATOR_HPP
# define SETITERATOR_HPP

# include "../utils/utils.hpp"

namespace ft
{
	template <class T, class Compare, class Alloc>
		class RBT_Set;
	template <class T, class node, class n, class Compare, class Alloc>
	class SetIterator: public ft::iterator<std::bidirectional_iterator_tag, T>
	{
		public:
			typedef typename	iterator<std::bidirectional_iterator_tag, T >::difference_type		difference_type;
			// typedef typename	iterator<std::bidirectional_iterator_tag, T >::T			T;
			typedef typename	iterator<std::bidirectional_iterator_tag, T >::pointer				pointer;
			typedef typename	iterator<std::bidirectional_iterator_tag, T >::reference			reference;
			typedef typename	iterator<std::bidirectional_iterator_tag, T >::iterator_category	iterator_category;

			typedef 			node*																m_pointer;


			// typedef	ft::RBT<key, key, Compare> RBT;
			/*
				* Constructors
			*/

			SetIterator		() {}
			operator SetIterator<const T, node, n, Compare, Alloc>() {
				return SetIterator<const T, node, n, Compare, Alloc>(_p, (m_pointer)helper.get_root2());
			}

			SetIterator		(const SetIterator &x)
			{
				// helper = x.helper;
				*this = x;
				// pointer r = helper.get_root(_p);
				// helper.set_root(r);
			}

			SetIterator		(pointer x): _p(x) {

				// pointer r = helper.get_root(_p);
				// if (x == r && (helper.in_order_pred(r) != r && helper.in_order_succ(r) != r))
				// 	_p = 0;
				helper.set_root((m_pointer)helper.get_root(x));
				// helper.set_root(r);
			}
			SetIterator		(pointer x, m_pointer root)
			{
				_p = x;
				helper.set_root(root);
			}

			SetIterator&	operator=(const SetIterator &x){
				_p = x._p;
				helper = x.helper;
				return *this;
			}

			/*
				* Destructors
			*/

			~SetIterator		() {}

			/*
				* Operators
			*/

			bool			operator==(const SetIterator& x) {	return _p == x._p;	}
			bool			operator!=(const SetIterator& x) {	return _p != x._p;	}
			reference		&operator*() const {
				return *_p;
			}
			pointer			operator->() const {	return &operator*();	}
			
			SetIterator&	operator++()
			{
				update_root();
				_p = helper.increment(_p);
				
				return *this;
			}
			SetIterator	operator++(int)
			{
				SetIterator tmp(*this);
				operator++();
				return tmp;
			}
			SetIterator&	operator--()
			{
				update_root();
				_p = helper.decrement(_p);
				
				return *this;
			}
			SetIterator	operator--(int)
			{
				SetIterator tmp(*this);
				operator--();
				return tmp;
			}

			void	print_addr()
			{
				std::cout << "_p = " << _p << std::endl;
			}

			void	update_root()
			{
				helper.set_root((m_pointer)helper.get_root(&helper.get_root2()->data));
			}
		
		private:
			pointer								_p;
			ft::RBT_Set<T, Compare, Alloc>	helper;

	};
}

#endif