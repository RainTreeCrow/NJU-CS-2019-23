package rl.huojing.dp.command.undo;

public class AddCommand implements Command {

	private OperationApi operation = null;
	
	private double opeNum;
	
	public AddCommand(OperationApi operation, double opeNum){
		this.operation = operation;
		this.opeNum = opeNum;
	}
	
	@Override
	public void execute() {
		this.operation.add(opeNum);
	}

	@Override
	public void undo() {
		this.operation.substract(opeNum);
	}

	

}
