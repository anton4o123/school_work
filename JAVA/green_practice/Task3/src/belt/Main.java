package belt;

import java.util.LinkedList;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int i=1,value;
		LinkedList<Chart> list = new LinkedList();
		while(i<10) {
			value=scan.nextInt();
			if(i%2==1) {
				list.add(new PieChart(value));
			} else {
				list.add(new BarChart(value));
			}
			i++;
		}
		
		for(Chart c : list) {
			c.print();
		}
		
		for(Chart c : list) {
			if(c instanceof PieChart) {
				((BarChart) c).anton();
			}
		}
		
		for(Chart c : list) {
			c.print();
		}
	}
}
