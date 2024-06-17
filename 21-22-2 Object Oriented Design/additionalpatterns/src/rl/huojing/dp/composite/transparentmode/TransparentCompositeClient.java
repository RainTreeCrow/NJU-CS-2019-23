package rl.huojing.dp.composite.transparentmode;

public class TransparentCompositeClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Graphics line = new Line();
		Graphics rect = new Rectangle();
		Graphics circle = new Circle();
		Graphics pic = new Picture();
		pic.add(line);
		pic.add(rect);
		pic.add(circle);
		pic.draw();
		
		//line.add(rect);
	}

}
