package ���̴ܰ�;
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
			return "�ѹ�";
		else if (dept == 12)
			return "�λ�";
		else if (dept == 13)
			return "��ȹ";
		else if (dept == 14)
			return "����";
		else
			return "����";
	}


	public void setDept(int dept) {
		this.dept = dept;
	}


	public String getPosition() {
		if (position == 21)
			return "�̻�";
		else if (position == 22)
			return "����";
		else if (position == 23)
			return "����";
		else if (position == 24)
			return "�븮";
		else
			return "���";
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
