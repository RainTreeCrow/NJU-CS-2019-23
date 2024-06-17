#include <stdlib.h>
#include <iostream>

#include "Expression.h" 
#include "string.h"
#include "math.h"

using namespace std;

Expression::Expression(){
}

Expression::~Expression(){
}

void Expression::Free( Token* RootToken ){
	if( NULL == RootToken )
		return;
	
	if( NULL != RootToken->Left ){
		Free( RootToken->Left );	
	}
	RootToken->Left = NULL;
	
	if( NULL != RootToken->Right ){	
		Free( RootToken->Right );
	}
	RootToken->Right = NULL;

	delete RootToken;	
}

//进行语法分析->得到语法二叉树，返回根节点 
Token* Expression::Analysis( char *ExpressionStr ){
	int Index = 0;
	int Brackets=0;			//圆括号匹配键值
	char MidExpress[128]; 		//括号中间的表达式
	char Number[32];	//一个数字不能超过32位 
	
	bool InBracket = false;	//是否在括号中 
	bool InArea  = false;	//是否在定积分中 
	
	Token *AreaToken = NULL;	//用来确定定积分区间的令牌 
	Token *CurrToken = NULL; 	//当前指向树中的令牌 
	Token *token = NULL;
	Token *RootToken = NULL; 
	
	memset( MidExpress, 0x00, sizeof( MidExpress ) ); 
	int MidExpressLength = 0;
	
	memset( Number, 0x00, sizeof( Number ) ); 
	int NumberLength = 0;

	while(ExpressionStr[Index]!='\0'){
		
		bool EffectChar = false;
		
		if( ExpressionStr[Index] == '(' ){
			//一旦找到左括号，则启动括号中间表达式
			Brackets++; 
			if( !InBracket ) {
				memset( MidExpress, 0x00, sizeof(MidExpress) );
				MidExpressLength = 0;
				InBracket = true;
				Index++;
				continue;
			}
			EffectChar = true;
		}

		if( ExpressionStr[Index] == ')' ){
			//一旦右边则键值递减，如果右键值为零说明已经匹配完成左括号，则将中间表达式重新解析 
			Brackets--;
			if( Brackets == 0 ){
				token = Analysis( MidExpress );
				if( NULL == token ){
					Free(RootToken);		//释放已经解析的所有令牌 
					return NULL;
				}

				if( NULL != AreaToken ){
					if( NULL != CurrToken ){
						CurrToken->Right = AreaToken;
						AreaToken->Parent = CurrToken;
					}else{
						RootToken = AreaToken;
					}
					AreaToken->Right = token;
					token->Parent = AreaToken;
					CurrToken = token;
					AreaToken = NULL;
				}else{
					if( NULL == CurrToken )
						CurrToken = token;
					else {
						CurrToken->Right = token; 
						token->Parent = CurrToken;
					}
					CurrToken = token;
				}

				InBracket = false; 
				Index++;
				continue;
			} 
			
			EffectChar = true;
		}
		
		//如果在括号内，其他都不做 
		if( InBracket ){
			MidExpress[MidExpressLength++] = ExpressionStr[Index];
			Index ++;
			continue;
		}
		
		if( ExpressionStr[Index] == '$' ){
			//进入定积分标识,如果定积分令牌还没结束，说明上个定积分还没完全解析，因此表达式错误 	
			if( InArea ){
				Free(RootToken);		//释放已经解析的所有令牌 
				return NULL;
			}
			InArea = true;
			AreaToken = new Token;
			AreaToken->ExpressChar = ExpressionStr[Index];
			AreaToken->Parent = NULL;
			AreaToken->Lower = -1;
			AreaToken->Height= -1;
			AreaToken->Type = ttIntArea;
			AreaToken->Left = NULL;
			AreaToken->Right= NULL; 
			AreaToken->Level = 3;
			
			EffectChar = true;
		}
	
		if( ExpressionStr[Index] == '[' ){
			if( !InArea ){	//如果没有定积分标识,方括号属于无效字符，表达式错误 
				Free(RootToken);	
				return NULL;
			}

			EffectChar = true;
		} 
		if( ExpressionStr[Index] == ']' ){
			if( !InArea ){	//如果没有定积分标识,方括号属于无效字符，表达式错误 
				Free(RootToken);	
				return NULL;
			}

			if( NumberLength<=0 ){	//必须有数字，如果没有说明区间表达式错误 
				Free(RootToken);	
				return NULL;
			} 
			InArea = false;

			AreaToken->Height = atof( Number );
			NumberLength = 0;
			memset( Number, 0x00, sizeof( Number ) );
			EffectChar = true;
		}
		if( ExpressionStr[Index] == ',' ){
			if( !InArea ){	//如果没有定积分标识,方括号属于无效字符，表达式错误 
				Free(RootToken);	
				return NULL;
			}
			if( NumberLength<=0 ){	//必须有数字，如果没有说明区间表达式错误 
				Free(RootToken);	
				return NULL;
			} 
			AreaToken->Lower = atof( Number );
			NumberLength = 0;
			memset( Number, 0x00, sizeof( Number ) ); 
			EffectChar = true;
		}
		
		
		if( ExpressionStr[Index]>=48 && ExpressionStr[Index]<=57 || ExpressionStr[Index] == '.' ){
			//数字,列入数字字符串内，一旦遇到加、减、乘、除，逗号，方括号，空格 说明数字结束 
			Number[NumberLength++] = ExpressionStr[Index];
			EffectChar = true;
		}
		
		if( ExpressionStr[Index]>=65 && ExpressionStr[Index]<=90 ){
			
			//表达式前面必须是加减乘除 
			if( NULL!=CurrToken && CurrToken->Type != ttAdd && CurrToken->Type != ttSub && CurrToken->Type != ttMul && CurrToken->Type != ttDiv ) {
				Free(RootToken);
				return NULL;
			}
			
			//表达式名称,建立表达式令牌 
			token = new Token;
			token->ExpressChar = ExpressionStr[Index];
			token->Parent = NULL;
			token->Type = ttPol;
			token->Left = NULL;
			token->Right= NULL;
			token->Level = 0;
			
			if( NULL != AreaToken ){
				if( NULL != CurrToken ){ 
					CurrToken->Right = AreaToken;
					AreaToken->Parent = CurrToken;
				}else{
					RootToken = AreaToken;
				}
				AreaToken->Right = token;
				token->Parent = AreaToken;
				CurrToken = token;
				AreaToken = NULL;
			}
			else{
				if( NULL == CurrToken ){
					CurrToken = token;
					RootToken = token;
				}
				else{
					CurrToken->Right = token;
					token->Parent = CurrToken;
					CurrToken = token;
				}
			}
			EffectChar = true;
		} 
		
		if( ExpressionStr[Index] == '!' ){
			//如果是导数运算符，则将之前产生的上级节点作为将要被导的多项式二叉树，置于导数节点的左子树 
			if( NULL == CurrToken ){
				Free(RootToken);	
				return NULL;
			}

			if( NumberLength > 0 ){	//数字不能求导 
				Free(RootToken);	
				return NULL;
			}

			if( NULL != AreaToken ){//定积分未确定多项式 
				Free(RootToken);
				return NULL;
			}

			token = new Token;
			token->ExpressChar = ExpressionStr[Index];
			token->Parent = NULL;
			token->Type = ttDer;
			token->Left = NULL;
			token->Right= NULL;
			token->Level = 4;
			
			token->Left = CurrToken;
			if( NULL != CurrToken->Parent ){
				CurrToken->Parent->Right = token;
				token->Parent = CurrToken->Parent;
			} else{
				RootToken = token;
			}
			CurrToken->Parent = token;
			CurrToken = token; 
			EffectChar = true;
		}
		
		if( ExpressionStr[Index] == '*' || ExpressionStr[Index] == '/' ){
			
			if( NULL == CurrToken ){
				Free(RootToken);	
				return NULL;
			}

			if( NULL != AreaToken ){//定积分未确定多项式 
				Free(RootToken);
				return NULL;
			}

			if( NumberLength > 0 ){	//处理数字令牌 
				token = new Token;
				token->ExpressChar = ExpressionStr[Index];
				token->Height = atof( Number );
				token->Parent = NULL;
				token->Left = NULL;
				token->Right= NULL;
				token->Type = ttNum;
				token->Level = 0;
				
				if( NULL != CurrToken ){
					CurrToken->Right = token;
					token->Parent = CurrToken;
					CurrToken = token;
				}
				else{
					CurrToken = token;
					RootToken = token;
				}
				
				NumberLength = 0;
				memset( Number, 0x00, sizeof( Number ) );	
			}

			//乘除号前面如果是一个无效的四则运算符则表达式错误 
			if( CurrToken->Type == ttAdd || CurrToken->Type == ttSub || CurrToken->Type == ttMul || CurrToken->Type == ttDiv ) {
				if( NULL == CurrToken->Left || NULL == CurrToken->Right ){
					Free(RootToken);
					return NULL;
				}
			}

			token = new Token;
			token->ExpressChar = ExpressionStr[Index];
			token->Parent = NULL;
			token->Left = NULL;
			token->Right= NULL;
			if( ExpressionStr[Index] == '*' )
				token->Type = ttMul;
			else
				token->Type = ttDiv;
			token->Level = 2;
			
			if( NULL!=CurrToken->Parent ){
				while( NULL!=CurrToken->Parent && token->Level <= CurrToken->Parent->Level ){	//先定积分后乘的情况 
					CurrToken = CurrToken->Parent; 
				}
			}

			token->Left = CurrToken;
			if( NULL != CurrToken->Parent ){
				CurrToken->Parent->Right = token;
				token->Parent = CurrToken->Parent;
			}else{
				RootToken = token;
			}
			CurrToken->Parent = token;
			CurrToken = token; 
			EffectChar = true;
		}
		
		if( ExpressionStr[Index] == '+' || ExpressionStr[Index] == '-' ){
			
			if( NULL == CurrToken ){
				Free(RootToken);	
				return NULL;
			}

			if( NULL != AreaToken ){//定积分未确定多项式 
				Free(RootToken);
				return NULL;
			}
			
			if( NumberLength > 0 ){	//处理数字令牌 
				token = new Token;
				token->ExpressChar = ExpressionStr[Index];
				token->Height = atof( Number );
				token->Parent = NULL;
				token->Left = NULL;
				token->Right= NULL;
				token->Type = ttNum;
				token->Level = 0;
				
				if( NULL != CurrToken ){
					CurrToken->Right = token;
					token->Parent = CurrToken;
					CurrToken = token;
				}
				else{
					CurrToken = token;
					RootToken = token;
				}
				
				NumberLength = 0;
				memset( Number, 0x00, sizeof( Number ) );	
			}

			//加减号前面如果是一个无效的四则运算符则表达式错误 
			if( CurrToken->Type == ttAdd || CurrToken->Type == ttSub || CurrToken->Type == ttMul || CurrToken->Type == ttDiv ) {
				if( NULL == CurrToken->Left || NULL == CurrToken->Right ){
					Free(RootToken);
					return NULL;
				}
			}

			token = new Token;
			token->ExpressChar = ExpressionStr[Index];
			token->Parent = NULL;
			token->Left = NULL;
			token->Right= NULL;
			if( ExpressionStr[Index] == '+' )
				token->Type = ttAdd;
			else
				token->Type = ttSub;
			token->Level = 1;

			if( CurrToken->Level==0 && NULL!=CurrToken->Parent ){
				while( NULL!=CurrToken->Parent && token->Level <= CurrToken->Parent->Level ){	//先乘后加的情况 
					CurrToken = CurrToken->Parent; 
				}
			}
			
			token->Left = CurrToken;
			if( token->Level <= CurrToken->Level ){
				RootToken = token;
			}else{
				if( NULL != CurrToken->Parent ){
					CurrToken->Parent->Right = token;
					token->Parent = CurrToken->Parent;
				}
				else
					RootToken = token;
			}
			CurrToken->Parent = token;
			CurrToken = token; 
			EffectChar = true;
		}
		
		if( ExpressionStr[Index] == ' ' ){
			
			if( NumberLength > 0 ){	
				token = new Token;
				token->Height = atof( Number );
				token->Parent = NULL;
				token->Left = NULL;
				token->Right= NULL;
				token->Type = ttNum;
				token->Level = 0;
				
				if( NULL != CurrToken ){
					CurrToken->Right = token;
					token->Parent = CurrToken;
					CurrToken = token;
				}
				else{
					CurrToken = token;
					RootToken = token;
				}
				
				NumberLength = 0;
				memset( Number, 0x00, sizeof( Number ) );	
			}

			Index ++ ;
			continue;
		}
		
		if( !EffectChar ){	//非法字符 
			Free(RootToken);
			return NULL;
		}
		
		Index ++ ;	
	}
	
	//最后一个数字还未处理 
	if( NumberLength > 0 ){	
		token = new Token;
		token->Height = atof( Number );
		token->Parent = NULL;
		token->Left = NULL;
		token->Right= NULL;
		token->Type = ttNum;
		token->Level = 0;
		
		if( NULL != CurrToken ){
			CurrToken->Right = token;
			token->Parent = CurrToken;
			CurrToken = token;
		}
		else{
			CurrToken = token;
			RootToken = token;
		}
		
		NumberLength = 0;
		memset( Number, 0x00, sizeof( Number ) );	
	}
	
	if( NULL != AreaToken ){//定积分未确定多项式 
		Free(RootToken);
		return NULL;
	}

	if( Brackets != 0 ){	//括号不匹配 
		Free(RootToken);
		return NULL;
	} 
	
	Root = RootToken; 
	return RootToken;
}

