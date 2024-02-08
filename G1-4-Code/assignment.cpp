#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <cctype>
#include <algorithm>

using namespace std;

const char AVAILABLE = '#';
const char TAKEN = '*';

// ANSI escape codes for text colors
const string COLOR_RESET = "\033[0m";
const string COLOR_AVAILABLE = "\033[32m";  // Green
const string COLOR_TAKEN = "\033[31m";      // Red

const int ROWS = 10,
COLUMNS = 10;

struct SaleRecord {
	string date;
	double amount;
	string type;
	bool isRefund;
};

// Function prototypes
void displayMenu();
void displaySeatingPrices(const double*);
void displaySeatingChart(const char[][COLUMNS]);
int inputValidate(int, int, int);
char inputValidateYesOrNo(char);
char inputValidateYesOrNo();
int displayLoginMenu();
int adminLoginMenu();
bool adminValidate(const string& keyInID, const string& keyInPassword);
void recordSale(double amount, int row_number, bool isRefund = false);
void displaySalesReport();

vector<SaleRecord> salesRecords;

// Function to record a sale and add the sale record to the vector
void recordSale(double amount, int row_number, bool isRefund) {
	// Get the current date and time and log the sale
	time_t t = time(0);
	struct tm now;
	localtime_s(&now, &t); // use localtime_s replace localtime

	SaleRecord record;
	record.date = to_string(now.tm_year + 1900) + '-' + to_string(now.tm_mon + 1) + '-' + to_string(now.tm_mday);

	// Determine the ticket type based on the row_number and set the amount
	if (row_number == 1) {
		record.type = "Ultimate Experience";
	}
	else if (row_number >= 2 && row_number <= 3) {
		record.type = "My Universe";
	}
	else if (row_number >= 4 && row_number <= 5) {
		record.type = "Higher Power";
	}
	else if (row_number == 6) {
		record.type = "Category 1";
	}
	else if (row_number >= 7 && row_number <= 8) {
		record.type = "Category 2";
	}
	else if (row_number >= 9 && row_number <= 10) {
		record.type = "Category 3";
	}

	if (amount >= 0) {
		// Use positive amount for sales
		record.amount = amount;
		record.isRefund = false; // Set isRefund to false for sales
	}
	else {
		// Use negative amount for refunds
		record.amount = -amount;
		record.isRefund = true; // Set isRefund to true only for refund records
	}

	// Add the sale record to the vector
	salesRecords.push_back(record);

	cout << "\n";
}

// Function to display the sales report
void displaySalesReport() {
	if (salesRecords.empty()) {
		cout << setw(75) << "No sales records available." << endl;
	}
	else {

		string currentDate = "";
		double totalSales = 0.0;

		// Iterate through sales records and display relevant information
		for (auto& record : salesRecords) {
			if (currentDate != record.date) {
				// Display a header for each new date
				cout << setw(55) << "Date: " << record.date << endl;
				cout << setw(80) << "----------------------------------------" << endl;
				cout << setw(68) << "Ticket Type    Sales\t\tRemark" << endl;
				currentDate = record.date;
				totalSales = 0.0;
			}

			// Display ticket information for both sales and refunds
			cout << setw(50) << record.type << ' ' << fixed << setprecision(2) << setw(5) << "RM" << record.amount;

			if (record.isRefund) {
				// Display refund records separately
				cout << setw(16) << "(Refund)";
			}

			cout << endl;

			// Add the amount to total sales for the date
			totalSales += (record.isRefund ? -record.amount : record.amount);
		}

		// Display the total sales for the date
		cout << setw(80) << "----------------------------------------" << endl;
		cout << setw(60) << "Total Sales for " << currentDate << ": RM" << totalSales << endl;
	}
}

bool adminValidate(const string& keyInID, const string& keyInPassword) {
	string adminID = "hehe";
	string adminPassword = "admin123";

	// Check password and ID are correct or not
	return keyInID == adminID && keyInPassword == adminPassword;
}

