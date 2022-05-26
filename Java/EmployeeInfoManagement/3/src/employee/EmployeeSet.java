package employee;

import java.util.Scanner;

import utils.Utils;

public class EmployeeSet {
	final int MAX_SIZE = 100;	// 배열 길이
	Employee [] Emp;		    // 직원 배열
	int indexEmp;	           // 등록된 직원에 대한 인원 수 
	int indexFullTime;
	int indexPartTime;
	
	public EmployeeSet() {
		Emp = new Employee[MAX_SIZE];
		
		indexEmp = 0;
		indexFullTime=0;
		indexPartTime=0;
	}
	
	public void RegisterFullTimeEmp(Scanner s) {
		System.out.println(">>> 정규직 등록 <<<");
		
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
		System.out.println(">>> 임시직 등록 <<<");
		
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
	// 정규직 일괄 검색
	public void SearchFull() {
		for (int n=0; n<indexEmp; n++) {
			if (Emp[n] instanceof FullTimeEmp) {
				Emp[n].print();
			}
		}
	}
	// 임시직 일괄 검색
	public void SearchPart() {
		for (int n=0; n<indexEmp; n++) {
			if (Emp[n] instanceof PartTimeEmp) {
				Emp[n].print();
			}
		}
	}
	// 이름 검색
	public void SearchName(Scanner s) {
		while(true) {
		System.out.println("검색할 이름을 입력하세요.");
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
			System.out.println("!!! 해당 이름의 직원이 없습니다.");
		}
		else
			break;
		}
		
	}
	
	public void UpdateEmp(Scanner s) {
		System.out.println("갱신할 직원의 id 확인을 위해 직원 이름을 검색합니다.");
		while(true){
			SearchName(s);
			System.out.println("정보를 갱신할 직원의 id를 입력하세요.");
			int id = Utils.getID(s);
			System.out.println("\n갱신할 정보를 입력하세요.");
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
			
				System.out.println("\n==== 갱신 결과 ====");
				Emp[index].print();
				break;
			}
		}
		
	}
	
