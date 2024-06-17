package MenuBar;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.filechooser.FileNameExtensionFilter;

import UserInterface.WhiteBoard;

public class FileMenu extends AbstractMenu {
	private final FileNameExtensionFilter fileFilter =
			new FileNameExtensionFilter("基础图形文件", "shape");
	private String defaultPath = "./shapes";
	private JFileChooser fileChooser = new JFileChooser(defaultPath);
	private File file;
	private JFrame jf;
	private WhiteBoard board;
	
	private JMenuItem mi_new = new JMenuItem("新建");
	private JMenuItem mi_open = new JMenuItem("打开");
	private JMenuItem mi_save = new JMenuItem("保存");
	private JMenuItem mi_saveAs = new JMenuItem("另存为");
	private JMenuItem mi_saveAsJPG = new JMenuItem("导出图片");
	
	public FileMenu(JFrame jf, WhiteBoard board) {
		super("文件");
		this.jf = jf;
		this.board = board;
		fileChooser.setFileFilter(fileFilter);
		
		mi_new.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ifSave();
				board.clean();
				file = null;
				jf.setTitle(jf.getName() + " - 未命名.shape");
			}
		});
		add(mi_new);
		
		mi_open.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ifSave();
				if (fileChooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
					file = fileChooser.getSelectedFile();
					board.open(file.getPath());
					jf.setTitle(jf.getName() + " - " + file.getName());
				}
				board.setDefaultMode();
			}
		});
		add(mi_open);
		
		mi_save.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (file == null) {
					save();
				}
				else {
					board.save(file.getPath());
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
	
	public void ifSave() {
		if (!board.changed())
			return;
		if (JOptionPane.YES_OPTION == JOptionPane.showConfirmDialog(null, 
				"是否保存当前文件？", "提示", JOptionPane.YES_NO_OPTION)) {
			if(file == null) {
				save();
			}
			else {
				board.save(file.getPath());
			}
		}
		board.setChanged(false);
	}
	
	public void save() {
		if (fileChooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
			file = fileChooser.getSelectedFile();
			String fileName = file.getName();
			int len = fileName.length();
			if (len <= 6 || fileName.lastIndexOf(".shape") != len - 6) {
				file = new File(fileChooser.getCurrentDirectory(),
						fileName + ".shape");
			}
			if (file.exists()) {
				if (JOptionPane.YES_OPTION == JOptionPane.showConfirmDialog(
						null, "此文件已存在，是否要覆盖？", "提示",
						JOptionPane.YES_NO_CANCEL_OPTION)) {
					board.save(file.getPath());					
				}
				else {
					save();
				}
			}
			else {
				board.save(file.getPath());				
			}
			jf.setTitle(jf.getName() + " - " + file.getName());
		}
	}
	
	public void saveAsJPG() {
		JFileChooser fileChooser = new JFileChooser(defaultPath);
		FileNameExtensionFilter fileFilter =
				new FileNameExtensionFilter("JPG文件", "jpg");
		fileChooser.setFileFilter(fileFilter);
		if (fileChooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
			File file = fileChooser.getSelectedFile();
			String fileName = file.getName();
			int len = fileName.length();
			if (len <= 4 || fileName.lastIndexOf(".jpg") != len - 4) {
				file = new File(fileChooser.getCurrentDirectory(), fileName + ".jpg");
			}
			if (file.exists()) {
				if(JOptionPane.YES_OPTION == JOptionPane.showConfirmDialog(
						null, "此文件已存在，是否要覆盖？", "提示",
						JOptionPane.YES_NO_CANCEL_OPTION)) {
					board.saveAsJPG(file.getPath());					
				}
				else {
					saveAsJPG();
				}
			}
			else {
				board.saveAsJPG(file.getPath());				
			}
		}
	}
}
