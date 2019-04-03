#include <iostream>
using namespace std;
template<typename T>
class P{
	friend T;
	private:
		int x = 1;
};

class F{
	public:
		int addP2F(P<F> p){
			return p.x + this->x;
		}
	private:
		int x = 1;
};

int main()
{
	
	return 0;
}
