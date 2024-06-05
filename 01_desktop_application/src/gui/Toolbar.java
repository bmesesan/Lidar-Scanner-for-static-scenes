package gui;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JPanel;

import com.fazecast.jSerialComm.SerialPort;

public class Toolbar extends JPanel {
	private static final long serialVersionUID = 1L;
	private JButton ScanPortsBtn;
	public JComboBox<String> PortsCombo;
	private JButton OpenBtn;
	private JButton CloseBtn;
	private JButton ScanBtn;
	
	private ComPortsListener portsListener;
	private OpenPortListener openPortListener;
	private ClosePortListener closePortListener;
	private StartScanListener startScanListener;

	public Toolbar() {
		setBorder(BorderFactory.createEtchedBorder());
		
		ScanPortsBtn = new JButton("Scan Ports");
		PortsCombo = new JComboBox<String>();
		OpenBtn = new JButton("Open Port");
		CloseBtn = new JButton("Close Port");
		ScanBtn = new JButton("Start Scan");

		ScanPortsBtn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ComPortsEvent ev = new ComPortsEvent(this);
				portsListener.ComPortsEventOccured(ev);
			}
		});
		
		OpenBtn.addActionListener(new ActionListener() {
			JComboBox<String> auxCombo = PortsCombo;
			
			public void actionPerformed(ActionEvent e) {
				OpenPortEvent ev = new OpenPortEvent(this, auxCombo);
				openPortListener.OpenPortEventOccurred(ev);
			}
		});
		
		CloseBtn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				closePortListener.ClosePort();
			}
		});
		ScanBtn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				startScanListener.StartScanEventOccurred();
			}
		});

		setLayout(new FlowLayout(FlowLayout.LEFT));
		add(ScanPortsBtn);
		add(PortsCombo);
		add(OpenBtn);
		add(CloseBtn);
		add(ScanBtn);
	}

	public void setPortsCombo(SerialPort sp_buffer[]) {
		DefaultComboBoxModel<String> PortsComboModel = new DefaultComboBoxModel<String>();

		for (SerialPort sp_aux : sp_buffer) {
			PortsComboModel.addElement(sp_aux.getSystemPortName());
		}
		PortsCombo.setModel(PortsComboModel);
	}

	public void setComPortsListener(ComPortsListener portsListener) {
		this.portsListener = portsListener;
	}
	
	public void setOpenPortListener(OpenPortListener openPortListener) {
		this.openPortListener = openPortListener;
	}
	
	public void setClosePortListener(ClosePortListener closePortListener) {
		this.closePortListener = closePortListener;
	}
	
	public void setStartScanListener(StartScanListener startScanListener) {
		this.startScanListener = startScanListener;
	}
}
