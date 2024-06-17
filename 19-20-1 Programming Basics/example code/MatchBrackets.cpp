#include <iostream>
#include <string> 	//string 字符串变量类型 
#include <string.h> //strlen 函数 

using namespace std;

int main( int argc, char** argv )
{
	
	cout <<"请一串表达式:"<<endl;
	// 可以考虑用两种字符串获取方案 
	string Expression;		//1： string变量可以不限制长度，
	cin >>Expression;
	int ExpressionLength = Expression.size();
	//char Expression[100];	//2:  用char指针需要申请指定长度空间  
	//cin >>Expression;
	//int ExpressionLength = strlen(Expression)
 
	int wCount = 0;
	int wIndex = 0;
	bool wHaveBrackets = false; 
	cout <<"开始匹配括号..."<<endl;	
	for( wIndex = 0; wIndex < ExpressionLength; wIndex++ )
	{
		if ( Expression[ wIndex ] == 40 )	//40 在ASICC表中表示左括号
		{
			wHaveBrackets = true;
			wCount ++;
		}
		if ( Expression[ wIndex ] == 41 )	//41 在ASICC表中表示右括号
		{  
			wHaveBrackets = true;
			wCount --;
		}
	}
	
	if ( !wHaveBrackets )
	{
		cout <<"一个括号都不输入，让我匹配啥呀~"<<endl;
		return 0;		
	}
	
	if (wCount != 0)
		cout <<"有括号没匹配上!"<<endl;
	else
		cout <<"所有括号都匹配上了!"<<endl;
	return 0;
}
