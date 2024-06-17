
#include "Polynomial.h"

//����ö�٣�   ���� �����������䣬�Ӻţ����ţ����ţ��˺ţ����ʽ, ���� 
enum TokenType { ttDer, ttIntArea, ttAdd, ttSub, ttDiv, ttMul, ttPol, ttNum };

//��������     ���� 4, ���� 3 ��/�� 2 ��/�� 1 ���� 0 

//���ƶ������ڵ� 
struct Token{
	char   ExpressChar;
	enum TokenType Type;	
	int    Level;   //���� 
	float  Height;	//���������ϼ� 
	float  Lower; 	//���������¼� 

	Token* Parent;
	Token* Left;
	Token* Right; 
};

class Expression{
	private:
		Token* Root;	//�����б� 
	public:
		Polynomial polynomials[26];	//26����ĸ��ÿ����ĸ��Ϊһ�����Ӧ�ù�����
		
		Expression();
		~Expression();
		
		Token* Analysis( char *Expression );
		Polynomial Execute(Token* RootToken);
		
		void Free( Token* RootToken );
		void Print( Token* RootToken );
};

