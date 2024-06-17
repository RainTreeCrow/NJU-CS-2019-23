package rl.huojing.dp.composite.safemode;

public class SafeCompositeClient {
	public static void main(String[] args){
		Graphics line = new Line();
		Graphics rect = new Rectangle();
		Graphics circle = new Circle();
		Picture pic = new Picture();
		Picture pic2 = new Picture();
		pic.add(line);
		pic.add(rect);
		pic.add(circle);
		System.out.println("Draw pic1:");
		pic.draw();
		pic2.add(line);
		pic2.add(pic);
		System.out.println("Draw pic2:");
		pic2.draw();
	}

}
