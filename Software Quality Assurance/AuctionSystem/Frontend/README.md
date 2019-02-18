#NOTE: THIS PROGRAM IS INTENDED TO RUN ON A LINUX UBUNTU SUBSYSTEM FOR WINDOWS

#RUNNING THE AUCTION-SYSTEM PROGRAM
--> open PowerShell in or cd to ./UOIT-Auction/auction_system
--> Run the following commands:
    > bash
    > make
    > ./auction_system ./iofiles/current_users.txt ./iofiles/available_items.txt ./iofiles/daily_transaction.txt

#RUNNING THE TEST SCRIPTS
--> open PowerShell in or cd to ./UOIT-Auction/auction_system/tests
--> run the following commands:
    > bash
    > ./test.sh

--> the ./test.sh script will run both test.sh (runs the tests) and the
    compare.sh script (compare test output with expected output).
