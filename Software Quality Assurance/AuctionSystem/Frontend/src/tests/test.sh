# Script: test.sh
# Authors: Francis Hackenberger, Ryan Goulding, Justin Estaris
# Details: Iterates over all testing input files and stores outputs in
#		   a directory to be used in the comparison script.

#Set the location of the test inputs to the 'FILES' variable
INPUT_FILES=./inputs/*.txt;
TEST_FILES_LOC=./outputs/actual;

#pre-condition files
CURRENT_USERS=../iofiles/current_users.txt
AVAIL_ITEMS=../iofiles/available_items.txt

#Color codes
GRAY='\033[0;37m';
NC='\033[0m';

#Remove previous test files
rm $TEST_FILES_LOC/*;

#Clear current users and available items files
truncate -s 0 $CURRENT_USERS $AVAIL_ITEMS

#Fill current users file with preset users to meet pre-conditions
printf "User01 AA 0\nUser02 FS 0\nUser03 BS 0\nUser04 SS 0" >> $CURRENT_USERS
	
#Iterate through all of the files specified in the 'FILES' variable
for file in $INPUT_FILES 
do 
	#Set the filename of the current test to be used for output
	filename=$(basename $file);
	testname=${filename%%.*};
	printf "${NC}Processing test: ${GRAY}$filename\n";
	
	#Run the auction system program and pipe output to external file named according to the current test name
	../auction_system ../iofiles/current_users.txt ../iofiles/available_items.txt $TEST_FILES_LOC/daily_transaction.txt < $file >> $TEST_FILES_LOC/$testname.txt
done

#Run the compare script to compare test output with expected output files
./compare.sh