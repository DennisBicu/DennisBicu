package Functionality;
import java.util.Scanner;

public class ATM {
	public final int RON500 = 500; //for a more clearer visualization
	public final int RON200 = 200;
	public final int RON100 = 100;
	public final int RON50 = 50;
	public final int RON20 = 20;
	public final int RON10 = 10;
	public final int RON5 = 5;
	//public int desiredAmount = 0;  
	
	public int[][] bills = { //assigning a bill's value to the number of bills available, starting with 10;
			{RON500, 10}, 
			{RON200, 10}, 
			{RON100, 10}, 
			{RON50, 10}, 
			{RON20, 10}, 
			{RON10, 10}, 
			{RON5, 10}
	}; 
	
	public ATM(){};
	
	//Method to display the available number of bills
	public void showAvailableBills(){
		for (int i = 0; i < 7; i++){
			System.out.println("Bill: " + bills[i][0] + ", Quantity: " + bills[i][1]);
		}
		System.out.println("=> ATM funds: " + this.fundsATM() + "RON");
	}
	
	//Method which shows the funds of the ATM
	public int fundsATM(){
		int funds = 0;
		for (int i = 0; i < 7; i++){
			funds = funds + bills[i][0] * bills[i][1]; 
		}
		return funds;
	}
	
	//Core method of the ATM
	public void insertCard(Card card, Scanner input){ 
		this.checkCard(card, input);
		String next = "Y"; //variable which determines whether the process continues or stops
		do {
			System.out.println("Select operation: 1 - 'Check Balance', 2 - 'Withdraw Cash'");
			this.selectOperation(input.nextInt(), card, input); //Keyboard input for selecting the operation
			
			System.out.println("Do you want to do another operation? (Y/N)");
			next = input.next(); //Keyboard input for continuing the operations
		} while (!next.equals("N"));
		System.out.println("Wait for the card to be ejected... \nThank you for using this ATM. Have a nice day!\n----------------");
		
	}
	
	//Method which deals with the operation chosen
	public void selectOperation(int answer, Card card, Scanner input){ 
		switch (answer){
			case 1: {
				System.out.println("Your card's current balance is: " + card.getBalance());
				break;
			}
			case 2:{ 
				System.out.println("Withdraw operation started. \nEnter desired amount (multiple of 10): ");
				int auxAmount = 0;
				int desiredAmount = this.insertAmount(auxAmount, card, input);
				card.setBalance(card.getBalance()-desiredAmount);
				int i = 0;
				while (i < 7){
					if (desiredAmount == 0){
						System.out.println("Withdraw operation completed.");
						break;
					}
					//The ATM tries to use the biggest bills, in DESC order (if there are any of that type left)
					if (desiredAmount >= bills[i][0] && bills[i][1] > 0){
						desiredAmount = desiredAmount - bills[i][0];
						if (bills[i][1] > 0) bills[i][1]--;
					}
					else i++;
				}
				break;
			}
		
			default:{
				System.out.println("Invalid operation. Try 1 - 'Check Balance' or 2 - 'Withdraw Cash'");
				break;
			}
		}
	}
	
	//Method for checking the card infos (PIN, number)
	public void checkCard(Card card, Scanner input){
		String number = null;
		do {
			System.out.println("Insert card number:");
			number = input.next();
			if(!number.equals(card.getCardNumber()))
				System.out.println("Invalid card number. Try again: ");
			} while (!number.equals(card.getCardNumber()));
		
		System.out.println("Correct card number. Insert PIN: ");
		String pin = null;
		int counter = 0; //counting no. of PIN insert trials (max. 3)
		do {
			pin = input.next();
			if(!pin.equals("1234")){
					//checking if the PIN is inserted incorrectly too many times times
					counter++;
					if (counter == 3){ 
						System.out.println("Incorrect PIN. ATM Blocked. Goodbye!");
						System.exit(-1);
					}
					System.out.println("Invalid PIN. Try again: ");
				}
			
			} while (!pin.equals("1234"));
		System.out.println("Correct PIN.");
	}
	
	//Method for inserting the correct amount to withdraw
	public int insertAmount(int desiredAmount, Card card, Scanner input){
		do {
			desiredAmount = input.nextInt();
			if(desiredAmount % 10 != 0 ||  desiredAmount == 0){
				System.out.println("Invalid amount. Try a multiple of 10 (e.g. 200, 100, etc.):");
				continue;
			}
			if (desiredAmount > this.fundsATM()){
				System.out.println("Insufficient ATM funds. Try a smaller amount of RON:");
				continue;
			}
			if (desiredAmount > card.getBalance()){
				System.out.println("Insufficient card funds! Try a smaller amount of RON:");
				continue;
			}
		}while(desiredAmount % 10 != 0 || desiredAmount > this.fundsATM() || desiredAmount > card.getBalance());
		
		return desiredAmount;
	}
	
}
