#include <iostream>
#include <vector>
#include <algorithm>
#include "Vector.hpp"

// using namespace std;

int main()
{
	// std::vector<int> foo (3,100);	// three ints with a value of 100
	// std::vector<int> bar (1, 15);	// five ints with a value of 200

	// ft::Vector<int> myv;


	// std::cout << "size = " << myv.size() << " capcity = " << myv.capacity() << std::endl;
	// myv.push_back(5);
	// std::cout << "size = " << myv.size() << " capcity = " << myv.capacity() << " " << myv[0] << std::endl;
	// myv.push_back(10);
	// std::cout << "size = " << myv.size() << " capcity = " << myv.capacity() << " " << myv[1] << std::endl;
	// myv.push_back(15);
	// std::cout << "size = " << myv.size() << " capcity = " << myv.capacity() << " " << myv[1] << std::endl;

	// myv.pop_back();
	// std::cout << "myv: size = " << myv.size() << " capcity = " << myv.capacity() << " " << myv[2] << std::endl;
	
	// ft::Vector<int> v2(myv);
	// std::cout << "v2: size = " << v2.size() << " capacity = " << v2.capacity() << std::endl;
	// for (ft::Vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
	// 	std::cout << *it << std::endl;

	// v2.push_back(30);
	// v2.push_back(40);
	// v2.push_back(60);
	// v2.push_back(80);
	// v2.push_back(60);
	// v2.push_back(80);
	// v2.push_back(60);
	// v2.push_back(80);
	// myv = v2;
	// std::cout << "v2: size = " << v2.size() << " capacity = " << v2.capacity() << std::endl;
	// std::cout << "myv: size = " << myv.size() << " capcity = " << myv.capacity() << std::endl;
	// ft::Vector<int> v3 = v2;
	// std::cout << "v2: size = " << v2.size() << " capacity = " << v2.capacity() << std::endl;
	// std::cout << "v3: size = " << v3.size() << " capacity = " << v3.capacity() << std::endl;


	// ft::Vector<int> v;
	// ft::Vector<int> v2;

	// for (int i = 0; i < 5; i++)
	// {
	// 	v.push_back(i + 1);
	// }

	// // for (int i = 0; i < 3; i++)
	// // {
	// // 	v2.push_back(i + 120);
	// // }
	// v2.push_back(123);
	// v2.push_back(127);
	// // v.assign(v2.begin(), v2.end());
	// // v.clear();

	// // for (ft::Vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
	// // 	std::cout << *it << std::endl;
	
	// // std::cout << std::endl;

	// v.insert(v.begin() + 2, v2.begin(), v2.end());

	// std::cout << "size = " << v.size() << " capacity = " << v.capacity() << std::endl;
	// // for (ft::Vector<int>::iterator k = v2.begin(); k != v2.end(); k++)
	// // 	std::cout  << "k : " << *k << std::endl;

	// ft::Vector<int>::iterator it = v.begin();
	// for (; it != v.end(); it++)
	// {
	// 	// it += 5;
	// 	// auto d = it += 5;
	// 	std::cout << *(it) << std::endl;
	// }
	
	// // for (std::vector<int>::iterator d = v.begin(); d != v.end(); d++)
	// // 	std::cout << *d << std::endl;
	// ft::Vector<int> v;
	// ft::Vector<int> v2;

	// for (int i = 0; i < 10; i++)
	// {
	// 	v.push_back(i);
	// }
	// for (int i = 0; i < 3; i++)
	// {
	// 	v2.push_back(i + 120);
	// }

	// v2.swap(v);

	// std::cout << "size = " << v.size() << " capacity = " << v.capacity() << std::endl;
	// std::cout << "size = " << v2.size() << " capacity = " << v2.capacity() << std::endl;
	
	// std::cout << "vector v" << std::endl; 
	// ft::Vector<int>::iterator it = v.begin();
	// for (; it != v.end(); it++)
	// {
	// 	std::cout << *it << std::endl;
	// }

	// std::cout << "vector v2" << std::endl;
	// ft::Vector<int>::iterator it2 = v2.begin();
	// for (; it2 != v2.end(); it2++)
	// {
	// 	std::cout << *it2 << std::endl;
	// }
	// {
	// 	std::vector<std::string> v(1e5, "fill constructor test");
	// 	std::cout << v[0] << std::endl;
	// 	ft::Vector<std::string> v2(1e5, "fill constructor test");
	// 	std::cout << v2[0] << std::endl;
	// }

	// std::vector<std::string> v(10, "range constructor test");
	ft::Vector<std::string> my_v(10, "fill constructor test");
	ft::Vector<std::string> my_v1(my_v.begin(), my_v.end());
	std::string my_res;

	std::cout << my_v1.capacity() << " " << my_v1.size() << std::endl;
	for (ft::Vector<std::string>::iterator it = my_v.begin(); it != my_v.end(); ++it) // fill my_res from ft::vector
            my_res += *it;
	
	std::cout << my_res << std::endl;
	return 0;
}
