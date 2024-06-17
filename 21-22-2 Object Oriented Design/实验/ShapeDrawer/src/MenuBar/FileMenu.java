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
			new FileNameExtensionFilter("����ͼ���ļ�", "shape");
	private String defaultPath = "./shapes";
	private JFileChooser fileChooser = new JFileChooser(defaultPath);
	private File file;
	private JFrame jf;
	private WhiteBoard board;
	
	private JMenuItem mi_new = new JMenuItem("�½�");
	private JMenuItem mi_open = new JMenuItem("��");
	private JMenuItem mi_save = new JMenuItem("����");
	private JMenuItem mi_saveAs = new JMenuItem("���Ϊ");
	private JMenuItem mi_saveAsJPG = new JMenuItem("����ͼƬ");
	
	public FileMenu(JFrame jf, WhiteBoard board) {
		super("�ļ�");
		this.jf = jf;
		this.board = board;
		fileChooser.setFileFilter(fileFilter);
		
		mi_new.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ifSave();
				board.clean();
				file = null;
				jf.setTitle(jf.getName() + " - δ����.shape");
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
				"�Ƿ񱣴浱ǰ�ļ���", "��ʾ", JOptionPane.YES_NO_OPTION)) {
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
						null, "���ļ��Ѵ��ڣ��Ƿ�Ҫ���ǣ�", "��ʾ",
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
				new FileNameExtensionFilter("JPG�ļ�", "jpg");
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
						null, "���ļ��Ѵ��ڣ��Ƿ�Ҫ���ǣ�", "��ʾ",
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
