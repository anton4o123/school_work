package firstTry;

import java.util.Scanner;

public class calculate {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		
		int a=in.nextInt();
		int b=in.nextInt();
		int c=in.nextInt();
		
		double d=b*b-4*a*c;
		System.out.println(d);
		double x1=(-b-Math.sqrt(d))/(2*a);
		double x2=(-b+Math.sqrt(d))/(2*a);
		
		System.out.println(x1);
		System.out.println(x2);
	}
}
