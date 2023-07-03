using namespace std;
#include <iostream>
#include<fstream>
#include<string>
#include<conio.h>


class Book {
private:
	int id;
	float price;
	string title;
public:
	// setters
	void setId(int _id) {
		id = _id;
	}
	void setPrice(float _price) {
		price = _price;
	}
	void setTitle(string _title) {
		title = _title;
	}
	// getters
	int getId() {
		return id;
	}
	float getPrice() {
		return price;
	}
	string getTitle() {
		return title;
	}
	// functions
	void AddBook(Book& book) {
		fstream file;
		file.open("Books", ios::app);
		file << "{" << book.id << "," << book.title << "," << book.price << "}" << endl;
		file.close();
	}
	// Function Overloading
	void AddBook(Book* books, int numberOfBooks) {
		for (int i = 0; i < numberOfBooks; i++) {
			fstream file;
			file.open("Books", ios::app);
			file << "{" << books[i].id << "," << books[i].title << "," << books[i].price << "}" << endl;
			file.close();
		}
	}
	void displayAllBooks() {
		fstream books;
		string str;
		books.open("Books", ios::in);
		cout << "{Id" << "\t\t\t" << "Title" << "\t\t\t" << "Price}" << endl;
		if (books.is_open()) {
			cout << "Books are :" << endl;
			while (books) {
				getline(books, str);
				cout << str << endl;
			}
		}
		else {
			cout << "There is nothing to view" << endl;
		}
		books.close();
	}
};


class User {
private:
	string name;
	int id;
	string email;
	string password;
	bool isAuthorize;
	bool isAccount;
	bool isBorrowBooks;
	int numberOfBooksBorrow;
	string booksBorrow[30];
	float charge;
	int delayDays;
	int dateOfBorrow;
	int dateOfReturn;
public:
	// getter
	string getName() {
		return name;
	}
	bool getIsBorrow() {
		return isBorrowBooks;
	}
	void setIsBorrow(bool _isBorrow) {
		isBorrowBooks = _isBorrow;
	}
	int getId() {
		return id;
	}
	string getEmail() {
		return email;
	}
	string getPassword() {
		return password;
	}
	bool getAuthorize() {
		return isAuthorize;
	}
	bool getAccount() {
		return isAccount;
	}
	int getNumberOfBooksBorrow() {
		return numberOfBooksBorrow;
	}
	string* getNamesOfBooksBorrow() {
		return booksBorrow;
	}
	float getCharge() {
		return charge;
	}
	int getDelayDays() {
		return delayDays;
	}
	int getDateBorrow() {
		return dateOfBorrow;
	}
	int getDateReturn() {
		return dateOfReturn;
	}
	void setName(string _name) {
		name = _name;
	}
	void setId(int _id) {
		id = _id;
	}
	void setEmail(string _email) {
		email = _email;
	}
	void setPassword(string _password) {
		password = _password;
	}
	void setAuthorize(bool _isAuthorize) {
		isAuthorize = _isAuthorize;
	}
	void setAccount(bool _isAccount) {
		isAccount = _isAccount;
	}
	void setNumberOfBooksBorrow(int _number) {
		numberOfBooksBorrow = _number;
	}
	void setNamesOfBooksBorrow(string* names, int num) {
		for (int i = 0; i < num; i++) {
			booksBorrow[i] = names[i];
		}
	}
	void setCharge(float _charge) {
		charge = _charge;
	}
	void setDelayDays(int _delay) {
		delayDays = _delay;
	}
	void setDateBorrow(int _date) {
		dateOfBorrow = _date;
	}
	void setDateReturn(int _date) {
		dateOfReturn = _date;
	}
	void borrowBooks() {
		string borrowedBooks[30];
		for (int i = 0; i < getNumberOfBooksBorrow(); i++) {
			borrowedBooks[i] = getNamesOfBooksBorrow()[i];
		}
		if (getIsBorrow()) {
			fstream borrow;
			borrow.open("BooksBorrow", ios::app);
			borrow << "{" << getId() << "," << getName() << ",";
			for (int i = 0; i < getNumberOfBooksBorrow(); i++) {
				borrow << borrowedBooks[i] << " ";
			}
			borrow << "}" << endl;
			borrow.close();
		}
	}
	
};

