package Main;
import java.util.Scanner;
import Functionality.ATM;
import Functionality.Card;

public class Simulation {
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);		
		ATM atm = new ATM();
		Card[] cards = {new Card("1234","9999","Gold", input),
						new Card("1234","1000","Basic", input)
		};
		System.out.println("START OF THE DAY. ATM's available bills:");
		atm.showAvailableBills();
		System.out.println("-----------------\nInsert first card:");
		atm.insertCard(cards[0], input);
		System.out.println("-----------------\nInsert second card:");
		atm.insertCard(cards[1], input);
		System.out.println("End of the day. Goodbye!");
		atm.showAvailableBills();
		input.close();
	}
}
