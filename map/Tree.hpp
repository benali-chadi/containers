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
		};
	
	template <class T1, class T2>
		class Tree{
			public:
				typedef struct node<T1, T2>	node;

				Tree(): root(0) {}

				node	*search(node n)
				{
					node *tmp = root;

					while (tmp)
					{
						if (n.key > tmp->key)
							tmp = tmp->right;
						else if (n.key < tmp->key)
							tmp  = tmp->left;
						else
							return 0;
					}
					return tmp->parent;
				}

				void	insert (node newNode)
				{
					if (!root)
					{
						newNode.color = 'B';
						newNode.left = 0;
						newNode.right = 0;
						newNode.parent = root;
						root = newNode;	
					}
					else
					{
						newNode.color = 'R';
						newNode.left = 0;
						newNode.right = 0;
						node *tmp = search(newNode);
						if (tmp)
						{
						// Place the node
							if (tmp.key > newNode.key)
								tmp.left = &newNode;
							else
								tmp.right = &newNode;
						// Check:
							// - if the parent is black then exit
							// - if the parent is red, check the parent's sibling:
								// - if the color is BLACK or NULL then rotate and recolor
								// - if the color is RED
									// - Recolor the parent and its sibling
									// - check if the parent's parent is not the root
										// - if true: recolor and recheck (the same above conditions)

						}
					}
				}

			private:
				node	*root;
				
				/*
					* Rotations
				*/

				void	rll(node *n) // Left left rotation
				{
					node *parent = n->parent;
					node *grand_parent = parent->parent;
					node *tmp = parent->right;

					parent->right = grand_parent;
					grand_parent->right = tmp;
					if (*root == grand_parent)
						root = parent;
				}

				void	rrr(node *n) // Right right rotation
				{
					node *tmp = parent->left;
					parent->left = grand_parent;
					grand_parent->right = tmp;
					if (*root == grand_parent)
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
						parent->left = tmp;
						rrr(n);
					}
					else if (n == parent->right && parent == grand_parent->left) // Rotation left right
					{
						node *tmp = n->left;
						n->left = parent;
						parent->right = tmp;
						lll(n);
					}
				}

				node	*sibling(node *n)
				{
					if (n == n.parent.left)
						return n.parent.left;
					return n.parent.right;
				}

				void	check(node *newNode)
				{
					node *parent = newNode.parent;
					node *sibling = sibling(parent);
					if (parent == 'B')
						return ;
					else // There is a red red conflict
					{
						if (sibling.color == 'B')
							// Rotate and recolor
						else
						{
							// Recolor the parent and the sibling 
							parent.color = parent.color == 'B' ? 'R' : 'B';
							sibling.color = sibling.color == 'B' ? 'R' : 'B';
							if (parent.parent != *root)
							{
								// if the parent's parent is not the root then recolre it and recheck
								parent.parent.color = parent.parent.color == 'B' ? 'R' : 'B';
								check(parent);
							}
						}
					}
				}
		};
}

#endif