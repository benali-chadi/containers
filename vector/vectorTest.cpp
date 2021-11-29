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
	std::cout << "size = " << myv.size() << " capcity = " << myv.capacity() << " " << myv[2] << std::endl;
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