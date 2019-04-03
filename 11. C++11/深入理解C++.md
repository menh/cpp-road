#### C++11 先对于C++98/03显著增强的方面
 * 通过内存模型、线程、原子操作等来支持本地并行编程
 * 通过统一初始化表达方式、auto、declytype、移动语义等来统一对泛型编程的支持。
 * 通过constexpr、POD(概念)等更好的支持系统编程
 * 通过内联命名空间、继承构造函数和右值引用等，以更好的支持库的构建

####### 2.1 保持与C99兼容
 2.1.2 __func__ 预定义标识符
   返回函数名,结构体，类等名称
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
   2.1.3 _Pragma 预定义标识符
   指示编译器，该头文件只被编译一次
    ```
    #pragam once
    与
    #ifndef THIS_HEADER
    #define THIS_HEADER
    与
    _Pragma("once")
    ...
    #endif
    效果一致
    ```
    2.1.4 变长参数的宏定义以及__VA_ARGS__
    ```
    // stderr 标准错误输出设备
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
    2.1.5 宽窄字符串的连接
    宽窄字符串连接时，将窄字符串转换成宽字符串，之后在与宽字符串进行拼接

###### 2.2 long long 整型
    long long 整型在不同平台有不同的长度，至少64位。
    long long = signed long long = long long int = signed long long int
    unsigned long long = unsigned long long int
    可通过LLONG_MIN,LLONE_MAX和ULLONG_MIN来查看最小的long long,最大的long long，最大的unsigned long long
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
###### 2.3 拓展的整型
    C++ 11 只定义了5种标准的有符号整型，每一种有符号整型都有无符号整数版本，且有符号整型与其对应的无符号整型具有相同大小的存储空间
    * signed char
    * short int
    * int
    * long int
    * long long int
    当两个不同整型运算的时候，需要对类型进行转换，转换规则由他们的"等级"决定.等级原则如下
    * 长度越大的整型等级越高，long long 等级高于 int
    * 长度相同时，标准整型的等级高于扩展类型，long long int 和 _int64 都是64位时， long long int 等级更高
    * 相同大小的有符号类型和无符号类型的等级相同

###### 2.4 __cplusplus
    通过宏__cplusplus 控制编译器支持的版本
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
###### 2.5 断言
  2.5.1 断言： 运行时与预处理时 assert
    断言用于排除设计的逻辑上不应该产生的情况,通过assert产生断言，通过定义NDEBUG屏蔽断言
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

2.5.2 静态断言static_assert
     使用static_assert在编译期间即可产生断言
     使用方法如下：
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
     static_assert的断言表达式的结果必须是在编译时期可以计算的表达式，如下则不对
    ```
    int positive(const int n){
	static_assert(1 > 0, "value must > 0");
}
    ```
##### 2.6 noexcept修饰符与noexcept操作符
  被noexcept修饰的函数发生异常是会直接调用std::terminate来中止程序的运行
  未被修饰的函数则会一层一层抛出异常，直到被catch到.
  析构函数默认是noexcept(true)的
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
#### 2.7 快速初始化成员变量
 c++98 只有常量静态成员整型或枚举型才能就地初始化。非静态成员常量必须在构造函数中进行
 c++11 可以使用=或者{}进行就地非静态成员变量的初始化
 ```
 stauct init{int a = 1; double b {1.2}; };
 ```
##### 2.8 非静态成员的sizeof
  可以对非静态成员进行sizeof操作
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
2.9 拓展的friend语法
    可以使用模板来声明友元
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
2.10 final/override 控制
    final，使函数不可被重载
    verride，使函数必须被重载
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
2.11 模板函数的默认模板参数
    支持默认模板参数
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
2.12 外部模板
2.12.1
  外部模板是使用extern关键字，使多个文件共享同一份变量，例如a.c中有定义int i,则在另一个文件中想使用他的话可以用extern int i

2.12.2 显式的实例化与外部模板的声明
  可使用extern关键字共享代码
  ```
    template <typename T> void fun(T)
    template void fun<int>(int)
    extern template void fun<int>(int)
  ```

3.1 继承构造函数
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
3.2 委派构造函数
