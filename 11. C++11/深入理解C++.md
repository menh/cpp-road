#### C++11 �ȶ���C++98/03������ǿ�ķ���
 * ͨ���ڴ�ģ�͡��̡߳�ԭ�Ӳ�������֧�ֱ��ز��б��
 * ͨ��ͳһ��ʼ����﷽ʽ��auto��declytype���ƶ��������ͳһ�Է��ͱ�̵�֧�֡�
 * ͨ��constexpr��POD(����)�ȸ��õ�֧��ϵͳ���
 * ͨ�����������ռ䡢�̳й��캯������ֵ���õȣ��Ը��õ�֧�ֿ�Ĺ���

####### 2.1 ������C99����
 2.1.2 __func__ Ԥ�����ʶ��
   ���غ�����,�ṹ�壬�������
   ```
   const char* testFunc(){
     return __func__;
   }

   struct TestStruct{
     TestStruct() : name(__func__){}
     const char* name;
   };

   class TestClass{
     public:
        TestClass() : name(__func__){}
        const char* name;
      };

    int main()
    {
  	     cout<<testFunc()<<endl;
  	     TestStruct ts;
  	     cout<<ts.name<<endl;
  	     TestClass tc;
  	     cout<<tc.name<<endl;
         return 0;
     }
   ```
   2.1.3 _Pragma Ԥ�����ʶ��
   ָʾ����������ͷ�ļ�ֻ������һ��
    ```
    #pragam once
    ��
    #ifndef THIS_HEADER
    #define THIS_HEADER
    ��
    _Pragma("once")
    ...
    #endif
    Ч��һ��
    ```
    2.1.4 �䳤�����ĺ궨���Լ�__VA_ARGS__
    ```
    // stderr ��׼��������豸
    #define LOG(...){\
	  fprintf(stderr,"%s: Line %d:\n", __FILE__, __LINE__);\
	  fprintf(stderr, __VA_ARGS__);\
	  fprintf(stderr, "\n");\
    }

    int main()
    {
	     int x = 3;
	     LOG("x = %d", x); // fprintf(stderr,"x = %d", x);
	     return 0;
    }
    ```
    2.1.5 ��խ�ַ���������
    ��խ�ַ�������ʱ����խ�ַ���ת���ɿ��ַ�����֮��������ַ�������ƴ��

###### 2.2 long long ����
    long long �����ڲ�ͬƽ̨�в�ͬ�ĳ��ȣ�����64λ��
    long long = signed long long = long long int = signed long long int
    unsigned long long = unsigned long long int
    ��ͨ��LLONG_MIN,LLONE_MAX��ULLONG_MIN���鿴��С��long long,����long long������unsigned long long
    ```
    int main()
    {
	     long long ll_min = LLONG_MIN;
	     long long ll_max = LLONG_MAX;
	     unsigned long long ull_max = ULLONG_MAX;

	     printf("min of long long: %lld\n", ll_min);

	     printf("max of long long: %lld\n", ll_max);

	     printf("max of unsigned long long: %llu\n", ull_max);

	     return 0;
     }
    ```
###### 2.3 ��չ������
    C++ 11 ֻ������5�ֱ�׼���з������ͣ�ÿһ���з������Ͷ����޷��������汾�����з������������Ӧ���޷������;�����ͬ��С�Ĵ洢�ռ�
    * signed char
    * short int
    * int
    * long int
    * long long int
    ��������ͬ���������ʱ����Ҫ�����ͽ���ת����ת�����������ǵ�"�ȼ�"����.�ȼ�ԭ������
    * ����Խ������͵ȼ�Խ�ߣ�long long �ȼ����� int
    * ������ͬʱ����׼���͵ĵȼ�������չ���ͣ�long long int �� _int64 ����64λʱ�� long long int �ȼ�����
    * ��ͬ��С���з������ͺ��޷������͵ĵȼ���ͬ

###### 2.4 __cplusplus
    ͨ����__cplusplus ���Ʊ�����֧�ֵİ汾
    ```
    #if __cplusplus < 201103L
	   #error "should use c++11 implementation"

     #endif
     #include <iostream>
     using namespace std;
     int main()
     {

	      return 0;
    }
    ```
