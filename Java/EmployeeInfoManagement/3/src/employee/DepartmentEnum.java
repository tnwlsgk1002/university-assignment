package employee;

public enum DepartmentEnum {
	GENERAL_AFFAIR(11, "총무"),
	PERSONNEL(12, "인사"),
	PLANNING(13, "기획"),
	PRODUCTION(14, "생산"),
	SALES(15, "영업");

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
