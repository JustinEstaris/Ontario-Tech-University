package backend;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.Vector;

/**
 * Users container class
 * the list of active users
 */
public class Users {
	// Private attributes
	private Vector<User> users;
	public Users() {
		users = new Vector<User>();
	}
	
	// Methods
	public double validateDouble(String doubleStr) {
            double creditD = 0;
            try{
                creditD = Double.parseDouble(doubleStr);
            }catch(NumberFormatException ex){ // handle your exception
               ex.printStackTrace();
            }
            return creditD;
	}
	
	//loads the user objects from the file into the vector
	public void load(String filename) {
            //loop through the file creating a user object for each record and adding them to the vector
            String userFile;
            String usernameIn;
            String accountTypeIn;
            double creditAmountIn;
	    try {
	        BufferedReader bufferreader = new BufferedReader(new FileReader(filename));
	        userFile = bufferreader.readLine();
	        int i = 1;
	        while (userFile != null) { 
	        	usernameIn = userFile.substring(0, 14);
	        	accountTypeIn = userFile.substring(16, 18);
	        	creditAmountIn = validateDouble(userFile.substring(19, 26));
	        	
	        	User newUser = new User(usernameIn, accountTypeIn, creditAmountIn);
	        	users.add(newUser);
	        
	        	userFile = bufferreader.readLine();
	        	i++;
	        }
	        bufferreader.close();

	    } catch (FileNotFoundException ex) {
	        ex.printStackTrace();
	    } catch (IOException ex) {
	        ex.printStackTrace();
	    }
	    //Print all users. For debugging purposes.
	    /*
		System.out.println("Printing all current users");
		int i = 0;
		while( i < users.size()) {
			users.get(i).formatOutput();
			i++;
		}
            */
	}
	
	//adds a newly created User to the vector
	public void createUser(String transaction) {
		//parses the transaction and creates a new user object and adds it to the vector
		//String[] splitStr = transaction.split("\\s+");
                
                String username = transaction.substring(3, 17);
                String accountType = transaction.substring(19, 21);
                Double credit = validateDouble(transaction.substring(23, 30));
                
		User createdUser = new User(username, accountType, credit);
		users.add(createdUser);
		System.out.println("User " + username + " has been created.");
	}
	
	//finds and removes a User from the vector
	public Auctions deleteUser(String transaction, Auctions auctions) throws IOException {
            //parse the transaction and removes the user object with a matching username from the vector
            //String[] splitStr = transaction.split("\\s+");
            String username = transaction.substring(3,17);
            for (int i = 0; i < users.size(); i++) {
                if (users.get(i).getUsername().equals(username)) {
                        users.remove(i);
                        System.out.println("User " + username + " has been deleted.");
                        break;
                }
            }
            auctions.deleteAllAuctions(username);
            
            return auctions;
	}
	
	//finds the 2 users and updates their credit amount
	public void refund(String transaction){
            //parses the transaction then uses findUser to find both users then use the updateCredits for both users
            //switching the sign where appropriate 
            String buyerName = transaction.substring(3,18);
            String sellerName = transaction.substring(19,34);
            Double credit = validateDouble(transaction.substring(35,43));
            
            System.out.println("refund amount " + credit);
            for (int i = 0; i < users.size(); i++) {
                //buyer
                if (users.get(i).getUsername().equals(buyerName)) {
                    users.get(i).updateCreditAmount(credit);
                     
                }//seller
                else if (users.get(i).getUsername().equals(sellerName)) {
                    users.get(i).updateCreditAmount(-credit);    
                }
            }

            System.out.println("Refund transaction completed");
	}
	
	//finds a user and updates their credit amount
	public void addCredit(String transaction){
            //parse the transaction then use findUser to locate the correct user object then use updateCredit for 
            //that user to add the credit  
            String username = transaction.substring(3, 17);
            Double credit = validateDouble(transaction.substring(23, 30));

            for (int i = 0; i < users.size(); i++) {
                if (users.get(i).getUsername().equals(username)) {
                    users.get(i).updateCreditAmount(credit);
                    System.out.println(credit+" has been added to " + username);
                    break;
                }
            }
	}
	
	//transfers the funds from the buyer to the seller when the auction ends
	public void closeAuction(String buyer, String seller, double amount) {
            //use findUser to locate the buyer and seller object then use the updateCredit method for each object to 
            //transfer the amount from the buyer to the seller
            for (int i = 0; i < users.size(); i++) {
                //add money to seller
                if (users.get(i).getUsername().equals(seller)) {
                        users.get(i).updateCreditAmount(amount);
                }//subtract credit from buyer
                else if (users.get(i).getUsername().equals(buyer)) {
                        users.get(i).updateCreditAmount(amount*-1);
                }
            }
            System.out.println("Auction closed");
	}
	
	//writes the formated users to the output file
	public void write(String filename) throws FileNotFoundException, IOException {
            //loops through the vector and writes the formatOutput string from each user object to the file
            PrintWriter writer = new PrintWriter(filename, "UTF-8");
            int i = 0;
            while( i < users.size()) {
                    writer.println(users.get(i).formatOutput());
                    i++;
            }
            writer.close();

            System.out.println("All users have been written to file.");
        }
	//add findUser method that search for a user with a specific username and returns its index 
}
