/* Program: Auction System
 * Authors: Francis Hackenberger, Justin Estaris, Ryan Goulding
 * Description: Auction-style sales service console application.
*/

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <type_traits>
#include <typeinfo>

#include "Record.h"			// DEFINES RECORD STRUCTS & FUNCTIONS, AND CONSTANTS
#include "FileController.h" // HANDLES ALL FILE CONTROL
#include "User.h"			// HANDLES USER ACTIONS (PROMPTS) AND CURRENT USER INFORMATION
#include "AuctionSystem.h"	// HANDLES MENU, SESSION (LOGIN, LOGOUT)

using namespace std;

/*
	Main - Auction System Program
	@param int argc: The number of arguments passed
	@param: char** argv: Array of input files (format: current users, available items, daily transaction)
*/
int main(int argc, char** argv){
	// Initialize Variables
	bool auctionOpen = true;	// Whether or not to close (Exit) the auction system
	bool userFound = false;		// Whether or not the user exists (for login)

	string command;				// Stores user action (input)
	string transactionCode;		// Stores the current user actions transaction code (if any)
	string transactionDetails;  // Stores the transaction log (formatted information to append to transaction history)

	// Initialize Objects
	FileController fc(argv[1], argv[2], argv[3]); 
	AuctionSystem auctionSys(true);				  
	User currentUser;						      

	// Repeat until auction closes (exit command sets auction to closed)
	while(auctionOpen){
		transactionCode.clear(); // Reset the transaction code

		// Prompt user to log in (repeat until user is logged in)
		while(!auctionSys.loggedIn){
			string username;	
			printf("Enter a username to login to the Auction System: ");
			getline(cin, username);

			if(username != "exit"){
				USER_RECORD userRecord = fc.getUser(username); // Search for username in the users file

				if(!userRecord.username.empty())
					auctionSys.Login(userRecord, currentUser);	
				else
					printf("\nUser %s not found, please try again.", username.c_str());
			}else{
				return 0; // Exit command was entered, break out of the program immediately.
			}
		}

		// Generate the menu based on users account type
		auctionSys.GenerateMenu(currentUser.accountType);

		// Listen for user actions
		printf("Enter a command: ");
		getline(cin, command);
		transform(command.begin(), command.end(), command.begin(), ::tolower); // Transform command entered to lower-case


		/* Identify command REQUESTED and RESTRICT access based on account type
		 * Create - Create a new user account
		 * Delete - Delete a user account
		 * Advertise - Put an item up for auction
		 * Bid - Bid on an item up for auction
		 * Display items - List all all items in available items file
		 * Refund - Transfer credit from a buyer account to a seller account
		 * Add credit - Add a credit amount to a user
		 * Logout - Close the current users session
		 * Exit - Break out of the program (exit the auction system program)
		*/
		
		if (command == "create" && currentUser.accountType == ADMIN){
		 	USER_RECORD newUserRecord = currentUser.CreateAccount(); // Create a new user record
			
			if(newUserRecord.accountType != "ER"){
				userFound = fc.findUser(newUserRecord.username); 	 // Check if user already exists

				if(userFound){
					printf("\nUsername Invalid - username already exists, please choose another name.\n");
				}else{
					fc.addUser(newUserRecord);			// Add the new user record to the current users file
					printf("\nAccount Created.\n");

					transactionCode = CREATE_TRANSACTION_CODE;
					transactionDetails = recordToString(newUserRecord);
				}	
			}else{
				cout << newUserRecord.username << endl;
			}
		}	

		else if (command == "delete" && currentUser.accountType == ADMIN){
			string username = currentUser.DeleteAccount();
			USER_RECORD userRecord = fc.getUser(username);

			if(!userRecord.username.empty()){
				if(userRecord.username != currentUser.username){
					if(userRecord.accountType != ADMIN){
						fc.deleteUser(username);
						printf("\nUser deleted");

						transactionCode = DELETE_TRANSACTION_CODE;
						transactionDetails = recordToString(userRecord);
					}else{
						printf("\nError - You cannot delete admin accounts.");
					}
				}else{
					printf("\nError - Account in use.");
				}
			}else{
				printf("\nError - User does not exist.");
			}
			cin.ignore();
		}

		else if (command == "advertise" && (currentUser.accountType == FULL_STANDARD || currentUser.accountType == SELL_STANDARD || currentUser.accountType == ADMIN)){
			ITEM_RECORD itemRecord = currentUser.Advertise(); // Create a new item record
			
			if(itemRecord.duration != MAX_DURATION){
				itemRecord.seller = currentUser.username;	   // Set the seller name to the current user
				itemRecord.buyer = "N/A";					   // Default buyer name
				fc.addItem(itemRecord);					       // Add the new item record to the available items file
				printf("\nSuccess - advertised item.\n");

				transactionCode = ADVERTISE_TRANSACTION_CODE;
				transactionDetails = recordToString(itemRecord);
			}else{
				printf("%s", itemRecord.itemName.c_str());	// Displays error messsage if any has occurred.
			}
			cin.ignore();
		}	

		else if (command == "bid" && (currentUser.accountType == FULL_STANDARD || currentUser.accountType == BUY_STANDARD || currentUser.accountType == ADMIN)){
			ITEM_RECORD itemRecord = currentUser.Bid(); 	  // Create item record for item to bid on
			if(itemRecord.duration > -1){
				float highestBid = fc.getItemBid(itemRecord); // Find item and the highest bid currently on it (return -1 if item not found)

				if(highestBid > -1){
					string amount;
					cout << "Current Highest Bid: " << highestBid << endl;
					printf("Enter a new bid amount: ");
					cin >> amount;

					std::stringstream sstr(amount);
					float f;
					if(sstr >> f){
						float famount = stof(amount);  // Convert the credit amount to a float
						if(typeid(famount) == typeid(float)){
							float newBid = famount;
							highestBid += highestBid*0.05; // Increase the highest bid by 5% (requirement)

							if(newBid >= highestBid){
								itemRecord.highestBid = newBid;
								fc.updateItemBid(itemRecord, currentUser.username);
								printf("\nSuccess - Your bid has been placed.\n");
								
								transactionCode = BID_TRANSACTION_CODE;
								transactionDetails = recordToString(itemRecord);
							}else{
								printf("\nBid must be 5%% higher then current highest bid.\n");	
							}
						}
					}else{
						std::printf("\nError - amount must be a number.");
					}
				}else{
					printf("\nError - This item does not exist.\n");
				}
			}
			cin.ignore();
		}

		else if (command == "display items"){
			fc.displayAvailableItems(); // Displays and formats current items file
		}

		else if (command == "refund" && currentUser.accountType == ADMIN){
			REFUND_RECORD refundRecord = currentUser.Refund();

			if(refundRecord.amount != 0){
				USER_RECORD buyerRecord = fc.getUser(refundRecord.buyer);
				USER_RECORD sellerRecord = fc.getUser(refundRecord.seller);

				if(!buyerRecord.username.empty() && !sellerRecord.username.empty()){
					if(typeid(refundRecord.amount) == typeid(float)){
						if(refundRecord.amount <= MAX_CREDIT){
							buyerRecord.credit += refundRecord.amount;  // Add the refund amount to the buyers account
							sellerRecord.credit -= refundRecord.amount; // Remove the refund amount from the sellers account

							fc.updateCredit(buyerRecord.username, buyerRecord.credit);   // Update the buyers credit record
							fc.updateCredit(sellerRecord.username, sellerRecord.credit); // Update the sellers credit record

							printf("\n$%f refunded from %s to %s", refundRecord.amount, refundRecord.seller.c_str(), refundRecord.buyer.c_str());
							transactionCode = REFUND_TRANSACTION_CODE;
							transactionDetails = recordToString(refundRecord);
						}else{
							printf("\nError - exceeded $%i refund limit.", MAX_CREDIT);
						}
					}else{
						printf("\nError - credit amount must be a number.\n");
					}	
				}else{
					printf("\nError - Username pair not found.\n");
				}
			}
			cin.ignore();
		}	

		else if (command == "add credit"){
			std::string username;
			if (currentUser.accountType == ADMIN){
				std::cout << "\nEnter a username to add credit to: ";
				std::cin >> username;
			}else{
				username == currentUser.username;
			}
			userFound = fc.findUser(username);
			if(userFound){
				float newCredit = currentUser.AddCredit(); // Get a new credit amount for the user
				if(newCredit == currentUser.credit){
					fc.updateCredit(username, newCredit); // Update users credit in the current users file

					transactionCode = ADDCREDIT_TRANSACTION_CODE;
					transactionDetails = currentUser.stringify();
				}	
			}else{
				printf("\nError - that user does not exist.");
			}
			cin.ignore();
		}	

		else if (command == "logout"){
			transactionCode = LOGOUT_TRANSACTION_CODE;
			transactionDetails = currentUser.stringify();

			currentUser = User(); // Reset current user information
			auctionSys.Logout();  // Logout user from auction system
		}	

		else if (command == "exit"){
			auctionOpen = false;
			auctionSys.Logout();  // Log the user out of the auction system gracefully
			return 0;			  // Exit command was entered, break out of the program immediately.
		}	

		else{
			cout << "\nCommand not recognized or invalid permissions, please try again." << endl;
		}

		if(!transactionCode.empty())
			fc.logTransaction(transactionCode, transactionDetails); // Log transactions
	}
    return 0;
}