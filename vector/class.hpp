#pragma  once
#include  <stdexcept>
#include	<iostream>
	
static int i = 0;
class Class{
	public:
		Class(void): x(0){
			std::cout << "default\n";
			i++;
			if (i == 5)
				throw std::length_error("test");
		}
		Class(Class const& obj){
			std::cout << "copy\n";
			x = obj.x;
			i++;
			if (i == 5)
				throw std::length_error("test");
		}
		~Class(){}
	private:
		int x;
};