#ifndef STACK_HPP
# define STACK_HPP

# include "../vector/Vector.hpp"

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
	const value_type&	value_type const {	return c.back();	}
	void 				push (const value_type& val) {	c.push_back(val);	}
	void				pop() {	c.pop_back();	}

	/*
		* Relational operators
	*/

	template <class T, class Container>
  		friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	template <class T, class Container>
		friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	template <class T, class Container>
		friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	template <class T, class Container>
		friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	template <class T, class Container>
		friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	template <class T, class Container>
		friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

	protected:
		container_type c;
};

/*
	* Non-member function overloads
*/

template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {	return lhs.c == rhs.c;	}
template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {	return lhs.c != rhs.c;	}
template <class T, class Container>
	bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {	return lhs.c < rhs.c;	}
template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {	return lhs.c <= rhs.c;	}
template <class T, class Container>
	bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {	return lhs.c > rhs.c;	}
template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {	return lhs.c >= rhs.c;	}

#endif