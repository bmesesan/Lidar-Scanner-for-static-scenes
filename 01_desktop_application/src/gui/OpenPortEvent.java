package gui;

import java.util.EventObject;

import javax.swing.JComboBox;

public class OpenPortEvent extends EventObject {
	private static final long serialVersionUID = 1L;
	public int selectedPort;
	
	public OpenPortEvent(Object source, JComboBox<String> ComPortsCombo) {
		super(source);
		selectedPort = ComPortsCombo.getSelectedIndex();
	}

	public int getSelectedPort() {
		return selectedPort;
	}

	public void setSelectedPort(int selectedPort) {
		this.selectedPort = selectedPort;
	}
}
