#include "set.hpp"
#include <set>

int main()
{
	// std::set<std::string> m;
	// ft::Set<int> ft_m;
	// ft::Set<int> ft_m1;
	// m.insert("HELLO");
	// my_m.insert("HELLO");


	// ft::Set<std::string>::iterator my_it = my_m.begin();
	// std::set<std::string>::iterator it = m.begin();
	// /*---------------------------------------------- */
	// std::cout << it->length() << " " << my_it->length() << std::endl;
	// ft_m.insert('a');
	// ft_m.insert('b');
	// ft_m.insert('c');
	// ft_m.insert('d');
	// ft_m.insert('e');
	// ft_m.insert('f');

	// ft::Set<char>::iterator ft_it = ft_m.find('e');

	// std::cout << "ft_it = " << *ft_it << std::endl; 

	// ft_m.erase(ft_it, ft_m.end());
	//  for (size_t i = 0; i < 1e6; ++i)
    // {
    //     ft_m.insert(i);
	// 	ft_m1.insert(i);
    // }
	// bool ft_res = ft_m == ft_m1;
	// std::cout << ft_res << std::endl;

	std::set<int> m;
	ft::Set<int> ft_m;
	int arr[] = {20, 10, 100, 15, 60, 90, 65, 200, 150}; // size = 9
	for (size_t i = 0; i < 9; ++i)
	{
		m.insert(arr[i]);
		ft_m.insert(arr[i]);
	}
	std::set<int> const c_m(m.begin(), m.end());
	ft::Set<int> const c_ft_m(ft_m.begin(), ft_m.end());
	std::cout << *m.equal_range(15).first << " " << *ft_m.equal_range(15).first << std::endl;
	std::cout << *m.equal_range(65).first << " " << *ft_m.equal_range(65).first << std::endl;
	std::cout << *m.equal_range(63).first << " " << *ft_m.equal_range(63).first << std::endl;
	std::cout << *m.equal_range(120).first << " " << *ft_m.equal_range(120).first << std::endl;
	std::cout << *m.equal_range(70).first << " " << *ft_m.equal_range(70).first << std::endl;

	std::cout << *c_m.equal_range(15).first << " " << *c_ft_m.equal_range(15).first << std::endl;
	std::cout << *c_m.equal_range(65).first << " " << *c_ft_m.equal_range(65).first << std::endl;
	std::cout << *c_m.equal_range(63).first << " " << *c_ft_m.equal_range(63).first << std::endl;
	std::cout << *c_m.equal_range(120).first << " " << *c_ft_m.equal_range(120).first << std::endl;
	std::cout << *c_m.equal_range(70).first << " " << *c_ft_m.equal_range(70).first << std::endl;
	// typedef ft::RBT_Set<int, std::less<int>, std::allocator<int> > RBT;

	// RBT tree;

	// for (int i = 0; i < 10; i++)
	// 	tree.insert(i + 1);

	// for (RBT::iterator it = tree.begin(); it != tree.end(); it++)
	// 	std::cout << *it << std::endl;
	
	// tree.delete_tree();

	// std::set<int> my_s;
    // std::set<int>::iterator my_it;

	// for (int i = 0; i < 1e5; i++)
	// 	my_s.insert(i);

	// my_it = my_s.begin();
    // my_it1 = ++(my_s.begin());

	// for (; my_it != my_s.end(); my_it++)
	// 	std::cout << *my_it << std::endl;
	
	// std::cout << std::endl;
	// std::cout << *my_s.find(8050127) << std::endl;

	return 0;
}