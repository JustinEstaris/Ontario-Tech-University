package backend;

//User Class - Contains individual user information and methods
public class User {
	// Private attributes
	private String username;
	private String accountType;
	private double creditAmount;
	
	// Constructor
	public User(String _username, String _accountType, double _creditAmount) {
		username = _username;
		accountType = _accountType;
		creditAmount = _creditAmount;
	}
	
	// Methods
	//Returns the users username
	public String getUsername(){
		return username;
	}
	
	//Adds the value passed as a parameter to the creditAmount
	public void updateCreditAmount(double credit) {
		creditAmount += credit;
	}

	//Creates a string in the correct format for the active user file
	public void setUsername(String username) {
		this.username = username;
	}
	
	//Returns the users account type
	public String getAccountType() {
		return accountType;
	}

	//Sets the users account type
	public void setAccountType(String accountType) {
		this.accountType = accountType;
	}

	//Returns the users total credit amount
	public double getCreditAmount() {
		return creditAmount;
	}

	//Sets the users credit amount
	public void setCreditAmount(double creditAmount) {
		this.creditAmount = creditAmount;
	}

	//Creates a string in the correct format for the active user file.
	public String formatOutput() {
		String output;
		
		//a string in the format 'UUUUUUUUUUUUUUU TT CCCCCCCCC'
		//where UUUUUUUUUUU is the username, TT is acountType, and CCCCCCCCC is creditAmount		
		output = String.format("%1$" + -15 + "s", username) + " " + accountType + " " + String.format("%09.2f", creditAmount);
		
		return output;
	}
}
