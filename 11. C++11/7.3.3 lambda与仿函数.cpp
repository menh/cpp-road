#include <iostream>
using namespace std;

class AirportPrice{
	private:
		float _dutyfreerate;
	public:
		AirportPrice(float rate):_dutyfreerate(rate){}
		float operator()(float price){
			return price * (1 - _dutyfreerate / 100);
		} 
}; 
int main()
{
	float tax_rate = 5.5f;
	AirportPrice Chang1(tax_rate);
	
	auto Chang2 = [tax_rate](float price) -> float{ return price * (1 - tax_rate / 100); };
	
	cout<< Chang1(3699) <<endl;
	cout<< Chang2(3699) <<endl;
	return 0;
}
