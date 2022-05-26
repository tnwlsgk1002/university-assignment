package menus;

public enum SearchMenuEnum {
	SEARCH(21, "일괄검색"),
	FULL_SEARCH(22, "정규직 일괄 검색"),
	PART_SEARCH(23, "임시직 일괄 검색"),
	NAME_SEARCH(24, "이름 검색"),
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
