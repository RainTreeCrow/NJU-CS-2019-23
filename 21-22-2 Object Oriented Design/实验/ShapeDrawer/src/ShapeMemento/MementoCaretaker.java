package ShapeMemento;

import java.util.ArrayList;

public class MementoCaretaker {
	private int currentIndex = 0;
	private ArrayList<ShapeMemento> mementolist = new ArrayList<ShapeMemento>();

	public MementoCaretaker() {
		mementolist.add(new ShapeMemento());
	}
	
	public ShapeMemento getLeftMemento() {
		ShapeMemento memento = null;
		if (currentIndex > 0) {
			memento = (ShapeMemento)mementolist.get(--currentIndex);
		}
		return memento;
	}
	
	public ShapeMemento getRightMemento() {
		ShapeMemento memento = null;
		if (currentIndex < mementolist.size() - 1) {
			memento = (ShapeMemento)mementolist.get(++currentIndex);
		}
		return memento;
	}

	public void addMemento(ShapeMemento memento) {
		int last = mementolist.size() - 1;
		for (int i = last; i > currentIndex; i--) {
			mementolist.remove(i);
		}
		mementolist.add(memento);
		currentIndex = mementolist.size() - 1;
	}
}
