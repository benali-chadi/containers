#include <iostream>
#include <vector>
#include <algorithm>
#include "vector.hpp"

// using namespace std;

int main()
{
	// std::vector<int> foo (3,100);	// three ints with a value of 100
	// std::vector<int> bar (1, 15);	// five ints with a value of 200

	// ft::vector<int> myv;


	// std::cout << "size = " << myv.size() << " capcity = " << myv.capacity() << std::endl;
	// myv.push_back(5);
	// std::cout << "size = " << myv.size() << " capcity = " << myv.capacity() << " " << myv[0] << std::endl;
	// myv.push_back(10);
	// std::cout << "size = " << myv.size() << " capcity = " << myv.capacity() << " " << myv[1] << std::endl;
	// myv.push_back(15);
	// std::cout << "size = " << myv.size() << " capcity = " << myv.capacity() << " " << myv[1] << std::endl;

	// myv.pop_back();
	// std::cout << "myv: size = " << myv.size() << " capcity = " << myv.capacity() << " " << myv[2] << std::endl;
	
	// ft::vector<int> v2(myv);
	// std::cout << "v2: size = " << v2.size() << " capacity = " << v2.capacity() << std::endl;
	// for (ft::vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
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
	// ft::vector<int> v3 = v2;
	// std::cout << "v2: size = " << v2.size() << " capacity = " << v2.capacity() << std::endl;
	// std::cout << "v3: size = " << v3.size() << " capacity = " << v3.capacity() << std::endl;


	ft::vector<int> v;

	for (int i = 0; i < 5; i++)
	{
		v.push_back(i + 1);
	}

	ft::vector<int>::iterator it = v.begin();
	for (; it != v.end(); it++)
	{
		// it += 5;
		// auto d = it += 5;
		std::cout << *(it + 5) << std::endl;
	}
	
	for (ft::vector<int>::iterator d = v.begin(); d != v.end(); d++)
		std::cout << *d << std::endl;

  return 0;
}