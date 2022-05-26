package 일이단계;
import java.util.Scanner;

class Employee {
	private int id;
	public int getId() {
		return id;
	}


	public void setId(int id) {
		this.id = id;
	}


	public String getName() {
		return name;
	}


	public void setName(String name) {
		this.name = name;
	}


	public String getDept() {
		if (dept ==11)
			return "총무";
		else if (dept == 12)
			return "인사";
		else if (dept == 13)
			return "기획";
		else if (dept == 14)
			return "생산";
		else
			return "영업";
	}


	public void setDept(int dept) {
		this.dept = dept;
	}


	public String getPosition() {
		if (position == 21)
			return "이사";
		else if (position == 22)
			return "부장";
		else if (position == 23)
			return "과장";
		else if (position == 24)
			return "대리";
		else
			return "사원";
	}


	public void setPosition(int position) {
		this.position = position;
	}


	public int getGrade() {
		return grade;
	}


	public void setGrade(int grade) {
		this.grade = grade;
	}


	private String name;
	private int dept;
	private int position;
	private int grade;
	
	
	public Employee(int id, String name, int dept, int position, int grade) {
		this.id=id;
		this.name=name;
		this.dept=dept;
		this.position=position;
		this.grade=grade;
	}
	
}
