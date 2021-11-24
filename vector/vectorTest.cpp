#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> v;
	for (int i = 0; i < 10; i++)
		v.push_back(i + 1);
	
	cout << "size = " << v.size() << " capacity = " << v.capacity() << endl;
	for (int c: v)
		cout << c << " ";
	cout << endl;

	v.assign(5, 2);

	cout << "size = " << v.size() << " capacity = " << v.capacity() << endl;
	for (int c: v)
		cout << c << " ";
	cout << endl;
	return 0;
}