package employee;

abstract class Employee {
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

	public DepartmentEnum getDep() {
		return dep;
	}

	public void setDep(DepartmentEnum dep) {
		this.dep = dep;
	}

	@Override
	public String toString() {
		return "Employee [id=" + id + ", name=" + name + ", dep=" + dep + "]";
	}

	protected int id;
	protected String name;
	protected DepartmentEnum dep;
	
	public Employee() {
		this.id=id;
		this.name=name;
		this.dep=dep;
	}
	
	public Employee(int id, String name, DepartmentEnum dep) {
		this.id=id;
		this.name=name;
		this.dep=dep;
	}
	
	abstract void print();
}
