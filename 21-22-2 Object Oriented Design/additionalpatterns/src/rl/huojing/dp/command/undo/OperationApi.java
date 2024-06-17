package rl.huojing.dp.command.undo;

public interface OperationApi {

	public double getResult();
	
	public void setResult(double result);
	
	public void add(double num);
	
	public void substract(double num);
}
