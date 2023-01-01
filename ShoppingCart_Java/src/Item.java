public class Item implements java.io.Serializable 
{

	private String name;
	private double price;

	public String getName() {
		return this.name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public double getPrice() {
		return this.price;
	}

	public void setPrice(double price) {
		this.price = price;
	}

	public Item(String itemName, double itemPrice) {
		this.name = itemName;
		this.price = itemPrice;
	}

	public String toString() {
		return "Item(s):" + this.name + "," + " Price:$" + this.price;
	}

}
