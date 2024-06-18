#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

// Declaring functions
void checkbalance(char *);
void transfermoney(void);
void display(char *);
void person(char *);
void login(void);
void loginsu(void);
void account(void);
void accountcreated(void);
void afterlogin(void);
void changePassword(char *);
void closeAccount(char *);
void logout(void);
int adminLogin();
void adminMenu(void);
void viewAllUsers(void);
void editUserDetails(void);
void deleteUserAccount(void);
void viewTransactionHistory(void);
int checkMinimumBalance(char *username, float minimumBalance);
void depositMoney(char *username);

// Declaring gotoxy function for setting cursor position
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;

	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Structure to keep track of amount transfer
struct money
{
	char usernameto[50];
	char userpersonfrom[50];
	float money1;
};

// Creating a structure to store data of the user
struct pass
{
	char username[50];
	int date, month, year;
	char pnumber[15];
	char adharnum[20];
	char fname[20];
	char lname[20];
	char fathname[20];
	char mothname[20];
	char address[50];
	char typeaccount[20];
	float balance;
	char password[50];
};

struct userpass
{
	char password[50];
};

// Driver Code
int main()
{
	int choice;

	do
	{
		system("cls");
		gotoxy(20, 3);
		printf("WELCOME TO BANK ACCOUNT SYSTEM\n\n");
		gotoxy(18, 5);
		printf("**********************************");
		gotoxy(25, 7);
		printf("DEVELOPER - Harsh Bhimjiyani");

		gotoxy(20, 10);
		printf("1.... CREATE A BANK ACCOUNT");

		gotoxy(20, 12);
		printf("2.... ALREADY A USER? SIGN IN");

		gotoxy(20, 14);
		printf("3.... ADMIN LOGIN");

		gotoxy(20, 16);
		printf("4.... EXIT\n\n");

		printf("\n\nENTER YOUR CHOICE..");

		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			system("cls");
			printf("\n\n USERNAME 50 CHARACTERS MAX!!");
			printf("\n\n PASSWORD 50 CHARACTERS MAX!!");
			account();
			break;

		case 2:
			login();
			break;

		case 3:
			if (adminLogin())
			{
				adminMenu();
			}
			else
			{
				printf("\n\nPress enter to go back to the main menu.");
				getch();
			}
			break;

		case 4:
			exit(0);
			break;

		default:
			printf("Invalid choice. Press enter to try again.");
			getch();
		}
	} while (choice != 4);

	return 0;
}

// Function to create accounts of users
void account(void)
{
	char password[20];
	int passwordlength, i, seek = 0;
	char ch;
	FILE *fp, *fu;
	struct pass u1;
	struct userpass p1;

	struct userpass u2;

	// Opening file to write data of a user
	fp = fopen("username.txt", "ab");

	// Inputs
	system("cls");
	printf("\n\n!!!!!CREATE ACCOUNT!!!!!");

	printf("\n\nFIRST NAME..");
	scanf("%s", &u1.fname);

	printf("\n\n\nLAST NAME..");
	scanf("%s", &u1.lname);

	printf("\n\nFATHER's NAME..");
	scanf("%s", &u1.fathname);

	printf("\n\nMOTHER's NAME..");
	scanf("%s", &u1.mothname);

	printf("\n\nADDRESS..");
	scanf("%s", &u1.address);

	printf("\n\nACCOUNT TYPE..");
	scanf("%s", &u1.typeaccount);

	printf("\n\nDATE OF BIRTH..");
	printf("\nDATE - ");
	scanf("%d", &u1.date);
	printf("\nMONTH - ");
	scanf("%d", &u1.month);
	printf("\nYEAR - ");
	scanf("%d", &u1.year);

	printf("\n\nADHAR NUMBER..");
	scanf("%s", u1.adharnum);

	printf("\n\nPHONE NUMBER..");
	scanf("%s", u1.pnumber);

	printf("\n\nUSERNAME.. ");
	scanf("%s", &u1.username);

	printf("\n\nPASSWORD..");

	// Taking password in the form of stars
	for (i = 0; i < 50; i++)
	{
		ch = getch();
		if (ch != 13)
		{
			password[i] = ch;
			ch = '*';
			printf("%c", ch);
		}
		else
			break;
	}

	u1.balance = 0.0;

	// Writing to the file
	fwrite(&u1, sizeof(u1),
		   1, fp);

	// Closing file
	fclose(fp);

	// Calling another function after successful creation of account
	accountcreated();
}

