#include<vector> 
#include<iostream> 
#include<iomanip> 
#include<cmath>
#include <limits>
using namespace std;

//function prototypes
void MainMenu();
void R1();
void R2();
void R3();
void R4();
void Menu4();
void SAS();
void PT();
void EP();
void STH();
void R5();
void R6();

int calculateTokenCost(string service, int inputSize, char userType);

class Service {
public:
	Service() {
		uid =" "; service = " "; spent = 0; charge = 0;
	}

	void setRecord(string id, string name, int token, int money) {
		uid = id;
		service = name;
		spent = token;
		charge = money;
	}
	string getUid()
	{
		return uid;
	}

	string getService()
	{
		return service;
	}

	int getSpent()
	{
		return spent;
	}

	int getCharge()
	{
		return charge;
	}

private:
	string uid;
	string service;
	int spent;
	int charge;
};

class Purchasing {
public:
	Purchasing() {
		uid = " "; buy = 0; money = 0;
	}

	void setPrecord(string id,int t,int m)
	{
		uid = id;
		buy = t;
		money = m;
	}

	string getUid()
	{
		return uid;
	}

	int getBuy() {
		return buy;
	}

	int getMoney() {
		return money;
	}

private:
	string uid;
	int buy;
	int money;
};


class User 
{
public:
	User(){
		ID = " "; Type = ' '; vToken.clear(); Auto = false;
	}

	// for input element
	void setUser(string _id, char _type, int _token, bool _auto) 
	{
		ID = _id;
		Type = _type;
		vToken.clear();
		vToken.push_back(_token);
		Auto = _auto;
	}

	void setType(char t)
	{
		Type = t;
	}

	void setAuto(bool a)
	{
		Auto = a;
	}

	void setbalance(int token) {
		vToken.push_back(token);
	}


	string getID()
	{
		return ID;
	}

	char getType()
	{
		return Type;
	}

	int getToken()
	{
		return vToken.back();
	}

	int get1Token()
	{
		return vToken.front();
	}

	void printTokens() {
		for (int token : vToken) {
			cout << token << endl;
		}
		cout << endl;
	}

	char getAuto()
	{
		if (Auto) {
			return 'Y';
		}
		else
			return 'N';
	}

private:
	string ID;
	char Type;
	bool Auto;
	vector<int> vToken;
};


//declare the vector for User
vector<User> vUser;
User user;
Service record;
Purchasing precord;
vector<Service> vRecord;
vector<Purchasing> vPrecord;


//declare the gobal variables
int r1Count = 0;
int userIndex = -1;


// fuction for the MainMenu
void MainMenu() 
{
	char prog_choice;

	cout << "Welcome to AI Service System" << endl;
	cout << "*** Main Menu ***" << endl;
	cout << "[1] Load Stating Data" << endl;
	cout << "[2] Show User Records" << endl;
	cout << "[3] Edit Users" << endl;
	cout << "[4] Enter User View" <<endl;
	cout << "[5] Show System Usage Summary" << endl;
	cout << "[6] Credits and Exit" << endl;
	cout << "*****************" << endl;

	while (true)
	{
		cout << "Option (1-6): ";
		cin >> prog_choice;

		if (cin.fail() || prog_choice < '1' || prog_choice > '6')
		{
			cin.clear();
			cout << "Error input. Please enter a number between 1 and 6." << endl;
		}
		else
		{
			break;
		}
	}

	if (prog_choice != '1' && r1Count < 1) {
		cout << "Starting Data dosen't load yet, please load the data before use other services" << endl;
		cout << endl;
		MainMenu();
	}
	else{
		switch (prog_choice){
		case '1': R1(); break;
		case '2': R2(); break;
		case '3': R3(); break;
		case '4': R4(); break;
		case '5': R5(); break;
		case '6': R6(); break;
		default:
			cout << "Error input ";
			break;
		}
	}
}

