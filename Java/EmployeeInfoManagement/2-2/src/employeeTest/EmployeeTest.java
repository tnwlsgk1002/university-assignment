package employeeTest;
import java.util.Scanner;

import employee.EmployeeSet;

public class EmployeeTest {

	public static void main(String[] args) {
		EmployeeSet set = new EmployeeSet();

		Scanner scanner = new Scanner(System.in);

		set.RegisterFullTimeEmp(scanner);
		set.RegisterFullTimeEmp(scanner);
		set.RegisterPartTimeEmp(scanner);
		set.RegisterPartTimeEmp(scanner);
		
		set.SearchAll();

		scanner.close();
	}
}
