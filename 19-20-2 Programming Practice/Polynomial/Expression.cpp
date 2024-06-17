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

//�����﷨����->�õ��﷨�����������ظ��ڵ� 
Token* Expression::Analysis( char *ExpressionStr ){
	int Index = 0;
	int Brackets=0;			//Բ����ƥ���ֵ
	char MidExpress[128]; 		//�����м�ı��ʽ
	char Number[32];	//һ�����ֲ��ܳ���32λ 
	
	bool InBracket = false;	//�Ƿ��������� 
	bool InArea  = false;	//�Ƿ��ڶ������� 
	
	Token *AreaToken = NULL;	//����ȷ����������������� 
	Token *CurrToken = NULL; 	//��ǰָ�����е����� 
	Token *token = NULL;
	Token *RootToken = NULL; 
	
	memset( MidExpress, 0x00, sizeof( MidExpress ) ); 
	int MidExpressLength = 0;
	
	memset( Number, 0x00, sizeof( Number ) ); 
	int NumberLength = 0;

	while(ExpressionStr[Index]!='\0'){
		
		bool EffectChar = false;
		
		if( ExpressionStr[Index] == '(' ){
			//һ���ҵ������ţ������������м���ʽ
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
			//һ���ұ����ֵ�ݼ�������Ҽ�ֵΪ��˵���Ѿ�ƥ����������ţ����м���ʽ���½��� 
			Brackets--;
			if( Brackets == 0 ){
				token = Analysis( MidExpress );
				if( NULL == token ){
					Free(RootToken);		//�ͷ��Ѿ��������������� 
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
		
		//����������ڣ����������� 
		if( InBracket ){
			MidExpress[MidExpressLength++] = ExpressionStr[Index];
			Index ++;
			continue;
		}
		
		if( ExpressionStr[Index] == '$' ){
			//���붨���ֱ�ʶ,������������ƻ�û������˵���ϸ������ֻ�û��ȫ��������˱��ʽ���� 	
			if( InArea ){
				Free(RootToken);		//�ͷ��Ѿ��������������� 
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
			if( !InArea ){	//���û�ж����ֱ�ʶ,������������Ч�ַ������ʽ���� 
				Free(RootToken);	
				return NULL;
			}

			EffectChar = true;
		} 
		if( ExpressionStr[Index] == ']' ){
			if( !InArea ){	//���û�ж����ֱ�ʶ,������������Ч�ַ������ʽ���� 
				Free(RootToken);	
				return NULL;
			}

			if( NumberLength<=0 ){	//���������֣����û��˵��������ʽ���� 
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
			if( !InArea ){	//���û�ж����ֱ�ʶ,������������Ч�ַ������ʽ���� 
				Free(RootToken);	
				return NULL;
			}
			if( NumberLength<=0 ){	//���������֣����û��˵��������ʽ���� 
				Free(RootToken);	
				return NULL;
			} 
			AreaToken->Lower = atof( Number );
			NumberLength = 0;
			memset( Number, 0x00, sizeof( Number ) ); 
			EffectChar = true;
		}
		
		
		if( ExpressionStr[Index]>=48 && ExpressionStr[Index]<=57 || ExpressionStr[Index] == '.' ){
			//����,���������ַ����ڣ�һ�������ӡ������ˡ��������ţ������ţ��ո� ˵�����ֽ��� 
			Number[NumberLength++] = ExpressionStr[Index];
			EffectChar = true;
		}
		
		if( ExpressionStr[Index]>=65 && ExpressionStr[Index]<=90 ){
			
			//���ʽǰ������ǼӼ��˳� 
			if( NULL!=CurrToken && CurrToken->Type != ttAdd && CurrToken->Type != ttSub && CurrToken->Type != ttMul && CurrToken->Type != ttDiv ) {
				Free(RootToken);
				return NULL;
			}
			
			//���ʽ����,�������ʽ���� 
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
			//����ǵ������������֮ǰ�������ϼ��ڵ���Ϊ��Ҫ�����Ķ���ʽ�����������ڵ����ڵ�������� 
			if( NULL == CurrToken ){
				Free(RootToken);	
				return NULL;
			}

			if( NumberLength > 0 ){	//���ֲ����� 
				Free(RootToken);	
				return NULL;
			}

			if( NULL != AreaToken ){//������δȷ������ʽ 
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

			if( NULL != AreaToken ){//������δȷ������ʽ 
				Free(RootToken);
				return NULL;
			}

			if( NumberLength > 0 ){	//������������ 
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

			//�˳���ǰ�������һ����Ч���������������ʽ���� 
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
				while( NULL!=CurrToken->Parent && token->Level <= CurrToken->Parent->Level ){	//�ȶ����ֺ�˵���� 
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

			if( NULL != AreaToken ){//������δȷ������ʽ 
				Free(RootToken);
				return NULL;
			}
			
			if( NumberLength > 0 ){	//������������ 
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

			//�Ӽ���ǰ�������һ����Ч���������������ʽ���� 
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
				while( NULL!=CurrToken->Parent && token->Level <= CurrToken->Parent->Level ){	//�ȳ˺�ӵ���� 
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
		
		if( !EffectChar ){	//�Ƿ��ַ� 
			Free(RootToken);
			return NULL;
		}
		
		Index ++ ;	
	}
	
	//���һ�����ֻ�δ���� 
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
	
	if( NULL != AreaToken ){//������δȷ������ʽ 
		Free(RootToken);
		return NULL;
	}

	if( Brackets != 0 ){	//���Ų�ƥ�� 
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
		cout << "ִ�д���,���ʽ["<<Root->ExpressChar<<"]������."<<endl;
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
		//���� 
		if ( LeftPoly.IsNull() ){
			cout << "ִ�д���,����ȷ�Ķ���ʽ."<<endl;
			return LeftPoly;
		}
		return LeftPoly.Derivation();
	}else if( Root->Type == ttIntArea ){
		//������ 
		if ( RightPoly.IsNull() ){
			cout << "ִ�д���,����������["<<Root->Lower<<","<<Root->Height<<"]����ȷ�Ķ���ʽ."<<endl;
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
