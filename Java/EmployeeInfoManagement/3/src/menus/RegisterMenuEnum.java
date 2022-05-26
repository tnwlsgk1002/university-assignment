package menus;

public enum RegisterMenuEnum {
	FULLTIME(11,"정규직 등록"),
	PARTTIME(12, "임시직 등록"),
	RETURN(19,"돌아가기");
	
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
