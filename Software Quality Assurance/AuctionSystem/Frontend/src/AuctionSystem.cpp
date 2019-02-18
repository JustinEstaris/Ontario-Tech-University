#include "AuctionSystem.h"
#include "User.h"
#include <algorithm>
#include <sstream>

// Initializes the Auction System
AuctionSystem::AuctionSystem(bool auctionStatus){
	isOpen = auctionStatus;
	loggedIn = false;
}

// Generates a menu based on current users account type
void AuctionSystem::GenerateMenu(std::string accountType) {
	std::cout << "\n\t    Main Menu  " << std::endl;
	std::cout << "\t-----------------" << std::endl;

	if (accountType == ADMIN) {
		std::cout << "\t-    Create     -" << std::endl;
		std::cout << "\t-    Delete     -" << std::endl;
		std::cout << "\t-   Advertise   -" << std::endl;
		std::cout << "\t-      Bid      -" << std::endl;
		std::cout << "\t-    Refund     -" << std::endl;	
	}
	else if (accountType == FULL_STANDARD) {
		std::cout << "\t-   Advertise   -" << std::endl;
		std::cout << "\t-      Bid      -" << std::endl;
	}
	else if (accountType == SELL_STANDARD) {
		std::cout << "\t-   Advertise   -" << std::endl;
	}
	else if (accountType == BUY_STANDARD) {
		std::cout << "\t-      Bid      -" << std::endl;
	}

	std::cout << "\t-   Add Credit  -" << std::endl;
	std::cout << "\t- Display Items -" << std::endl;
	std::cout << "\t-    Logout     -" << std::endl;
	std::cout << std::endl;
}


bool AuctionSystem::Login(USER_RECORD userRecord, User &currentUser) {
	loggedIn = true;

	currentUser.username = userRecord.username;
	currentUser.accountType = userRecord.accountType;
	currentUser.credit = userRecord.credit;

	std::cout << "\nWelcome to the Auction System, " << currentUser.username << std::endl;
	return loggedIn;
}

void AuctionSystem::Logout() {
	std::cout << "\nExited Session." << std::endl;
	loggedIn = false;
}

