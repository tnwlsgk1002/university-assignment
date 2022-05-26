import java.util.Scanner;

public class EmployeeTest {
	public static void main(String [] args) {
		int input;
		
		Scanner scanner = new Scanner(System.in);
		do {
			int sinput;
			input = mainMenu(scanner);
			if(input == 1) {
				do {
					sinput = registerMenu(scanner);
					if(sinput == 11) {
						System.out.println(">>> ������ ��� <<<");
					}
					else if(sinput == 12) {
						System.out.println(">>> �ӽ��� ��� <<<");
					}
				} while(sinput != 19);
			}
			else if(input == 2) {
				do {
					sinput = searchMenu(scanner);
					if(sinput == 21) {
						System.out.println(">>> �ϰ� �˻� <<<");
					}
				} while(sinput != 29);
			}

		} while(input != 9);
		scanner.close();
		
		System.out.println("Good Bye!");
	}
	
	static int mainMenu(Scanner scanner) {
		int input;

		printMainMenu();
		input = getMainMenu(scanner);
		
		return input;
	}

	static void printMainMenu() {
		System.out.println("======== Main Menu ===");
		System.out.println("  1. ���� ���");
		System.out.println("  2. ���� �˻�");
		System.out.println("  9. ���α׷� ����");
	}
	
	static int getMainMenu(Scanner scanner) {
		while (true)
		{
			System.out.print("����>>> ");
			int input = scanner.nextInt();
			if (input !=1 && input !=2 && input !=9)
			{
				System.out.println("Invalid Input, Try again");
			}
			else
			{
				return input;
			}
		}	
	}
	
	static int registerMenu(Scanner scanner) {
		int input;

		printRegisterMenu();
		input = getRegisterMenu(scanner);
		
		return input;
	}

	static void printRegisterMenu() {
		System.out.println("======== Register Menu ===");
		System.out.println("  11. ������ ���");
		System.out.println("  12. �ӽ��� ���");
		System.out.println("  19. ���ư���");
	}
	
	static int getRegisterMenu(Scanner scanner) {
		while (true)
		{
			System.out.print("����>>> ");
			int input = scanner.nextInt();
			if (input !=11 && input !=12 && input !=19)
			{
				System.out.println("Invalid Input, Try again");
			}
			else
			{
				return input;
			}
		}	
	}

	static int searchMenu(Scanner scanner) {
		int input;

		printSearchMenu();
		input = getSearchMenu(scanner);
		
		return input;
	}

	static void printSearchMenu() {
		System.out.println("======== Search Menu ===");
		System.out.println("  21. �ϰ� �˻�");
		System.out.println("  29. ���ư���");
	}
	
	static int getSearchMenu(Scanner scanner) {
		while (true)
		{
			System.out.print("����>>> ");
			int input = scanner.nextInt();
			if (input !=21 && input !=29)
			{
				System.out.println("Invalid Input, Try again");
			}
			else
			{
				return input;
			}
		}
	}
}