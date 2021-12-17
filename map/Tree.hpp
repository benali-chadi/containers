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
					node *n = search_to_erase(key);

					if (n)
					{
						// if node key is a leaf node
						if (n->right == 0 && n->left == 0)
						{
							// if its red, delete it
							if (n->color == 'R')
								remove(n);
							// if its black
							else
							{
								// the checks

							}
						}
						// if node key has one child
						else if (n->right == 0 || n->left == 0)
						{
							node	*toDelete = n->right ? in_order_succ(n->right) : in_order_pred(n->left);
							// swap its key with its leaf node
							n->key = toDelete->key;
							toDelete->key = key;
							// the checks on leaf node
						}
						// if node key has two children
						else
						{
							// search for the in-order predecessor (the largest element in the left side of the node)
							node	*toDelete = in_order_pred(n->left);
							// swap its key with the IOP
							n->key = toDelete->key;
							toDelete->key = key;
							// the checks the leaf node

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
					std::cout << n->key << " color = " << n->color << std::endl;
					print(n->right);
				}

				/*
					* Rotations
				*/

				void	rll(node *n) // Left left rotation
				{
					node *parent = n->parent;
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
					
					if (root == grand_parent)
						root = parent;
				}

				void	rrr(node *n) // Right right rotation
				{
					node *parent = n->parent;
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
						rll(n);
					else if (n == parent->right && parent == grand_parent->right) // Rotation right right
						rrr(n);

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
						rrr(parent);
					}
					else if (n == parent->right && parent == grand_parent->left) // Rotation left right
					{
						node *tmp = n->left;
						n->left = parent;
						n->parent = grand_parent;
						parent->parent = n;
						parent->right = tmp;
						grand_parent->left = n;
						rll(parent);
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
						
						else (tmp->key == key)
							return tmp;
					}
					return 0;
				}

				void	remove(node *n)
				{
					if (n == n->parent->left)
						n->parent->left = 0;
					else
						n->parent->right = 0;
				}

				node	*in_order_pred(node *n)
				{
					node	*tmp = root;

					while (tmp->right != 0)
						tmp = tmp->right;
					
					return tmp;
				}

				node	*in_order_succ(node *n)
				{
					node	*tmp = root;

					while (tmp ->left != 0)
						tmp = tmp->left;
					
					return tmp;
				}

		};
}

#endif