class Account : public User {
public:
	bool makeAccount(User& user) {
		fstream accounts;
		accounts.open("Accounts", ios::app);
		if (user.getIsBorrow()) {
			accounts << "{" << user.getId() << "," << user.getName() << "," << user.getEmail() << "," << user.getPassword()
				<< "," << user.getAccount() << "," << user.getNumberOfBooksBorrow()
				<< "}" << endl;
		}
		accounts.close();

		return true;
	}
	bool Authorize(int id, string email, string password) {
		fstream accounts;

		accounts.open("Accounts", ios::in);
		if (accounts.is_open()) {
			while (accounts) {
				string str = "";
				getline(accounts, str);
				int commas = 0;
				int emailCharacters = 0;
				string emailStr;
				int passwordCharacters = 0;
				string passwordStr;
				for (int i = 0; i < str.length(); i++) {
					if (str[i] == ',') {
						commas++;
					}
					if (commas == 2 && str[i] != ',') {
						emailCharacters++;
						emailStr += str[i];
					}
					if (commas == 3 && str[i] != ',') {
						passwordCharacters++;
						passwordStr += str[i];
					}
					int result1 = email.compare(emailStr);
					int result2 = password.compare(passwordStr);
					if (result1 == 0 && result2 == 0) {
						return true;
					}
				}
				commas = 0;
			}
		}
		return false;
	}
};

class Cart {
public:
	Cart() {
		totalFees = 0;
	}
	string books[30];
	int length;
	long totalFees;
	void calculateFees() {
		fstream file;
		string enrolledBooks;
		string PriceStr;
		file.open("Books", ios::in);
		if (file.is_open()) {
			while (file) {
				string str = "";
				getline(file, str);
				int commas = 0;
				int TitleCharacters = 0;
				int PriceCharacters = 0;
				for (int i = 0; i < str.length(); i++) {
					if (str[i] == ',') {
						commas++;
					}
					if (commas == 1 && str[i] != ',') {
						TitleCharacters++;
						enrolledBooks += str[i];
					}
					if (commas == 2 && str[i] != ',' && str[i] != '}') {
						PriceCharacters++;
						PriceStr += str[i];
					}
				}
				for (int i = 0; i < length; i++) {
					if (enrolledBooks == books[i]){
						totalFees += stol(PriceStr);
					}
				}
				enrolledBooks = "";
				PriceStr = "";
			}
		}
	}
};

void menu() {
		cout << "\t\t\t ****** Library Management System ******" << endl;
		cout << "Menu :" << endl;
		cout << "1. View Books" << endl;
		cout << "2. Add Books" << endl;
		cout << "3. Make Account" << endl;
		cout << "4. Borrow Books" << endl;
		cout << "5. Display Cart" << endl;
		cout << "6. Exit" << endl;
}

