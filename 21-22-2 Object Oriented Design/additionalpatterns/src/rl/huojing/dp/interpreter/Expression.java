package rl.huojing.dp.interpreter;

/**
 * 
 * Expression ::=
 *               Expression AND Expression
 *              |Expression OR Expression
 *              |NOT Expression
 *              |Variable
 *              |Constant
 * Variable ::= 任何标识符
 * Constant ::= 'true'|'false'
 *	
 */
public abstract class Expression {
	/**
	 * 以Context为准，解释给定的任何一个表达式
	 * @param cxt
	 * @return
	 */
	public abstract boolean interpret(Context cxt);
	
	/**
	 * 检验两个表达式在结构上是否相同
	 */
	public abstract boolean equals(Object o);
	
	/**
	 * 返回表达式的hash code
	 */
	public abstract int hashCode();
	
	/**
	 * 将表达式转换为字符串
	 */
	public abstract String toString();
}
