package gui;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.border.Border;

public class FormPanel extends JPanel {
	private static final long serialVersionUID = 1L;
	private JLabel StepperAngleResolutionLabel;
	private JLabel MaxStepperStepsLabel;
	private JLabel ServoAngleResolutionLabel;
	private JLabel MaxServoStepsLabel;
	private JLabel ServoStartPositionLabel;
	private JLabel LidarConfigurationLabel;
	private JTextField ServoAngleResolutionField;
	private JTextField MaxServoStepsField;
	private JTextField ServoStartPositionField;
	private JComboBox<String> StepperAngleResolutionCombo;
	private JComboBox<String> MaxStepperStepsCombo;
	private JComboBox<String> LidarConfigurationCombo;
	private JButton setParamsBtn;
	private FormListener formListener;
	
	
	public FormPanel() {
		Dimension dim = getPreferredSize();
		dim.width = 350;
		setPreferredSize(dim);
		
		setupLabels();
		setupTextFields();
		setupComboBoxes();
		
		setParamsBtn = new JButton("Set Parameters");
		
		setParamsBtn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String StepperAngleResolution = Integer.toString((int) Math.pow(2,StepperAngleResolutionCombo.getSelectedIndex()));
				String  MaxStepperSteps = Integer.toString((int) Math.pow(2,MaxStepperStepsCombo.getSelectedIndex() + 8));
				String ServoAngleResolution;
				String MaxServoSteps;
				String ServoStartPosition;
				if (ServoAngleResolutionField.getText().length() == 0) {
					ServoAngleResolution = "1";
				}
				else {
					ServoAngleResolution = ServoAngleResolutionField.getText();
				}
				
				if (MaxServoStepsField.getText().length() == 0) {
					MaxServoSteps = "-120";
				}
				else {
					MaxServoSteps = MaxServoStepsField.getText();
				}
				
				if (ServoStartPositionField.getText().length() == 0) {
					ServoStartPosition = "-10";
				}
				else {
					ServoStartPosition = ServoStartPositionField.getText();
				}
				String LidarConfiguration = Integer.toString(LidarConfigurationCombo.getSelectedIndex());
				
				FormEvent ev = new FormEvent(this, 
						StepperAngleResolution,
						MaxStepperSteps,
						ServoAngleResolution,
						MaxServoSteps,
						ServoStartPosition,
						LidarConfiguration);
				
				if (formListener != null)
				{
					formListener.formEventOccurred(ev);
				}
			}
		});
		
		Border innerBorder = BorderFactory.createTitledBorder("Scan Parameters");
		Border outerBorder = BorderFactory.createEmptyBorder(5, 5, 5, 5);
		setBorder(BorderFactory.createCompoundBorder(outerBorder, innerBorder));
		
		layoutComponents();
	}
	
	public void setupLabels() {
		StepperAngleResolutionLabel = new JLabel("Yawn Angle Resolution: ");
		MaxStepperStepsLabel = new JLabel("Maximum yawn Steps: ");
		ServoAngleResolutionLabel = new JLabel("Pitch Angle Resolution: ");
		MaxServoStepsLabel = new JLabel("Maximum Pitch Angle: ");
		ServoStartPositionLabel = new JLabel("Pitch Start position: ");
		LidarConfigurationLabel = new JLabel("Lidar Configuration: ");
	}
	
	public void setupTextFields() {
		ServoAngleResolutionField = new JTextField(5);
		MaxServoStepsField = new JTextField(5);
		ServoStartPositionField = new JTextField(5);
	}
	
	public void setupComboBoxes() {
		StepperAngleResolutionCombo = new JComboBox<String>();
		DefaultComboBoxModel<String> StepperAngleResolutionModel = new DefaultComboBoxModel<String>();
		StepperAngleResolutionModel.addElement("0.087");
		StepperAngleResolutionModel.addElement("0.175");
		StepperAngleResolutionModel.addElement("0.351");
		StepperAngleResolutionModel.addElement("0.703");
		StepperAngleResolutionModel.addElement("1.406");
		StepperAngleResolutionCombo.setModel(StepperAngleResolutionModel);
		
		MaxStepperStepsCombo = new JComboBox<String>();
		DefaultComboBoxModel<String> MaxStepperStepsComboModel = new DefaultComboBoxModel<String>();
		MaxStepperStepsComboModel.addElement("22.5");
		MaxStepperStepsComboModel.addElement("45");
		MaxStepperStepsComboModel.addElement("90");
		MaxStepperStepsComboModel.addElement("180");
		MaxStepperStepsComboModel.addElement("360");
		MaxStepperStepsCombo.setModel(MaxStepperStepsComboModel);
		
		LidarConfigurationCombo = new JComboBox<String>();
		DefaultComboBoxModel<String> LidarConfigurationComboModel = new DefaultComboBoxModel<String>();
		LidarConfigurationComboModel.addElement("Default mode");
		LidarConfigurationComboModel.addElement("Short range, high speed");
		LidarConfigurationComboModel.addElement("Default range, higher speed");
		LidarConfigurationComboModel.addElement("Maximum range");
		LidarConfigurationComboModel.addElement("High sensitivity detection");
		LidarConfigurationComboModel.addElement("Low sensitivity detection");
		LidarConfigurationCombo.setModel(LidarConfigurationComboModel);
	}
	
	public void layoutComponents() {
setLayout(new GridBagLayout());
		
		GridBagConstraints gc = new GridBagConstraints();
		
		
		///////// -First Row- ////////
		gc.gridy = 0;
		gc.weightx = 1;
		gc.weighty = 0.1;
		
		gc.gridx = 0;
		gc.fill = GridBagConstraints.NONE;
		
		gc.anchor = GridBagConstraints.LINE_END;
		gc.insets = new Insets(0, 0, 0, 5);
		add(StepperAngleResolutionLabel, gc);
		gc.gridx = 1;
		gc.anchor = GridBagConstraints.LINE_START;
		gc.insets = new Insets(0, 0, 0, 0);
		add(StepperAngleResolutionCombo, gc);
		
		///////// -Next Row- ////////
		gc.gridy++;
		
		gc.gridx = 0;
		gc.anchor = GridBagConstraints.LINE_END;
		gc.insets = new Insets(0, 0, 0, 5);
		add(MaxStepperStepsLabel, gc);
		gc.gridx = 1;
		gc.anchor = GridBagConstraints.LINE_START;
		gc.insets = new Insets(0, 0, 0, 0);
		add(MaxStepperStepsCombo, gc);
		
		///////// -Next Row- ////////
		gc.gridy++;
		
		gc.gridx = 0;
		gc.anchor = GridBagConstraints.LINE_END;
		gc.insets = new Insets(0, 0, 0, 5);
		add(ServoAngleResolutionLabel, gc);
		gc.gridx = 1;
		gc.anchor = GridBagConstraints.LINE_START;
		gc.insets = new Insets(0, 0, 0, 0);
		add(ServoAngleResolutionField, gc);
		
		///////// -Next Row- ////////
		gc.gridy++;
		
		gc.gridx = 0;
		gc.anchor = GridBagConstraints.LINE_END;
		gc.insets = new Insets(0, 0, 0, 5);
		add(MaxServoStepsLabel, gc);
		gc.gridx = 1;
		gc.anchor = GridBagConstraints.LINE_START;
		gc.insets = new Insets(0, 0, 0, 0);
		add(MaxServoStepsField, gc);
		
		///////// -Next Row- ////////
		gc.gridy++;
		
		gc.gridx = 0;
		gc.anchor = GridBagConstraints.LINE_END;
		gc.insets = new Insets(0, 0, 0, 5);
		add(ServoStartPositionLabel, gc);
		gc.gridx = 1;
		gc.anchor = GridBagConstraints.LINE_START;
		gc.insets = new Insets(0, 0, 0, 0);
		add(ServoStartPositionField, gc);
		
		///////// -Next Row- ////////
		gc.gridy++;
		
		gc.gridx = 0;
		gc.anchor = GridBagConstraints.LINE_END;
		gc.insets = new Insets(0, 0, 0, 5);
		add(LidarConfigurationLabel, gc);
		gc.gridx = 1;
		gc.anchor = GridBagConstraints.LINE_START;
		gc.insets = new Insets(0, 0, 0, 0);
		add(LidarConfigurationCombo, gc);
		
		///////// -Next Row- ////////
		gc.gridy++;
		
		gc.weightx = 1;
		gc.weighty = 1;
		gc.gridx = 0;
		gc.anchor = GridBagConstraints.FIRST_LINE_END;
		add(setParamsBtn, gc);
		
	}
	
	public void setFormListener(FormListener listener) {
		this.formListener = listener;
	}
}
