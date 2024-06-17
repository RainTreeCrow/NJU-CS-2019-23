package rl.huojing.dp.proxy.smartproxy;

public class SearcherClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Search searcher = new Proxy();
		String userId = "Admin";
		String searching = "SEARCH_BY_ACCOUNT_NUMBER";
		String result = searcher.doSearch(userId, searching);
		System.out.println(result);
	}

}
