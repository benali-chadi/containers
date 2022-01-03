#include <iostream>
// #include "RBT_Tree.hpp"
# include "../vector/vector.hpp"
#include "../utils/pair.hpp"
// #include "MapIterator.hpp"
#include "map.hpp"
#include <cstdio>
#include <map>

int main()
{
	ft::Map<int, std::string> ft_m;
	for (size_t i = 0; i < 5; ++i)
	{
		ft_m.insert(ft::make_pair(i, "value"));
	}
	// ft::Map<int, std::string>::iterator it = --ft_m.end();
	// for (; it != ft_m.begin(); --it)
	// 	std::cout << it->first << std::endl;
	ft::Map<int, std::string>::const_reverse_iterator rit(ft_m.end());
	std::cout << rit->first << std::endl;

	// typedef ft::node<int, int> node;
	// typedef ft::Map<int, int> RBT;
	// RBT My_map;
	// for (size_t i = 0; i < 10; i++)
	// 	My_map.insert(ft::make_pair(i, i + 1));
	
	// RBT::iterator my_it = My_map.begin();
	// std::cout << my_it->first << " " << my_it->second << std::endl;
	// const RBT::iterator c_ob(my_it);
	// my_it->second++;

	// std::cout << My_map[0] << std::endl;
	// std::cout << c_ob->first << std::endl;

	// for (RBT::const_iterator cit = My_map.begin(); cit != My_map.end(); cit++)
	// 	std::cout << cit->first << std::endl;
	// typedef ft::RBT<int, int, ft::less<int> > RBT;
	// RBT rbt;

	// rbt.insert(ft::make_pair(2, 2));
	// rbt.insert(ft::make_pair(3, 3));
	// rbt.insert(ft::make_pair(5, 5));
	// rbt.insert(ft::make_pair(1, 1));
	// rbt.insert(ft::make_pair(6, 6));
	// rbt.insert(ft::make_pair(4, 4));
	// rbt.insert(ft::make_pair(7, 7));
	// rbt.insert(ft::make_pair(8, 8));
	// rbt.insert(ft::make_pair(10, 10));

	// std::cout << "size = " << rbt.size() << std::endl;
	// ft::pair<RBT::iterator, RBT::iterator> p = rbt.equal_range(10);

	// 	std::cout << p.first->first << " " << p.second->first << std::endl;
	// std::cout << rbt.here(rbt.giveIt(), 10) << std::endl;	
	// rbt.erase(5);
	// rbt.erase(7);
	// rbt.erase(8);
	// rbt.erase(2);
	// rbt.erase(4);

	// rbt.traverse();
	// rbt.traverse();
	// std::cout << rbt[5] << std::endl;
	// RBT::iterator it = rbt.begin();
	// RBT::iterator itr = rbt.end();
	// std::cout << rbt[1] << std::endl;
	// it->second++;
	// std::cout << rbt[1] << std::endl;
	// // it++;
	// // std::cout << "begin = " << it->first << std::endl; 
	// // --itr;
	// 	// std::cout << "end = " << *itr << std::endl;
	// // std::cout << it->value << std::endl;
	// // std::cout << *itr << std::endl;
	// for (; it != itr; it++)
	// {
	// 	std::cout << it->first << std::endl;
	// }

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

	// std::system("leaks -u a.out");

	// std::cout << "\n" << rbt.find(5)->left->key << std::endl;
	return 0;
}