//function for the Load Stating Data
void R1()
{
	r1Count++;
	cout << left;
	cout << setw(60) << "User ID" << setw(10) << "Type" << setw(20) << "Token Balance" << setw(15) << "Auto Top-up" << endl;
	cout << string(100, '-') << endl;
	
	for (auto it = vUser.begin(); it != vUser.end(); it++) {
		cout << setw(60) << it->getID() << setw(10) << it->getType() << setw(20) << it->getToken() << setw(15) << it->getAuto() << endl;
	}

	cout << endl;

	MainMenu();

}

//fucition for the Show User Records
void R2()
{
	vector<User> sortedUsers = vUser;

	for (int i = 0; i < sortedUsers.size() - 1; i++) {
		for (int j = 0; j < sortedUsers.size() - i - 1; j++) {
			if (sortedUsers[j].getID() > sortedUsers[j + 1].getID()) {
				User temp = sortedUsers[j];
				sortedUsers[j] = sortedUsers[j + 1];
				sortedUsers[j + 1] = temp;
			}
		}
	}

	cout << "\nUser Records (Sorted by User ID)" << endl;
	cout << string(100, '-') << endl;
	cout << left;
	cout << setw(60) << "User ID"
		<< setw(10) << "Type"
		<< setw(20) << "Token Balance"
		<< setw(15) << "Auto Top-up" << endl;
	cout << endl;

	for (User& user : sortedUsers) {
		cout << left;
		cout << setw(60) << user.getID()
			<< setw(10) << user.getType()
			<< setw(20) << user.getToken()
			<< setw(15) << user.getAuto() << endl;
	}

	cout << endl;

	MainMenu();
}

//fucition for the Edit Users 
void R3()
{
	char choice;
	int userIndex = -1;
	string uid;
	char type;
	int token;
	bool autoTopup;
	int count = 0;
	const int maxCount = 3;

	cout << "Please enter User ID: ";
	cin >> uid;
	cout << endl;

	//delete user
	for (int i = 0; i < vUser.size(); i++) {
		if (vUser[i].getID() == uid) {
			userIndex = i;
			cout << "The detail of the account of " << uid << " is below:" << endl;
			cout << "UserID :" << vUser[i].getID() << endl;
			cout << "The account type: " << vUser[i].getType() << endl;
			cout << "The toekn balance :" << vUser[i].getToken() << endl;
			cout << "Auto-top up: " << vUser[i].getAuto() << endl;
			cout << "Confirm to delete this user record (Y / N) :";
			cin >> choice;
			if (choice == 'Y') {
				vUser.erase(vUser.begin() + i);
				cout << "The record of " << uid << " is deleted" << endl << endl;
				MainMenu();
			}
			else {
				cout << endl;
				MainMenu();
			}
		}
	}

	//add user
	if (userIndex == -1) {
		while (count < maxCount) {
			cout << "Please select your account type (T/F/S): ";
			cin >> type;

			if (type != 'T' && type != 'F' && type != 'S') {
				count++;
				cout << "Invalid account type. Please try again." << endl;
				continue;
			}

			cout << "Please enter your token balance : ";
			cin >> token;
			if (cin.fail() || token < 0) {
				cin.clear();
				count++;
				cout << "Invalid token balance. Please try again. " << endl;
				continue;
			}

			cout << "Please choose to use auto-top up or not (Y/N): ";
			cin >> choice;
			if (choice != 'Y' && choice != 'N') {
				count++;
				cout << "Invalid choice for auto-top up. Please try again." << endl;
				continue;
			}
			break;
		}

		if (count >= maxCount) {
			cout << "Exceeded maximum attempts. Return to the mainmeun" << endl << endl;
			MainMenu();
		}

		if (choice == 'Y')
			autoTopup = true;
		else
			autoTopup = false;

		user.setUser(uid, type, token, autoTopup);
		vUser.push_back(user);

		cout << "New account with username " << uid << " is added" << endl<<endl;
		MainMenu();

	}
}

