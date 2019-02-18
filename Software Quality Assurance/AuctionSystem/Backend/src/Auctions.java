package backend;

import java.util.*;
import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Auctions Container Class
 * the list of all the available items
 */
public class Auctions {
	// Private attributes
	private Vector<Auction> auctions;
        public Auctions() {
            auctions = new Vector();
	}
        
    public void displayAuctions() {
    	System.out.println("Printing all AUCTIONS");
        int i = 0;
        while( i < auctions.size()) {
            auctions.get(i).formatOutput();
            i++;
        }
    }
    
    public void deleteAllAuctions(String username) {
    	int i = 0;
    	while (i < auctions.size()) {
            if(auctions.get(i).getSellerName().equals(username)) {
                auctions.remove(i);
                break;
            }
            i++;
    	}
    	System.out.println("All of " + username.trim() + " auctions have been deleted.");
    }
	
	// Methods
	//loads the auctions from a file to the vector
	public void load(String filename) throws FileNotFoundException {
            //loop through the file creating an auction object for each record and adding them to the vector
            System.out.println("Load all auctions");
            File file = new File(filename);
            Scanner input = null;

            input = new Scanner(file);

            List<String> list = new ArrayList<String>();

            while (input.hasNextLine()) {
                list.add(input.nextLine());
            }
            
            //Populate auctions vector from file list
            for (String item : list) { 	
                String itemName = item.substring(0, 24);
                String sellerName = item.substring(26, 40);
                String buyerName = item.substring(42, 56);
                int daysRemaining = Integer.parseInt(item.substring(58, 61));
                //max bid
                double highestBid = Double.parseDouble(item.substring(62, 68));
                
                Auction newAuction = new Auction(itemName, sellerName, buyerName, daysRemaining, highestBid);
                auctions.add(newAuction);
            }
	}
	
	//adds a new auction to the vector
	public void advertise(String transaction){
            //parse the transaction to create an auction object and add it to the vector
            System.out.println("Create advertisement");

            String itemName = transaction.substring(3, 27);
            String sellerName = transaction.substring(29, 43);
            String buyerName = sellerName;
            int daysRemaining = Integer.parseInt(transaction.substring(45, 47));
            double highestBid = Double.parseDouble(transaction.substring(49, 55));
            Auction newAuction = new Auction(itemName, sellerName, buyerName, daysRemaining, highestBid);
            auctions.add(newAuction);
	}
	
	//updates an auction through newBid
	public void bid(String transaction){
            //parse the transaction to  identify the element in the vector that needs to be updated with findAuction
            //and update its buyer and high bid through newBid()
            System.out.println("create bid");

            String itemName = transaction.substring(3, 23); 
            String sellerName = transaction.substring(25, 40);
            String buyerName = transaction.substring(42, 57);
            double highestBid = Double.parseDouble(transaction.substring(59, 65));
           
            for (int i = 0; i < auctions.size(); i++) {
            	if (auctions.get(i).getSellerName().trim().equals(sellerName.trim()) && auctions.get(i).getItemName().trim().equals(itemName.trim())) {
                    //if bid > maxbid
                        //close aution
                    //else
                    auctions.get(i).newBid(buyerName, highestBid);
                    System.out.println("Bid transaction completed");
                    break;
                }
            }
	}
	
	//removes an auction from the list
	public void delete(String item, String seller){
            //locates the element with the matching item name and seller name and removes it from the vector
            
            for (int i = 0; i < auctions.size(); i++) {
                if (auctions.get(i).getSellerName().equals(seller) && auctions.get(i).getItemName().equals(item)) {
                	System.out.println("AUCTION DELETED");
                    //Auction auctionToRemove = new Auction(item, seller, auctions.get(i).getBuyerName(), auctions.get(i).getDaysRemaining(), auctions.get(i).getHighestBid());
                    //auctions.remove(auctionToRemove);
                    auctions.remove(i);
                    break;
                }
            }
	}
	
	//subtracts 1 from the days remaining for each auction if the daysRemaining becomes 0 close the auction
	public Users endDay(Users users) {
            //loop through the vector decreasing the daysRemaining for each Auction in the list
            //when days remeaining hit 0 use the closeAuction method of Users with the sellerName, buyerName, and highestBid
            //then delete the auction from the vector

            for (int i = 0; i < auctions.size(); i++) {
                int daysRemaining = auctions.get(i).getDaysRemaining() - 1;
                if(daysRemaining == 0){
                    String itemName = auctions.get(i).getItemName();
                    String buyerName = auctions.get(i).getBuyerName();
                    String sellerName = auctions.get(i).getSellerName();
                    Double highestBid = auctions.get(i).getHighestBid();
                    System.out.println("Buyer: " + buyerName + " Seller: " + sellerName + " Credit: " + highestBid);

                    //TODO: Add closeAuction from Users
                    users.closeAuction(buyerName, sellerName, highestBid);
                    delete(itemName, sellerName);
                }else{
                    auctions.get(i).setDaysRemaining(daysRemaining);
                }
            }
            System.out.println("All auctions decremented");
            
            return users;
	}
	
	//outputs the formated auctions to the new available items file
	public void write(String filename) throws FileNotFoundException, UnsupportedEncodingException {
            try ( //loop through the vector writing the formatOutput value for each auction to the file
                    PrintWriter writer = new PrintWriter(filename, "UTF-8")) {
                int i = 0;
                while( i < auctions.size()) {
                    writer.println(auctions.get(i).formatOutput());
                    i++;
                }
            }

            System.out.println("All auctions have been written to file.");
	}
	//add findAuction function to search the vector for an item with a item name and seller name and returns the index
}
