package employee;

import java.util.Scanner;

import utils.Utils;

public class EmployeeSet {
	final int MAX_SIZE = 100;	// �迭 ����
	Employee [] Emp;		    // ���� �迭
	int indexEmp;	           // ��ϵ� ������ ���� �ο� �� 
	int indexFullTime;
	int indexPartTime;
	
	public EmployeeSet() {
		Emp = new Employee[MAX_SIZE];
		
		indexEmp = 0;
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

		Emp[indexEmp] = new FullTimeEmp(id, name, department, position, grade);
		indexEmp++;
		indexFullTime++;
	}

	public void RegisterPartTimeEmp(Scanner s) {
		System.out.println(">>> �ӽ��� ��� <<<");
		
		int id = 50101 + indexPartTime;
		String name = Utils.getName(s);
		DepartmentEnum department = Utils.getDepartment(s);
		int hours = Utils.getHours(s);

		Emp[indexEmp] = new PartTimeEmp(id, name, department, hours);
		indexEmp++;
		indexPartTime++;
	}
	
	public void SearchAll() {
		for(int n=0; n<indexEmp; n++) {
			Emp[n].print();
		}
	}
	// ������ �ϰ� �˻�
	public void SearchFull() {
		for (int n=0; n<indexEmp; n++) {
			if (Emp[n] instanceof FullTimeEmp) {
				Emp[n].print();
			}
		}
	}
	// �ӽ��� �ϰ� �˻�
	public void SearchPart() {
		for (int n=0; n<indexEmp; n++) {
			if (Emp[n] instanceof PartTimeEmp) {
				Emp[n].print();
			}
		}
	}
	// �̸� �˻�
	public void SearchName(Scanner s) {
		while(true) {
		System.out.println("�˻��� �̸��� �Է��ϼ���.");
		String name = Utils.getName(s);
		String temp = null;
		for (int n=0; n<indexEmp; n++) {
				if (name.equals(Emp[n].name)) {
					Emp[n].print();
					temp = Emp[n].name;
					break;
				}
		}
		
		if (temp==null){
			System.out.println("!!! �ش� �̸��� ������ �����ϴ�.");
		}
		else
			break;
		}
		
	}
	
	public void UpdateEmp(Scanner s) {
		System.out.println("������ ������ id Ȯ���� ���� ���� �̸��� �˻��մϴ�.");
		while(true){
			SearchName(s);
			System.out.println("������ ������ ������ id�� �Է��ϼ���.");
			int id = Utils.getID(s);
			System.out.println("\n������ ������ �Է��ϼ���.");
			int index=0;
		//	if (10101 <=id && id < 50101)
		//	{
				for(int n=0;n<indexEmp;n++)
				{
					if (id==Emp[n].id)
					{
						index=n;
						break;
					}
					
				}
				
				if (Emp[index] instanceof FullTimeEmp)
				{
					String name = Utils.getName(s);
					DepartmentEnum department = Utils.getDepartment(s);
					PositionEnum position = Utils.getPosition(s);
					int grade = Utils.getGrade(s);

					Emp[index] = new FullTimeEmp(id, name, department, position, grade);
				}
				
				if (Emp[index] instanceof PartTimeEmp)
				{
					String name = Utils.getName(s);
					DepartmentEnum department = Utils.getDepartment(s);
					int hours = Utils.getHours(s);

					Emp[index] = new PartTimeEmp(id, name, department, hours);
				}
			
				System.out.println("\n==== ���� ��� ====");
				Emp[index].print();
				break;
			}
		}
		
	}
	