//fucition for Enter User View  
void R4()
{
	string uid;
	cout << "R4" << endl;
	cout << "Please enter your User ID: ";
	while (true)
	{
		cin >> uid;
		// Check if the user ID is empty or contains invalid characters
		if (uid.empty())
		{
			cout << "Invalid input. User ID cannot be empty. Please enter again: ";
		}
		else
		{
			break; // Valid input, exit the loop
		}
	}
	
	for (int i = 0; i < vUser.size(); i++) {
		if (vUser[i].getID() == uid) {
			userIndex = i;
			Menu4();
			break;
		}
	}
	if (userIndex == -1) {
		cout << "User not found." << endl << endl;
		MainMenu();
	}
}

//fucition for User meun
void Menu4()
{
	char prog_choice;
	cout << "Action for User ID: " << vUser[userIndex].getID() << endl;
	cout << "*****User View Menu*****" << endl;
	cout << "[1] Select AI Service" << endl;
	cout << "[2] Purchase Tokens" << endl;
	cout << "[3] Edit Profile" << endl;
	cout << "[4] Show Transaction History" << endl;
	cout << "[5] Return to Main Menu" << endl;
	cout << "*****************" << endl;
	cout << "Option (1-5) : ";
	cin >> prog_choice;
	cout << endl << endl;

	if (prog_choice != '1' && prog_choice != '2' && prog_choice != '3' && prog_choice != '4' && prog_choice != '5') {
		cout << "Not a valid option!" << endl;
		cout << endl;
		Menu4();
	}
	else {
		switch (prog_choice) {
		case '1': SAS(); break;
		case '2': PT(); break;
		case '3': EP(); break;
		case '4': STH(); break;
		case '5': MainMenu(); break;
		}
	}
}

int calculateTokenCost(string service, int inputSize, char userType) {
	if (service == "Image Recognition") {
		if (inputSize < 3) {
			return (userType == 'T') ? 5 : (userType == 'F') ? 5 : 4;
		}
		else {
			return (userType == 'T') ? -1 : (userType == 'F') ? 8 : 7;
		}
	}
	else if (service == "Speech-to-text") {
		if (inputSize <= 3) return inputSize * 2;
		return 3 * 2 + (inputSize - 3) * 3;
	}
	else if (service == "Predictive Analysis") {
		return 10 * inputSize;
	}
	else if (service == "NLP") {
		int tokens = ceil(inputSize / 500.0);
		if (userType == 'T' && inputSize > 2500) return -1; // Invalid for Trial over 2500
		return tokens;
	}
	return -1;
}

//fucition for Select AI Service
void SAS()
{
	cout << "Select AI Service View" << endl;;

	// Display AI services
	cout << "Available AI Services:"<<endl;
	cout << "[1] Image Recognition" << endl;
	cout << "[2] Speech - to - text" << endl; 
	cout << "[3] Predictive Analysis" << endl;
	cout << "[4] NLP" << endl;

	int choice = 0;
	while (true)
	{
		cout << "Select service (1-4): ";
		cin >> choice;

		if (cin.fail() || choice < 1 || choice > 4)
		{
			cin.clear();										 
			cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
		}
		else
		{
			// Valid input, exit the loop
			break;												
		}
	}

	string service;
	int inputSize = 0;

	switch (choice)
	{
	case 1:
		service = "Image Recognition";
		cout << "Enter image size (in MB): ";
		break;
	case 2:
		service = "Speech-to-text";
		cout << "Enter audio length (in minutes): ";
		break;
	case 3:
		service = "Predictive Analysis";
		cout << "Enter number of prediction tasks: ";
		break;
	case 4:
		service = "NLP";
		cout << "Enter text length (in characters): ";
		break;
	}

	// Input validation for inputSize
	while (true)
	{
		cin >> inputSize;

		if (cin.fail() || inputSize < 0)
		{														 
			cin.clear();
			cout << "Invalid input. Please enter a non-negative integer." << endl;
		}
		else
		{
			break;
		}
	}


	char userType = vUser[userIndex].getType();
	int tokenCost = calculateTokenCost(service, inputSize, userType);


	if (tokenCost == -1) {
		cout << "Service not allowed for this user type." << endl << endl;
		Menu4();
	}

	int currentBalance = vUser[userIndex].getToken();
	bool autoTopUp = (vUser[userIndex].getAuto() == 'Y');

	int charge=0;

	if (currentBalance >= tokenCost) {
		cout << "Service paid with " << tokenCost << " tokens." << endl;
		// Deduct tokens
		currentBalance -= tokenCost;

		//Insert the service record
		record.setRecord(vUser[userIndex].getID(),service, tokenCost, charge);
		vRecord.push_back(record);
	}
	else if (autoTopUp) {
		int additionalTokens = ((tokenCost - currentBalance + 19) / 20) * 20; // Round up to nearest 20
		cout << "Auto Top-up enabled. Adding " << additionalTokens << " tokens."<<endl;
		currentBalance += additionalTokens - tokenCost;
		charge = additionalTokens * 2;

		//Insert the service record
		record.setRecord(vUser[userIndex].getID(),service, tokenCost, charge);
		vRecord.push_back(record);
	}
	else {
		cout << "Insufficient balance and Auto Top-up disabled." << endl;
	}

	// Update user balance
	vUser[userIndex].setbalance(currentBalance);
	cout << "Updated balance: " << currentBalance << " tokens."<<endl<<endl;

	Menu4();
}

