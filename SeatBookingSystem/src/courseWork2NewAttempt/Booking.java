package courseWork2NewAttempt;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;
import java.util.ArrayList;

public class Booking extends Seats {
	static Scanner sc = new Scanner(System.in);

	// Global variables
	static String choice;
	static boolean temp;
	static int count = 0;
	
	static ArrayList<Seats> seats = new ArrayList<Seats>();//Using the seats class 


	public static void fileRead() throws FileNotFoundException {
		// Making fileReader to read external txt and Scanner to read the txt as inputs
		FileReader file = new FileReader("seats.txt");
		Scanner read = new Scanner(file);

		//While loop will keep looping until there are no more line to be read in the .txt file
		while (read.hasNext()){
			seatNum = read.next();
			seatClass = read.next();
			isWindow = read.nextBoolean();
			isAisle = read.nextBoolean();
			isTable = read.nextBoolean();
			seatPrice = read.nextFloat();
			eMail = read.nextLine();

		}

	}

	public static void displayFile() throws FileNotFoundException {
		//Reading the file again manully because the using the method does not have the object saved over
		FileReader file = new FileReader("seats.txt");
		Scanner read = new Scanner(file);

		while (read.hasNext()){
			seatNum = read.next();
			seatClass = read.next();
			isWindow = read.nextBoolean();
			isAisle = read.nextBoolean();
			isTable = read.nextBoolean();
			seatPrice = read.nextFloat();
			eMail = read.nextLine();


			//Making of the Object
			Seats newSeats = new Seats(seatNum, seatClass, isWindow, isAisle, isTable, seatPrice, eMail);
			
			//Adding the object into the array
			seats.add(newSeats);
			
			//Printing out the array list using the method from the Seats class
			System.out.println(seats.get(0).toString());
		}
		
		
	}

	//This does not work properly
	public static void reservedSeat() throws FileNotFoundException {
		// reading file manually instead of using the method because the object is not
		// transferred
		FileReader file = new FileReader("seats.txt");
		Scanner read = new Scanner(file);
		while (read.hasNext()){
			seatNum = read.next();
			seatClass = read.next();
			isWindow = read.nextBoolean();
			isAisle = read.nextBoolean();
			isTable = read.nextBoolean();
			seatPrice = read.nextFloat();
			eMail = read.nextLine();


			
			Seats newSeats = new Seats(seatNum, seatClass, isWindow, isAisle, isTable, seatPrice, eMail);
			
			seats.add(newSeats);
		}
		
		//Local Variables for the reservations
		String tempSeatType2 = "";
		String seatType2 = "";
		boolean temp2 = true;

		// Asking for all the users preferences
		System.out.print("Would you like a first class, or standard class seat?[1|0]: ");
		
		//While loop in case the user inputs an invalid value
		while(temp2) {
			 tempSeatType2 = sc.nextLine();

		try {
			Integer.parseInt(tempSeatType2);//Using parseFloat to limit the allowed input characters to only float/decimal values
			if(tempSeatType2.contentEquals("1") || tempSeatType2.contentEquals("0"))
			temp2 = false;
			
		}catch(NumberFormatException e) {//Catch exception acts a validation check to see if the input is a float
			temp2 = true;
			System.out.println("Invalid input, please re-enter: ");
		}
	}
		//Changing the Integer value the user input into a seat type so that it can be compared and matched
		if(tempSeatType2.contentEquals("1")) {
		seatType2 =	tempSeatType2.replace("1", "1ST");
			
		}else {
		seatType2 =	tempSeatType2.replace("0", "STD");

		}
		
		//comparing the preference to the seats
		if(seats.toString().contains(seatType2)) {
			
		} 
			
		System.out.print("Would you like a seat by the window?[T/F] ");
		String window = sc.nextLine();
		
		if(seats.toString().contains(window)) 
			count++;
		
		
		System.out.print("Would you like a seat with a table?[Y/N] ");
		String table = sc.nextLine();

		
		
}
	
	public static void cancelSeat()throws FileNotFoundException {
		// reading file manually instead of using the method because the object is nottransferred
		FileReader file = new FileReader("seats.txt");
		Scanner read = new Scanner(file);
		
		while (read.hasNext()){
			seatNum = read.next();
			seatClass = read.next();
			isWindow = read.nextBoolean();
			isAisle = read.nextBoolean();
			isTable = read.nextBoolean();
			seatPrice = read.nextFloat();
			eMail = read.nextLine();


			
			Seats newSeats = new Seats(seatNum, seatClass, isWindow, isAisle, isTable, seatPrice, eMail);
			
			seats.add(newSeats);
		}
			//Getting the user to enter their email to check if it has been used to reserve a seat	
			System.out.println("Please enter the email you used to book your seat:");
			String eMail = sc.nextLine();	
			
			//Checking if the email that the user entered is in any of the Objects in the ArrayList
			if(seats.toString().contains(eMail)) {
				eMail = "free";//Replaces the eMail variable and replaces it with "free" indiciating that it has been cancelled
				System.out.println("The booking has been cancelled");
					
			}else {
				System.out.println("There is no seat booked under that eMail");
				
			}
				

		
	}
	

	public static void mainMenu() throws FileNotFoundException {
		System.out.println("--Seat Booking System--\n");
		System.out.println("--MAIN MENU--\n");

		System.out.println("1 - Reserve Seat\n");
		System.out.println("2 - Cancel Seat\n");
		System.out.println("3 - View Seat Reservations\n");
		System.out.println("Q - Quit\n");
		System.out.print("Pick: ");

		//Local variable so that the Menu is repeating until conditions are met
		temp = false;
		
		do
		{
			choice = sc.nextLine();
			
			//Switch case used for each scenario of the user input
			switch (choice)
			{
			case "1":
				reservedSeat();//Calling the previous method that has been made to reserve seats 

				System.out.println("\n----------\n");

				mainMenu();//Calling mainMenu method so that after the previous action is complete, the user will then again be put into the main menu to continue

				break;
			case "2":
				cancelSeat();//Calling the previous method that has been made to cancel seats

				System.out.println("\n----------\n");

				mainMenu();

				break;
			case "3":
				displayFile();//Calling the previous method that has been made to display seats

				System.out.println("\n----------\n");

				mainMenu();

				break;
			case "Q"://Case to break the while loop
			case "q":
				System.out.println("Exiting...");
				temp = true;

				break;
			default:
				System.out.println("Invalid, please enter again:");
				choice = sc.nextLine();

			}
		} while (!temp);

	}

	public static void main(String[] args) throws FileNotFoundException {
		fileRead();//calling method to read the .txt file straight away so that it can be initialized

		mainMenu();
	}
}
