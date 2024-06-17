//designpatterns.command.calculator.Client.java
package designpatterns.command.calculator;

public class Client {
	public static void main(String args[]) {
		CalculatorForm form = new CalculatorForm();
		AbstractCommand command;
		command = new AddCommand();
		form.setCommand(command); //向发送者注入命令对象
		
		form.compute(10);
		form.compute(5);
		form.compute(10);
		form.undo();   //撤销
		form.undo();
	}
}
