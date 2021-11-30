#include <iostream>
#include <vector>
#include <algorithm>
#include "vector.hpp"

// using namespace std;

int main()
{
	// std::vector<int> foo (3,100);	// three ints with a value of 100
	// std::vector<int> bar (1, 15);	// five ints with a value of 200

	ft::vector<int> myv;


	std::cout << "size = " << myv.size() << " capcity = " << myv.capacity() << std::endl;
	myv.push_back(5);
	std::cout << "size = " << myv.size() << " capcity = " << myv.capacity() << " " << myv[0] << std::endl;
	myv.push_back(10);
	std::cout << "size = " << myv.size() << " capcity = " << myv.capacity() << " " << myv[1] << std::endl;
	myv.push_back(15);
	std::cout << "size = " << myv.size() << " capcity = " << myv.capacity() << " " << myv[1] << std::endl;

	myv.pop_back();
	std::cout << "myv: size = " << myv.size() << " capcity = " << myv.capacity() << " " << myv[2] << std::endl;
	
	ft::vector<int> v2(myv);
	std::cout << "v2: size = " << v2.size() << " capacity = " << v2.capacity() << std::endl;
	for (ft::vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		std::cout << *it << std::endl;

	v2.push_back(30);
	v2.push_back(40);
	v2.push_back(60);
	v2.push_back(80);
	v2.push_back(60);
	v2.push_back(80);
	v2.push_back(60);
	v2.push_back(80);
	myv = v2;
	std::cout << "v2: size = " << v2.size() << " capacity = " << v2.capacity() << std::endl;
	std::cout << "myv: size = " << myv.size() << " capcity = " << myv.capacity() << std::endl;
	ft::vector<int> v3 = v2;
	std::cout << "v2: size = " << v2.size() << " capacity = " << v2.capacity() << std::endl;
	std::cout << "v3: size = " << v3.size() << " capacity = " << v3.capacity() << std::endl;


	// ft::vector<int>::iterator it = myv.begin();
	// for (; it != myv.end(); it++)
	// 	std::cout << *it << std::endl;
	// foo.push_back(100);
	// bar.push_back(200);
	// std::cout << "foo capacity " << foo.capacity() << " bar capacity " << bar.capacity() << std::endl;
	// foo.swap(bar);

	// std::cout << "foo capacity " << foo.capacity() << " bar capacity " << bar.capacity() << std::endl;

	// std::cout << "foo contains:";
	// for (unsigned i=0; i<foo.size(); i++)
	// std::cout << ' ' << foo[i];
	// std::cout << '\n';

	// std::cout << "bar contains:";
	// for (unsigned i=0; i<bar.size(); i++)
	// std::cout << ' ' << bar[i];
	// std::cout << '\n';

  return 0;
}