int main()
{
	double seat_prices[ROWS] = { 998, 898, 898, 698, 698, 598, 498, 498, 398, 398 };
	char seating_chart[ROWS][COLUMNS] = {
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
	};

	int menu_choice,
		seats_sold = 0;
	char user_choice = 0;
	double total_ticket_sales = 0;
	int row_number = 0;
	int seat_number = 0;
	int number = 0;
	int cardnum = 0;
	char choose;
	double order_total = 0;

	displayLoginMenu();

	do
	{
		cout << setw(70) << "Enter menu choice: ";
		cin >> menu_choice;

		if (menu_choice == 1)
		{
			cout << setw(65) << "Menu choice = " << menu_choice << endl;
			cout << "\n";
			cout << setw(64) << "Seat prices: " << endl;
			displaySeatingPrices(seat_prices);
			chrono::seconds delay(1);
			this_thread::sleep_for(delay);
			displayMenu();

		}
		else if (menu_choice == 2)
		{
			cout << "\n";
			cout << setw(65) << "Menu choice = " << menu_choice << endl;
			cout << setw(66) << "Seating chart: " << endl
				<< setw(73) << "Taken = * | Available = #" << endl;
			displaySeatingChart(seating_chart);
			chrono::seconds delay(2);
			this_thread::sleep_for(delay);
			displayMenu();

		}
		else if (menu_choice == 3)
		{
			// Set total_ticket_sales to 0
			total_ticket_sales = 0;

			cout << setw(73) << "Taken = * | Available = #" << endl;
			displaySeatingChart(seating_chart);
			cout << setw(65) << "Menu choice = " << menu_choice << endl;

			cout << setw(65) << "Choose a seat " << endl;
			cout << setw(64) << "Enter row #: ";
			int row_number = inputValidate(0, 1, 10);

			cout << setw(65) << "Enter seat #: ";
			int seat_number = inputValidate(0, 1, 10);

			if (seating_chart[row_number - 1][seat_number - 1] == '#')
			{
				cout << setw(70) << "That seat is available." << endl << endl;
				cout << setw(60) << "The price for Row #:" << row_number
					<< " Seat #" << seat_number
					<< " is RM" << seat_prices[row_number - 1] << "."
					<< endl;

				cout << setw(70) << "Would you like to purchase Row # (Y/N):" << row_number << " Seat #" << seat_number << "? :";
				user_choice = inputValidateYesOrNo(user_choice);

				if (user_choice == 'Y' || user_choice == 'y')
				{
					// User has chosen to purchase a seat

					// Reset total_ticket_sales to 0
					total_ticket_sales = 0;
					do
					{
						// Every time a ticket or group of tickets is purchased, 
						// the program should display the total ticket prices 
						// and update the seating chart.

						// Update seating chart and calculate total ticket sales
						seating_chart[row_number - 1][seat_number - 1] = '*';
						total_ticket_sales += seat_prices[row_number - 1];

						cout << setw(66) << "Total charges: RM" << total_ticket_sales << endl;

						// keep a total of all ticket sales. 
						seats_sold++;

						// Prompt user if they want to choose another seat
						cout << setw(80) << "Do you want to choose another seat? (Y/N):";
						cin >> choose;

						if (choose == 'Y' || choose == 'y')
						{
							// Prompt user for row and seat number
							cout << setw(64) << "Enter row #: ";
							row_number = inputValidate(0, 1, 10);

							cout << setw(65) << "Enter seat #: ";
							seat_number = inputValidate(0, 1, 10);
							cout << setw(60) << "The price for Row #:" << row_number
								<< " Seat #" << seat_number
								<< " is RM" << seat_prices[row_number - 1] << "."
								<< endl;

							while (seating_chart[row_number - 1][seat_number - 1] == '*')
							{
								// Seat is already taken, prompt user to choose another seat
								cout << setw(50) << "Seat #" << seat_number << " in Row #" << row_number << " is already taken. Choose another seat." << endl;

								// Prompt user for row and seat number again
								cout << setw(64) << "Enter row #: ";
								row_number = inputValidate(0, 1, 10);

								cout << setw(65) << "Enter seat #: ";
								seat_number = inputValidate(0, 1, 10);
								cout << setw(60) << "The price for Row #:" << row_number << " Seat #"
									<< seat_number << " is RM" << seat_prices[row_number - 1] << "." << endl;
							}
						}
					} while (choose == 'Y' || choose == 'y');

					// Process payment options
					do
					{
						cout << "\n";
						cout << setw(80) << "------------------------------------------" << endl;
						cout << setw(65) << "PAYMENT GATEWAY" << endl;
						cout << setw(80) << "------------------------------------------" << endl;
						cout << setw(70) << "[1] Credit or Debit Card\n" << setw(66) << "[2] Internet Banking\n" << setw(76) << "[3] Cash Payment with 7 Eleven\n" << setw(69) << "[4] Boost or TNG eWallet" << endl;
						cout << setw(70) << "Choose a payment method: ";
						cin >> number;

						// Process payment based on the selected method
						string cardnum;
						if (number == 1) {
							cout << setw(70) << "Enter Credit or Debit Card No( 16 digit): ";
							cin >> cardnum;

							while (cardnum.length() != 16 || !all_of(cardnum.begin(), cardnum.end(), ::isdigit)) {
								cout << "Invalid input. Please enter a 16-digit number: ";
								cin >> cardnum;
							}
							cout << "Valid card number: " << cardnum << endl;
						}
						else if (number == 2) {
							cout << setw(70) << "Please bank in to our company's public bank, \nbank account number is 51343002155" << endl;

						}
						else if (number == 3) {
							cout << setw(85) << "Scan this barcode and pay at 7 Eleven" << endl;
							cout << setw(70) << "|| |||  | | ||| |||   | |||" << endl;

						}
						else if (number == 4) {
							cout << setw(70) << "Scan this barcode" << endl;
							cout << setw(70) << "| || ||| ||| || ||| | |||||" << endl;
						}
					} while (number != 1 && number != 2 && number != 3 && number != 4);

					// Record the sale, display success message, and generate admission pass
					recordSale(total_ticket_sales, row_number);
					cout << setw(70) << "Payment in progress..." << endl;
					chrono::seconds delay(2);
					this_thread::sleep_for(delay);
					cout << setw(65) << "Payment successful" << endl;
					cout << setw(73) << "Admission pass is generating" << endl;
					chrono::seconds delay2(2);
					this_thread::sleep_for(delay2);
					cout << setw(80) << "---------------------------------------" << endl;
					cout << setw(80) << "|                                     |" << endl;
					cout << setw(80) << "|                                     |" << endl;
					cout << setw(80) << "|                                     |" << endl;
					cout << setw(80) << "|            Admission Pass           |" << endl;
					cout << setw(80) << "|                                     |" << endl;
					cout << setw(80) << "|                                     |" << endl;
					cout << setw(80) << "|                                     |" << endl;
					cout << setw(80) << "|                                     |" << endl;
					cout << setw(80) << "---------------------------------------" << endl;
					cout << "\n" << endl;
					cout << setw(75) << "Thank you for purchase our ticket" << endl;
					cout << "\n" << endl;

				}
				else if (user_choice == 'N' || user_choice == 'n')
				{
					// User has chosen not to purchase a seat, display main menu
					displayMenu();
					continue;

				}

			}

			else
			{
				cout << setw(80) << "That seat is NOT available." << endl;
				cout << setw(80) << "Would you like to pick another seat?(Y/N) :";
				char user_choice = inputValidateYesOrNo();

			}
			chrono::seconds delay(1);
			this_thread::sleep_for(delay);
			displayMenu();
		}

		// User has chosen to proceed with a refund
		// Display refund options and prompt user for row and seat number
		else if (menu_choice == 4)
		{

			cout << setw(80) << "----------------------------------------" << endl;
			cout << setw(65) << "REFUND" << endl;
			cout << setw(80) << "----------------------------------------" << endl;

			cout << setw(73) << "Taken = * | Available = #" << endl;
			displaySeatingChart(seating_chart);
			cout << setw(65) << "Menu choice = " << menu_choice << endl;

			cout << setw(65) << "Choose a seat " << endl;
			cout << setw(64) << "Enter row #: ";
			int row_number = inputValidate(0, 1, 10);

			cout << setw(65) << "Enter seat #: ";
			int seat_number = inputValidate(0, 1, 10);

			if (seating_chart[row_number - 1][seat_number - 1] == '*')
			{
				cout << "\n";
				cout << setw(60) << "Refund for Row #" << row_number << " Seat #" << seat_number << " is RM" << seat_prices[row_number - 1] << "." << endl;
				cout << setw(90) << "Would you like to proceed with the refund? (Y/N): ";
				char refund_choice = inputValidateYesOrNo();

				if (refund_choice == 'Y' || refund_choice == 'y')
				{

					string num;
					// Refund the money through banking
					cout << setw(70) << "Enter your credit/debit card number:";
					cin >> num;
					while (num.length() != 16 || !all_of(num.begin(), num.end(), ::isdigit)) {
						cout << "Invalid input. Please enter a 16-digit number: ";
						cin >> num;
					}
					cout << "Valid card number: " << num << endl;

					// Perform the refund
					seating_chart[row_number - 1][seat_number - 1] = '#';
					total_ticket_sales -= seat_prices[row_number - 1];
					seats_sold--;

					cout << setw(70) << "Refund successful." << endl;
					recordSale(-seat_prices[row_number - 1], row_number, true);
				}
				else
				{
					cout << setw(70) << "Refund canceled." << endl;
				}
			}
			else
			{
				cout << setw(80) << "Seat is not taken. No refund available." << endl;
			}
			chrono::seconds delay(1);
			this_thread::sleep_for(delay);
			displayMenu(); // Let customer can return to menu 

		}
		else if (menu_choice == 5) {
			chrono::seconds delay(1);
			this_thread::sleep_for(delay);
			displayLoginMenu(); // For staff return to the login menu

		}

		else if (menu_choice == 6) {
			cout << setw(80) << "Exiting program. Have a nice day!" << endl;
			break; //Use to stop the program
		}


	} while (menu_choice != 6);

	return 0;
} // END int main()