###### 2.5 ����
  2.5.1 ���ԣ� ����ʱ��Ԥ����ʱ assert
    ���������ų���Ƶ��߼��ϲ�Ӧ�ò��������,ͨ��assert�������ԣ�ͨ������NDEBUG���ζ���
    ```
    #include <iostream>
#include <cassert>
using namespace std;
#define NDEBUG NDEBUG

#ifdef NDEBUG
# define assert(expr) (static_cast<void>(0))
#endif

char* ArrayAlloc(int n){
	assert(n > 0);
	return new char[n];
}
int main()
{
	char* a = ArrayAlloc(0);
	return 0;
}
    ```

2.5.2 ��̬����static_assert
     ʹ��static_assert�ڱ����ڼ伴�ɲ�������
     ʹ�÷������£�
     ```
     #include <iostream>
using namespace std;
template <typename T, typename U>
void bit_copy(T& a, U& b)
{
	static_assert(sizeof(b) == sizeof(a), "the parameters of bit_copy must have same width.");

}

int main()
{
	int a = 0x2468;
	double b;
	bit_copy(a,b);
	return 0;
}
     ```
     static_assert�Ķ��Ա��ʽ�Ľ���������ڱ���ʱ�ڿ��Լ���ı��ʽ�������򲻶�
    ```
    int positive(const int n){
	static_assert(1 > 0, "value must > 0");
}
    ```
##### 2.6 noexcept���η���noexcept������
  ��noexcept���εĺ��������쳣�ǻ�ֱ�ӵ���std::terminate����ֹ���������
  δ�����εĺ������һ��һ���׳��쳣��ֱ����catch��.
  ��������Ĭ����noexcept(true)��
  ```
  #include <iostream>
using namespace std;
struct A{
	~A(){
		throw;
	}
};

struct B{
	~B() noexcept(false){
		throw 2;
	}
};
int main()
{
	try{
		B b;
	}
	catch(...){
		cout<<"b throw"<<endl;
	}

	try{
		A a;
	}
	catch(...){
		cout<<"a throw"<<endl;
	}
	return 0;
}
  ```
#### 2.7 ���ٳ�ʼ����Ա����
 c++98 ֻ�г�����̬��Ա���ͻ�ö���Ͳ��ܾ͵س�ʼ�����Ǿ�̬��Ա���������ڹ��캯���н���
 c++11 ����ʹ��=����{}���о͵طǾ�̬��Ա�����ĳ�ʼ��
 ```
 stauct init{int a = 1; double b {1.2}; };
 ```
##### 2.8 �Ǿ�̬��Ա��sizeof
  ���ԶԷǾ�̬��Ա����sizeof����
  ```
  #include <iostream>
using namespace std;

struct People{
	public:
		int hand;
		static People* all;
};
int main()
{
	People p;
	cout << sizeof(p)<<endl;
	cout << sizeof(p.hand) <<endl;
	cout << sizeof(People::all) <<endl;
	cout << sizeof(People::hand) <<endl;
	return 0;
}
  ```
2.9 ��չ��friend�﷨
    ����ʹ��ģ����������Ԫ
    ```
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
    ```
2.10 final/override ����
    final��ʹ�������ɱ�����
    verride��ʹ�������뱻����
```
#include <iostream>
using namespace std;
class Base{
	virtual void func1();
	virtual void func2();
};

class DerivedMid: public Base{
	virtual void func1() override;
	virtual void func2() override final;
};

class DerivedTop: public DerivedMid{
	virtual void func1() override;
	//virtual void func2() override final;
};
int main()
{

	return 0;
}
```
2.11 ģ�庯����Ĭ��ģ�����
    ֧��Ĭ��ģ�����
```
#include <iostream>
using namespace std;

template<class T, class U = int>
void add(T t, U u){
	cout<< t + u <<endl;
}
int main()
{
	add(1,2);
	string t = "1";
	string u = "2";
	add(t,u);
	return 0;
}
```
2.12 �ⲿģ��
2.12.1
  �ⲿģ����ʹ��extern�ؼ��֣�ʹ����ļ�����ͬһ�ݱ���������a.c���ж���int i,������һ���ļ�����ʹ�����Ļ�������extern int i

2.12.2 ��ʽ��ʵ�������ⲿģ�������
  ��ʹ��extern�ؼ��ֹ������
  ```
    template <typename T> void fun(T)
    template void fun<int>(int)
    extern template void fun<int>(int)
  ```

3.1 �̳й��캯��
```
#include <iostream>
using namespace std;

struct A{
	A(int _a) { a = _a;}
	int a;
};

struct B : A {
	using A::A;

};
int main()
{
	B b(1);

	cout<<b.a<<endl;
	return 0;
} 
```
3.2 ί�ɹ��캯��
