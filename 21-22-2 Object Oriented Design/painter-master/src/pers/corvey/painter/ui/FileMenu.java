package pers.corvey.painter.ui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import javax.swing.JOptionPane;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.filechooser.FileNameExtensionFilter;

/**
 * 文件菜单（继承JMenu）
 */
public class FileMenu extends JMenu {
	
	private final FileNameExtensionFilter fileFilter = new FileNameExtensionFilter("几何画板文件", "graph");
	private String defaultPath = "C:\\Users\\Administrator\\Desktop";
	private JFileChooser fileChooser = new JFileChooser(defaultPath);
	private File file;
	private JFrame jf;
	private JPanel board;
	private JMenuItem mi_new = new JMenuItem("新建");
	private JMenuItem mi_open = new JMenuItem("打开");
	private JMenuItem mi_save = new JMenuItem("保存");
	private JMenuItem mi_saveAs = new JMenuItem("另存为");
	private JMenuItem mi_saveAsJPG = new JMenuItem("另存为图片");
	
	public FileMenu(JFrame jf, JPanel board) {
		super("文件");
		this.jf = jf;
		this.board = board;
		fileChooser.setFileFilter(fileFilter);
		
		mi_new.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ifSave();
			}
		});
		add(mi_new);
		
		mi_open.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(fileChooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
					file = fileChooser.getSelectedFile();
					((Board)board).open(file.getPath());
					jf.setTitle(jf.getName() + " - " + file.getName());
				}
			}
		});
		add(mi_open);
		
		mi_save.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(file == null) {
					save();
				} else {
					((Board)board).save(file.getPath());
				}
			}
		});
		add(mi_save);
		
		mi_saveAs.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				save();
			}
		});
		add(mi_saveAs);
		
		mi_saveAsJPG.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				saveAsJPG();
			}
		});
		add(mi_saveAsJPG);
	}
	
	/**
	 * 是否保存文件
	 */
	public void ifSave() {
		if(JOptionPane.YES_OPTION == JOptionPane.showConfirmDialog(null, 
				"是否保存当前文件？", "提示", JOptionPane.YES_NO_OPTION)) {
			if(file == null) {
				save();
			} else {
				((Board)board).save(file.getPath());
			}
		}
		((Board)board).clean();
		file = null;
		jf.setTitle(jf.getName() + " - 未命名.graph");
	}
	
	/**
	 * 保存文件
	 */
	public void save() {
		if(fileChooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
			file = fileChooser.getSelectedFile();
			String fileName = file.getName();
			int len = fileName.length();
			if(len <= 6 || fileName.lastIndexOf(".graph") != len - 6) {
				file = new File(fileChooser.getCurrentDirectory(), fileName + ".graph");
			}
			if(file.exists()) {
				if(JOptionPane.YES_OPTION == JOptionPane.showConfirmDialog(null, "此文件已存在，是否要覆盖？",
											"提示", JOptionPane.YES_NO_CANCEL_OPTION)) {
					((Board)board).save(file.getPath());					
				} else {
					save();
				}
			} else {
				((Board)board).save(file.getPath());				
			}
			jf.setTitle(jf.getName() + " - " + file.getName());
		}
	}
	
	/**
	 * 另存为图片
	 */
	public void saveAsJPG() {
		JFileChooser fileChooser = new JFileChooser(defaultPath);
		FileNameExtensionFilter fileFilter = new FileNameExtensionFilter("JPG文件", "jpg");
		fileChooser.setFileFilter(fileFilter);
		if(fileChooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
			File file = fileChooser.getSelectedFile();
			String fileName = file.getName();
			int len = fileName.length();
			if(len <= 4 || fileName.lastIndexOf(".jpg") != len - 4) {
				file = new File(fileChooser.getCurrentDirectory(), fileName + ".jpg");
			}
			if(file.exists()) {
				if(JOptionPane.YES_OPTION == JOptionPane.showConfirmDialog(null, "此文件已存在，是否要覆盖？",
											"提示", JOptionPane.YES_NO_CANCEL_OPTION)) {
					((Board)board).saveAsJPG(file.getPath());					
				} else {
					saveAsJPG();
				}
			} else {
				((Board)board).saveAsJPG(file.getPath());				
			}
		}
	}
}