// Function to validate and ensure the user enters a valid 'Y' or 'N'
// Returns the validated character representing the user's choice.
char inputValidateYesOrNo()
{
	char letter;
	cin >> letter;

	// Keep prompting the user until a valid input ('Y' or 'N') is provided

	while (!(letter == 'Y' || letter == 'y' || letter == 'N' || letter == 'n'))
	{
		// Display an error message and clear the input buffer if an invalid input is detected
		cout << setw(80) << "Error: Enter a \"Y\" for yes or \"N\" for \"no\"";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> letter;
	}

	return letter;
}




// Function to display the main menu options
void displayMenu()
{
	cout << setw(80) << "-------------------------------------------" << endl;
	cout << setw(76) << "Cool Play Concert Ticketing System" << endl;
	cout << setw(80) << "-------------------------------------------" << endl;
	cout << "\n";
	cout << setw(69) << "Choose from menu: " << endl
		<< setw(66) << "[1] Seat Prices" << endl
		<< setw(68) << "[2] Seating Chart" << endl
		<< setw(70) << "[3] Purchase a seat" << endl
		<< setw(61) << "[4] Refund" << endl
		<< setw(75) << "[5] Return to Login Menu" << endl
		<< setw(60) << "[6] Quit " << endl
		<< setw(70) << endl;
}

