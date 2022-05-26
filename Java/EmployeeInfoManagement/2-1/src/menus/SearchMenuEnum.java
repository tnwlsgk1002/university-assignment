package menus;

public enum SearchMenuEnum {
	SEARCH(21, "일괄검색"),
	RETURN(29, "돌아가기");

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
