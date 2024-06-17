
#include "Polynomial.h"

//依次枚举：   导数 ，定积分区间，加号，减号，除号，乘号，表达式, 数字 
enum TokenType { ttDer, ttIntArea, ttAdd, ttSub, ttDiv, ttMul, ttPol, ttNum };

//级别排序     导数 4, 积分 3 乘/除 2 加/减 1 其他 0 

//令牌二叉树节点 
struct Token{
	char   ExpressChar;
	enum TokenType Type;	
	int    Level;   //级别 
	float  Height;	//积分区间上级 
	float  Lower; 	//积分区间下级 

	Token* Parent;
	Token* Left;
	Token* Right; 
};

class Expression{
	private:
		Token* Root;	//令牌列表 
	public:
		Polynomial polynomials[26];	//26个字母，每个字母作为一个多项，应该够用了
		
		Expression();
		~Expression();
		
		Token* Analysis( char *Expression );
		Polynomial Execute(Token* RootToken);
		
		void Free( Token* RootToken );
		void Print( Token* RootToken );
};

