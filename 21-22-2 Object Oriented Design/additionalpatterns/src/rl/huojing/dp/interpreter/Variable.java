package rl.huojing.dp.interpreter;

public class Variable extends Expression {
	
	private String name;
	
	public Variable(String name){
		this.name = name;
	}

	@Override
	public boolean equals(Object o) {
		if(o!=null && o instanceof Variable){
			return this.name.equals(((Variable)o).name);
		}
		return false;
	}

	@Override
	public int hashCode() {
		return (this.toString()).hashCode();
	}

	@Override
	public boolean interpret(Context cxt) {
		return cxt.lookup(this);
	}

	@Override
	public String toString() {
		return name;
	}

}
