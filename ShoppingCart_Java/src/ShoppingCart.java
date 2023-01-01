import java.util.Scanner;
import java.io.Serializable;
import java.util.ArrayList;

public class ShoppingCart implements Serializable
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 3408933457219902521L;

	transient Scanner sc = new Scanner(System.in);

	public static int amountOfItems;
	public static double total;
	public static int sizeOfCart = 5;
	ArrayList<Item> cart = new ArrayList<Item>();// ArrayList for items to be stored in
	String name; // Name for the item object

	public static boolean isValidPrice (String possibleDouble) {

        try {
            double k = Double.parseDouble(possibleDouble);
            if( k < 0) {
                return false;
            }
        }
        catch(Exception e) {
            return false;
        }
        return true;
    }
	

	public ShoppingCart() {
		// empty constructor
	}

	public void checkCart() {
		System.out.println("Your cart is now worth:" + total + "$" + " and has " + amountOfItems + " items in it");
	}

	public void addToCart() {
		String price;
		name = IBIO.input("What is the name of your item?");
		price = IBIO.input("How much does your item cost?");
		while(!isValidPrice(price)) {
            price = IBIO.input("Error, please enter a valid value:");
        }
        double priceAsDouble = Double.parseDouble(price);
		total = total + priceAsDouble;
		Item item = new Item(name, priceAsDouble);
		System.out.println("Your item " + name + " has been added!");
		amountOfItems++;
		cart.add(item);

	}

	public void increaseCartSize() {
		sizeOfCart += 10;
	}

	public void removeFromCart() {
		int count = 0;//Numbering for index
		for (int i = 0; i < cart.size(); i++)
		{
			count++;
			System.out.println(count + ")" + cart.get(i).toString());
		}
		System.out.println("----------");
		int choice = IBIO.inputInt("What would you like to remove?") - 1;
		cart.remove(choice);
		System.out.println("Your item(s) has been removed");
		for (int i = 0; i < cart.size(); i++)
		{
			System.out.println(cart.get(i).toString());
		}
	}

	public void displayCart() {// printArray method
		for (int i = 0; i < cart.size(); i++)
		{
			System.out.println(cart.get(i).toString());
		}
	}

}
