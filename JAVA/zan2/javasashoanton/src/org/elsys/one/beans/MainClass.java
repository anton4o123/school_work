package org.elsys.one.beans;

public class MainClass {

	public static void main(String[] args) {
		Farm farm = new Farm();
		for(int i = 0; i < 10; i++) {
			if ((i%2) == 0) {
				farm.addAnimal(new Horse());
				
			}
			else {
				farm.addAnimal(new Pigeon());
			}
		}
		farm.walkTheAnimals();
	}
	
	
}
