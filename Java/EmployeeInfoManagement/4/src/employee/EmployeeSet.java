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
		System.out.println(">>> 정규직 등록 <<<");
		
		int id = 10101 + indexFullTime;
		String name = Utils.getName(s);
		DepartmentEnum department = Utils.getDepartment(s);
		PositionEnum position = Utils.getPosition(s);
		int grade = Utils.getGrade(s);
		Emp.add(new FullTimeEmp(id, name, department, position, grade));
		indexFullTime++;
	}

	public void RegisterPartTimeEmp(Scanner s) {
		System.out.println(">>> 임시직 등록 <<<");
		
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
	// 정규직 일괄 검색
	public void SearchFull() {
		for (int n=0; n<Emp.size(); n++) {
			if (Emp.get(n) instanceof FullTimeEmp) {
				Emp.get(n).print();
			}
		}
	}
	// 임시직 일괄 검색
	public void SearchPart() {
		for (int n=0; n<Emp.size(); n++) {
			if (Emp.get(n) instanceof PartTimeEmp) {
				Emp.get(n).print();
			}
		}
	}
	// 이름 검색
	public boolean SearchName(Scanner s) {
		System.out.println("");
		while(true) {
		System.out.println("검색할 이름을 입력하세요.");
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
			System.out.println("!!! 해당 이름의 직원이 없습니다.");
			return false;
		}
		else
			break;
		}
		return true;
		
	}
	
	
	public void UpdateEmp(Scanner s) {
		System.out.println("");
		System.out.println("갱신할 직원의 id 확인을 위해 직원 이름을 검색합니다.");
		while(true){
			while(true) {
				if (SearchName(s))
					break;
			}
			System.out.println("\n정보를 갱신할 직원의 id를 입력하세요.");
			int id = Utils.getID(s);
			System.out.println("갱신할 정보를 입력하세요.");
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
			
				System.out.println("\n==== 갱신 결과 ====");
				Emp.get(index).print();
				break;
			}
		}
	
	public void DeleteEmp(Scanner s){
		System.out.println("");
		System.out.println("삭제할 직원의 id 확인을 위해 직원 이름을 검색합니다.");
		while(true) {
			if (SearchName(s))
				break;
		}
		System.out.println("");
		System.out.println("삭제할 id를 입력하세요");
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
		System.out.println(Emp.get(index).getName() + " 삭제하겠습니까? (1:예, 2:아니오)");
		System.out.print("선택>>> ");
		int i = s.nextInt();
		switch (i) {
		case 1:
			Emp.remove(index);
			System.out.println("해당 직원을 삭제하였습니다.");
			break;
		case 2:
			System.out.println("작업을 취소하였습니다.");
			break;
		default:
			System.out.println("번호를 잘못 입력하였습니다.");
			break;
		}
		
		
	}
		
}

	
