#include "RBT_Tree_set.hpp"

int main()
{
	typedef ft::RBT_Set<int, std::less<int>, std::allocator<int> > RBT;

	RBT tree;

	for (int i = 0; i < 10; i++)
		tree.insert(i + 1);

	for (RBT::iterator it = tree.begin(); it != tree.end(); it++)
		std::cout << *it << std::endl;
	
	tree.delete_tree();

	return 0;
}