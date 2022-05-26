package 일이단계;
import java.util.Scanner;

public class EmployeeTest {
	public static void main(String [] args) {
		EmployeeSet set = new EmployeeSet();

		Scanner scanner = new Scanner(System.in);

		set.RegisterEmp(scanner);
		set.RegisterEmp(scanner);
		set.RegisterEmp(scanner);
		
		set.SearchAll();

		scanner.close();
	}
}