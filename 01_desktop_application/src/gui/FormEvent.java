package gui;

import java.util.EventObject;

public class FormEvent extends EventObject {
	private static final long serialVersionUID = 1L;
	private String StepperAngleResolution;
	private String MaxStepperSteps;
	private String ServoAngleResolution;
	private String MaxServoSteps;
	private String ServoStartPosition;
	private String LidarConfiguration;
	
	public FormEvent (Object source) {
		super(source);
	}
	
	public FormEvent (Object source,
			String StepperAngleResolution,
			String MaxStepperSteps,
			String ServoAngleResolution,
			String MaxServoSteps,
			String ServoStartPosition,
			String LidarConfiguration) {
		super(source);
		
		this.StepperAngleResolution = StepperAngleResolution;
		this.MaxStepperSteps = MaxStepperSteps;
		this.ServoAngleResolution = ServoAngleResolution;
		this.MaxServoSteps = MaxServoSteps;
		this.ServoStartPosition = ServoStartPosition;
		this.LidarConfiguration = LidarConfiguration;
	}

	public String getStepperAngleResolution() {
		return StepperAngleResolution;
	}

	public void setStepperAngleResolution(String stepperAngleResolution) {
		StepperAngleResolution = stepperAngleResolution;
	}

	public String getMaxStepperSteps() {
		return MaxStepperSteps;
	}

	public void setMaxStepperSteps(String maxStepperSteps) {
		MaxStepperSteps = maxStepperSteps;
	}

	public String getServoAngleResolution() {
		return ServoAngleResolution;
	}

	public void setServoAngleResolution(String servoAngleResolution) {
		ServoAngleResolution = servoAngleResolution;
	}

	public String getMaxServoSteps() {
		return MaxServoSteps;
	}

	public void setMaxServoSteps(String maxServoSteps) {
		MaxServoSteps = maxServoSteps;
	}

	public String getServoStartPosition() {
		return ServoStartPosition;
	}

	public void setServoStartPosition(String servoStartPosition) {
		ServoStartPosition = servoStartPosition;
	}

	public String getLidarConfiguration() {
		return LidarConfiguration;
	}

	public void setLidarConfiguration(String lidarConfiguration) {
		LidarConfiguration = lidarConfiguration;
	}
	
	
}
