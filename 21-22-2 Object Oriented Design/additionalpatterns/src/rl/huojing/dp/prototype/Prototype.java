package rl.huojing.dp.prototype;

public interface Prototype {
	public Prototype getClone() throws CloneNotSupportedException;
	public void operation();
}