// Successful account creation
void accountcreated(void)
{
	int i;
	char ch;
	system("cls");
	printf(
		"PLEASE WAIT....\n\nYOUR DATA IS PROCESSING....");
	for (i = 0; i < 200000000; i++)
	{
		i++;
		i--;
	}

	gotoxy(30, 10);

	printf("ACCOUNT CREATED SUCCESSFULLY....");
	gotoxy(0, 20);

	printf("Press enter to login");

	getch();
	login();
}

// Login function to check the username of the user
void login(void)
{
	system("cls");

	char username[50];
	char password[50];

	int i, j, k;
	char ch;
	FILE *fp, *fu;
	struct pass u1;
	struct userpass u2;

	// Opening file of user data
	fp = fopen("username.txt",
			   "rb");

	if (fp == NULL)
	{
		printf("ERROR IN OPENING FILE");
	}
	gotoxy(34, 2);
	printf(" ACCOUNT LOGIN ");
	gotoxy(7, 5);
	printf("***********************************************"
		   "********************************");

	gotoxy(35, 10);
	printf("==== LOG IN ====");

	// Take input
	gotoxy(35, 12);
	printf("USERNAME.. ");
	scanf("%s", &username);

	gotoxy(35, 14);
	printf("PASSWORD..");

	// Input the password
	for (i = 0; i < 50; i++)
	{
		ch = getch();
		if (ch != 13)
		{
			password[i] = ch;
			ch = '*';
			printf("%c", ch);
		}

		else
			break;
	}

	// Checking if username exists in the file or not
	while (fread(&u1, sizeof(u1),
				 1, fp))
	{
		if (strcmp(username,
				   u1.username) == 0)
		{
			loginsu();
			display(username);
		}
	}

	// Closing the file
	fclose(fp);
}

// Redirect after successful login
void loginsu(void)
{
	int i;
	FILE *fp;
	struct pass u1;
	system("cls");
	printf("Fetching account details.....\n");
	for (i = 0; i < 20000; i++)
	{
		i++;
		i--;
	}

	gotoxy(30, 10);
	printf("LOGIN SUCCESSFUL....");
	gotoxy(0, 20);
	printf("Press enter to continue");

	getch();
}

// Display function to show the data of the user on screen
void display(char username1[])
{
	system("cls");
	FILE *fp;
	int choice, i;
	fp = fopen("username.txt", "rb");
	struct pass u1;

	if (fp == NULL)
	{
		printf("error in opening file");
	}

	while (fread(&u1, sizeof(u1),
				 1, fp))
	{
		if (strcmp(username1,
				   u1.username) == 0)
		{
			gotoxy(30, 1);
			printf("WELCOME, %s %s",
				   u1.fname, u1.lname);

			gotoxy(28, 2);
			printf("..........................");
			gotoxy(00, 6);
			printf("==== YOUR ACCOUNT INFO ====");
			gotoxy(00, 8);
			printf("***************************");
			gotoxy(00, 10);
			printf("NAME..%s %s", u1.fname,
				   u1.lname);

			gotoxy(00, 12);
			printf("FATHER's NAME..%s %s",
				   u1.fathname,
				   u1.lname);

			gotoxy(00, 14);
			printf("MOTHER's NAME..%s",
				   u1.mothname);

			gotoxy(00, 16);
			printf("ADHAR CARD NUMBER..%s",
				   u1.adharnum);

			gotoxy(00, 18);
			printf("MOBILE NUMBER..%s",
				   u1.pnumber);

			gotoxy(00, 20);
			printf("DATE OF BIRTH.. %d-%d-%d",
				   u1.date, u1.month, u1.year);

			gotoxy(00, 22);
			printf("ADDRESS..%s", u1.address);

			gotoxy(00, 24);
			printf("ACCOUNT TYPE..%s",
				   u1.typeaccount);
		}
	}

	fclose(fp);

	gotoxy(55, 6);

	// Menu to perform different actions by user
	printf(" HOME ");
	gotoxy(55, 7);
	printf("*********");
	gotoxy(55, 9);
	printf(" 1....CHECK BALANCE");
	gotoxy(55, 11);
	printf(" 2....DEPOSIT MONEY");
	gotoxy(55, 13);
	printf(" 3....TRANSFER MONEY");
	gotoxy(55, 15);
	printf(" 4....CHANGE PASSWORD");
	gotoxy(55, 17);
	printf(" 5....CLOSE ACOUNT");
	gotoxy(55, 19);
	printf(" 6....LOG OUT");
	gotoxy(55, 21);
	printf(" 7....EXIT");
	gotoxy(55, 23);
	printf(" ENTER YOUR CHOICES..");
	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		checkbalance(username1);
		break;

	case 2:
		depositMoney(username1);
		break;

	case 3:
		transfermoney();
		break;

	case 4:
		changePassword(username1);
		break;

	case 5:
		closeAccount(username1);
		break;

	case 6:
		logout();
		main();
		break;

	case 7:
		exit(0);
		break;

	default:
		printf("Invalid choice. Press enter to try again.");
		getch();
	}
}

