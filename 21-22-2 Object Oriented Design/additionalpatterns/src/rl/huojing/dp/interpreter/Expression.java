package rl.huojing.dp.interpreter;

/**
 * 
 * Expression ::=
 *               Expression AND Expression
 *              |Expression OR Expression
 *              |NOT Expression
 *              |Variable
 *              |Constant
 * Variable ::= �κα�ʶ��
 * Constant ::= 'true'|'false'
 *	
 */
public abstract class Expression {
	/**
	 * ��ContextΪ׼�����͸������κ�һ�����ʽ
	 * @param cxt
	 * @return
	 */
	public abstract boolean interpret(Context cxt);
	
	/**
	 * �����������ʽ�ڽṹ���Ƿ���ͬ
	 */
	public abstract boolean equals(Object o);
	
	/**
	 * ���ر��ʽ��hash code
	 */
	public abstract int hashCode();
	
	/**
	 * �����ʽת��Ϊ�ַ���
	 */
	public abstract String toString();
}
