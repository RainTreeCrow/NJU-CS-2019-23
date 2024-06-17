package rl.huojing.dp.proxy.dynamicproxy;

public class PersonImpl implements Person {
	String name;
	String gender;
	String interests;
	int rate;

	@Override
	public String getName() {
		return name;
	}

	@Override
	public String getGender() {
		return gender;
	}

	@Override
	public void setName(String name) {
		this.name = name;
	}

	@Override
	public void setGender(String gender) {
		this.gender = gender;
	}

	@Override
	public void setRate(int rate) {
		this.rate = rate;
	}

	@Override
	public int getRate() {
		return rate;
	}

}