// Function to check if the user has a minimum balance
int checkMinimumBalance(char *username, float minimumBalance)
{
	FILE *fp;
	struct pass u1;

	// Opening file in read mode to read user's information
	fp = fopen("username.txt", "rb");

	// Finding the record of the user
	while (fread(&u1, sizeof(u1), 1, fp))
	{
		if (strcmp(username, u1.username) == 0)
		{
			fclose(fp);
			return (u1.balance >= minimumBalance);
		}
	}

	fclose(fp);
	return 0; // Return 0 if the username is not found
}

// Function to transfer money from one user to another
void transfermoney(void)
{
	int i, j;
	FILE *fp;
	struct pass u1;
	struct money m1;
	char usernamet[20];
	char usernamep[20];
	float transferAmount;

	system("cls");

	fp = fopen("username.txt", "r+");

	if (fp == NULL)
	{
		printf("Error in opening file.");
		getch();
		return;
	}

	gotoxy(33, 4);
	printf("---- TRANSFER MONEY ----");
	gotoxy(33, 5);
	printf("========================");

	gotoxy(33, 11);
	printf("FROM (your username).. ");
	scanf("%s", usernamet);

	// Check balance before allowing transfer
	if (!checkMinimumBalance(usernamet, m1.money1))
	{
		printf("Insufficient balance. Press enter to go back to the main menu.");
		getch();
		display(usernamet);
		return;
	}

	gotoxy(33, 13);
	printf("TO (username of person)..");
	scanf("%s", usernamep);

	// Find the sender's record
	while (fread(&u1, sizeof(u1), 1, fp))
	{
		if (strcmp(usernamet, u1.username) == 0)
		{
			break;
		}
	}

	// Prompt for transfer amount
	gotoxy(33, 16);
	printf("ENTER THE AMOUNT TO BE TRANSFERRED..");
	scanf("%f", &transferAmount);

	// Check if the sender has enough balance
	if (checkMinimumBalance(usernamet, transferAmount))
	{
		// Deduct the transferred amount from the sender's balance
		u1.balance -= transferAmount;

		// Update the sender's balance in the file
		fseek(fp, -sizeof(u1), SEEK_CUR);
		fwrite(&u1, sizeof(u1), 1, fp);

		// Find the receiver's record to update their balance
		fseek(fp, 0, SEEK_SET);
		while (fread(&u1, sizeof(u1), 1, fp))
		{
			if (strcmp(usernamep, u1.username) == 0)
			{
				// Add the transferred amount to the receiver's balance
				u1.balance += transferAmount;

				// Update the receiver's balance in the file
				fseek(fp, -sizeof(u1), SEEK_CUR);
				fwrite(&u1, sizeof(u1), 1, fp);
				break;
			}
		}

		// Creating another file to write the amount along with the username to which the amount is going to be transferred
		FILE *fm = fopen("moneyhistory.txt", "w");

		// Write to the transaction history file
		strcpy(m1.usernameto, u1.username);
		strcpy(m1.userpersonfrom, usernamet);
		m1.money1 = transferAmount;
		fwrite(&m1, sizeof(m1), 1, fm);

		// Close the transaction history file
		fclose(fm);

		gotoxy(33, 18);
		printf("AMOUNT SUCCESSFULLY TRANSFERRED....");
		getch();

		// Close the files
		fclose(fp);
	}
	else
	{
		printf("Insufficient balance. Press enter to go back to the main menu.");
		getch();
		display(usernamet);
	}

	// Function to return to the home screen
	display(usernamet);
}

