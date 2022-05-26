package menus;

public enum MainMenuEnum {
	REGISTER(1, "���� ���"),
	SEARCH(2, "���� �˻�"),
	UPDATE(3, "���� ����"),
	DELETE(4, "���� ����"),
	EXIT(9, "����");
	
	int code;
	String message;
	
	MainMenuEnum(int code, String message) {
		this.code = code;
		this.message = message;
		//System.out.println("������ in MainMenuEnum: " + code);
	}
	
	public int getCode() {
		return code;
	}
	
	public String getMessage() {
		return message;
	}
}

