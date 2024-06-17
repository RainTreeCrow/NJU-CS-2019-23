package ShapeDrawer;

import java.awt.EventQueue;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JFrame;
import javax.swing.JMenuBar;

import MenuBar.AppearanceMenu;
import MenuBar.ColorMenu;
import MenuBar.EditMenu;
import MenuBar.FileMenu;
import MenuBar.ModifyMenu;
import MenuBar.ShapeMenu;
import MenuBar.TransparencyMenu;
import MenuBar.WidthMenu;
import UserInterface.WhiteBoard;

public class ShapeDrawer extends JFrame {
	
	private final String name = "基础图形绘制";
	private WhiteBoard board = new WhiteBoard();
	
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					ShapeDrawer frame = new ShapeDrawer();
					frame.setVisible(true);
				}
				catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
	
	public ShapeDrawer() {
		super();
		setName(name);
		setTitle(name + " - 未命名.shape");
		setBounds(0, 0, 1200, 600);
		setLocationRelativeTo(null);
		getContentPane().add(board);
		
		JMenuBar menuBar = new JMenuBar();
		setJMenuBar(menuBar);
		
		FileMenu fileMenu = new FileMenu(this, board);
		menuBar.add(fileMenu);
		
		EditMenu editMenu = new EditMenu(board);
		menuBar.add(editMenu);

		ShapeMenu shapeMenu = new ShapeMenu(board);
		menuBar.add(shapeMenu);
		
		ModifyMenu modifyMenu = new ModifyMenu(board);
		menuBar.add(modifyMenu);

		ColorMenu colorMenu = new ColorMenu(board);
		AppearanceMenu.setColorMenu(colorMenu);
		menuBar.add(colorMenu);

		WidthMenu thicknessMenu = new WidthMenu(board);
		AppearanceMenu.setWidthMenu(thicknessMenu);
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
