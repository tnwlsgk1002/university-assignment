package menus;

public enum MainMenuEnum {
	REGISTER(1, "직원 등록"),
	SEARCH(2, "직원 검색"),
	UPDATE(3, "직원 갱신"),
	DELETE(4, "직원 삭제"),
	EXIT(9, "종료");
	
	int code;
	String message;
	
	MainMenuEnum(int code, String message) {
		this.code = code;
		this.message = message;
		//System.out.println("생성자 in MainMenuEnum: " + code);
	}
	
	public int getCode() {
		return code;
	}
	
	public String getMessage() {
		return message;
	}
}

