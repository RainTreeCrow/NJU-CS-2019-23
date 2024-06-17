package pers.corvey.painter;

import java.awt.EventQueue;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JPanel;
import javax.swing.UIManager;

import pers.corvey.painter.ui.AppearanceMenu;
import pers.corvey.painter.ui.Board;
import pers.corvey.painter.ui.ColorMenu;
import pers.corvey.painter.ui.FileMenu;
import pers.corvey.painter.ui.PatternMenu;
import pers.corvey.painter.ui.ShapeMenu;
import pers.corvey.painter.ui.ThicknessMenu;
import pers.corvey.painter.ui.TransparencyMenu;

/**
 * 客户端（继承JFrame）
 */
public class App extends JFrame {

	private static final long serialVersionUID = 5096147644474297857L;

	private final String name = "几何画板";
	
	/**
	 * 画板
	 */
	private JPanel board = new Board();
	
	
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					final String lookAndFeel = "com.sun.java.swing.plaf.windows.WindowsLookAndFeel";
					UIManager.setLookAndFeel(lookAndFeel);
					App frame = new App();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});	
	}

	public App() {
		super();
		setName(name);
		setTitle(name + " - 未命名.graph");
		setBounds(100, 100, 1000, 618);
		setLocationRelativeTo(null);
		
		getContentPane().add(board);
		
		JMenuBar menuBar = new JMenuBar();
		setJMenuBar(menuBar);
		
		FileMenu fileMenu = new FileMenu(this, board);
		menuBar.add(fileMenu);

		PatternMenu modelMenu = new PatternMenu(board);
		menuBar.add(modelMenu);

		ShapeMenu shapeMenu = new ShapeMenu(board);
		menuBar.add(shapeMenu);

		ColorMenu colorMenu = new ColorMenu(board);
		AppearanceMenu.setColorMenu(colorMenu);
		menuBar.add(colorMenu);

		ThicknessMenu thicknessMenu = new ThicknessMenu(board);
		AppearanceMenu.setThicknessMenu(thicknessMenu);
		menuBar.add(thicknessMenu);		

		TransparencyMenu transparencyMenu = new TransparencyMenu(board);
		AppearanceMenu.setTransparencyMenu(transparencyMenu);
		menuBar.add(transparencyMenu);
		
		this.addWindowListener(new WindowAdapter() {
			@Override
	          public void windowClosing(WindowEvent e) {
				fileMenu.ifSave();
				System.exit(0);
	          }
		});
	}
}