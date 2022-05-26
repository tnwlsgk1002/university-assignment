package 일이단계;
import java.util.Scanner;

public class EmployeeSet {
	final int MAX_SIZE = 100;	// 배열 길이
	Employee [] emp;			// 직원
	int indexEmp;				// 등록된 직원에 대한 인원 수 
	
	public EmployeeSet() {
		emp = new Employee[MAX_SIZE];
		indexEmp = 0;
	}
	
	public void RegisterEmp(Scanner s) {
		System.out.println("");
		System.out.println(">>> 직원 등록 <<<");
		
		int id = 10101 + indexEmp;

		// 코드 작성
		// 이름, 부서, 직위, 호봉 입력
		System.out.print(">> name:");
		String name = s.next();
		System.out.println("== 부서 목록: 총무(11) 인사(12) 기획(13) 생산(14) 영업(15)");
		System.out.print(">> department: ");
		int dept = s.nextInt();
		System.out.println("== 직위 목록: 이사(21) 부장(22) 과장(23) 대리(24) 사원(25)");
		System.out.print(">> position: ");
		int position = s.nextInt();
		System.out.print(">> grade: ");
		int grade = s.nextInt();
		
		emp[indexEmp] = new Employee(id, name, dept, position, grade);
		indexEmp++;

		s.nextLine(); // 버퍼 비움
	}

	public void SearchAll() {
		for (int i=0; i<indexEmp;i++)
		{
			System.out.println("\n===============");
			System.out.println("id: "+emp[i].getId());
			System.out.println("name: "+emp[i].getName());
			System.out.println("department: "+emp[i].getDept());
			System.out.println("position: "+emp[i].getPosition());
			System.out.println("grade: "+emp[i].getGrade());
		}
	}
}
