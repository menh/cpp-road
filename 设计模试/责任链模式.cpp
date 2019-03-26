#include <iostream>
#include <cstring>
#include <string>
using namespace std;


class Request
{
	private:
		int  requestLevel;
	public:
		Request(int requestLevel)
		{
			this->requestLevel = requestLevel;
		}
		
		int getRequestLevel()
		{
			return requestLevel;
		}
		
		int setRequestLevel(int requestLevel)
		{
			this->requestLevel = requestLevel;
		}
		
};

class Handler
{
	public:
		Handler(string handlerName, int handlerLevel)
		{
			this->handlerName = handlerName;
			this->handlerLevel = handlerLevel;
		}
		
		void setNextHandler(Handler* nextHandler)
		{
			this->nextHandler = nextHandler;
		}
		
		int getHandlerLevel()
		{
			return handlerLevel;
		}
		
		string getHandlerName()
		{
			return handlerName;
		}
		
		virtual void handlerRequest(Request* request) = 0;
	private:
		string handlerName;
		int handlerLevel;
	protected:
		Handler* nextHandler;
};

class Handler1 : public Handler
{
	public:
		Handler1(string handlerName,int handlerLevel):Handler(handlerName, handlerLevel){}
		void handlerRequest(Request* request)
		{
			if(request->getRequestLevel() == this->getHandlerLevel())
			{
				cout<<getHandlerName()<<" Handle Request"<<endl;
			}
			else
			{
				if(nextHandler != NULL)
				{
					nextHandler->handlerRequest(request);
				}
				else
				{
						cout<<"No Handler"<<" Handle Request"<<endl;
				}
			}
		}
};

class Handler2 : public Handler
{
	public:
		Handler2(string handlerName,int handlerLevel):Handler(handlerName, handlerLevel){}
		void handlerRequest(Request* request)
		{
			if(request->getRequestLevel() == this->getHandlerLevel())
			{
				cout<<getHandlerName()<<" Handle Request"<<endl;
			}
			else
			{
				if(nextHandler != NULL)
				{
					nextHandler->handlerRequest(request);
				}
				else
				{
						cout<<"No Handler"<<" Handle Request"<<endl;
				}
			}
		}
};

int main()
{
	Request* request1 = new Request(100);
	Request* request2 = new Request(200);
	Handler* handler1 = new Handler1("handler1", 100);
	Handler* handler2 = new Handler1("handler2", 200);
	handler1->setNextHandler(handler2);
	
	handler1->handlerRequest(request2);
	handler1->handlerRequest(request1);
	
	
	return 0;
}
