package employee;

public enum DepartmentEnum {
	GENERAL_AFFAIR(11, "�ѹ�"),
	PERSONNEL(12, "�λ�"),
	PLANNING(13, "��ȹ"),
	PRODUCTION(14, "����"),
	SALES(15, "����");

	int code;
	String message;
	
	DepartmentEnum(int code, String message) {
		this.code = code;
		this.message = message;
	}
	
	public int getCode() {
		return code;
	}
	
	public String getMessage() {
		return message;
	}
}
