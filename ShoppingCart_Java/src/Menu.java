import java.io.FileInputStream;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Scanner;

public class Menu extends ShoppingCart // Serialization not working?
{
	public Menu() {

	}

	Scanner sc = new Scanner(System.in);
	// static double total = total;

	public void displayMenu() {
		System.out.println("---MENU---");
		System.out.println("1)Add to Cart \n2)ViewCart \n3)Remove from Cart \n4)Exit");
		System.out.println("What would you like to do? ");
	}
	
	

	public static void main(String[] args) throws ClassNotFoundException {
		boolean exit = false;
		do
		{
			Item item = null;
			Scanner sc = new Scanner(System.in);

			Menu menu = new Menu();
			menu.displayMenu();

			ShoppingCart cart = new ShoppingCart();

			// Choice of the menu
			int choice = sc.nextInt();
			switch (choice)
			{
			case 1:
				System.out.println("You picked Add to Cart");
				break;
			case 2:
				System.out.println("You picked to view your Cart");
				break;
			case 3:
				System.out.println("You picked to Remove from your cart");
				break;
			case 4:
				System.out.println("You picked to exit");
			default:
				while(choice <= 0 || choice > 4){
					System.out.println("Error, please enter a valid value:");
					choice = sc.nextInt() ;
				}
				break;
			}

			if (choice == 1)
			{
				// start of Serialization/Saving the Array list
				try
				{
					FileInputStream fileIn = new FileInputStream("ShoppingCart.ser");
					ObjectInputStream in = new ObjectInputStream(fileIn);
					cart = (ShoppingCart) in.readObject();
					in.close();
					fileIn.close();
				} catch (Exception e)
				{
					System.out.println("saved");
				}
				// Saving the total amount of money
				try
				{
					FileInputStream fileIn = new FileInputStream("Total.ser");
					ObjectInputStream in = new ObjectInputStream(fileIn);
					total = (double) in.readObject();
					in.close();
					fileIn.close();
				} catch (Exception e)
				{
					System.out.println("saved");
				}

				cart.addToCart();
				try // Reading object form serialization/deserialization
				{
					FileOutputStream fileOut = new FileOutputStream("ShoppingCart.ser");
					ObjectOutputStream out = new ObjectOutputStream(fileOut);
					out.writeObject(cart);
					System.out.println("");
					out.close();
					fileOut.close();
				} catch (Exception e)
				{
					System.out.println("File not found");
				}
				cart.checkCart();
				while (amountOfItems < sizeOfCart)
				{
					System.out.println("Would you like to add another item? y/n");
					// Using char to ask if they want to add another item
					// start of Serialization/Saving the Array list
					try
					{
						FileInputStream fileIn = new FileInputStream("ShoppingCart.ser");
						ObjectInputStream in = new ObjectInputStream(fileIn);
						cart = (ShoppingCart) in.readObject();
						in.close();
						fileIn.close();
					} catch (Exception e)
					{
						System.out.println("saved");
					}
					if (sc.next().startsWith("y"))
					{
						cart.addToCart();
						cart.checkCart();
						cart.displayCart();
						try // Reading object form serialization/deserialization
						{
							FileOutputStream fileOut = new FileOutputStream("ShoppingCart.ser");
							ObjectOutputStream out = new ObjectOutputStream(fileOut);
							out.writeObject(cart);
							System.out.println("Success");
							out.close();
							fileOut.close();
						} catch (Exception e)
						{
							System.out.println("File not found");
						}
					} else
					{
						cart.checkCart();
						cart.displayCart();
						break;

					} // Increasing size of ArrayList
					if (amountOfItems == sizeOfCart)
					{
						System.out.println("Your cart is full, would you like to add more space? y/n");
						if (sc.next().startsWith("y"))
						{
							cart.increaseCartSize();
							System.out.println("Your cart size has increased by 10");
						} else
						{
							System.out.println("");
							break;
						}
					}
				}
			} else if (choice == 2)
			{
				try
				{// loading the object in from ShoppingCart.ser
					FileInputStream fileIn = new FileInputStream("ShoppingCart.ser");
					ObjectInputStream in = new ObjectInputStream(fileIn);
					cart = (ShoppingCart) in.readObject();
					in.close();
					fileIn.close();
				} catch (Exception e)
				{
					System.out.println("saved");
				}
				cart.displayCart();
			} else if (choice == 3)
			{
				// start of Serialization/Saving the Array list
				try
				{
					FileInputStream fileIn = new FileInputStream("ShoppingCart.ser");
					ObjectInputStream in = new ObjectInputStream(fileIn);
					cart = (ShoppingCart) in.readObject();
					in.close();
					fileIn.close();
				} catch (Exception e)
				{
					System.out.println("saved");
				}
				cart.removeFromCart();
				try // Reading object form serialization/deserialization
				{
					FileOutputStream fileOut = new FileOutputStream("ShoppingCart.ser");
					ObjectOutputStream out = new ObjectOutputStream(fileOut);
					out.writeObject(cart);
					System.out.println("Success");
					out.close();
					fileOut.close();
				} catch (Exception e)
				{
					System.out.println("File not found");
					break;
				}
				while (amountOfItems < sizeOfCart)
				{
					System.out.println("Would you like to add another item? y/n");
					// Using char to ask if they want to add another item
					// start of Serialization/Saving the Array list
					try
					{
						FileInputStream fileIn = new FileInputStream("ShoppingCart.ser");
						ObjectInputStream in = new ObjectInputStream(fileIn);
						cart = (ShoppingCart) in.readObject();
						in.close();
						fileIn.close();
					} catch (Exception e)
					{
						System.out.println("saved");
					}
					if (sc.next().startsWith("y"))
					{
						cart.removeFromCart();
						cart.checkCart();
						cart.displayCart();
						try // Reading object form serialization/deserialization
						{
							FileOutputStream fileOut = new FileOutputStream("ShoppingCart.ser");
							ObjectOutputStream out = new ObjectOutputStream(fileOut);
							out.writeObject(cart);
							System.out.println("Success");
							out.close();
							fileOut.close();
						} catch (Exception e)
						{
							System.out.println("File not found");
						}
					} else
					{
						cart.checkCart();
						cart.displayCart();
						break;
					}
				}
			} else if (choice == 4)
			{
				exit = true;
				break;
			}

		} while (!exit);
	}

}