Polynomial Expression::Execute(Token* Root){	
	Polynomial Result;
	if( NULL == Root )
		return Result;
		
	if( Root->Type == ttNum ){
		Result.Initialization(Root->Height);
		return Result;
	}else if( Root->Type == ttPol ){
		for ( int i=0; i<26; i++ ){
			if ( polynomials[i].Nameis( Root->ExpressChar ) ){
				Result = polynomials[i];
				return Result;
			} 
		}
		cout << "执行错误,表达式["<<Root->ExpressChar<<"]不存在."<<endl;
		return Result;
	}

	Polynomial LeftPoly;
	Polynomial RightPoly;

	if( NULL != Root->Left )
		LeftPoly = Execute( Root->Left );

	if( NULL != Root->Right )
		RightPoly = Execute( Root->Right );

	if( Root->Type == ttAdd ){
		return LeftPoly.Add( RightPoly );
	}else if( Root->Type == ttSub ){
		return LeftPoly.Sub( RightPoly );
	}else if( Root->Type == ttMul ){
		return LeftPoly.Mul( RightPoly );
	}else if( Root->Type == ttDer ){
		//导数 
		if ( LeftPoly.IsNull() ){
			cout << "执行错误,无明确的多项式."<<endl;
			return LeftPoly;
		}
		return LeftPoly.Derivation();
	}else if( Root->Type == ttIntArea ){
		//定积分 
		if ( RightPoly.IsNull() ){
			cout << "执行错误,定积分区间["<<Root->Lower<<","<<Root->Height<<"]无明确的多项式."<<endl;
			return RightPoly;
		}
		float coefs[1];
		coefs[0] = RightPoly.Definite_Integral( Root->Lower, Root->Height );
		Result.Initialization('0',1,coefs);
		return Result;
	}
	
	return Result;
}

