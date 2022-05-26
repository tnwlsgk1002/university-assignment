package employeeTest;
import java.util.Scanner;

import employee.EmployeeSet;
import menus.DeleteMenuEnum;
import menus.MainMenuEnum;
import menus.Menu;
import menus.RegisterMenuEnum;
import menus.SearchMenuEnum;
import menus.UpdateMenuEnum;

public class EmployeeTest {
	public static void main(String[] args) {
		Menu menu = new Menu();

		Scanner scanner = new Scanner(System.in);
		EmployeeSet set = new EmployeeSet(); // 새로 추가
		while(true) {
			MainMenuEnum mm = menu.MainMenu(scanner);
			if(mm == MainMenuEnum.REGISTER) {
				while(true) {
					RegisterMenuEnum rm = menu.RegisterMenu(scanner);
					if (rm == RegisterMenuEnum.RETURN) {
						break;
					}
					else {
						if (rm == RegisterMenuEnum.FULLTIME) {
							set.RegisterFullTimeEmp(scanner);
						}
						else if (rm == RegisterMenuEnum.PARTTIME) {
							set.RegisterPartTimeEmp(scanner);
						}
							
				    }
			   }
			}
			else if(mm == MainMenuEnum.SEARCH) {
				while(true) {
					SearchMenuEnum sm = menu.SearchMenu(scanner);
					if (sm == SearchMenuEnum.RETURN) {
						break;
					}
					else {
						if (sm == SearchMenuEnum.SEARCH) {
							set.SearchAll();
						}
						else if (sm == SearchMenuEnum.FULL_SEARCH) {
							set.SearchFull();
						}
						else if (sm == SearchMenuEnum.PART_SEARCH) {
							set.SearchPart();
						}
						else if (sm == SearchMenuEnum.NAME_SEARCH) {
							set.SearchName(scanner);
						}
					}
					
				}
			}
			
			else if (mm == MainMenuEnum.UPDATE) {
				while(true) {
					UpdateMenuEnum um = menu.UpdateMenu(scanner);
					if (um == UpdateMenuEnum.RETURN) {
						break;
					}
					else if (um == UpdateMenuEnum.UPDATE)
					{
						set.UpdateEmp(scanner);
					}
				}
				
			}
			
			else if (mm == MainMenuEnum.DELETE)
				while(true) {
					DeleteMenuEnum dm = menu.DeleteMenu(scanner);
					if (dm == DeleteMenuEnum.RETURN) {
						break;
					}
					else if (dm == DeleteMenuEnum.DELETE)
					{
						set.DeleteEmp(scanner);
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


