package courseWork2NewAttempt;

public class Seats{
	
	//Variables that make the constructor of the seat object
	protected static String seatNum;
	protected static String seatClass;
	protected static boolean isWindow;
	protected static boolean isAisle;
	protected static boolean isTable;
	protected static float seatPrice;
	protected static String eMail;
	
	//Constructor for seats Object
	public Seats(String seatNum, String seatClass, boolean isWindow, boolean isAisle, boolean isTable, float seatPrice, String eMail) {
		Seats.seatNum = seatNum;
		Seats.seatClass = seatClass;
		Seats.isWindow = isWindow;
		Seats.isAisle = isAisle;
		Seats.isTable = isTable;
		Seats.seatPrice = seatPrice;
		Seats.eMail = eMail;
		

		
	}
	
	//Deconstructor
	public Seats() {
		
	}
	
	public String toString() {
		String result;
		
		result = seatNum + " " + seatClass + " " + isWindow + " " + isAisle + " " + isTable + " " + seatPrice + eMail;
		
		return result;
	}

	
}