// Function to display seating prices
void displaySeatingPrices(const double array[])
{
	for (int i = 0; i < ROWS; i++)
		cout << setw(56) << "Row #" << (i + 1) << " = RM" << array[i] << " " << endl;

	cout << endl;

}

// Function to display seating chart
void displaySeatingChart(const char array[][COLUMNS]) {
	cout << setw(80) << "---------------------------------------" << endl;
	cout << setw(67) << "Seating Chart" << endl;
	cout << setw(80) << "---------------------------------------" << endl;
	cout << setw(75) << "------------------------------" << endl;
	cout << setw(75) << "|           STAGE            |" << endl;
	cout << setw(75) << "------------------------------" << endl;

	for (int row = 0; row < ROWS; ++row) {
		cout << setw(50) << "|";
		for (int column = 0; column < COLUMNS; ++column) {
			if (array[row][column] == AVAILABLE) {
				cout << COLOR_AVAILABLE << setw(2) << array[row][column] << COLOR_RESET;
			}
			else if (array[row][column] == TAKEN) {
				cout << COLOR_TAKEN << setw(2) << array[row][column] << COLOR_RESET;
			}
			else {
				cout << setw(2) << array[row][column];
			}
		}
		cout << setw(2) << "|";
		cout << endl;
	}
	cout << setw(75) << "row 1 = Ultimate Experience" << endl
		<< setw(69) << "row 2-3 = My Universe" << endl
		<< setw(70) << "row 4-5 = Higher power" << endl
		<< setw(66) << "row 6 = Category 1" << endl
		<< setw(68) << "row 7-8 = Category 2" << endl
		<< setw(69) << "row 9-10 = Category 3" << endl;
}




