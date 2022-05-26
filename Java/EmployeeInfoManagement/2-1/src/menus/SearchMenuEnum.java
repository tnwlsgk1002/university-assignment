package menus;

public enum SearchMenuEnum {
	SEARCH(21, "�ϰ��˻�"),
	RETURN(29, "���ư���");

	int code;
	String message;
	
	SearchMenuEnum(int code, String message) {
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
