package utils;

import java.util.InputMismatchException;
import java.util.Scanner;

public class Utils {
	static public int checkInputInteger(Scanner s, String msg) {
		int n=0;
		boolean valid; // ��ȿ�� �� �Է� Ȯ��
		do {
			valid = true;
			System.out.print(msg);

			try {
				n = s.nextInt(); // ���� �Է�
			}
			catch(InputMismatchException e) { // ���� �Է� Ȯ��
				System.out.println("���� �Է��ϼ���.");
				s.next(); // �Է� ��Ʈ���� �ִ� ������ �ƴ� ��ū�� ������.
				valid = false;
			}
		} while(!valid);
		
		return n;
	}
}
