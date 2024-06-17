//designpatterns.builder.DevilBuilder.java
package designpatterns.builder;

public class DevilBuilder extends ActorBuilder {
	public void buildType() {
		actor.setType("恶魔");
	}

	public void buildSex() {
		actor.setSex("妖");
	}

	public void buildFace() {
		actor.setFace("丑陋");
	}

	public void buildCostume() {
		actor.setCostume("黑衣");
	}

	public void buildHairstyle() {
		actor.setHairstyle("光头");
	}	
}