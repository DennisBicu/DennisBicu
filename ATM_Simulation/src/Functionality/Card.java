package Functionality;

import java.util.Scanner;

public class Card {
	private String PIN;
	private String cardNumber;
	private String cardType;
	private int balance; 
	
	public Card (){}
	
	public Card (String pin, String cardNumber, String type, Scanner input){
		this.setPIN(pin, input);
		this.setCardNumber(cardNumber);
		this.setCardType(type, input);
	}
	
	//PIN getter
	public String getPIN() {
		return PIN;
	}
	
	//PIN inserter - in case the set value is != "1234"
	public String insertPIN(Scanner input){ 
		String pin;
		do{
			System.out.println("PIN is not 1234. Insert new PIN: ");
			pin = input.next();
			if (!pin.equals("1234")) 
				System.out.println ("Invalid. Try again:");
		} while (!pin.equals("1234"));
		return pin;
	}
	
	//PIN setter
	public void setPIN(String pin, Scanner input) {
		if (pin.equals("1234"))
			PIN = pin;
		else{ 
			System.out.println("Invalid PIN. Try again: ");
			PIN = this.insertPIN(input);
		}
	}
	
	//Card number getter
	public String getCardNumber() {
		return cardNumber;
	}
	
	//Card number setter
	public void setCardNumber(String cardNumber) {
			this.cardNumber = cardNumber;
	}
	
	//cardType getter 
	public String getCardType() {
		return cardType;
	}
	
	//Card type inserter - used for setter when no correct value set
	public String insertType(Scanner input){ //User to insert either 'Gold' or 'Basic' type 
		String newType;
		do{
			System.out.println("Insert card type: ");
			newType = input.next();
			if (!newType.equals("Gold") && !newType.equals("Basic")) 
				System.out.println ("Unknown. Try 'Gold' or 'Basic': ");
		} while (!newType.equals("Gold") && !newType.equals("Basic"));
		
		return newType;
	}
	
	//Card type setter
	public void setCardType(String cardType, Scanner input) {
		if (cardType.equals("Gold")){ 
			this.cardType = cardType;
			this.setBalance(1000);
		}
		else if (cardType.equals("Basic")){
			this.cardType = cardType;
			this.setBalance(500);
		}
		else{
			System.out.println("Unknown card type. Try 'Gold' or 'Basic': ");
			this.cardType = this.insertType(input);
			if (this.cardType.equals("Gold")){ 
				this.setBalance(1000);
			}
			else if (this.cardType.equals("Basic")){
				this.setBalance(500);
			}
		}
	}
	
	//Balance getter&setter
	public int getBalance() {
		return balance;
	}
	public void setBalance(int balance) {
		this.balance = balance;
	}
}