void checkbalance(char username2[])
{
	system("cls");
	FILE *fp;
	struct pass u1;

	// Initialize balance to 0.0
	float balance;

	// Opening the user data file
	fp = fopen("username.txt", "r+");

	if (fp == NULL)
	{
		printf("Error in opening file");
		return;
	}

	// Reading user data to get the balance
	while (fread(&u1, sizeof(u1), 1, fp))
	{
		if (strcmp(username2, u1.username) == 0)
		{
			printf("==== BALANCE DASHBOARD ====\n");
			printf("USERNAME: %s\n", username2);
			printf("CURRENT BALANCE: %.2f\n", u1.balance);
			break;
		}
	}

	fclose(fp);

	printf("\nPress enter to go back to the main menu.");
	getch();
	display(username2);
}

// Function to deposit money into the user's account
void depositMoney(char username[])
{
	system("cls");
	FILE *fp;
	struct pass u1;

	// Opening file in read mode to read user's data
	fp = fopen("username.txt", "r+b");

	if (fp == NULL)
	{
		printf("Error in opening file.");
		getch();
		return;
	}

	// Check if the username exists
	bool userFound = false;

	while (fread(&u1, sizeof(u1), 1, fp))
	{
		if (strcmp(username, u1.username) == 0)
		{
			userFound = true;
			break;
		}
	}

	gotoxy(30, 2);
	printf("==== DEPOSIT MONEY ====");
	gotoxy(30, 3);
	printf("***************************");

	// If the user is found, proceed with the deposit
	if (userFound)
	{
		float depositAmount;

		// Get the amount to deposit
		gotoxy(30, 6);
		printf("Enter the amount to deposit: ");
		scanf("%f", &depositAmount);

		// Check if the deposit amount is valid
		if (depositAmount > 0)
		{
			// Update the user's balance
			u1.balance += depositAmount;
			fseek(fp, -sizeof(u1), SEEK_CUR);
			fwrite(&u1, sizeof(u1), 1, fp);

			// Display success message
			printf("Amount deposited successfully. New balance: %.2f\n", u1.balance);
		}
		else
		{
			// Display error message if the deposit amount is invalid
			printf("Error: Invalid deposit amount.\n");
		}
	}
	else
	{
		// Display error message if the user is not found
		printf("Error: User not found.\n");
	}

	getch();

	// Close the file
	fclose(fp);

	// Function to return to the home screen
	display(username);
}

// Function to change user password
void changePassword(char username[])
{
	system("cls");
	FILE *fp = fopen("username.txt", "r+b");
	struct pass u1;

	if (fp == NULL)
	{
		printf("Error in opening file.");
		getch();
		return;
	}

	// Find the user's record
	while (fread(&u1, sizeof(u1), 1, fp))
	{
		if (strcmp(username, u1.username) == 0)
		{
			printf("\n==== CHANGE PASSWORD ====\n\n");
			printf("Enter new password: ");
			scanf("%s", u1.password);

			fseek(fp, -sizeof(u1), SEEK_CUR);
			fwrite(&u1, sizeof(u1), 1, fp);

			printf("\nPassword changed successfully.");
			break;
		}
	}

	fclose(fp);
	printf("\nPress enter to go back to the main menu.");
	getch();
	display(username);
}

