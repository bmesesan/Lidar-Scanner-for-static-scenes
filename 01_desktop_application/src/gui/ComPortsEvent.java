package gui;

import java.util.EventObject;

import com.fazecast.jSerialComm.SerialPort;

public class ComPortsEvent extends EventObject {
	private static final long serialVersionUID = 1L;
	private SerialPort sp_buffer[];
	
	public ComPortsEvent (Object source) {
		super(source);
		sp_buffer = SerialPort.getCommPorts();
	}

	public SerialPort[] getSp_buffer() {
		return sp_buffer;
	}

	public void setSp_buffer(SerialPort[] sp_buffer) {
		this.sp_buffer = sp_buffer;
	}
}
