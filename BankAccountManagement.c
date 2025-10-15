#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define datFILENAME "BANK.dat"
#define LENGTH 20

typedef struct BankAccount
{
	char AccountNumber[LENGTH];
	char AccountHolderName[LENGTH];
	float Balance;
} BankAccount;

typedef struct Node
{
	BankAccount account;
	struct Node *next;
} Node;

Node *head = NULL;
Node *currentNode = NULL;

void removeNewline(char *text);
void readText(char *destination, int length);
void readNumber(float *number);
void inputAccount(BankAccount *newAccount);

void appendNodeToList(BankAccount *newAccount);

void saveListToFile();
void loadListFromFile();

void printDetails(Node *currentNode);

void createAccount();
void displayAll();
void updateAccount();
void deleteAccount();
void showMenu();

void printDetails(Node *currentNode);

void pause();

void pause()
{
	printf("\nPress any key to continue...");
	getchar();
}

void removeNewline(char *text)
{
	text[strcspn(text, "\n")] = '\0';
}

void readText(char *destination, int length)
{
	fgets(destination, length, stdin);
	removeNewline(destination);
}

void readNumber(float *number)
{
	scanf("%f", number)
		;
	getchar();
}

void inputAccount(BankAccount *newAccount)
{
	printf("Enter Account Number: ");
	readText(newAccount->AccountNumber, LENGTH);

	printf("Enter Account Holder Name: ");
	readText(newAccount->AccountHolderName, LENGTH);
+++++
	printf("Enter Account Balance: ");
	readNumber(&newAccount->Balance);
}


void appendNodeToList(BankAccount *newAccount)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->account = *newAccount;
	newNode->next = NULL;

	if (head == NULL)
	{
		head = newNode;
	}
	else
	{
		currentNode->next = newNode;
	}

	currentNode = newNode;
}

void saveListToFile()
{
	FILE *fp = fopen(datFILENAME, "wb");

	if (fp == NULL)
	{
		printf("Error opening file for saving!\n");
		return;
	}

	Node *currentNode = head;

	while (currentNode != NULL)
	{
		fwrite(&currentNode->account, sizeof(BankAccount), 1, fp);
		currentNode = currentNode->next;
	}

	fclose(fp);
}

void loadListFromFile()
{
	FILE *fp = fopen(datFILENAME, "rb");

	if (fp == NULL)
	{
		printf("No accounts available.\n");
		return;
	}

	BankAccount newAccount;

	while (fread(&newAccount, sizeof(BankAccount), 1, fp) == 1)
	{
		appendNodeToList(&newAccount);
	}

	fclose(fp);
}

void printDetails(Node *currentNode)
{
	printf("\nAccount No: %s", currentNode->account.AccountNumber);
	printf("\nHolder Name: %s", currentNode->account.AccountHolderName);
	printf("\nBalance: %f\n", currentNode->account.Balance);
	printf("-----------------------------\n");
}

void createAccount()
{
	BankAccount newAccount;

	printf("\nCREATING A NEW ACCOUNT............................\n\n");

	inputAccount(&newAccount);
	appendNodeToList(&newAccount);
	saveListToFile();

	printf("\nAccount created successfully!\n");
	pause();
}

void displayAll()
{
	if (head == NULL)
	{
		printf("No accounts available.\n");
		pause();
		return;
	}
	printf("\nAVAILABLE ACCOUNTS\n");
	Node *currentNode = head;
	
	while (currentNode != NULL)
	{
		printDetails(currentNode);
		currentNode = currentNode->next;
	}

	pause();
}

void updateAccount()
{
	if (head == NULL)
	{
		printf("No records available to update!\n");
		pause();
		return;
	}

	char accountNumberToUpdate[LENGTH];
	printf("Enter the Account Number to update: ");
	readText(accountNumberToUpdate, LENGTH);

	Node *currentNode = head;

	while (currentNode != NULL)
	{
		if (strcmp(currentNode->account.AccountNumber, accountNumberToUpdate) == 0)
		{
			printf("\nCurrent Details of the account to be updated:\n");
			printDetails(currentNode);

			printf("Enter new Account Holder Name: ");
			readText(currentNode->account.AccountHolderName, LENGTH);

			printf("Enter new Account Balance: ");
			readNumber(&currentNode->account.Balance);

			saveListToFile();

			printf("\nAccount updated successfully!\n");
			pause();
			return;
		}
		currentNode = currentNode->next;
	}

	printf("\nAccount Number not found!\n");
	pause();
}

void deleteAccount()
{
	if (head == NULL)
	{
		printf("No records to delete.\n");
		pause();
		return;
	}

	char accNo[LENGTH];
	printf("Enter Account Number to delete: ");
	readText(accNo, LENGTH);

	Node *previousNode = NULL;
	currentNode = head;

	while (currentNode != NULL)
	{
		if (strcmp(currentNode->account.AccountNumber, accNo) == 0)
		{
			printf("\nCurrent details of account to be deleted...");
	         printDetails(currentNode);
			break;
		}
		else
		{
			previousNode = currentNode;
			currentNode = currentNode->next;
		}
	}

	if (currentNode == NULL)
	{
		printf("Account not found.\n");
		pause();
		return;
	}

	if (previousNode == NULL)
		head = currentNode->next;
	else
		previousNode->next = currentNode->next;

	free(currentNode);

	saveListToFile();

	printf("\nAccount deleted successfully!\n");

	pause();
}

void showMenu()
{
	printf("\nBANK ACCOUNT MANAGEMENT\n\n");
	printf("1. Create Account\n");
	printf("2. Display All Accounts\n");
	printf("3. Update Account\n");
	printf("4. Delete Account\n");
	printf("0. Exit\n");
}

int main()
{
	loadListFromFile();
	int choice;
	do
	{
		showMenu();
		printf("\nEnter your choice: ");
		scanf("%d", &choice);
		getchar();

		switch (choice)
		{
			case 1:
				createAccount();
				break;
			case 2:
				displayAll();
				break;
			case 3:
				updateAccount();
				break;
			case 4:
				deleteAccount();
				break;
			case 0:
				printf("\nExiting program...\n");
				break;
			default:
				printf("Invalid choice!\n");
				pause();
		}
	} while (choice != 0);
}