int main()
	{
		menu();

		Cart cart;
		do {
			Book book1;
			Account account;
			string name;
			int accountId;
			string email;
			string password;
			bool isBorrowBooks;
			int numberOfBooksBorrow;
			string booksBorrow[30];
			float charge;
			Book* book = &book1;
			cout << "Enter your choice :";
			char choose = _getch();
			char ch;
			cout << endl;
			int number;
			int id;
			string bookName;
			float price;
			Book books[30];
			// display cart
			bool isAccount = false;

			switch (choose)
			{
			case '1':
				book->displayAllBooks();
				system("pause");
				system("cls");
				menu();

				break;
			case '2':
				cout << "Enter number of books :" << endl;
				cin >> number;
				if (number == 1) {
					cout << "Enter book id :" << endl;
					cin >> id;
					cout << "Enter Book Name :" << endl;
					cin >> bookName;
					cout << "Enter Book Price :" << endl;
					cin >> price;
					book1.setId(id);
					book1.setTitle(bookName);
					book1.setPrice(price);
					book->AddBook(book1);
					cout << "Your book is successfully added" << endl;
				}
				else if (number > 1) {
					for (int i = 0; i < number; i++) {
						cout << "Enter Book " << i + 1 << " Id :" << endl;
						cin >> id;
						cout << "Enter Book " << i + 1 << " Name :" << endl;
						cin >> bookName;
						cout << "Enter Book " << i + 1 << " Price :" << endl;
						cin >> price;
						books[i].setId(id);
						books[i].setTitle(bookName);
						books[i].setPrice(price);
					}
					book->AddBook(books, number);
					cout << "Your books are successfully added" << endl;
				}
				system("pause");
				system("cls");
				menu();

				break;
			case '3':
				cout << "Enter your name :";
				cin >> name;
				cout << "Enter id of Account :";
				cin >> accountId;
				cout << "Enter email :";
				cin >> email;
				cout << "Enter password :";
				cin >> password;
				account.setName(name);
				account.setId(accountId);
				account.setEmail(email);
				account.setPassword(password);
				account.setAccount(true);
				cout << "Your account is successfully created :)" << endl;
				system("pause");
				system("cls");
				menu();
				cout << "Do you want to borrow books - Press 1 to say yes:";
				ch = _getch();
				cout << endl;
				system("cls");
				menu();
				if (ch == '1') {
					isBorrowBooks = true;
					book->displayAllBooks();
					cout << "Enter the number of books do you want to borrow :";
					cin >> numberOfBooksBorrow;
					account.setNumberOfBooksBorrow(numberOfBooksBorrow);
					cout << "Enter the names of books" << endl;
					for (int i = 0; i < numberOfBooksBorrow; i++) {
						cout << i + 1 << " ." << " ";
						cin >> booksBorrow[i];
					}

					cart.length = numberOfBooksBorrow;
					for (int i = 0; i < numberOfBooksBorrow; i++) {
						cart.books[i] = booksBorrow[i];
					}
					account.setNamesOfBooksBorrow(cart.books, numberOfBooksBorrow);
					account.borrowBooks();
				}
				else {
					isBorrowBooks = false;
				}
				if (account.makeAccount(account)) {
					cout << "Your account is successfully created :)" << endl;
				}
				system("pause");
				system("cls");
				menu();
				break;
			case '4':
				// borrow books
				cout << "Do you have an account ?Press y for yes" << endl;
				char c;
				c = _getch();
				if (c == 'y') {
					isAccount = true;
				}
				if (isAccount) {
					cout << "Enter User Id :" << endl;
					cin >> id;
					cout << "Enter email :" << endl;
					cin >> email;
					cout << "Enter password :" << endl;
					cin >> password;
					if (account.Authorize(id, email, password)) {
						cout << "Borrow Books :" << endl;
						cout << "----------------------------------------------------------------------------------------------" << endl;
						isBorrowBooks = true;
						book->displayAllBooks();
						cout << "Enter the number of books do you want to borrow :";
						cin >> numberOfBooksBorrow;
						account.setNumberOfBooksBorrow(numberOfBooksBorrow);
						cout << "Enter the names of books" << endl;
						for (int i = 0; i < numberOfBooksBorrow; i++) {
							cout << i + 1 << " ." << " ";
							cin >> booksBorrow[i];
						}
						cart.length = numberOfBooksBorrow;

						for (int i = 0; i < numberOfBooksBorrow; i++) {
							cart.books[i] = booksBorrow[i];
						}
						account.setNamesOfBooksBorrow(cart.books, numberOfBooksBorrow);
						account.borrowBooks();
					}
				}
				break;
			case '5':
				// display cart
				for (int i = 0; i < cart.length; i++) {
					cout << cart.books[i] << endl;
				}
				cart.calculateFees();
				cout << "Total bill is " << cart.totalFees << endl;
				break;
			case '6':
				return false;
				break;
			default:
				cout << "Please select the number 1 to 6" << endl;
				break;
			}
		} while (true);
	}
