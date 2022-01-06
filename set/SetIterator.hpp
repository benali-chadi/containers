#ifndef SETITERATOR_HPP
# define SETITERATOR_HPP

# include "../utils/utils.hpp"

namespace ft
{
	template <class T, class Compare, class Alloc>
		class RBT_Set;
	template <class T, class key, class Compare, class Alloc>
	class SetIterator: public ft::iterator<std::bidirectional_iterator_tag, T>
	{
		public:
			typedef typename	iterator<std::bidirectional_iterator_tag, key >::difference_type		difference_type;
			// typedef typename	iterator<std::bidirectional_iterator_tag, key >::key			key;
			typedef typename	iterator<std::bidirectional_iterator_tag, key >::pointer				pointer;
			typedef typename	iterator<std::bidirectional_iterator_tag, key >::reference			reference;
			typedef typename	iterator<std::bidirectional_iterator_tag, key >::iterator_category	iterator_category;

			typedef 			T*																	m_pointer;


			// typedef	ft::RBT<key, key, Compare> RBT;
			/*
				* Constructors
			*/

			SetIterator		() {}
			operator SetIterator<T, const key, Compare, Alloc>() {
				return SetIterator<T, const key, Compare, Alloc>(_p, helper.get_root2());
			}
			SetIterator		(const SetIterator &x)
			{
				// helper = x.helper;
				*this = x;
				// m_pointer r = helper.get_root(_p);
				// helper.set_root(r);
			}

			SetIterator		(m_pointer x): _p(x) {

				// pointer r = helper.get_root(_p);
				// if (x == r && (helper.in_order_pred(r) != r && helper.in_order_succ(r) != r))
				// 	_p = 0;
				helper.set_root(helper.get_root(x));
				// helper.set_root(r);
			}
			SetIterator		(m_pointer x, m_pointer root)
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
				// reference ret(static_cast<ft::pair<const key, T2> >(_p->data));

				return _p->data;
			}
			pointer			operator->() const {	return &operator*();	}
			
			SetIterator&	operator++()
			{
				_p = helper.increment(_p);
				
				return *this;
			}
			SetIterator	operator++(int)
			{
				update_root();
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
				helper.set_root(helper.get_root(helper.get_root2()));
			}
			// 	template <class T, typename key, typename key, class Compare, class Alloc>


		
		private:
			m_pointer 						_p;
			ft::RBT_Set< key, Compare, Alloc>	helper;

	};
}

#endif