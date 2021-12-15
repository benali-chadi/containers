#ifndef STACK_HPP
# define STACK_HPP

# include "../vector/Vector.hpp"

namespace ft {

	template <class T, class Container = Vector<T> >
	class Stack {
		public:
			typedef				Container					container_type;
			typedef typename	Container::value_type		value_type;
			typedef typename	Container::size_type		size_type;

		/*
			* Constructor
		*/
		explicit Stack (const container_type& ctnr = container_type()): c(ctnr) {}

		/*
			* Member functions
		*/

		bool				empty() const {	return c.empty();	}
		size_type			size() const {	return c.size();	}
		value_type&			top() {	return c.back();	}
		const value_type&	top() const {	return c.back();	}
		void 				push (const value_type& val) {	c.push_back(val);	}
		void				pop() {	c.pop_back();	}

		/*
			* Relational operators
		*/

		template <class Type, class C>
			friend bool operator== (const Stack<Type,C>& lhs, const Stack<Type,C>& rhs);
		template <class Type, class C>
			friend bool operator!= (const Stack<Type,C>& lhs, const Stack<Type,C>& rhs);
		template <class Type, class C>
			friend bool operator<  (const Stack<Type,C>& lhs, const Stack<Type,C>& rhs);
		template <class Type, class C>
			friend bool operator<= (const Stack<Type,C>& lhs, const Stack<Type,C>& rhs);
		template <class Type, class C>
			friend bool operator>  (const Stack<Type,C>& lhs, const Stack<Type,C>& rhs);
		template <class Type, class C>
			friend bool operator>= (const Stack<Type,C>& lhs, const Stack<Type,C>& rhs);

		protected:
			container_type c;
	};

	/*
		* Non-member function overloads
	*/

	template <class Type, class C>
		bool operator== (const Stack<Type,C>& lhs, const Stack<Type,C>& rhs) {	return lhs.c == rhs.c;	}
	template <class Type, class C>
		bool operator!= (const Stack<Type,C>& lhs, const Stack<Type,C>& rhs) {	return lhs.c != rhs.c;	}
	template <class Type, class C>
		bool operator< (const Stack<Type,C>& lhs, const Stack<Type,C>& rhs) {	return lhs.c < rhs.c;	}
	template <class Type, class C>
		bool operator<= (const Stack<Type,C>& lhs, const Stack<Type,C>& rhs) {	return lhs.c <= rhs.c;	}
	template <class Type, class C>
		bool operator> (const Stack<Type,C>& lhs, const Stack<Type,C>& rhs) {	return lhs.c > rhs.c;	}
	template <class Type, class C>
		bool operator>= (const Stack<Type,C>& lhs, const Stack<Type,C>& rhs) {	return lhs.c >= rhs.c;	}
}

#endif