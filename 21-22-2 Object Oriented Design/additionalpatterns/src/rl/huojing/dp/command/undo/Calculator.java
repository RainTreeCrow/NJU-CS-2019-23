package rl.huojing.dp.command.undo;

import java.util.ArrayList;
import java.util.List;

public class Calculator {

	private List<Command> undoCmds = new ArrayList<Command>();
	private List<Command> redoCmds = new ArrayList<Command>();
	
	private Command addCmd = null;
	private Command substractCmd = null;
	
	public void setAddCmd(Command addCmd){
		this.addCmd = addCmd;
	}
	
	public void setSubstractCmd(Command substractCmd){
		this.substractCmd = substractCmd;
	}
	
	public void addPressed(){
		this.addCmd.execute();
		undoCmds.add(this.addCmd);
	}
	
	public void substractPressed(){
		this.substractCmd.execute();
		undoCmds.add(this.substractCmd);
	}
	
	public void undoPressed(){
		if(this.undoCmds.size()>0){
			Command cmd = this.undoCmds.get(undoCmds.size()-1);
			cmd.undo();
			this.redoCmds.add(cmd);
			this.undoCmds.remove(cmd);
		}
		else{
			System.out.println("sorry, no command to be undo");
		}
	}
	
	public void redoPressed(){
		if(this.redoCmds.size()>0){
			Command cmd = this.redoCmds.get(redoCmds.size()-1);
			cmd.execute();
			this.undoCmds.add(cmd);
			this.redoCmds.remove(cmd);
		}
		else{
			System.out.println("sorry, no command to be redo");
		}
	}
}
