package employeeTest;

import java.util.Scanner;

import menus.Menu;
import menus.MainMenuEnum;
import menus.RegisterMenuEnum;
import menus.SearchMenuEnum;

public class EmployeeTest {

	public static void main(String[] args) {
		Menu menu = new Menu();

		Scanner scanner = new Scanner(System.in);
		while(true) {
			MainMenuEnum mm = menu.MainMenu(scanner);
			if(mm == MainMenuEnum.REGISTER) {
				System.out.println("Register");
				// ���� ��� �޴� ��� �� �Է� ó��
				while(true) {
					RegisterMenuEnum rm = menu.RegisterMenu(scanner);
					if (rm == RegisterMenuEnum.RETURN) {
						break;
					}
					else
						System.out.println(">>"+rm.getMessage()+"<<");
				}

			}
			else if(mm == MainMenuEnum.SEARCH) {
				System.out.println("Search");
				// ���� ���� ��� �޴� ��� �� �Է� ó��
				while(true) {
					SearchMenuEnum sm = menu.SearchMenu(scanner);
					if (sm == SearchMenuEnum.RETURN) {
						break;
					}
					else
						System.out.println(">>"+sm.getMessage()+"<<");
				}
			}
			else if(mm == MainMenuEnum.EXIT) {
				System.out.print("Good BYE!");
				scanner.close();
				break;
			}
		}
		
		scanner.close();
	}
}