// Function to validate user input within a specified range
int inputValidate(int user_number, int lowest, int highest)
{
	while (!(cin >> user_number) || (user_number < lowest || user_number > highest))
	{
		cout << setw(77) << "Error: Enter a number from " << lowest << " to " << highest << ": ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return user_number;

}

// Function to validate user input for yes or no
char inputValidateYesOrNo(char letter)
{
	cin >> letter;
	while (!(letter == 'Y' || letter == 'y' || letter == 'N' || letter == 'n'))
	{
		cout << setw(80) << "Error: Enter a \"Y\" for yes or \"N\" for \"no\"";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> letter;
	}

	return letter;

}
// Function to display the admin login menu and handle authentication
int adminLoginMenu() {
	string adminID;
	string adminPassword;

	cout << setw(64) << "Enter ID: ";
	cin >> adminID;
	cout << setw(70) << "Enter password: ";
	cin >> adminPassword;

	// Check if the entered ID and password are correct
	if (adminValidate(adminID, adminPassword)) {
		cout << setw(80) << "----------------------------------------" << endl;
		cout << setw(80) << "             Sales Report               " << endl;
		cout << setw(80) << "----------------------------------------" << endl;
		displaySalesReport(); // Display sales report for the admin

		char answer;
		cout << setw(77) << "Press E to return to Login Menu:";
		cin >> answer;

		while (answer != 'E' && answer != 'e') {
			cout << setw(80) << "Invalid answer. Enter the correct answer (E/e):";
			cin >> answer;
		}
		displayLoginMenu(); // Recursive call to the login menu
	}
	else {
		cout << setw(85) << "Wrong ID or password, please try again.\n";
		adminLoginMenu(); // Ask the user to enter ID and password again
	}

	return 0;
}


// Function to display the login menu and handle user authentication
int displayLoginMenu() {
	int user_type;
	char answer;
	cout << setw(80) << "----------------------------------------" << endl;
	cout << setw(65) << "Log In Menu" << endl;
	cout << setw(80) << "----------------------------------------" << endl;
	cout << setw(65) << "[1] Customer" << endl;
	cout << setw(62) << "[2] Admin" << endl;
	cout << setw(72) << "Choose your user type: ";
	cin >> user_type;

	if (user_type == 1)
	{
		displayMenu();// Assuming this should display the main menu for the customer

	}
	else if (user_type == 2)
	{
		adminLoginMenu();
	}
	else if (user_type != 1 && user_type != 2)
	{
		cout << setw(80) << "Invalid user type. Please enter again." << endl;
		displayLoginMenu();
	}

	return 0;
}