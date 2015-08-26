#include <iostream>

class A
{
public:
	static int i;
public: 
	void f()
	{
		i++;
	}

};

int main()
{
	A a;
	a.f();
	return 0;
}