//fucition for Purchase Tokens 
void PT()
{
	cout << "Purchase Tokens"<<endl;

	int amount;
	while (true)
	{
		cout << "Enter amount of money to spend on tokens (even integer): ";
		cin >> amount;

		if (cin.fail() || amount <= 0 || amount % 2 != 0)
		{
			cin.clear();										 
			cout << "Error: Amount must be a positive even integer." << endl
				<< endl;
		}
		else
		{
			break;
		}
	}

	int tokensToAdd = amount / 2; // Each token costs $2

	int currentBalance = vUser[userIndex].getToken();
	currentBalance += tokensToAdd; // Add tokens to balance

	// Update user balance
	vUser[userIndex].setbalance(currentBalance);

	//Insert the Purchas record
	precord.setPrecord(vUser[userIndex].getID(),tokensToAdd, amount);
	vPrecord.push_back(precord);

	cout << "Purchase successful! New token balance: " << currentBalance << endl<<endl;
	Menu4();
}

//fucition for Edit Profile  
void EP()
{
	int choice;
	char t, a;
	int tErrorCount = 0;
	int aErrorCount = 0;
	bool aType;

	while (true)
	{
		cout << "[1] Change Account Type" << endl;
		cout << "[2] Change Auto Top-up" << endl;
		cout << "Select service: ";
		cin >> choice;

		if (cin.fail() || (choice != 1 && choice != 2))
		{
			cin.clear();
			cout << "Invalid input. Please enter 1 or 2." << endl;
		}
		else
		{
			break;
		}
	}

	switch (choice) {
	case 1:

		bool tValid;
		cout << "Trial Account please enter T" << endl;
		cout << "Full Account please enter F" << endl;
		cout << "Student Account please enter S" << endl;

		do {
			cout << "Please enter the type(T/F/S):";
			cin >> t;

			if (t == 'T' || t == 'F' || t == 'S') {
				tValid = true;
			}
			else {
				tValid = false;
				tErrorCount++;
			}

			if (tValid == false && tErrorCount > 0 && tErrorCount < 3) {
				cout << " Invalid input, please input again" << endl << endl;
			}

			if (tValid == false && tErrorCount == 3) {
				cout << "Invalid input 3 times, return to the menu" << endl << endl;
				Menu4();
				break;
			}
		} while (tValid == false);

		if (tValid) {
			vUser[userIndex].setType(t);
			cout << "Chaning is completed" << endl << endl;
			Menu4();
		}
		break;
	case 2:
		bool aValid;
		cout << "Open the Auto-up please enter Y" << endl;
		cout << "Close the Auto-up please enter N" << endl;
		do {
			cout << "Please Enter(Y/N) :";
			cin >> a;

			if (a == 'Y' || a == 'N') {
				aValid = true;
			}
			else {
				aValid = false;
				aErrorCount++;
			}
			if (aValid == false && aErrorCount > 0 && aErrorCount < 3) {
				cout << " Invalid input, please input again" << endl << endl;
			}

			if (aValid == false && aErrorCount == 3) {
				cout << "Invalid input 3 times, return to the menu" << endl << endl;
				Menu4();
				break;
			}
		} while (aValid == false);

		if (aValid) {
			if (a == 'Y')
				aType = true;
			else
				aType = false;

			vUser[userIndex].setAuto(aType);
			cout << "Chaning is completed" << endl << endl;
			Menu4();
		}
		break;
	default:
		cout << "Error input ";
		break;
	}
}

//fucition for Show Transaction History
void STH()
{
	string user = "none";

	for (int i = 0; i < vRecord.size(); i++) {
		if (vRecord[i].getUid() == vUser[userIndex].getID()) {
			user = vUser[userIndex].getID();
			break;
		}
	}

	for (int i = 0; i < vPrecord.size(); i++) {
		if (vPrecord[i].getUid() == vUser[userIndex].getID()) {
			user = vUser[userIndex].getID();
			break;
		}
	}

	if (user == "none") {
		cout << " No Transactions Record, Reurn to the User View Menu." << endl << endl;
		Menu4();
	}
	else {
		cout << "Token transactions record for AI services:" << endl;
		cout << setw(20) << "Services" << setw(20) << "Token Spent" << setw(10) << "Auto-to Charge" << endl;
		cout << string(100, '-') << endl;
		for (int i = 0; i < vRecord.size(); i++) {
			if (vRecord[i].getUid() == user) {
				cout << setw(20) << vRecord[i].getService() << setw(20) << vRecord[i].getSpent() << setw(20) << vRecord[i].getCharge() << endl;
			}
		}
		cout << endl;

		cout << "Token transactions record for purchasing tokens:" << endl;
		cout << setw(20) << "Token purchase" << setw(20) << "Money spent" << endl;
		cout << string(100, '-') << endl;
		for (int i = 0; i < vPrecord.size(); i++) {
			if (vPrecord[i].getUid() == user) {
				cout << setw(20) << vPrecord[i].getBuy() << setw(20) << vPrecord[i].getMoney() << endl;
			}
		}

		cout << endl;

		cout << "First Token balance: " << vUser[userIndex].get1Token() << endl;
		cout << "Final token balance: " << vUser[userIndex].getToken() << endl;
		cout << "The change of token: " << endl;
		vUser[userIndex].printTokens();

		int spentSum = 0;
		int chargeSum = 0;
		int totalsum;

		for (int i = 0; i < vRecord.size(); i++) {
			if (vRecord[i].getUid() == user) {
				spentSum += vRecord[i].getCharge();
			}
		}

		for (int i = 0; i < vPrecord.size(); i++) {
			if (vPrecord[i].getUid() == user) {
				chargeSum += vPrecord[i].getMoney();
			}
		}

		totalsum = spentSum + chargeSum;

		cout << "The total amount of money paid for buying tokens :" << totalsum << endl << endl;

		Menu4();
	}
}

