#include <iostream>
#include <vector>
#include <algorithm>
#include "vector.hpp"

#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include "class.hpp"
#define TIME_FAC 3

time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return (msecs_time);
}

// using namespace std;

int main()
{
	Class toto;
	ft::Vector<Class> vec1(1, toto);
	try{
		vec1.insert(vec1.begin(), 10, toto);
	}catch(...){}
	std::cout << "size: " << vec1.size() << "\n";
	std::cout << "cap: " << vec1.capacity() << "\n";

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
	
	// typedef ft::Vector<int>::iterator myIterator;
	// typedef std::vector<std::string>::iterator iterator;
	
	
	// ft::Vector<std::string> ft_v1(10, "string2");
	// std::vector<std::string> v2(10, "string2");
	// std::string res, ft_res;

	// for (ft::Vector<std::string>::reverse_iterator rit = ft_v1.rbegin(); rit != ft_v1.rend(); ++rit) // fill ft_res from ft_v1
	// {
	// 	std::cout << *rit << std::endl;
	// 	ft_res += *rit;
	// }
	// for (std::vector<std::string>::reverse_iterator rit = v2.rbegin(); rit != v2.rend(); ++ rit)
	// 	res += *rit;
	
	// std::cout << res << "\n" << ft_res << std::endl;
	// ft::Vector<int> v;

	// for (int i = 0; i < 5; i++)
	// 	v.push_back(i + 1);
	// ft::Vector<int>::reverse_iterator rit(v.end());
	// rit = v.rbegin();
	// for (;rit != v.rend(); rit++)
	// 	std::cout << *(rit.base()) << std::endl;
	// ft::Vector<int> v(4, 5);
	// ft::Vector<int>::reverse_iterator my_rit2(v.end());
	// ft::Vector<int>::const_reverse_iterator c_it, c_ob(v.end());
	// c_it = my_rit2;
	// std::cout << "c_it = " << &(*c_it) << " rit = " << &(*my_rit2) << std::endl;
	// if (&(*my_rit2) == &(*c_it) && (&(*my_rit2) == &(*c_ob)))
	// 	std::cout << "true\n";
	// else
	// 	std::cout << "false\n";

	// for (iterator it = ft_v1.begin(); it != ft_v1.end(); it++)
	// 	std::cout << *it << std::endl;
	// std::cout << "s1 = " << s1 << std::endl;
	return 0;
}
