#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <sstream>

/* CONSTANTS DECLARATIONS */
// Account Types
const std::string ADMIN = "AA";
const std::string FULL_STANDARD = "FS";
const std::string SELL_STANDARD = "SS";
const std::string BUY_STANDARD = "BS";

// Transaction Codes
const std::string LOGOUT_TRANSACTION_CODE = "00";
const std::string CREATE_TRANSACTION_CODE = "01";
const std::string DELETE_TRANSACTION_CODE = "02";
const std::string ADVERTISE_TRANSACTION_CODE = "03";
const std::string BID_TRANSACTION_CODE = "04";
const std::string REFUND_TRANSACTION_CODE = "05";
const std::string ADDCREDIT_TRANSACTION_CODE = "06";

// Minimums and Maximums
const int MAX_CREDIT = 999999;
const int MIN_CREDIT = 0;
const int MAX_CREDIT_ADD = 1000;
const int MAX_DURATION = 999;
const int MAX_USERNAME_LENGTH = 15;

/* RECORD DELCARATIONS */
struct ITEM_RECORD {
	std::string itemName;
    std::string seller;
	std::string buyer;
	float highestBid = 0;
	float minBid = 0;
    int duration = 1;
};

struct REFUND_RECORD {
	std::string buyer;
	std::string seller;
	float amount;
};

struct USER_RECORD {
    std::string username;
	std::string accountType;
	float credit = 0;
};

/* RECORD FUNCTIONS */
// Puts a record (item record) into a string
inline std::string recordToString(ITEM_RECORD itemRecord){
    std::stringstream itemStream;
	itemStream << itemRecord.itemName << " " << itemRecord.seller << " " << itemRecord.duration << " " << itemRecord.minBid;
	std::string itemInfo = itemStream.str();
	return itemInfo;
}

// Overloads the recordToString function to accept a refund record
inline std::string recordToString(REFUND_RECORD refundRecord){
    std::stringstream refundStream;
	refundStream << refundRecord.buyer << " " << refundRecord.seller << " " << refundRecord.amount;
	std::string refundInfo = refundStream.str();
	return refundInfo;
}

// Overloads the recordToString function to accept a user record
inline std::string recordToString(USER_RECORD userRecord){
    std::stringstream userStream;
	userStream << userRecord.username << " " << userRecord.accountType << " " << userRecord.credit;
	std::string userInfo = userStream.str();
	return userInfo;
}

#endif