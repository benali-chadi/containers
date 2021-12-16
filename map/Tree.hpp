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

				node	*search(node n)
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
						node *tmp = search(newNode);
						if (tmp)
						{
							node *n = new node(newNode);
							n->parent = tmp;
						// Place the node
							if (tmp->key > newNode.key)
								tmp->left = n;
							else
								tmp->right = n;
							
							if (tmp != root)
								check(n);
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

					parent->right = grand_parent;
					parent->color = grand_parent->color;
					parent->parent = grand_parent->parent;
					grand_parent->parent = parent;
					grand_parent->color = c;
					grand_parent->right = tmp;
					
					if (root == grand_parent)
						root = parent;
				}

				void	rrr(node *n) // Right right rotation
				{
					node *parent = n->parent;
					node *grand_parent = parent->parent;
					node *tmp = parent->left;
					char c = parent->color;

					
					parent->left = grand_parent;
					parent->color = grand_parent->color;
					parent->parent = grand_parent->parent;
					grand_parent->parent = parent;
					grand_parent->color = c;
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
						n->parent = parent->parent;
						parent->parent = n;
						parent->left = tmp;
						rrr(n);
					}
					else if (n == parent->right && parent == grand_parent->left) // Rotation left right
					{
						node *tmp = n->left;
						n->left = parent;
						n->parent = parent->parent;
						parent->parent = n;
						parent->right = tmp;
						rll(n);
					}
				}

				node	*get_sibling(node *n)
				{
					if (n == n->parent->left)
						return n->parent->right;
					return n->parent->left;
				}

				void	check(node *newNode)
				{
					node *parent = newNode->parent;
					node *sibling = get_sibling(parent);
					
					if (parent->color == 'B')
						return ;
					else // There is a red red conflict
					{
						if (!sibling || sibling->color == 'B')
						{
							// Rotate and recolor
							rotate(newNode);
						}
						else
						{
							// Recolor the parent and the sibling 
							parent->color = parent->color == 'B' ? 'R' : 'B';
							sibling->color = sibling->color == 'B' ? 'R' : 'B';
							if (parent->parent != root)
							{
								// if the parent's parent is not the root then recolre it and recheck
								parent->parent->color = parent->parent->color == 'B' ? 'R' : 'B';
								check(parent);
							}
						}
					}
				}
		};
}

#endif