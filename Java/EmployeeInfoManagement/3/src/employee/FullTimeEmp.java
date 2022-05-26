package employee;

public class FullTimeEmp extends Employee {
	public PositionEnum getPos() {
		return pos;
	}

	public void setPos(PositionEnum pos) {
		this.pos = pos;
	}

	public int getGrade() {
		return grade;
	}

	public void setGrade(int grade) {
		this.grade = grade;
	}


	protected PositionEnum pos;
	protected int grade;
	
	public FullTimeEmp() {
		this.id=id;
		this.name=name;
		this.dep=dep;
		this.pos=pos;
		this.grade=grade;
			
		}


	public FullTimeEmp(int id, String name, DepartmentEnum dep, PositionEnum pos, int grade) {
		super(id, name, dep);
		this.pos=pos;
		this.grade=grade;
	}
	

	public void print() {
		System.out.println("===============");
		System.out.println("id: "+ getId());
		System.out.println("name: "+getName());
		System.out.println("department: "+ getDep().message);
		System.out.println("position: "+getPos().message);
		System.out.println("grade: "+getGrade());
	}
}
