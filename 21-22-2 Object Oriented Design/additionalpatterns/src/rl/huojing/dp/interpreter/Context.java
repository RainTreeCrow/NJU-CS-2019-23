package rl.huojing.dp.interpreter;

import java.util.HashMap;

public class Context {
	private HashMap<Variable, Boolean> map = new HashMap<Variable, Boolean>();
	
	public void assign(Variable var, boolean value){
		map.put(var, new Boolean(value));
	}
	
	public boolean lookup(Variable var) throws IllegalArgumentException{
		Boolean value = (Boolean)map.get(var);
		if(value == null){
			throw new IllegalArgumentException();
		}
		return value.booleanValue();
	}
}