//fucition for Show System Usage Summary 
void R5()
{
	int s1Sum = 0;
	int s2Sum = 0;
	int s3Sum = 0;
	int s4Sum = 0;
	int totalsSum;

	int chagreSum = 0;
	int spentSum = 0;
	int totalMoney;

	//The token spent on Services"Image Recognition"
	for (int i = 0; i < vRecord.size(); i++) {
			if (vRecord[i].getService() == "Image Recognition") {
				s1Sum += vRecord[i].getSpent();
			}
	}
	cout << "The number of tokens spent on Image Recognition :" << s1Sum << endl;

	//The token spent on Services"Speech-to-text"
	for (int i = 0; i < vRecord.size(); i++) {
		if (vRecord[i].getService() == "Speech-to-text") {
			s2Sum += vRecord[i].getSpent();
		}
	}
	cout << "The number of tokens spent on Speech-to-text :" << s2Sum << endl;

	//The token spent on Services"Predictive Analysis"
	for (int i = 0; i < vRecord.size(); i++) {
			if (vRecord[i].getService() == "Predictive Analysis") {
				s3Sum += vRecord[i].getSpent();
			}
		}
	cout << "The number of tokens spent on Predictive Analysis :" << s3Sum << endl;
	
	//The token spent on Services"NLP"
	for (int i = 0; i < vRecord.size(); i++) {
			if (vRecord[i].getService() == "NLP") {
				s4Sum += vRecord[i].getSpent();
			}
	}
	cout << "The number of tokens spent on NLP :" << s4Sum << endl;

	//The total number  of tokens spent on all AI services by all users"
	totalsSum = s1Sum + s2Sum + s3Sum + s4Sum;
	cout << "The total number  of tokens spent on all AI services by all users : " << totalsSum<<endl;

	//The money spent on the auto-up charge
	for (int i = 0; i < vRecord.size(); i++) {
			chagreSum += vRecord[i].getCharge();
	}
	//The money spent on the purchase tokens 
	for (int i = 0; i < vPrecord.size(); i++) {
			spentSum += vPrecord[i].getMoney();
	}
	//Total money spent
	totalMoney = chagreSum + spentSum;
	cout << "the total amount of money paid for buying tokensby all users: " << totalMoney << endl << endl;

	//Reuturn to the mainmenu
	MainMenu();
	
}

//fucition for Credits and Exit 
void R6()
{
	char input;
	bool v;

	cout << "[Y]Show the Credits and Exit " << endl;
	cout << "[N]Return to the Main Menu" << endl;
	do {
		
		cout << "Please input(Y/N) : ";
		cin >> input;

		if (input == 'Y' || input == 'y' || input == 'N' || input == 'n')
			v = true;
		else {
			v = false;
			cout << "Incorrect input, input again" << endl;
		}
	} while (v!=true);
	
	if (v) {
		if (input == 'Y' || input == 'y') {
			cout << setw(20) << "Name" << setw(15) << "Student ID" << setw(10) << "tut group" << endl;
			cout << setw(20) << "Chow Hoi Hei" << setw(15) << "24047908S" << setw(10) << "102" << endl;
			cout << setw(20) << "Cheung chun Kan" << setw(15) << "24057490S" << setw(10) << "102" << endl;
			cout << setw(20) << "Feng Gao" << setw(15) << "24070414S" << setw(10) << "102" << endl;
			cout << setw(20) << "Kwok Mong Tat" << setw(15) << "24079330S" << setw(10) << "102" << endl;
			cout << setw(20) << "Wong Cheuk Him" << setw(15) << "24064801S" << setw(10) << "102" << endl;
			cout << "Thank you for using the AI services, hope to see you again" << endl;
		}
		else {
			cout << endl;
			MainMenu();
		}
	}

}





int main() 
{
	//Add user into vector 
	user.setUser("SkyWalker", 'T', 20, false);
	vUser.push_back(user);

	user.setUser("Ocean123", 'T', 30, false);
	vUser.push_back(user);

	user.setUser("Forest99", 'T', 6, true);
	vUser.push_back(user);

	user.setUser("Valley777", 'F', 10, true);
	vUser.push_back(user);

	user.setUser("Desert2022", 'F', 25, false);
	vUser.push_back(user);

	user.setUser("River456", 'F', 20, true);
	vUser.push_back(user);

	user.setUser("Blaze2023", 'F', 100, false);
	vUser.push_back(user);

	user.setUser("Meadow888", 'S', 40, true);
	vUser.push_back(user);

	user.setUser("Galaxy", 'S', 15, true);
	vUser.push_back(user);

	user.setUser("Storm2024", 'S', 30, false);
	vUser.push_back(user);

	MainMenu();

return 0;
}