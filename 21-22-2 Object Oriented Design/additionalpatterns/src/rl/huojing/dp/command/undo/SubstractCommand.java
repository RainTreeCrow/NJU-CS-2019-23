package rl.huojing.dp.command.undo;

public class SubstractCommand implements Command {
	
	private OperationApi operation = null;
	
	private double opeNum;
	
	public SubstractCommand(OperationApi operation, double opeNum){
		this.operation = operation;
		this.opeNum = opeNum;
	}
	
	@Override
	public void execute() {
		this.operation.substract(opeNum);
	}

	@Override
	public void undo() {
		this.operation.add(opeNum);
	}

}
