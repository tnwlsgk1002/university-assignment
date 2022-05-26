package employee;

public enum PositionEnum {
	DIRECTOR(21, "�̻�"),
	GENERAL_MANAGER(22, "����"),
	MENAGER(23, "����"),
	ASSISTANT_MANAGER(24, "�븮"),
	STAFF(25, "���");
	

	int code;
	String message;
	
	PositionEnum(int code, String message){
		this.code=code;
		this.message=message;
	}
	
	public int getCode() {
		return code;
	}

	public String getMessage() {
		return message;
	}	
}
