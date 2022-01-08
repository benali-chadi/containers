#ifndef RBT_TREE_SET_HPP
#define RBT_TREE_SET_HPP

# include "../utils/pair.hpp"
# include "SetIterator.hpp"
# include "../utils/reverse_iterator.hpp"

namespace ft
{
	template <class T>
		struct node {
			T				data;
			char			color;
			struct node 	*parent;
			struct node		*left;
			struct node 	*right;

			node() {
				parent = 0;
				left = 0;
				right = 0;
			}
			node(const T &p)
			{
				data = p;
				parent = 0;
				left = 0;
				right = 0;
			}
			node (struct node const &n)
			{
				data = n.data;
				color = n.color;
				parent = 0;
				left = 0;
				right = 0;
			}

			operator node<const T>() {
				return node<const T>(data);
			}
		};
	
	template <	
				class T,
				class Compare,
				class Alloc
			 >
		class RBT_Set {
			public:
				typedef				T															value_type;
				typedef struct		node<const value_type>										Node;
				typedef struct 		node<value_type>											node;
				typedef 			ft::SetIterator<T, Node, node, Compare, Alloc>			iterator;
				typedef 			ft::SetIterator<const T, Node, node, Compare, Alloc>		const_iterator;
				typedef				ft::reverse_iterator<iterator>								reverse_iterator;
				typedef				ft::reverse_iterator<const_iterator>						const_reverse_iterator;
				typedef	typename	Alloc::template rebind<node>::other							m_Alloc;

				RBT_Set(): root(0) {}
				RBT_Set(node *r): root(r) {}

				RBT_Set&	operator=(RBT_Set const &x)
				{
					root = x.root;
					_alloc = x._alloc;
					cmpr = x.cmpr;

					return *this;
				}

				void	deep_copy(RBT_Set const &x)
				{
					delete_tree();

					for(const_iterator it = x.begin(); it != x.end(); it++)
						insert(*it);
				}

				/*
					Iterators
				*/

				iterator					begin() {	return iterator(&in_order_succ(root)->data, (Node *)root);	}
				const_iterator				begin() const {	return iterator(&in_order_succ(root)->data, (Node *)root);	}

				iterator					end() {	return iterator(0, (Node *)root);	}
				const_iterator				end() const {	return iterator(0, (Node *)root);	}
				
				reverse_iterator			rbegin() {	return reverse_iterator(iterator(0, (Node *)root));	}
				const_reverse_iterator		rbegin() const {	return reverse_iterator(iterator(0, (Node *)root));	}

				reverse_iterator			rend() {	return reverse_iterator(iterator(&in_order_succ(root)->data, (Node *)root));	}
				const_reverse_iterator		rend() const {	return reverse_iterator(iterator(&in_order_succ(root)->data, (Node *)root));	}

				/*
					* Main functions
				*/

				ft::pair<iterator, bool>	insert (value_type p)
				{
					node		*newNode = _alloc.allocate(1);
					newNode->data = p;
					newNode->left = 0;
					newNode->right = 0;

					if (!root)
					{
						newNode->color = 'B';
						newNode->parent = root;
						root = newNode;
						return ft::make_pair(&newNode->data, true);
					}
					newNode->color = 'R';
					
					node *tmp = search_to_erase(newNode->data);
					if (tmp)
					{
						// _alloc.deallocate(newNode, 1);
						return ft::make_pair(&tmp->data, false);
					}
					
					tmp = search_to_insert(*newNode);
					newNode->parent = tmp;
					
					// Place the node
					if (!cmpr(tmp->data,newNode->data))
						tmp->left = newNode;
					else
						tmp->right = newNode;

					check(newNode);
					return ft::make_pair(&newNode->data, true);
				}
				
				bool						erase(value_type p)
				{
					node	*n = search_to_erase(p);

					if (n)
					{
						n = get_leaf_node(n);
						// if the leaf is red, delete it
						if (n->color == 'R' || n == root)
							remove(n);
						// the node is BLACK!!
						else
						{
							n = node_is_black(n);
							remove(n);
						}
						return true;
					}
					return false;
				}

				void	delete_tree()
				{
					while (root != 0)
						erase(in_order_pred(root)->data);
				}

				void						traverse()
				{
					node *tmp = root;
					print(tmp);
				}

				/*
					* Map operation methods helpers
				*/

