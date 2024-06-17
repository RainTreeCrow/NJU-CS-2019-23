package rl.huojing.dp.proxy.smartproxy;

public class Proxy implements Search {

	private RealSearcher searcher;
	private UsageLogger usageLogger;
	private AccessValidator accessValidator;
	
	public Proxy(){
		searcher = new RealSearcher();
	}
	public String doSearch(String userId, String keyValue) {
		if(checkAccess(userId)){
			String result = searcher.doSearch(userId, keyValue);
			logUsage(userId);
			return result;
		}
		else{
			return null;
		}
	}
	
	private boolean checkAccess(String userId){
		accessValidator = new AccessValidator();
		return accessValidator.validateUser(userId);
	}
	
	private void logUsage(String userId){
		usageLogger = new UsageLogger();
		usageLogger.setUserId(userId);
		usageLogger.save();
	}

}
