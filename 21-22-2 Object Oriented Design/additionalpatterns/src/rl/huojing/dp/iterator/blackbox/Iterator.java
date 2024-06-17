package rl.huojing.dp.iterator.blackbox;

public interface Iterator {
	/**
	 * 迭代方法：移动到第一个元素
	 */
	void first();
	
	/**
	 * 迭代方法：移动到下一个元素
	 */
	void next();
	
	/**
	 * 迭代方法：是否是最后一个元素
	 * @return
	 */
	boolean isDone();
	
	/**
	 * 迭代方法：返回当前元素
	 * @return
	 */
	Object currentItem();
}
