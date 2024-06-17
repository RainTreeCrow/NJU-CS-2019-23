package rl.huojing.dp.composite.parentref;

public class ParentRefClient {
	public static void main(String[] args) {
		Graphics line1 = new Line();
		Graphics rect1 = new Rectangle();
		Graphics circle1 = new Circle();
		Graphics pic1 = new Picture();
		pic1.add(line1);
		pic1.add(rect1);
		pic1.add(circle1);
		Graphics line2 = new Line();
		Graphics rect2 = new Rectangle();		
		Graphics pic2 = new Picture();
		pic2.add(line2);
		pic2.add(rect2);
		pic1.add(pic2);		
		pic1.draw();
		System.out.println("---remove----");
		pic1.remove(pic2);
		pic1.draw();
	}
}
