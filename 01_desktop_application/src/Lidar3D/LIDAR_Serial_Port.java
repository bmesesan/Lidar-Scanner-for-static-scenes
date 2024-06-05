package Lidar3D;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import com.fazecast.jSerialComm.SerialPort;

public class LIDAR_Serial_Port {
	// The chosen serial port, which will communicate with the LIDAR system
	private SerialPort sp;
	// The buffer where all the open serial ports will be stored
	private SerialPort sp_buffer[];
	// Used for transmitting data to the LIDAR system
	private OutputStream outstr;
	// Used to receive data from the LIDAR system
	private InputStream instr;

	private int stepper_resolution;
	private int stepper_max_steps;
	private int servo_angle_resolution;
	private int servo_max_angle;
	private int servo_start_position;
	private int lidar_config;
	
	public boolean portIsOpen = false;

	BufferedWriter writer1;
	BufferedWriter writer2;
	BufferedWriter writer3;

	String path1;
	String path2;
	String path3;

	public LIDAR_Serial_Port() throws IOException {
		// Makes the
		path1 = new String();
		path2 = new String();
		path3 = new String();

		stepper_resolution = 8;
		stepper_max_steps = 1024;
		servo_angle_resolution = 3;
		servo_max_angle = -120;
		servo_start_position = 0;
		lidar_config = 0;
	}

	public void set_Path(int num, String path) {
		if (num == 1)
			path1 = path;
		if (num == 2)
			path2 = path;
		if (num == 3)
			path3 = path;
	}

	void setup_Writer(int num) throws IOException {
		if (num == 1)
			writer1 = new BufferedWriter(new FileWriter(path1));
		if (num == 2)
			writer2 = new BufferedWriter(new FileWriter(path2));
		if (num == 3)
			writer3 = new BufferedWriter(new FileWriter(path3));
	}

	public void setup_all_Writers() throws IOException {
		writer1 = new BufferedWriter(new FileWriter(path1));
		writer2 = new BufferedWriter(new FileWriter(path2));
		writer3 = new BufferedWriter(new FileWriter(path3));
	}

	public void close_Writer(int num) throws IOException {
		if (num == 1)
			writer1.close();
		if (num == 2)
			writer2.close();
		if (num == 3)
			writer3.close();
	}

	// Store all the open COM ports in the buffer
	public void setPortsBuffer() {
		sp_buffer = SerialPort.getCommPorts();
	}

	// n is the number of the port, stored in the sp_buffer
	// also does all the necessary settings for serial communication
	public void setLidarPort(int n) {
		sp = sp_buffer[n];
		// BAUD = 78600, 8-bit frame, 1 stop bit, no parity
		sp.setComPortParameters(76800, 8, 1, 0);
		outstr = sp.getOutputStream();
		instr = sp.getInputStream();
	}

	// Displays the available Serial ports
	public void displayPorts() {
		int i;

		i = 0;
		for (SerialPort sp_aux : sp_buffer) {
			System.out.println(i++ + " " + sp_aux.getSystemPortName());
		}
	}

	// Opens the chosen COM port
	public boolean openLidarPort() throws IOException, InterruptedException {
		if (sp.openPort()) {
			System.out.println("\nPort is opened.");
			Thread.sleep(2000);
			portIsOpen = true;
			return (true);
		} else {
			System.out.println("\nPort is closed.");
			writer1.close();
			writer2.close();
			portIsOpen = false;
			return (false);
		}
	}

	// Sends the character 127 through the serial port which means start
	// communication
	public void startCommunication() throws IOException {
		sp.setComPortTimeouts(SerialPort.TIMEOUT_WRITE_BLOCKING, 0, 0);
		outstr.write(127);
		System.out.println("\nSent: " + 127);
	}

	// receives data from the LIDAR system and writes it in two files
	// when the character 127 is received, we know that the communication has ended
	public void receiveData() throws IOException {
		boolean aux = false;
		byte x[] = new byte[2];

		sp.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 0, 0);

