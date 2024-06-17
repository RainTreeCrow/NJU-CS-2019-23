package rl.huojing.dp.command.undo;

public class Client {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		OperationApi operation = new Operation();
		AddCommand addCmd = new AddCommand(operation,5);
		SubstractCommand substractCmd = new SubstractCommand(operation,3);
		
		Calculator calculator = new Calculator();
		calculator.setAddCmd(addCmd);
		calculator.setSubstractCmd(substractCmd);
		
		calculator.addPressed();
		System.out.println("Result after add operation: "+operation.getResult());
		calculator.substractPressed();
		System.out.println("Result after substract operation: "+operation.getResult());
		
		//test undo
		calculator.undoPressed();
		System.out.println("Result after undo operation: "+operation.getResult());
		calculator.undoPressed();
		System.out.println("Result after undo operation: "+operation.getResult());
		
		//test redo
		calculator.redoPressed();
		System.out.println("Result after redo operation: "+operation.getResult());
		calculator.redoPressed();
		System.out.println("Result after redo operation: "+operation.getResult());

	}

}
