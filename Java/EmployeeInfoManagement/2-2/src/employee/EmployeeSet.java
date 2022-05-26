package employee;

import java.util.Scanner;

import utils.Utils;

public class EmployeeSet {
	final int MAX_SIZE = 100;	// 배열 길이
	FullTimeEmp [] ftEmp;		// 정규직 직원
	PartTimeEmp [] ptEmp;		// 임시직 직원
	int indexFullTime;			// 등록된 정규직 직원에 대한 인원 수 
	int indexPartTime;			// 등록된 임시직 직원에 대한 인원 수
	
	public EmployeeSet() {
		ftEmp = new FullTimeEmp[MAX_SIZE];
		ptEmp = new PartTimeEmp[MAX_SIZE];
		
		indexFullTime = 0;
		indexPartTime = 0;
	}
	
	public void RegisterFullTimeEmp(Scanner s) {
		System.out.println("");
		System.out.println(">>> 정규직 등록 <<<");
		
		int id = 10101 + indexFullTime;
		String name = Utils.getName(s);
		DepartmentEnum department = Utils.getDepartment(s);
		PositionEnum position = Utils.getPosition(s);
		int grade = Utils.getGrade(s);

		ftEmp[indexFullTime] = new FullTimeEmp(id, name, department, position, grade);
		indexFullTime++;
	}

	public void RegisterPartTimeEmp(Scanner s) {
		System.out.println("");
		System.out.println(">>> 임시직 등록 <<<");
		
		int id = 50101 + indexPartTime;
		String name = Utils.getName(s);
		DepartmentEnum department = Utils.getDepartment(s);
		int hours = Utils.getHours(s);

		ptEmp[indexPartTime] = new PartTimeEmp(id, name, department, hours);
		indexPartTime++;
	}
	
	public void SearchAll() {
		for(int n=0; n<indexFullTime; n++) {
			ftEmp[n].print();
		}

		for(int n=0; n<indexPartTime; n++) {
			ptEmp[n].print();
		}
	}
}
