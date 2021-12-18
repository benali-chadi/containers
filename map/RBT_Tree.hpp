#ifndef RBT_TREE_HPP
#define RBT_TREE_HPP

# include "../utils/pair.hpp"
# include "MapIterator.hpp"
# include "../reverse_iterator.hpp"

namespace ft
{
	template <class T1, class T2>
		struct node {
			T1			key;
			T2			value;
			char			color;
			struct node 	*parent;
			struct node		*left;
			struct node 	*right;

			node(ft::pair<T1, T2> p) {
				key = p.first;
				value = p.second;
				parent = 0;
				left = 0;
				right = 0;
			}
			node (struct node const &n) {
				key = n.key;
				value = n.value;
				color = n.color;
				parent = 0;
				left = 0;
				right = 0;
			}
		};
	
	template <class T1, class T2, class Compare>
		class RBT {
			public:
				typedef struct node<T1, T2>								node;
				typedef ft::MapIterator<node, T1, T2, Compare>			iterator;
				typedef ft::MapIterator<const node, T1, T2, Compare>	const_iterator;

				RBT(): root(0) {}
				RBT(node *r): root(r) {}

				/*
					Iterators
				*/

				iterator	begin()
				{
					return in_order_succ(root);
				}

				iterator	end()
				{
					std::cout << "end = " << in_order_pred(root) + 1 << std::endl;
					return (in_order_pred(root) + 1);
				}

				/*
					* Member functions
				*/

				void	traverse()
				{
					node *tmp = root;
					print(tmp);
				}

				bool	insert (node newNode)
				{
					if (!root)
					{
						newNode.color = 'B';
						newNode.left = 0;
						newNode.right = 0;
						newNode.parent = root;
						root = &newNode;
						return true;	
					}
					newNode.color = 'R';
					node *tmp = search_to_insert(newNode);
					if (tmp)
					{
						newNode.parent = tmp;
						
						// Place the node
						if (!cmpr(tmp->key,newNode.key))
							tmp->left = &newNode;
						else
							tmp->right = &newNode;

						check(&newNode);
						return true;
					}
					return false;
				}
				
				void	erase(T1 key)
				{
					// search the position of key
					node	*n = search_to_erase(key);

					if (n)
					{
						n = get_leaf_node(n);
						// if the leaf is red, delete it
						if (n->color == 'R' || n == root)
							remove(n);
						// the node is BLACK!!
						else
						{
							node_is_black(n);
							remove(n);
						}
					}
				}

				node	*find(T1 key) {	return search_to_erase(key);	}
				
				/*
					Iterator Helper functions
				*/

				node	*in_order_pred(node *n)
				{
					node	*tmp = n;

					while (tmp && tmp->right != 0)
						tmp = tmp->right;
					
					return tmp;
				}

				node	*in_order_succ(node *n)
				{
					node	*tmp = n;

					while (tmp && tmp->left != 0)
						tmp = tmp->left;
					return tmp;
				}

				node	*find_bigger_parent(node *parent, T1 key)
				{
					while (parent != root)
					{
						if (!cmpr(parent->key, key))
							return parent;
						parent = parent->parent;
					}

					// if the parent's key is less than the key return the end() address
					if (cmpr(parent->key, key))
						return 0;

					return parent;
				}

				node	*find_smaller_parent(node *parent, T1 key)
				{
					while (parent != root)
					{
						if (cmpr(parent->key, key))
							return parent;
						parent = parent->parent;
					}

					// if the parent's key is bigger than the key return the end() address
					if (!cmpr(parent->key, key))
						return 0;
					
					return parent;	
				}

				node	*increment(node *p)
				{
					node	*tmp = in_order_succ(p->right);

					if (tmp)
						return tmp;
	
					tmp = find_bigger_parent(p->parent, p->key);
					if (tmp)
						return tmp;
					return p + 1;
				}

				node	*decrement(node *p)
				{
					std::cout << "HEEERE\n";
					if (!p->key)
						std::cout << "okokok\n";
					node	*tmp = in_order_pred(p->left);

					if (tmp)
						return tmp;

					tmp = find_smaller_parent(p->parent, p->key);
					if (tmp)
						return tmp;
					return p - 1;
				}

				node	*get_root(node *p)  // getting the root of the iterator
				{
					node *tmp = p;

					if (tmp->color != 'R' && tmp->color != 'B')
						return tmp;
					while (tmp && tmp->parent != 0)
						tmp = tmp->parent;
					return tmp;
				}

				void	set_root(node *r)
				{
					root = r;
				}

			private:

				node	*root;
				Compare	cmpr;

				void	print(node *n)
				{
					if (n == 0)
						return ;
					print(n->left);
					if (n == root)
						std::cout << "this is root\n";
					std::cout << n->key << " color = " << n->color << std::endl;
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
						grand_parent->parent->left = parent;
					
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
						grand_parent->parent->right = parent;

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

					if (tmp->key == n.key)
						return 0;

					while (tmp && (tmp->right != 0 || tmp->left != 0))
					{
						if (!cmpr(n.key, tmp->key))
						{
							if (!tmp->right)
								return tmp;
							tmp = tmp->right;
						}
						else if (cmpr(n.key, tmp->key))
						{
							if (!tmp->left)
								return tmp;
							tmp  = tmp->left;
						}
						else
							return 0;
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

				node	*search_to_erase(T1 key)
				{
					node	*tmp = root;

					while (tmp)
					{
						if (tmp->key == key)
							return tmp;
						if (!cmpr(tmp->key, key))
							tmp = tmp->left;
						
						else if (cmpr(tmp->key, key))
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
							T1	key = tmp->key;
							tmp->key = toDelete->key;
							toDelete->key = key;
							
							tmp = toDelete;
						}
						else
						{
							// search for the in-order predecessor (the largest element in the left side of the node)
							node	*toDelete = in_order_pred(n->left);
							// swap its key with the IOP
							T1	key = tmp->key;
							tmp->key = toDelete->key;
							toDelete->key = key;

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
				}

				

				char	get_direction(node *n)
				{
					if (n == n->parent->left)
						return 'L';
					else
						return 'R';
				}

				void	node_is_black(node *n)
				{
					node	*parent = n->parent;

					if (parent == root)
						return ;
					
					char	n_direction = get_direction(n);
					node	*sibling = get_sibling(n);

					// the sibling's color is red
					if (sibling && sibling->color == 'R')
					{
						if (n_direction == 'L')
							rll(parent);
						else
							rrr(parent);

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
						else
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
								rll(sibling);
							else
								rrr(sibling);
							node_is_black(n);
						}
							
					}
				}
		};
}

#endif