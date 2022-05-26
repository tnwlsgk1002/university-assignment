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
		super(id,name,dep);
		this.hours=hours;
	}
	
	public void print() {
		System.out.println("===============");
		System.out.println("id: "+ getId());
		System.out.println("name: "+getName());
		System.out.println("department: "+ getDep().message);
		System.out.println("hours: "+getHours());
	}

}
