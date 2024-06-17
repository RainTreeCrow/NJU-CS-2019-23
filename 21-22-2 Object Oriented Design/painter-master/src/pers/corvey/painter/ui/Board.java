package pers.corvey.painter.ui;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import javax.imageio.ImageIO;
import javax.swing.JPanel;

import pers.corvey.painter.bll.pattern.Chooser;
import pers.corvey.painter.bll.pattern.Painter;
import pers.corvey.painter.bll.pattern.PatternAbs;
import pers.corvey.painter.model.shape.MyShapeItf;

/**
 * 画板（继承JPanel）
 */
public class Board extends JPanel {

	/**
	 * 记录所有图形
	 */
	private ArrayList<MyShapeItf> myShapeList = new ArrayList<MyShapeItf>();
	private Painter painter = new Painter(this);
	private Chooser chooser = new Chooser(this);
	private MyShapeItf myShape;
	
	/**
	 * 当前模式
	 */
	private PatternAbs nowPattern;
	
	public Board() {
		super();
		setFocusable(true);
		setBackground(Color.white);
	}
	
	@Override
	public void paint(Graphics g) {
		super.paint(g);
		Graphics2D g2 = (Graphics2D)g;
		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		for(MyShapeItf item : myShapeList) {
			item.applyAppearance(g2);
			g2.draw(item.getShape());
			g2.fill(item.getShape());
		}
		myShape = painter.getMyShape();
		if(myShape != null && myShape.getStartPoint() != null && myShape.getEndPoint() != null) {
			myShape.applyAppearance(g2);
			g2.draw(myShape.getShape());
		}
		g.dispose();
	}
	
	public Painter getPainter() {
		return painter;
	}

	public Chooser getChooser() {
		return chooser;
	}
	
	public ArrayList<MyShapeItf> getArrayList() {
		return myShapeList;
	}
	
	/**
	 * 切换至画笔模式
	 */
	public void ActivePainter() {
		painter.setState(true);
		chooser.setState(false);
		nowPattern = painter;
		myShape = null;
	}
	
	/**
	 * 切换至选择模式
	 */
	public void ActiveChooser() {
		chooser.setState(true);
		painter.setState(false);
		nowPattern = chooser;
		myShape = null;
	}
	
	/**
	 * 获取当前模式
	 * @return PatternAbs
	 */
	public PatternAbs getNowPattern() {
		return nowPattern;
	}
	
	/**
	 * 清屏
	 */
	public void clean() {
		myShapeList.clear();
		repaint();
	}
	
	/**
	 * 保存数据为源文件
	 * @param path - 文件路径
	 */
	public void save(String path) {
		try {
			ObjectOutputStream os = new ObjectOutputStream(new FileOutputStream(path));
			os.writeObject(myShapeList);
			os.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * 打开源文件
	 * @param path - 文件路径
	 */
	public void open(String path) {
		try {
			ObjectInputStream is = new ObjectInputStream(new FileInputStream(path));
			myShapeList = (ArrayList<MyShapeItf>) is.readObject();
			repaint();
			is.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	/**
	 * 保存当前画板为图片
	 * @param path - 文件路径
	 */
	public void saveAsJPG(String path) {
		BufferedImage image = new BufferedImage(getWidth(), getHeight(), BufferedImage.TYPE_INT_RGB);
		paint(image.createGraphics());
		File file = new File(path);
		try {
			ImageIO.write(image, "jpg", file);
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
}
