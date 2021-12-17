#ifndef TREE_HPP
#define TREE_HPP

namespace ft {
	template <class T1, class T2>
		struct node {
			T1			key;
			T2			value;
			char		color;
			struct node *parent;
			struct node	*left;
			struct node *right;

			node(T1 key, T2 value): key(key), value(value) {}
			node (struct node const &n) {
				key = n.key;
				value = n.value;
				color = n.color;
				parent = 0;
				left = 0;
				right = 0;
			}
		};
	
	template <class T1, class T2>
		class Tree{
			public:
				typedef struct node<T1, T2>	node;

				Tree(): root(0) {}
				void	traverse()
				{
					node *tmp = root;
					print(tmp);
				}

				void	insert (node newNode)
				{
					if (!root)
					{
						newNode.color = 'B';
						newNode.left = 0;
						newNode.right = 0;
						newNode.parent = root;
						root = &newNode;	
					}
					else
					{
						newNode.color = 'R';
						node *tmp = search_to_insert(newNode);
						if (tmp)
						{
							newNode.parent = tmp;
							
							// Place the node
							if (tmp->key > newNode.key)
								tmp->left = &newNode;
							else
								tmp->right = &newNode;

							check(&newNode);
						}
					}
				}
				
				void	erase(T1 key)
				{
					// search the position of key
					node	*n = search_to_erase(key);
					// node	*right = n->right;
					// node	*left = n->left;

					if (n)
					{
						n = get_leaf_node(n);
						std::cout << "n parent key = " << n->parent->key << std::endl;
						// if the leaf is red, delete it
						if (n->color == 'R')
							remove(n);
						else
						{
							node_is_black(n);
							remove(n);
						}
					}
				}
			private:
				node	*root;
				

				void	print(node *n)
				{
					if (n == 0)
						return ;
					print(n->left);
					if (n == root)
						std::cout << "this is root\n";
					// if (n->key == 4)
					// 	std::cout << "4's parent key = " << n->parent->key << std::endl;
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

				node	*get_sibling(node *n)
				{
					if (n == n->parent->left)
						return n->parent->right;
					return n->parent->left;
				}

				/*
					* Insert helpers
				*/

				node	*search_to_insert(node n)
				{
					node *tmp = root;

					while (tmp && (tmp->right != 0 || tmp->left != 0))
					{
						if (n.key > tmp->key)
						{
							if (!tmp->right)
								return tmp;
							tmp = tmp->right;
						}
						else if (n.key < tmp->key)
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
						if (tmp->key > key)
							tmp = tmp->left;
						
						else if (tmp->key < key)
							tmp = tmp->right;
						
						else
							return tmp;
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
							// swap its key with its leaf node
							T1	key = tmp->key;
							tmp->key = toDelete->key;
							toDelete->key = key;
							
							tmp = toDelete;
						}
						else
						{
							// search for the in-order predecessor (the largest element in the left side of the node)
							node	*toDelete = in_order_pred(n->left);
							std::cout << "toDelete key = " << toDelete->key << " parent key = " << toDelete->parent->key << std::endl;
							// swap its key with the IOP
							T1	key = n->key;
							n->key = toDelete->key;
							toDelete->key = key;

							tmp = toDelete;
						}
					}

					return tmp;
				}

				void	remove(node *n)
				{
					if (n == n->parent->left)
					{
						n->parent->left = 0;
						// if (left)
						// 	left->parent = n->parent;
					}
					else
					{
						n->parent->right = 0;
						// if (right)
						// 	right->parent = parent;
					}
				}

				node	*in_order_pred(node *n)
				{
					node	*tmp = n;

					while (tmp->right != 0)
						tmp = tmp->right;
					
					return tmp;
				}

				node	*in_order_succ(node *n)
				{
					node	*tmp = n;

					while (tmp ->left != 0)
						tmp = tmp->left;
					
					return tmp;
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
					std::cout << "node is black\n";
					node	*parent = n->parent;
					char	n_direction = get_direction(n);

					if (parent == root)
					{
						std::cout << "parent = " << parent << " parent key = " << n->key << " root = " << root << std::endl;
						return ;
					}
					
					node	*sibling = get_sibling(n);

					// the sibling's color is red
					if (sibling && sibling->color == 'R')
					{
						std::cout << "sibling red\n";
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
						std::cout << "sibling black, both children black\n";
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
						std::cout << "sibling black, one or both children red\n";
						// the case of the red child is far from the node, opposite directions
						if ((sibling->left && get_direction(sibling->left) != n_direction && sibling->left->color == 'R') || 
							(sibling->right && get_direction(sibling->right) != n_direction && sibling->right->color == 'R'))
						{
							std::cout << "sibling black, red child far\n";
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
							std::cout << "sibling black, red child close\n";
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