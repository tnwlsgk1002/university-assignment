package employee;

import java.util.Scanner;
import java.util.Vector;

import utils.Utils;

public class EmployeeSet {

	int indexFullTime;
	int indexPartTime;
	
	Vector <Employee> Emp;
	
	public EmployeeSet() {
		Emp = new Vector<Employee>();
		
		indexFullTime=0;
		indexPartTime=0;
	}
	
	public void RegisterFullTimeEmp(Scanner s) {
		System.out.println(">>> ������ ��� <<<");
		
		int id = 10101 + indexFullTime;
		String name = Utils.getName(s);
		DepartmentEnum department = Utils.getDepartment(s);
		PositionEnum position = Utils.getPosition(s);
		int grade = Utils.getGrade(s);
		Emp.add(new FullTimeEmp(id, name, department, position, grade));
		indexFullTime++;
	}

	public void RegisterPartTimeEmp(Scanner s) {
		System.out.println(">>> �ӽ��� ��� <<<");
		
		int id = 50101 + indexPartTime;
		String name = Utils.getName(s);
		DepartmentEnum department = Utils.getDepartment(s);
		int hours = Utils.getHours(s);
		Emp.add(new PartTimeEmp(id, name, department, hours));
		indexPartTime++;
	}
	
	public void SearchAll() {
		for(int n=0; n<Emp.size(); n++) {
			Emp.get(n).print();
		}
	}
	// ������ �ϰ� �˻�
	public void SearchFull() {
		for (int n=0; n<Emp.size(); n++) {
			if (Emp.get(n) instanceof FullTimeEmp) {
				Emp.get(n).print();
			}
		}
	}
	// �ӽ��� �ϰ� �˻�
	public void SearchPart() {
		for (int n=0; n<Emp.size(); n++) {
			if (Emp.get(n) instanceof PartTimeEmp) {
				Emp.get(n).print();
			}
		}
	}
	// �̸� �˻�
	public boolean SearchName(Scanner s) {
		System.out.println("");
		while(true) {
		System.out.println("�˻��� �̸��� �Է��ϼ���.");
		String name = Utils.getName(s);
		String temp = null;
		for (int n=0; n<Emp.size(); n++) {
				if (name.equals(Emp.get(n).name)) {
					Emp.get(n).print();
					temp = Emp.get(n).name;
					break;
				}
		}
		
		if (temp==null){
			System.out.println("!!! �ش� �̸��� ������ �����ϴ�.");
			return false;
		}
		else
			break;
		}
		return true;
		
	}
	
	
	public void UpdateEmp(Scanner s) {
		System.out.println("");
		System.out.println("������ ������ id Ȯ���� ���� ���� �̸��� �˻��մϴ�.");
		while(true){
			while(true) {
				if (SearchName(s))
					break;
			}
			System.out.println("\n������ ������ ������ id�� �Է��ϼ���.");
			int id = Utils.getID(s);
			System.out.println("������ ������ �Է��ϼ���.");
			int index=0;
				for(int n=0;n<Emp.size();n++)
				{
					if (id==Emp.get(n).id)
					{
						index=n;
						break;
					}
					
				}
				
				if (Emp.get(index) instanceof FullTimeEmp)
				{
					String name = Utils.getName(s);
					DepartmentEnum department = Utils.getDepartment(s);
					PositionEnum position = Utils.getPosition(s);
					int grade = Utils.getGrade(s);

					Emp.set(index,new FullTimeEmp(id, name, department, position, grade));
				}
				
				if (Emp.get(index) instanceof PartTimeEmp)
				{
					String name = Utils.getName(s);
					DepartmentEnum department = Utils.getDepartment(s);
					int hours = Utils.getHours(s);

					Emp.set(index,new PartTimeEmp(id, name, department, hours));
				}
			
				System.out.println("\n==== ���� ��� ====");
				Emp.get(index).print();
				break;
			}
		}
	
	public void DeleteEmp(Scanner s){
		System.out.println("");
		System.out.println("������ ������ id Ȯ���� ���� ���� �̸��� �˻��մϴ�.");
		while(true) {
			if (SearchName(s))
				break;
		}
		System.out.println("");
		System.out.println("������ id�� �Է��ϼ���");
		int id = Utils.getID(s);
		int index=0;
		for(int n=0;n<Emp.size();n++)
		{
			if (id==Emp.get(n).id)
			{
				index=n;
				break;
			}			
		}
		System.out.println("");
		System.out.println(Emp.get(index).getName() + " �����ϰڽ��ϱ�? (1:��, 2:�ƴϿ�)");
		System.out.print("����>>> ");
		int i = s.nextInt();
		switch (i) {
		case 1:
			Emp.remove(index);
			System.out.println("�ش� ������ �����Ͽ����ϴ�.");
			break;
		case 2:
			System.out.println("�۾��� ����Ͽ����ϴ�.");
			break;
		default:
			System.out.println("��ȣ�� �߸� �Է��Ͽ����ϴ�.");
			break;
		}
		
		
	}
		
}

	
