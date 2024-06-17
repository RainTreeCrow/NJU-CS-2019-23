package rl.huojing.dp.proxy.smartproxy;

public class UsageLogger {
	private String userId;
	
	public void setUserId(String userId){
		this.userId = userId;
	}
	
	public void save(){
		String sql = "INSERT INTO USAGE_TABLE (user_id)"+" VALUES("+userId+")";
		System.out.println("executing "+sql);
	}
	
	public void save(String userId){
		this.userId = userId;
		save();
	}
}
