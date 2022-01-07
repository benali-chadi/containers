#include "set.hpp"
#include <set>

int main()
{
	// typedef ft::RBT_Set<int, std::less<int>, std::allocator<int> > RBT;

	// RBT tree;

	// for (int i = 0; i < 10; i++)
	// 	tree.insert(i + 1);

	// for (RBT::iterator it = tree.begin(); it != tree.end(); it++)
	// 	std::cout << *it << std::endl;
	
	// tree.delete_tree();

	std::set<int> my_s;
    std::set<int>::iterator my_it;

	for (int i = 0; i < 1e5; i++)
		my_s.insert(i);

	my_it = my_s.begin();
    // my_it1 = ++(my_s.begin());

	// for (; my_it != my_s.end(); my_it++)
	// 	std::cout << *my_it << std::endl;
	
	std::cout << std::endl;
	std::cout << *my_s.find(8050127) << std::endl;

	return 0;
}