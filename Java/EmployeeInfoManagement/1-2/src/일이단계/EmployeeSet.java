package ���̴ܰ�;
import java.util.Scanner;

public class EmployeeSet {
	final int MAX_SIZE = 100;	// �迭 ����
	Employee [] emp;			// ����
	int indexEmp;				// ��ϵ� ������ ���� �ο� �� 
	
	public EmployeeSet() {
		emp = new Employee[MAX_SIZE];
		indexEmp = 0;
	}
	
	public void RegisterEmp(Scanner s) {
		System.out.println("");
		System.out.println(">>> ���� ��� <<<");
		
		int id = 10101 + indexEmp;

		// �ڵ� �ۼ�
		// �̸�, �μ�, ����, ȣ�� �Է�
		System.out.print(">> name:");
		String name = s.next();
		System.out.println("== �μ� ���: �ѹ�(11) �λ�(12) ��ȹ(13) ����(14) ����(15)");
		System.out.print(">> department: ");
		int dept = s.nextInt();
		System.out.println("== ���� ���: �̻�(21) ����(22) ����(23) �븮(24) ���(25)");
		System.out.print(">> position: ");
		int position = s.nextInt();
		System.out.print(">> grade: ");
		int grade = s.nextInt();
		
		emp[indexEmp] = new Employee(id, name, dept, position, grade);
		indexEmp++;

		s.nextLine(); // ���� ���
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
