package rl.huojing.dp.proxy.smartproxy;

public class RealSearcher implements Search {

	public String doSearch(String userId, String keyValue) {
		String sql = "SELECT * FROM data_table WHERE key_col = "+keyValue+"";
		System.out.println("do searching: "+sql);
		return "result set";
	}

}
