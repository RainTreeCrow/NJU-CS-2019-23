package rl.huojing.dp.simplefactory;

public class FruitGardener {
	public static Fruit factory(String which)throws BadFruitException{
		if (which.equals("Grape")){
			return new Grape();
		}
		else if (which.equals("Apple")){
			return new Apple();
		}
		else if (which.equals("Strawberry")){
			return new Strawberry();
		}
		else{
			throw new BadFruitException("Bad fruit request");
		}
			
	}
}
