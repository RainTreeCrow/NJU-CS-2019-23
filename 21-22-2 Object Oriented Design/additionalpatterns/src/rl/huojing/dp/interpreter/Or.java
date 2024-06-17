package rl.huojing.dp.interpreter;

public class Or extends Expression {

	private Expression left, right;
	
	public Or(Expression left, Expression right){
		this.left = left;
		this.right = right;
	}
	
	@Override
	public boolean equals(Object o) {
		if(o!=null && o instanceof Or){
			return this.left.equals(((Or)o).left)&& 
			         this.right.equals(((Or)o).right);
		}
		return false;
	}

	@Override
	public int hashCode() {
		return (this.toString()).hashCode();
	}

	@Override
	public boolean interpret(Context cxt) {
		return left.interpret(cxt) || right.interpret(cxt);
	}

	@Override
	public String toString() {
		return "("+left.toString()+" OR "+right.toString()+")";
	}

}
