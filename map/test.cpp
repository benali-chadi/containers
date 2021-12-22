#include <iostream>
// #include "RBT_Tree.hpp"
# include "../vector/Vector.hpp"
#include "../utils/pair.hpp"
// #include "MapIterator.hpp"
#include "map.hpp"
#include <cstdio>
#include <map>


int main()
{
	// ft::Map<int, char> My_map;
	// for (size_t i = 0; i < 10; i++)
	// 	My_map.insert(ft::make_pair(i, '1'));
	
	// ft::Map<int, char>::iterator my_it = My_map.begin();
	// std::cout << my_it->first << " " << my_it->second << std::endl;
	// ft::Map<int, char>::const_iterator c_it, c_ob(my_it);
    // c_it = my_it;
	// typedef ft::node<int, int> node;
	typedef ft::Map<int, int> RBT;
	
	
	// typedef ft::RBT<int, int, ft::less<int> > RBT;
	RBT rbt;

	// ft::Map<int, int> const m;

	// m.insert(ft::make_pair(2,3));
	// ft::Map<int,int>::iterator it = m.begin();
	// std::cout << it->first << std::endl;
	// ft::Vector<int> const v;

	// ft::Vector<const int>::iterator it = v.begin();

	// rbt.insert(2, 3);
	// rbt.insert(3, 4);
	// rbt.insert(5, 4);
	// rbt.insert(1, 4);
	// rbt.insert(6, 4);
	// rbt.insert(4, 4);
	// rbt.insert(7, 4);
	// rbt.insert(8, 3);
	// rbt.insert(10, 3);
	rbt.insert(ft::make_pair(2, 2));
	rbt.insert(ft::make_pair(3, 3));
	rbt.insert(ft::make_pair(5, 5));
	rbt.insert(ft::make_pair(1, 1));
	rbt.insert(ft::make_pair(6, 6));
	rbt.insert(ft::make_pair(4, 4));
	rbt.insert(ft::make_pair(7, 7));
	rbt.insert(ft::make_pair(8, 8));
	rbt.insert(ft::make_pair(10, 10));

	// std::cout << "size = " << rbt.size() << std::endl;
	// ft::pair<RBT::iterator, RBT::iterator> p = rbt.equal_range(10);

	// 	std::cout << p.first->first << " " << p.second->first << std::endl;
	// std::cout << rbt.here(rbt.giveIt(), 10) << std::endl;	
	rbt.erase(5);
	rbt.erase(7);
	rbt.erase(8);
	rbt.erase(2);
	rbt.erase(4);

	// rbt.traverse();
	// rbt.traverse();
	// std::cout << rbt[5] << std::endl;
	RBT::iterator it = rbt.begin();
	RBT::iterator itr = rbt.end();
	// // it++;
	// // std::cout << "begin = " << it->first << std::endl; 
	// // --itr;
	// 	// std::cout << "end = " << *itr << std::endl;
	// // std::cout << it->value << std::endl;
	// // std::cout << *itr << std::endl;
	for (; it != itr; it++)
	{
		// std::cout << it->first << std::endl;
	}

	// rbt.clear();
	// std::cout << "size = " << rbt.size() << std::endl;
	
	// it = rbt.begin();
	// itr = rbt.end();
	// for (; it != itr; it++)
	// {
	// 	std::cout << it->second << std::endl;
	// }
	// --itr;
	// for (; itr != it; itr--)
	// {
	// 	std::cout << *itr << std::endl;
	// }
	// // for (; it != rbt.end(); it++)
	// itr--;
	// 	std::cout << *itr << std::endl;

	// std::map<int, int> m;

	// m.insert(std::pair<int, int>(2, 3));
	// m.insert(std::pair<int, int>(1, 4));
	// m.insert(std::pair<int, int>(5, 6));

	// // std::map<int,int>::iterator it = m.begin();
	// std::map<int,int>::iterator itr = m.end();
	// std::map<int,int>::iterator test(itr);

	// --test;

	// std::cout << test->first << std::endl;
	// --itr;
	// for (; itr != it; itr--)
	// 	std::cout << itr->first << std::endl;
	
	// std::pair<int, int> pr = *it;
	// std::cout << pr.first << std::endl;
	// printf("%d\n", pr.second);


	// std::cout << "\n" << rbt.find(5)->left->key << std::endl;
	return 0;
}