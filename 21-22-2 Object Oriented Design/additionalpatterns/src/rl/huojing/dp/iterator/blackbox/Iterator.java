package rl.huojing.dp.iterator.blackbox;

public interface Iterator {
	/**
	 * �����������ƶ�����һ��Ԫ��
	 */
	void first();
	
	/**
	 * �����������ƶ�����һ��Ԫ��
	 */
	void next();
	
	/**
	 * �����������Ƿ������һ��Ԫ��
	 * @return
	 */
	boolean isDone();
	
	/**
	 * �������������ص�ǰԪ��
	 * @return
	 */
	Object currentItem();
}