// Function to close user account
void closeAccount(char username[])
{
	system("cls");
	FILE *fp = fopen("username.txt", "rb");
	FILE *temp = fopen("temp.txt", "wb");
	struct pass user;

	if (fp == NULL || temp == NULL)
	{
		printf("Error in opening file.");
		getch();
		return;
	}

	char confirmation;

	printf("\n==== CLOSE ACCOUNT ====\n\n");
	printf("Are you sure you want to close your account? (y/n): ");
	scanf(" %c", &confirmation);

	if (confirmation == 'y' || confirmation == 'Y')
	{
		while (fread(&user, sizeof(user), 1, fp))
		{
			if (strcmp(username, user.username) == 0)
			{
				printf("\nAccount closed successfully.\n");
			}
			else
			{
				fwrite(&user, sizeof(user), 1, temp);
			}
		}

		fclose(fp);
		fclose(temp);

		remove("username.txt");
		rename("temp.txt", "username.txt");

		printf("\nPress enter to go back to the main menu.");
		getch();
		main();
	}
	else
	{
		fclose(fp);
		fclose(temp);
		printf("\nAccount closure canceled. Press enter to go back to the main menu.");
		getch();
		display(username);
	}
}

// Logout function to bring user to the login screen
void logout(void)
{
	int i, j;
	system("cls");
	printf("please wait, logging out");

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 25000000; j++)
		{
			i++;
			i--;
		}
		printf(".");
	}

	gotoxy(30, 10);
	printf("Sign out successfully..\n");

	gotoxy(0, 20);
	printf("press any key to continue..");

	getch();
}

// Function to handle admin login
int adminLogin()
{
	system("cls");

	char adminUsername[] = "admin";
	char adminPassword[] = "admin123";

	char enteredUsername[50];
	char enteredPassword[50];

	gotoxy(34, 2);
	printf(" ADMIN LOGIN ");
	gotoxy(7, 5);
	printf("************************************************************");

	gotoxy(35, 10);
	printf("==== ADMIN LOGIN ====");

	// Take input for admin username
	gotoxy(35, 12);
	printf("USERNAME.. ");
	scanf("%s", enteredUsername);

	// Take input for admin password
	gotoxy(35, 14);
	printf("PASSWORD..");

	int i = 0;
	char ch;
	while ((ch = getch()) != '\n')
	{
		if (ch == 13) // Enter key
		{
			break;
		}
		else if (ch == 8) // Backspace key
		{
			if (i > 0)
			{
				i--;
				printf("\b \b");
			}
		}
		else
		{
			enteredPassword[i++] = ch;
			printf("*");
		}
	}
	enteredPassword[i] = '\0';

	// Check if entered credentials match admin credentials
	if (strcmp(enteredUsername, adminUsername) == 0 && strcmp(enteredPassword, adminPassword) == 0)
	{
		return 1; // Return 1 to indicate successful login
	}
	else
	{
		printf("\n\nIncorrect username or password. Press enter to go back to the main menu.");
		getch();
		return 0; // Return 0 to indicate unsuccessful login
	}
}

// Admin menu function
void adminMenu(void)
{
	int adminChoice;

	do
	{
		system("cls");
		gotoxy(34, 2);
		printf(" ADMIN MENU ");
		gotoxy(7, 5);
		printf("************************************************************");

		gotoxy(35, 10);
		printf("1. View All Users");

		gotoxy(35, 12);
		printf("2. Edit User Details");

		gotoxy(35, 14);
		printf("3. Delete User Account");

		gotoxy(35, 16);
		printf("4. View Transaction History");

		gotoxy(35, 18);
		printf("5. Logout");

		gotoxy(35, 20);
		printf("Enter your choice: ");
		scanf("%d", &adminChoice);

		switch (adminChoice)
		{
		case 1:
			viewAllUsers();
			break;

		case 2:
			editUserDetails();
			break;

		case 3:
			deleteUserAccount();
			break;

		case 4:
			viewTransactionHistory();
			break;

		case 5:
			// Logout logic
			printf("\nLogging out...");
			getch();
			break;

		default:
			printf("\nInvalid choice. Press enter to try again.");
			getch();
		}
	} while (adminChoice != 5);
}