void Expression::Print( Token* RootToken ){
	if( NULL == RootToken )
		return;
	
	if( NULL != RootToken->Left ){
		bool HaveBracket = false;
		if( RootToken->Left->Level < RootToken->Level && RootToken->Left->Level!=0 ){
			cout << "( ";
			HaveBracket = true;
		}
			
		Print( RootToken->Left );
		
		if( HaveBracket )
			cout << ") ";	
	}
	
	if( RootToken->Type == ttDer || RootToken->Type == ttPol || 
	    RootToken->Type == ttAdd || RootToken->Type == ttSub ||
		RootToken->Type == ttMul || RootToken->Type == ttDiv ){
		cout << RootToken->ExpressChar << " ";
	}else if( RootToken->Type == ttIntArea ){
		cout << "$[" <<RootToken->Lower<<","<<RootToken->Height<<"]";
	}else if( RootToken->Type == ttNum){
		cout << RootToken->Height<<" ";
	}
	
	if( NULL != RootToken->Right ){
		bool HaveBracket = false;
		if( RootToken->Right->Level < RootToken->Level && RootToken->Right->Level!=0 ){
			cout << "( ";
			HaveBracket = true;
		}
			
		Print( RootToken->Right );
		
		if( HaveBracket )
			cout << ") ";	
	}
}