				bool						contains(value_type k) const
				{
					node	*tmp = root;

					while (tmp)
					{
						if (tmp->data == k)
							return true;
						if (!cmpr(tmp->data, k))
							tmp = tmp->left;
						
						else if (cmpr(tmp->data, k))
							tmp = tmp->right;
					}
					return false;
				}

				node						*find(value_type p) const {	return search_to_erase(p);	}

				ft::pair<iterator, bool>	search(const value_type &k)
				{
					node	*tmp = root;

					while (tmp)
					{
						if (tmp->data > k && (!tmp->left || in_order_pred(tmp->left)->data < k))
							return ft::make_pair(&tmp->data, true);
						if (tmp->data == k)
							return ft::make_pair(&tmp->data, false);
						if (tmp->data > k)
							tmp = tmp->left;
						else
							tmp = tmp->right;
					}
					return ft::make_pair(end(), false);
				}

				ft::pair<const_iterator, bool>	search(const value_type &k) const
				{
					node	*tmp = root;

					while (tmp)
					{
						if (tmp->data == k)
							return ft::make_pair(&tmp->data, false);
						if (tmp->data > k && (!tmp->left || in_order_pred(tmp->left)->data < k))
							return ft::make_pair(&tmp->data, true);
						if (tmp->data > k)
							tmp = tmp->left;
						else
							tmp = tmp->right;
					}
					return ft::make_pair(end(), false);
				}

				ft::pair<iterator, bool>	search_for_upper_bound(const value_type &k)
				{
					node	*tmp = root;

					while (tmp)
					{
						if (tmp->data > k && (!tmp->left || in_order_pred(tmp->left)->data <= k))
							return ft::make_pair(&tmp->data, true);
						if (tmp->data > k)
							tmp = tmp->left;
						else
							tmp = tmp->right;
					}
					return ft::make_pair(end(), false);
				}

				ft::pair<const_iterator, bool>	search_for_upper_bound(const value_type &k) const
				{
					node	*tmp = root;

					while (tmp)
					{
						if (tmp->data > k && (!tmp->left || in_order_pred(tmp->left)->data <= k))
							return ft::make_pair(&tmp->data, true);
						if (tmp->data > k)
							tmp = tmp->left;
						else
							tmp = tmp->right;
					}
					return ft::make_pair(end(), false);
				}

				/*
					Iterator Helper functions
				*/

				node						*in_order_pred(node *n)
				{
					node	*tmp = n;

					while (tmp && tmp->right != 0)
						tmp = tmp->right;
					
					return tmp;
				}

				const node						*in_order_pred(node *n) const
				{
					node	*tmp = n;

					while (tmp && tmp->right != 0)
						tmp = tmp->right;
					
					return tmp;
				}

				node						*in_order_succ(node *n) const
				{
					node	*tmp = n;

					while (tmp && tmp->left != 0)
						tmp = tmp->left;
					return tmp;
				}

				// node						*in_order_succ(value_type *n) const
				// {
				// 	node	*tmp = find(n);

				// 	while (tmp && tmp->left != 0)
				// 		tmp = tmp->left;
				// 	return tmp;
				// }

				// node						*in_order_pred(value_type *n)
				// {
				// 	node	*tmp = find(n);

				// 	while (tmp && tmp->right != 0)
				// 		tmp = tmp->right;
					
				// 	return tmp;
				// }

				node						*find_bigger_parent(node *parent, value_type p)
				{
					while (parent != root)
					{
						if (!cmpr(parent->data, p))
							return parent;
						parent = parent->parent;
					}

					// if the parent's key is less than the key return the end() address
					if (cmpr(parent->data, p))
						return 0;

					return parent;
				}

				node						*find_smaller_parent(node *parent, value_type p)
				{
					while (parent != root)
					{
						if (cmpr(parent->data, p))
							return parent;
						parent = parent->parent;
					}

					// if the parent's key is bigger than the key return the end() address
					if (!cmpr(parent->data, p))
						return 0;
					
					return parent;
				}

				value_type*						increment(value_type *p)
				{
					if (!p)
						return &in_order_succ(root)->data;
					node	*tmp = in_order_succ(find(*p)->right);

					if (tmp)
						return &tmp->data;
	
					tmp = find(*p)->parent ? find_bigger_parent(find(*p)->parent, *p) : 0;
					if (tmp)
						return &tmp->data;
					return 0;
				}

