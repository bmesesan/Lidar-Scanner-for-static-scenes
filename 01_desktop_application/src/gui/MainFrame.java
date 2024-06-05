package gui;
import java.awt.BorderLayout;
import java.io.IOException;

import javax.swing.JFrame;

import Lidar3D.Files_Processor;
import Lidar3D.LIDAR_Serial_Port;

public class MainFrame extends JFrame {
	private static final long serialVersionUID = 1L;
	private TextPanel textPanel;
	private Toolbar toolbar;
	private FormPanel formPanel;
	private LIDAR_Serial_Port lidsp;
	private Files_Processor files_proc;
	
	public MainFrame() throws IOException {
		super("3D LIDAR");
		
		setLayout(new BorderLayout());
		
		setupLidar();
		setupFilesProcessor();
		toolbar = new Toolbar();
		textPanel = new TextPanel();
		formPanel = new FormPanel();
		
		toolbar.setComPortsListener(new ComPortsListener() {
			public void ComPortsEventOccured(ComPortsEvent ev) {
				textPanel.appendText("Scan Com Ports\n");
				toolbar.setPortsCombo(ev.getSp_buffer());
			}
		});
		
		toolbar.setOpenPortListener(new OpenPortListener() {
			public void OpenPortEventOccurred(OpenPortEvent ev) {
				textPanel.appendText("Open Com Port " + toolbar.PortsCombo.getSelectedItem() + "\n");
				lidsp.setPortsBuffer();
				lidsp.setLidarPort(ev.getSelectedPort());
				boolean aux = false;
				try {
					aux = lidsp.openLidarPort();
				} catch (IOException e) {
					e.printStackTrace();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				if (aux == true) {
					textPanel.appendText("Open Port Successfull\n");
				}
				else
				{
					textPanel.appendText("Open Port Fail\n");
				}
				
			}
		});
		
		toolbar.setStartScanListener(new StartScanListener() {
			public void StartScanEventOccurred() {
				if (lidsp.portIsOpen == true) {
					try {
						lidsp.setup_all_Writers();
					} catch (IOException e) {
						e.printStackTrace();
					}
					
					try {
						lidsp.write_parameters();
					} catch (IOException e2) {
						e2.printStackTrace();
					}
					
					try {
						lidsp.close_Writer(3);
					} catch (IOException e2) {
						e2.printStackTrace();
					}
					
					try {
						lidsp.startCommunication();
					} catch (IOException e) {
						e.printStackTrace();
					}
					
					try {
						lidsp.receiveData();
					} catch (IOException e) {
						e.printStackTrace();
					}
					
					try {
						lidsp.close_Writer(1);
					} catch (IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					try {
						lidsp.close_Writer(2);
					} catch (IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					try {
						files_proc.setup_Reader(1);
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					try {
						files_proc.setup_Reader(2);
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					try {
						files_proc.setup_Writer(3);
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					files_proc.set_DimBuff(4096);
					try {
						files_proc.Process_Data();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					
					try {
						files_proc.close_Reader(1);
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					try {
						files_proc.close_Reader(2);
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					try {
						files_proc.close_Writer(3);
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					
					System.out.println("\nProgram Done!");
					textPanel.appendText("Scan done!");
				}
				else {
					textPanel.appendText("Open the port before scanning!\n");
				}
			}
		});
		
		toolbar.setClosePortListener(new ClosePortListener() {
			public void ClosePort() {
				try {
					lidsp.closeLidarPort();
				} catch (IOException e) {
					e.printStackTrace();
				}
				textPanel.appendText("Com Port Closed.");
			}
		});
		
		
		formPanel.setFormListener(new FormListener() {
			public void formEventOccurred(FormEvent e) {
				setLidarParameters(e);
				
				if (lidsp.portIsOpen == true) {
					try {
						lidsp.send_parameters();
					} catch (IOException e1) {
						e1.printStackTrace();
					} catch (InterruptedException e1) {
						e1.printStackTrace();
					}
					textPanel.appendText("Scan Parameters Sent!\n");
				}
				else {
					textPanel.appendText("Open the port before sending data!\n");
				}
			}
		});
		
		add(formPanel, BorderLayout.WEST);
		add(toolbar, BorderLayout.NORTH);
		add(textPanel, BorderLayout.CENTER);
		
		setSize(700
				, 350);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setVisible(true);
	}
	
	public void setLidarParameters(FormEvent e) {
		String StepperAngleResolution = e.getStepperAngleResolution();
		String MaxStepperSteps = e.getMaxStepperSteps();
		String ServoAngleResolution = e.getServoAngleResolution();
		String MaxServoSteps = e.getMaxServoSteps();
		String ServoStartPosition = e.getServoStartPosition();
		String LidarConfiguration = e.getLidarConfiguration();
		
		lidsp.set_stepper_resolution(Integer.parseInt(StepperAngleResolution));
		lidsp.set_stepper_max_steps(Integer.parseInt(MaxStepperSteps));
		lidsp.set_servo_angle_resolution(Integer.parseInt(ServoAngleResolution));
		lidsp.set_servo_max_angle(Integer.parseInt(MaxServoSteps));
		lidsp.set_servo_start_position(Integer.parseInt(ServoStartPosition));
		lidsp.set_lidar_config(Integer.parseInt(LidarConfiguration));
		
		textPanel.appendText(Integer.parseInt(StepperAngleResolution) + "; " +
				Integer.parseInt(MaxStepperSteps) + "; " + 
				Integer.parseInt(ServoAngleResolution) + "; " + 
				Integer.parseInt(MaxServoSteps) + "; " + 
				Integer.parseInt(ServoStartPosition) + "; " + 
				Integer.parseInt(LidarConfiguration) + "\n");
	}
	
	public void setupLidar() throws IOException {
		lidsp = new LIDAR_Serial_Port();
		lidsp.set_Path(1, "D:\\Facultate\\Licenta\\Serial_Java\\file1.txt");
		lidsp.set_Path(2, "D:\\Facultate\\Licenta\\Serial_Java\\file2.txt");
		lidsp.set_Path(3, "D:\\Facultate\\Licenta\\Serial_Java\\params.txt");
	}
	
	public void setupFilesProcessor() {
		files_proc = new Files_Processor();
		files_proc.set_Path(1, "D:\\Facultate\\Licenta\\Serial_Java\\file1.txt");
		files_proc.set_Path(2, "D:\\Facultate\\Licenta\\Serial_Java\\file2.txt");
		files_proc.set_Path(3, "D:\\Facultate\\Licenta\\Serial_Java\\results.txt");
	}
}
