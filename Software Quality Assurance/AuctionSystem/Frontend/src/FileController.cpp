#include "FileController.h"
#include "User.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

// Initializes the File Controller
FileController::FileController(std::string userFile, std::string itemFile, std::string transFile){
	currentUsersFile = userFile;
	availableItemsFile = itemFile;
	dailyTransactionFile = transFile;
}

// Appends a transaction to the daily transaction file
void FileController::logTransaction(std::string transactionNumber, std::string output){
	std::ofstream outfile;
    outfile.open(dailyTransactionFile, std::ios_base::app);
    outfile << transactionNumber << " " << output << std::endl;
}

// Retrieves a user record from the current users file
USER_RECORD FileController::getUser(std::string lookupName){
	std::ifstream infile(currentUsersFile);

	USER_RECORD userRecord;
	std::string username;
	std::string type;
	float credit;

	while (infile >> username >> type >> credit){
		if (lookupName == username){ // If username in file matches lookup name then set user attributes to those in file
			userRecord.username = lookupName;
			userRecord.accountType = type;
			userRecord.credit = credit;
		}
	}
	return userRecord;
}

// Checks if a user exists in the current users file
bool FileController::findUser(std::string lookupName){
	std::ifstream infile(currentUsersFile);

	bool userFound = false;
	std::string username;
	std::string inputs;

	while (infile >> username >> inputs >> inputs){
		if (lookupName == username) 
			userFound = true;	
	}
	return userFound;
}

// Adds a user to the current users file
void FileController::addUser(USER_RECORD newUser){
	std::ofstream outfile;
    outfile.open(currentUsersFile, std::ios_base::app);
    outfile << newUser.username << " " 
			<< newUser.accountType << " " 
			<< newUser.credit << std::endl;
}

// Deletes a user and all of its associated items from the current users file and the available items file
void FileController::deleteUser(std::string username){
	// DELETE THE USER
	std::ifstream infile(currentUsersFile);
	std::ofstream outfile;

	std::vector<USER_RECORD> current_users;
	USER_RECORD myUser;

	while (infile >> myUser.username >> myUser.accountType >> myUser.credit){
		if(username != myUser.username)	
			current_users.push_back(myUser);
	}
	infile.close();
    outfile.open(currentUsersFile, std::ofstream::out | std::ofstream::trunc); // Clear the file to rewrite contents
	outfile.close();

	outfile.open(currentUsersFile, std::ios_base::app); // Rewrite contents to the file
	for (int i = 0; i < current_users.size(); ++i)
		outfile << current_users[i].username << " " << current_users[i].accountType << " " << current_users[i].credit << std::endl;
	outfile.close();

	// DELETE THE USERS ITEMS
	infile.open(availableItemsFile);
	std::vector<ITEM_RECORD> available_items;
	ITEM_RECORD item;

	while (infile >> item.itemName >> item.seller >> item.buyer >> item.duration >> item.minBid){
		if(username != item.seller)
			available_items.push_back(item);	
	}
	infile.close();
    outfile.open(availableItemsFile, std::ofstream::out | std::ofstream::trunc); // Clear the file to rewrite contents
	outfile.close();

	outfile.open(availableItemsFile, std::ios_base::app); // Rewrite contents to the file
	for (int i = 0; i < available_items.size(); ++i)
		outfile << available_items[i].itemName << " " 
				<< available_items[i].seller << " " 
				<< available_items[i].buyer << " " 
				<< available_items[i].duration << " " 
				<< available_items[i].minBid << std::endl;
	outfile.close();
}

// Updates a users credit amount in the current users file
void FileController::updateCredit(std::string username, float credit){
	std::ifstream infile(currentUsersFile);
	std::ofstream outfile;

	std::vector<USER_RECORD> current_users;
	USER_RECORD myUser;

	while (infile >> myUser.username >> myUser.accountType >> myUser.credit){
		if(username == myUser.username)
			myUser.credit = credit;	
		current_users.push_back(myUser);
	}

    outfile.open(currentUsersFile, std::ofstream::out | std::ofstream::trunc); // Clear the file to rewrite contents
	outfile.close();

	outfile.open(currentUsersFile, std::ios_base::app); // Rewrite contents to the file
	for (int i = 0; i < current_users.size(); ++i)
		outfile << current_users[i].username << " " << current_users[i].accountType << " " << current_users[i].credit << std::endl;
	outfile.close();
}

// Adds an auction item to the available items file
void FileController::addItem(ITEM_RECORD itemRecord){
	std::ofstream outfile;
    outfile.open(availableItemsFile, std::ios_base::app);

    outfile << itemRecord.itemName << " " 
			<< itemRecord.seller << " " 
			<< itemRecord.buyer << " " 
			<< itemRecord.duration << " " 
			<< itemRecord.minBid << std::endl;
}

// Displays and formats the available items file
void FileController::displayAvailableItems(){
	std::ifstream infile(availableItemsFile);

	ITEM_RECORD itemRecord;
	std::string itemName;
	std::string seller;
	std::string buyer;
	int duration;
	float highestBid;

	while (infile >> itemName >> seller >> buyer >> duration >> highestBid)
		std::cout << "Item name: " << itemName 
				  << " | Seller: " << seller 
				  << " | Bid: " << highestBid 
				  << " | Duration:" << duration << std::endl;
}

// Returns the current highest bid on an item in the available items file
float FileController::getItemBid(ITEM_RECORD itemRecord){ // Return -1 if item record is not found in file
	std::ifstream infile(availableItemsFile);

	std::string itemName;
	std::string seller;
	std::string buyer;
	int duration;
	float highestBid;

	itemRecord.highestBid = -1;

	while (infile >> itemName >> seller >> buyer >> duration >> highestBid){
		if(itemRecord.itemName == itemName && itemRecord.seller == seller && itemRecord.duration == duration)
			itemRecord.highestBid = highestBid;
	}

	return itemRecord.highestBid;
}

// Updates the current highest bid on an item in the available items file
void FileController::updateItemBid(ITEM_RECORD itemRecord, std::string buyer){
	std::ifstream infile(availableItemsFile);
	std::ofstream outfile;

	std::vector<ITEM_RECORD> current_items;
	ITEM_RECORD item;

	while (infile >> item.itemName >> item.seller >> item.buyer >> item.duration >> item.highestBid){
		if(itemRecord.itemName == item.itemName && itemRecord.seller == item.seller && itemRecord.duration == item.duration){
			item.highestBid = itemRecord.highestBid;	
			item.buyer = buyer;
			std::cout << item.buyer << " " << item.highestBid<< std::endl;
		}
		current_items.push_back(item);
	}


    outfile.open(availableItemsFile, std::ofstream::out | std::ofstream::trunc); // Clear the file to rewrite contents
	outfile.close();

	outfile.open(availableItemsFile, std::ios_base::app); // Append new contents to the file
	for (int i = 0; i < current_items.size(); ++i){
		outfile << current_items[i].itemName << " " 
				<< current_items[i].seller << " " 
				<< current_items[i].buyer << " " 
				<< current_items[i].duration << " "
				<< current_items[i].highestBid << std::endl;
	}
	outfile.close();
}