				value_type*						decrement(value_type *p)
				{
					if (!p)
						return &in_order_pred(root)->data;
					node	*tmp = in_order_pred(find(*p)->left);

					if (tmp)
						return &tmp->data;

					tmp = find(*p)->parent ? find_smaller_parent(find(*p)->parent, *p) : 0;
					if (tmp)
						return &tmp->data;
					
					return 0;
				}

				node						*get_root(value_type *p)  // getting the root of the iterator
				{
					node *tmp = find(*p);

					while (tmp && tmp->parent)
						tmp = tmp->parent;
					return tmp;
				}

				node						*get_root2() const {	return root;	}

				void						set_root(Node *r) {	root = (node *)r;	}
				// void						set_root(Node *r) {	root = (node *)r;	}

				operator Node() {
				return Node();
				}

			private:

				node	*root;
				Compare	cmpr;
				m_Alloc	_alloc;

				void	print(node *n)
				{
					if (n == 0)
						return ;
					print(n->left);
					if (n == root)
						std::cout << "this is root\n";
					std::cout << n->data << " color = " << n->color << std::endl;
					print(n->right);
				}

				/*
					* Rotations
				*/

				void	rll(node *parent) // Left left rotation
				{
					node *grand_parent = parent->parent;
					node *tmp = parent->right;
					char c = parent->color;

					// change the colors and make the parent in the middle

					parent->right = grand_parent;
					parent->color = grand_parent->color;
					
					parent->parent = grand_parent->parent;
					
					// If the grand parent isn't root change its parent's right to the parent
					if (grand_parent != root)
					{
						if (get_direction(grand_parent) == 'L')
							grand_parent->parent->left = parent;
						else
							grand_parent->parent->right = parent;
					}
					
					grand_parent->parent = parent;
					grand_parent->color = c;
					
					// if there was any elements in the right of the parent
					grand_parent->left = tmp;
					if (tmp)
						tmp->parent = grand_parent;
					
					if (root == grand_parent)
						root = parent;
				}

				void	rrr(node *parent) // Right right rotation
				{
					node *grand_parent = parent->parent;
					node *tmp = parent->left;
					char c = parent->color;

					// change the colors and make the parent in the middle

					parent->left = grand_parent;
					parent->color = grand_parent->color;
					
					parent->parent = grand_parent->parent;

					// If the grand parent isn't root change its parent's right to the parent
					if (grand_parent != root)
					{
						if (get_direction(grand_parent) == 'L')
							grand_parent->parent->left = parent;
						else
							grand_parent->parent->right = parent;
					}

					grand_parent->parent = parent;
					grand_parent->color = c;
					
					// if there was any elements in the left of the parent
					grand_parent->right = tmp;
					if (tmp)
						tmp->parent = grand_parent;

					if (root == grand_parent)
						root = parent;
				}

				void	rotate(node *n)
				{
					node *parent = n->parent;
					node *grand_parent = parent->parent;

					/*
						* Single Rotation
					*/

					if (n == parent->left && parent == grand_parent->left) // Rotation left left
						rll(parent);
					else if (n == parent->right && parent == grand_parent->right) // Rotation right right
						rrr(parent);

					/*
						* Double Rotation 
					*/

					else if (n == parent->left && parent == grand_parent->right) // Rotation right left
					{
						node *tmp = n->right;
						n->right = parent;
						n->parent = grand_parent;
						parent->parent = n;
						parent->left = tmp;
						grand_parent->right = n;
						rrr(n);
					}
					else if (n == parent->right && parent == grand_parent->left) // Rotation left right
					{
						node *tmp = n->left;
						n->left = parent;
						n->parent = grand_parent;
						parent->parent = n;
						parent->right = tmp;
						grand_parent->left = n;
						rll(n);
					}
				}

				/*
					* Insert helpers
				*/

				node	*get_sibling(node *n)
				{
					if (n == n->parent->left)
						return n->parent->right;
					return n->parent->left;
				}

				node	*search_to_insert(node n)
				{
					node *tmp = root;

					if (tmp->data == n.data)
					{
						return 0;
					}

					while (tmp && (tmp->right != 0 || tmp->left != 0))
					{
						if (tmp->data == n.data)
							return 0;
						if (cmpr(n.data, tmp->data))
						{
							if (!tmp->left)
								return tmp;
							tmp  = tmp->left;
						}
						else
						{
							if (!tmp->right)
								return tmp;
							tmp = tmp->right;
						}
					}
					return tmp;
				}

