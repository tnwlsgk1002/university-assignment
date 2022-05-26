package menus;

public enum RegisterMenuEnum {
	FULLTIME(11,"������ ���"),
	PARTTIME(12, "�ӽ��� ���"),
	RETURN(19,"���ư���");
	
	int code;
	String message;
	
	RegisterMenuEnum(int code, String message) {
		this.code =code;
		this.message = message;
	}

	public int getCode() {
		return code;
	}
	
	public String getMessage() {
		return message;
	}

}
