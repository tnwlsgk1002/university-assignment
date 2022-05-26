package menus;

public enum UpdateMenuEnum {
	UPDATE(31, "직원 정보 갱신(by id)"),
	RETURN(39, "돌아가기");

	int code;
	String message;
	
	UpdateMenuEnum(int code, String message) {
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
