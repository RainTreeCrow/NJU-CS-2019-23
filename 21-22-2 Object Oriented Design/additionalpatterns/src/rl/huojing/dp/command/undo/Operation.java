package rl.huojing.dp.command.undo;

public class Operation implements OperationApi {

	private double result;
	
	@Override
	public double getResult() {
		return result;
	}

	@Override
	public void setResult(double result) {
		this.result = result;
	}

	@Override
	public void add(double num) {
		result += num;
	}

	@Override
	public void substract(double num) {
		result -= num;
	}

}
