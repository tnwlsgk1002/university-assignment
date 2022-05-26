package employee;

public class PartTimeEmp extends Employee {
	public int getHours() {
		return hours;
	}

	public void setHours(int hours) {
		this.hours = hours;
	}

	protected int hours;
	
	public PartTimeEmp() {
		this.id=id;
		this.name=name;
		this.dep=dep;
		this.hours=hours;
	}

	public PartTimeEmp(int id, String name, DepartmentEnum dep, int hours) {
		// 코드 작성
		super(id,name,dep);
		this.hours=hours;
	}
	
	public void print() {
		super.print();
		System.out.println("hours: "+getHours());
	}

	// setters 및 getters 정의
}
