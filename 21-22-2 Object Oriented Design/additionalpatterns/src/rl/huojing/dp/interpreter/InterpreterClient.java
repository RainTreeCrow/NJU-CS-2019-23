package rl.huojing.dp.interpreter;

public class InterpreterClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Context cxt = new Context();
		Variable x = new Variable("x");
		Variable y = new Variable("y");
		Constant c = new Constant(true);
		cxt.assign(x, false);
		cxt.assign(y, true);
		Expression exp = new Or(new And(c,x),
		              new And(y, new Not(x)));
		System.out.println("x = "+x.interpret(cxt));
		System.out.println("y = "+y.interpret(cxt));
		System.out.println(exp.toString()+" = "+exp.interpret(cxt));
	}

}