				void	check(node *newNode)
				{
					node *parent = newNode->parent;
					if (parent == root || parent->color == 'B')
						return ;
					node *sibling = get_sibling(parent);

					if (!sibling || sibling->color == 'B')
						rotate(newNode); // Rotate and recolor
					else
					{
						// Recolor the parent and the sibling 
						parent->color = 'B';
						sibling->color = 'B';
						if (parent->parent != root)
						{
							// if the parent's parent is not the root then recolore it and recheck
							parent->parent->color = parent->parent->color == 'B' ? 'R' : 'B';
							check(parent->parent);
						}
					}
				}

				/*
					* Erase helpers
				*/

				node	*search_to_erase(value_type p) const
				{
					node	*tmp = root;

					while (tmp)
					{
						if (tmp->data == p)
							return tmp;
						else if (cmpr(p, tmp->data))
							tmp = tmp->left;
						else
							tmp = tmp->right;
					}
					return 0;
				}

				node	*get_leaf_node(node *n)
				{
					node	*tmp = n;
					while (tmp && (tmp->right != 0 || tmp->left != 0))
					{
						if (tmp->right == 0 || tmp->left == 0)
						{
							node	*toDelete = tmp->right ? in_order_succ(tmp->right) : in_order_pred(tmp->left);
							// swap its key with the IOP or IOS
							value_type	t = tmp->data;
							tmp->data = toDelete->data;
							toDelete->data = t;
							
							tmp = toDelete;
						}
						else
						{
							// search for the in-order predecessor (the largest element in the left side of the node)
							node	*toDelete = in_order_pred(n->left);
							// swap its key with the IOP
							value_type	t = tmp->data;
							tmp->data = toDelete->data;
							toDelete->data = t;

							tmp = toDelete;
						}
					}

					return tmp;
				}

				void	remove(node *n)
				{
					if (n == root)
						root = 0;
					else if (n == n->parent->left)
						n->parent->left = 0;
					else
						n->parent->right = 0;

					_alloc.deallocate(n, 1);
				}

				char	get_direction(node *n)
				{
					if (n == n->parent->left)
						return 'L';
					else
						return 'R';
				}

				node	*node_is_black(node *n)
				{
					if (n == root)
						return n;

					node	*parent = n->parent;
					
					char	n_direction = get_direction(n);
					node	*sibling = get_sibling(n);

					// the sibling's color is red
					if (sibling && sibling->color == 'R')
					{
						// parent->color = 'R';
						if (n_direction == 'L')
							rrr(sibling);
						else
							rll(sibling);
						node_is_black(n);
					}
					// the sibling is black (or null) and its children are both black (or null)
					else if (!sibling || (sibling->color == 'B' &&
									(!sibling->left || sibling->left->color == 'B') &&
									(!sibling->right || sibling->right->color == 'B') ))
					{
						if (sibling)
							sibling->color = 'R';
						if (parent->color == 'R')
							parent->color = 'B';
						else if (parent != root)
							node_is_black(parent);
					}
					// the sibling is black and one or both of the children are red
					else
					{
						// the case of the red child is far from the node, opposite directions
						if ((sibling->left && get_direction(sibling->left) != n_direction && sibling->left->color == 'R') || 
							(sibling->right && get_direction(sibling->right) != n_direction && sibling->right->color == 'R'))
						{
							if (sibling->left && get_direction(sibling->left) != n_direction && sibling->left->color == 'R')
								sibling->left->color = 'B';
							else
								sibling->right->color = 'B';
							
							// swap in the direction of the node, the colors will be swaped inside rll or rrr
							if (n_direction == 'L')
								rrr(sibling);
							else
								rll(sibling);
						}
						// the case of the red child is close to the node, same direction
						else
						{
							// Rotate in the opposite direction of the node, the colors will be swapped inside rrr or rll
							if (n_direction == 'L')
							{
								if (sibling->left && get_direction(sibling->left) == n_direction && sibling->left->color == 'R')
									rll(sibling->left);
								else
									rll(sibling->right);
							}
							else
							{
								if (sibling->left && get_direction(sibling->left) == n_direction && sibling->left->color == 'R')
									rrr(sibling->left);
								else
									rrr(sibling->right);
							}
							node_is_black(n);
						}
					}
					return n;
				}

				/*
					* Other Iterator helpers
				*/

				bool	check_end(node *n)
				{
					if (!n)
						return true;
					return false;
				}
		};
}

#endif