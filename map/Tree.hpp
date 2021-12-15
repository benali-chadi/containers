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
					node tmp = *root;

					while (tmp)
					{
						if (n.key > tmp.key)
							tmp = tmp->right;
						else if (n.key < tmp.key)
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
						// Place the node
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

			private:
				node	*root;
		};
}

#endif