// Function to view all users
void viewAllUsers(void)
{
	system("cls");
	FILE *fp = fopen("username.txt", "rb");

	if (fp == NULL)
	{
		printf("Error in opening file.");
		getch();
		return;
	}

	struct pass user;

	printf("==== ALL USERS ====\n\n");

	while (fread(&user, sizeof(user), 1, fp))
	{
		printf("Username: %s\n", user.username);
		printf("Name: %s %s\n", user.fname, user.lname);
		printf("DOB: %d-%d-%d\n", user.date, user.month, user.year);
		printf("Address: %s\n", user.address);
		printf("Phone: %s\n", user.pnumber);
		printf("Account Type: %s\n", user.typeaccount);
		printf("Balance: %.2f\n", user.balance);

		printf("------------------------------\n");
	}

	fclose(fp);
	printf("\nPress enter to go back to the admin menu.");
	getch();
}

// Function to edit user details
void editUserDetails(void)
{
	system("cls");

	FILE *fp = fopen("username.txt", "r+b");

	if (fp == NULL)
	{
		printf("Error in opening file.");
		getch();
		return;
	}

	char usernameToEdit[50];
	struct pass user;

	printf("Enter the username to edit: ");
	scanf("%s", usernameToEdit);

	int found = 0;

	while (fread(&user, sizeof(user), 1, fp))
	{
		if (strcmp(usernameToEdit, user.username) == 0)
		{
			found = 1;

			printf("\n==== EDIT USER DETAILS ====\n\n");
			printf("Current Details:\n");
			printf("Name: %s %s\n", user.fname, user.lname);
			printf("Address: %s\n", user.address);
			printf("Phone: %s\n", user.pnumber);

			printf("\nEnter new details:\n");
			printf("Name: ");
			scanf("%s %s", user.fname,
				  user.lname);
			printf("Address: ");
			scanf("%s", user.address);
			printf("Phone: ");
			scanf("%s", user.pnumber);

			fseek(fp, -sizeof(user), SEEK_CUR);
			fwrite(&user, sizeof(user), 1, fp);

			printf("\nDetails updated successfully.");
			break;
		}
	}

	if (!found)
	{
		printf("User not found.");
	}

	fclose(fp);
	printf("\nPress enter to go back to the admin menu.");
	getch();
}

// Function to delete user account
void deleteUserAccount(void)
{
	system("cls");

	FILE *fp = fopen("username.txt", "rb");
	FILE *temp = fopen("temp.txt", "wb");

	if (fp == NULL || temp == NULL)
	{
		printf("Error in opening file.");
		getch();
		return;
	}

	char usernameToDelete[50];
	struct pass user;

	printf("Enter the username to delete: ");
	scanf("%s", usernameToDelete);

	int found = 0;

	while (fread(&user, sizeof(user), 1, fp))
	{
		if (strcmp(usernameToDelete, user.username) == 0)
		{
			found = 1;
			printf("\n==== DELETE USER ACCOUNT ====\n\n");
			printf("Account deleted successfully.\n");
		}
		else
		{
			fwrite(&user, sizeof(user), 1, temp);
		}
	}

	if (!found)
	{
		printf("User not found.");
	}

	fclose(fp);
	fclose(temp);

	remove("username.txt");
	rename("temp.txt", "username.txt");

	printf("\nPress enter to go back to the admin menu.");
	getch();
}

// Function to view transaction history
void viewTransactionHistory(void)
{
	system("cls");

	FILE *fm = fopen("moneyhistory.txt", "r");

	if (fm == NULL)
	{
		printf("Error in opening file.");
		getch();
		return;
	}

	struct money transaction;

	printf("==== TRANSACTION HISTORY ====\n\n");

	while (fread(&transaction, sizeof(transaction), 1, fm))
	{
		printf("From: %s\n", transaction.userpersonfrom);
		printf("To: %s\n", transaction.usernameto);
		printf("Amount: %.2f\n", transaction.money1);
		printf("------------------------------\n");
	}

	fclose(fm);

	printf("\nPress enter to go back to the admin menu.");
	getch();
}
