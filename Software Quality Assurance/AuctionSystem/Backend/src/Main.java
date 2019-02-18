package backend;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.File;

public class Main {
	public static void main(String[] args) throws FileNotFoundException, IOException {
		Users users = new Users();
		users.load("usernames.txt");
		
		Auctions auctions = new Auctions();
		auctions.load("auctions.txt");
		auctions.displayAuctions();
		
		String transaction;
	    try {

	        BufferedReader bufferreader = new BufferedReader(new FileReader("EOF.txt"));
	        transaction = bufferreader.readLine();

	        while (transaction != null) {     
	        	
	        	String[] splitStr = transaction.split("\\s+");
	        	System.out.println("tranaction: " + splitStr[0]);
	        	switch (splitStr[0]) {
		  		case "00":
		  			break;
		  		case "01":
		  			users.createUser(transaction);
		  			break;
		  		case "02":
		  			users.deleteUser(transaction, auctions);
		  			break;
		  		case "03":
		  			auctions.advertise(transaction);
		 			break;
		  		case "04":
		  			auctions.bid(transaction);
		  			break;
		  		case "05":
		  			users.refund(transaction);
		  			break;
		 		case "06":
		 			users.addCredit(transaction);
		 			break;
		  		}
	    
	        	transaction = bufferreader.readLine();
	        }
	        
	    } catch (FileNotFoundException ex) {
	        ex.printStackTrace();
                } catch (IOException ex) {
	        ex.printStackTrace();
	    }
		  
	    auctions.endDay(users);
            auctions.write("auctions.txt");
            users.write("usernames.txt");
	}
}
