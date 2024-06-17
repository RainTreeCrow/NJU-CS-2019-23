package rl.huojing.dp.proxy.smartproxy;

public class AccessValidator {
	public boolean validateUser(String userId){
		if(userId.equals("Admin")){
			return true;
		}
		else{
			return false;
		}
	}
}