		do {
			instr.read(x, 0, 1);
			if (x[0] != 127) {
				if (aux == false)
					writer1.write((char) x[0]);
				else
					writer2.write((char) x[0]);
				if (x[0] == '\n')
					aux = !aux;
			}
		} while (x[0] != 127);
	}

	// close the LIDAR COM port
	public void closeLidarPort() throws IOException {
		writer1.close();
		writer2.close();

		if (sp.closePort()) {
			System.out.println("\nClose port successfull!");
			portIsOpen = false;
		} else {
			System.out.println("\nClose port not successfull!");
		}
	}

	public void set_stepper_resolution(int stepper_resolution) {
		this.stepper_resolution = stepper_resolution;
	}

	public int get_stepper_resolution() {
		return (this.stepper_resolution);
	}

	public void set_stepper_max_steps(int stepper_max_steps) {
		this.stepper_max_steps = stepper_max_steps;
	}

	public int get_stepper_max_steps() {
		return (this.stepper_max_steps);
	}

	public void set_servo_angle_resolution(int servo_angle_resolution) {
		this.servo_angle_resolution = servo_angle_resolution;
	}

	public int get_servo_angle_resolution() {
		return (this.servo_angle_resolution);
	}

	public void set_servo_max_angle(int servo_max_angle) {
		this.servo_max_angle = servo_max_angle;
	}

	public int get_servo_max_angle() {
		return (this.servo_max_angle);
	}

	public void set_servo_start_position(int servo_start_position) {
		this.servo_start_position = servo_start_position;
	}

	public int get_servo_start_position() {
		return (this.servo_start_position);
	}

	public void set_lidar_config(int lidar_config) {
		this.lidar_config = lidar_config;
	}

	public int get_lidar_config() {
		return (lidar_config);
	}

	// returns the mirrored number of the input
	private int mirr_number(int num) {
		int val = 0;
		while (num > 0) {
			val = val * 10 + num % 10;
			num = num / 10;
		}
		return (val);
	}

	// returns the number of digits in a given number
	private int nr_cif(int num) {
		int sum = 0;

		while (num > 0) {
			sum++;
			num = num / 10;
		}

		return (sum);
	}

	private void checkSend() throws IOException {
		byte x[] = new byte[2];

		sp.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 0, 0);

		do {
			instr.read(x, 0, 1);
		} while (x[0] != 125);
	}
	
	public void send_char(char c) throws InterruptedException, IOException
	{
		checkSend();
		sp.setComPortTimeouts(SerialPort.TIMEOUT_WRITE_BLOCKING, 0, 0);
		outstr.write((byte)(c));
	}
	
	public void send_Integer(int num) throws IOException, InterruptedException {
		int val;
		int cif;
		// in case the number is negative
		if (num < 0) {
			send_char('-');
			num = num * (-1);
		}
		
		// in case the number ends with a 0 we need to know the number of digits it has
		cif = nr_cif(num);
		// we send the digits in reverse order
		val = mirr_number(num);

		while (val > 0) {
			// write digit by digit
			send_char((char) (val % 10 + 48));
			val = val / 10;
			cif--;
		}
		if (cif > 0 || num == 0) {
			// case in which the original number ends with a '0' digit, we send out one more
			// '0'
			send_char('0');
			if (cif > 0)
				cif--;
			while (cif > 0) {
				send_char('0');
				cif--;
			}
		}
	}
	
	public void send_parameters() throws IOException, InterruptedException {
		sp.setComPortTimeouts(SerialPort.TIMEOUT_WRITE_BLOCKING, 0, 0);
		outstr.write(126);
		System.out.println("\nSent: " + 126);
		
		send_Integer(stepper_resolution);
		send_char(' ');
		System.out.println("\nStepper resolution: " + stepper_resolution);
		
		send_Integer(stepper_max_steps);
		send_char(' ');
		System.out.println("\nStepper_max_steps: " + stepper_max_steps);
		
		send_Integer(servo_angle_resolution);
		send_char(' ');
		System.out.println("\nServo_angle_resolution: " + servo_angle_resolution);
		
		send_Integer(servo_max_angle);
		send_char(' ');
		System.out.println("\nServo_max_angle: " + servo_max_angle);
		
		send_Integer(servo_start_position);
		send_char(' ');
		System.out.println("\nServo_start_position: " + servo_start_position);
		
		send_Integer(lidar_config);
		send_char(' ');
		System.out.println("\nLidar_config: " + lidar_config);
		
		send_char((char)(126));
		System.out.println("\nSent: " + 126);
	}
	
	public void write_parameters() throws IOException {
		writer3.write(Integer.toString(this.stepper_resolution) + " ");
		writer3.write(Integer.toString(this.stepper_max_steps) + " ");
		writer3.write(Integer.toString(this.servo_angle_resolution) + " ");
		writer3.write(Integer.toString(this.servo_max_angle) + " ");
		writer3.write(Integer.toString(this.servo_start_position) + " ");
		writer3.write(Integer.toString(this.lidar_config));
	}
}
