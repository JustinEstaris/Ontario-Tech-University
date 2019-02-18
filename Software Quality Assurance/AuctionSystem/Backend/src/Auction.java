package backend;

//Auction Class - stores the information for an individual auction
public class Auction {
	// Private attributes
	private String itemName;
	private String sellerName;
	private String buyerName;
	private int daysRemaining;
        //max bid
	private double highestBid;
	
	// Constructor
	public Auction(String _itemName, String _sellerName, String _buyerName, int _daysRemaining, double _highestBid) {
		itemName = _itemName;
		sellerName = _sellerName;
		buyerName = _buyerName;
		daysRemaining = _daysRemaining;
                //maxbid
		highestBid = _highestBid;
	}
	
	// Methods
	
	//add methods getItemName() and getSellerName()
	public String getItemName(){
		return itemName;
	}
	
	public String getSellerName(){
		return sellerName;
	}
        
        public String getBuyerName(){
		return buyerName;
	}
        
        public double getHighestBid(){
		return highestBid;
	}
        
        public int getDaysRemaining(){
            return daysRemaining;
        }
        
        public void setDaysRemaining(int days){
            daysRemaining = days;
        }
	
	//updates the buyerName and highBid for an auction item
	public void newBid(String buyer, double bid) {
		buyerName = buyer;
		highestBid = bid;
	}
        
	//Creates a string in the correct format for the available items file.
	public String formatOutput() {
		String output;
		//a string with the format 'IIIIIIIIIIIIIIIIIII SSSSSSSSSSSSSSS UUUUUUUUUUUUUU DDD PPPPPP'
		//where IIIIIIIIIIIII is itemName, SSSSSSS is sellerName, UUUUU is buyerName, DDD is days remaining 
		//and PPPPP is highestBid
                //add maxbid
		output = String.format("%-25s", itemName) + " " + String.format("%-15s", sellerName) + " " + String.format("%-15s", buyerName) + " " + String.format("%03d", daysRemaining) +" " + String.format("%06.2f", highestBid);
		System.out.println(output);
		return output;
	}
}
