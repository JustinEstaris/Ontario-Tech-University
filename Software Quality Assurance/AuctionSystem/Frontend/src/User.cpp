#include "User.h"
#include <string>
#include <iostream>
#include <sstream>
#include <type_traits>
#include <typeinfo>

// Puts current user information into a string
std::string User::stringify(){
	std::stringstream userStream;
	userStream << username << " " << accountType << " " << credit;
	std::string userInfo = userStream.str();
	return userInfo;
}

USER_RECORD User::CreateAccount() {
	bool userExists = false;
	USER_RECORD newUser;

	std::printf("\nEnter a username for the new account: ");
	std::cin >> newUser.username;
	std::printf("\nEnter an account type: ");
	std::cin >> newUser.accountType;

	if(newUser.username.length() > 15){
		newUser.username = "\nUsername Invalid - must be between 1-15 characters";
		newUser.accountType = "ER";
	}else if(newUser.accountType != "AA" && newUser.accountType != "FS" && newUser.accountType != "BS" && newUser.accountType != "SS"){
		newUser.username = "\nError - Invalid account type";
		newUser.accountType = "ER";
	}
	std::cin.ignore();

	return newUser;
}

std::string User::DeleteAccount() {
	std::string username;
	std::printf("\nEnter username to delete: ");
	std::cin >> username;

	return username;
}

ITEM_RECORD User::Advertise() {
	ITEM_RECORD itemRecord;
	std::string minBid;
	std::string duration;

	std::printf("\nEnter Item Name: ");
	std::cin >> itemRecord.itemName;
	std::cin.clear();
	std::printf("\nEnter Minimum Bid: ");
	std::cin >> minBid;
	std::cin.clear();
	std::printf("\nEnter Duration of Auction (Days): ");
	std::cin >> duration;

	if(is_number(minBid) == false){
		itemRecord.duration = 999;
		itemRecord.itemName = "\nError - Minimum Bid must be a number";
		return itemRecord;
	}else{
		itemRecord.minBid = std::stoi(minBid);
	}

	if(is_number(duration) == false){
		itemRecord.duration = 999;
		itemRecord.itemName = "\nError - Auction Duration must be a number";
		return itemRecord;
	}else{
		itemRecord.duration = std::stoi(duration);
	}

	if(itemRecord.itemName.length() > 25 || itemRecord.itemName.length() < 1){
		itemRecord.duration = 999;
		itemRecord.itemName = "\nError - Item Name must be between 1 -25 Characters";
	}else if(itemRecord.minBid > 999.99 || itemRecord.minBid < 0){
		itemRecord.duration = 999;
		itemRecord.itemName = "\nError - Minimum Bid must be between 0 - 999.99";
	}else if(itemRecord.duration > 100 || itemRecord.duration < 1){
		itemRecord.duration = 999;
		itemRecord.itemName = "\nError - Auction Duration must be between 1-100 days";
	}

	return itemRecord;
}

float User::AddCredit() {
	std::string amount;	
	std::cout << "\nHow much would you like to add? : ";
	std::cin >> amount;

	std::stringstream sstr(amount);
	float f;
	if(sstr >> f){
		float famount = std::stof(amount);
		if(typeid(famount) == typeid(float)){
			if(famount < MAX_CREDIT_ADD){
				if((credit+famount) < MAX_CREDIT){
					credit += famount;
					std::cout << "\nSuccessfully added $ " << amount << std::endl;
					std::cout << "\nCredit is now: " << credit << std::endl;
				}else{
					std::printf("\nError - exceeded $%i credit limit.", MAX_CREDIT);
				}
			}else{
				std::printf("\nError - exceeded $%i session limit.", MAX_CREDIT_ADD);
			}
		}
	}else{
		std::printf("\nError - amount must be a number.");
	}

	return credit;
}

ITEM_RECORD User::Bid() {
	ITEM_RECORD itemRecord;
	std::string duration;

	std::printf("\nEnter Item Name: ");
	std::cin >> itemRecord.itemName;
	std::printf("\nEnter number of days to auction: ");
	std::cin >> duration;
	std::printf("\nEnter Seller Username: ");
	std::cin >> itemRecord.seller;

	if(is_number(duration) == false){
		std::printf("\nError - Auction Duration must be a number.");
		itemRecord.duration = -1;
	}else{
		itemRecord.duration = stoi(duration);
	}

	return itemRecord;
}

REFUND_RECORD User::Refund() {
	REFUND_RECORD refundRecord;
	std::string amount;
	std::printf("\nEnter buyer's username: ");
	std::cin >> refundRecord.buyer;
	std::printf("\nEnter seller's username: ");
	std::cin >> refundRecord.seller;
	std::printf("\nEnter refund amount: ");
	std::cin >> amount;

	std::stringstream sstr(amount);
	float f;
	if(sstr >> f){
		float famount = std::stof(amount);
		if(typeid(famount) == typeid(float)){
			refundRecord.amount = famount;
		}
	}else{
		std::printf("\nError - amount must be a number.");
		refundRecord.buyer.empty();
		refundRecord.seller.empty();
		refundRecord.amount = 0;
	}

	return refundRecord;
}

bool User::is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}