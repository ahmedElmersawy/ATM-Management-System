#define _CRT_NONSTDC_NO_DEPRECATE //use ISO(international standard of C) define names instead of POSIX(portable operating system interface based on unix) define names
#include <stdio.h> //inputs and outputs handle library
#include <stdlib.h> //C standard library
#include <string.h> //string handle library (to handle string datatypes)
#include<windows.h> //no much use, just to use some UI related things
#include<time.h> //no much use, just to retrive current time from OS 
#include<MMsystem.h>
#include<cstdlib>
#include<dos.h>
#pragma warning(disable : 4996) //disable 4996 warning message
#pragma comment(lib, "winmm.lib") //link winmm.lib to the compiler

//arrays that store data retrived from bank accounts database
long long int visaNumber[1024]; //array that save retrived visa numbers from database
int xpMonth[1024]; //array that save retrived expire month of visa cards from database
int xpYear[1024]; //array that save retrived expire year of visa cards from database
int CVV[1024]; //array that save retrived CVV number of visa cards from database
float accountBalance[1024]; //array that save retrived accountBalance from database
int PIN[1024]; //array that save retrived expire month of visa cards from database
char name[1024][50]; //array that save retrived account owner name from database
char bankName[1024][1024]; //array that save the bank name that the account signed on from database
int passPIN[1024]; //array that save retrived expire month of visa cards from database
long long int accountNumber[1024]; //array that save retrived account numbers from database
int cardStatus[1024]; //array that save retrived card statues of the visa cards from database

//array that store data retrived from wallet services database
long long int phoneNumber[1024];
long long int walletID[1024];
float walletBalance[1024];
int walletStatus[1024];

//varibles that help handling code
int currentUser; //current active account handler
int invalidTries = 0; //invalid tries number handler
char trash[1024]; //grabage value at buffer handler

const char* getfieldname(char* line, int num) //function to split string line to tokens/column and return required token/column value in const char datatype "similar to string"
{
    const char* tok;
    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")) {//keep looping tell reaching the rquired token/column number
        if (!--num)
            return tok; //return value of required column in const char datatype "similarr to string"
    }
    return NULL; //return nothing if required token/column number can't be found
}

long long int getfield(char* line, int num) //function to split string line to tokens/column and return required token/column value in long long int datatype
{
    const char* tok;
    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")) { //keep looping tell reaching the rquired token/column number
        long long int value;
        value = strtoll(tok, NULL, 0); //convert the token value from const char"string" to long long int
        if (!--num)
            return value;//return value of required column in long long int datatype
    }
    return NULL; //return nothing if required token/column number can't be found
}

float getfieldFloat(char* line, int num) //function to split string line to tokens/column and return required token/column value in float datatype
{
    const char* tok;
    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")) { //keep looping tell reaching the rquired token/column number
        float value;
        value = strtof(tok, NULL); //convert the token value from const char"string" to float
        if (!--num)
            return value;
    }
    return NULL; //return nothing if required token/column number can't be found
}

void readCardServicesDatabase() { //function to retrive data from the database
    for (int x = 1; x <= 11; x++) { //x is the number of column
        if (x == 1) {
            int i = 0;
            FILE* stream = fopen("database.csv", "r");//open the database in read mode
            char line[1024]; //to store database line value
            while (fgets(line, 1024, stream)) { //loop database lines/rows one by one
                char* tmp = strdup(line); //duplicate the string to the pointer to pass its location
                // NOTE strtok clobbers tmp
                visaNumber[i] = getfield(tmp, x); //get the required column value from the row/line then store to the array
                i++; //move to the next array feild
                free(tmp); //free the pointer declartion
            }
            fclose(stream); //close the file after saving all rows column values
        }
        else if (x == 2) {
            int i = 0;
            FILE* stream = fopen("database.csv", "r"); //open the database in read mode
            char line[1024]; //to store database line value
            while (fgets(line, 1024, stream)) { //loop database lines/rows one by one
                char* tmp = strdup(line); //duplicate the string to the pointer to pass its location
                // NOTE strtok clobbers tmp
                xpMonth[i] = getfield(tmp, x); //get the required column value from the row/line then store to the array
                i++; //move to the next array feild
                free(tmp); //free the pointer declartion
            }
            fclose(stream); //close the file after saving all rows column values
        }
        else if (x == 3) {
            int i = 0;
            FILE* stream = fopen("database.csv", "r"); //open the database in read mode
            char line[1024]; //to store database line value
            while (fgets(line, 1024, stream)) { //loop database lines/rows one by one
                char* tmp = strdup(line);
                // NOTE strtok clobbers tmp
                xpYear[i] = getfield(tmp, x); //get the required column value from the row/line then store to the array
                i++; //move to the next array feild
                free(tmp); //free the pointer declartion
            }
            fclose(stream); //close the file after saving all rows column values
        }
        else if (x == 4) {
            int i = 0;
            FILE* stream = fopen("database.csv", "r"); //open the database in read mode
            char line[1024]; //to store database line value
            while (fgets(line, 1024, stream)) { //loop database lines/rows one by one
                char* tmp = strdup(line);
                // NOTE strtok clobbers tmp
                CVV[i] = getfield(tmp, x); //get the required column value from the row/line then store to the array
                i++; //move to the next array feild
                free(tmp); //free the pointer declartion
            }
            fclose(stream); //close the file after saving all rows column values
        }
        else if (x == 5) {
            int i = 0;
            FILE* stream = fopen("database.csv", "r"); //open the database in read mode
            char line[1024]; //to store database line value
            while (fgets(line, 1024, stream)) { //loop database lines/rows one by one
                char* tmp = strdup(line);
                // NOTE strtok clobbers tmp
                accountBalance[i] = getfieldFloat(tmp, x); //get the required column value from the row/line then store to the array
                i++; //move to the next array feild
                free(tmp); //free the pointer declartion
            }
            fclose(stream); //close the file after saving all rows column values
        }
        else if (x == 6) {
            int i = 0;
            FILE* stream = fopen("database.csv", "r"); //open the database in read mode
            char line[1024]; //to store database line value
            while (fgets(line, 1024, stream)) { //loop database lines/rows one by one
                char* tmp = strdup(line);
                // NOTE strtok clobbers tmp
                PIN[i] = getfield(tmp, x); //get the required column value from the row/line then store to the array
                i++; //move to the next array feild
                free(tmp); //free the pointer declartion
            }
            fclose(stream); //close the file after saving all rows column values
        }
        else if (x == 7) {
            int i = 0;
            FILE* stream = fopen("database.csv", "r"); //open the database in read mode
            char line[1024]; //to store database line value
            while (fgets(line, 1024, stream)) { //loop database lines/rows one by one
                char* tmp = strdup(line);
                // NOTE strtok clobbers tmp
                strcpy(name[i], getfieldname(tmp, x)); //get the required column value from the row/line then store to the array
                i++; //move to the next array feild
                free(tmp); //free the pointer declartion
            }
            fclose(stream); //close the file after saving all rows column values
        }
        else if (x == 8) {
            int i = 0;
            FILE* stream = fopen("database.csv", "r"); //open the database in read mode
            char line[1024]; //to store database line value
            while (fgets(line, 1024, stream)) { //loop database lines/rows one by one
                char* tmp = strdup(line);
                // NOTE strtok clobbers tmp
                strcpy(bankName[i], getfieldname(tmp, x)); //get the required column value from the row/line then store to the array
                i++; //move to the next array feild
                free(tmp); //free the pointer declartion
            }
            fclose(stream); //close the file after saving all rows column values
        }
        else if (x == 9) {
            int i = 0; //to store database line value
            FILE* stream = fopen("database.csv", "r"); //open the database in read mode
            char line[1024]; //to store database line value
            while (fgets(line, 1024, stream)) { //loop database lines/rows one by one
                char* tmp = strdup(line);
                // NOTE strtok clobbers tmp
                passPIN[i] = getfield(tmp, x); //get the required column value from the row/line then store to the array
                i++; //move to the next array feild
                free(tmp); //free the pointer declartion
            }
            fclose(stream); //close the file after saving all rows column values
        }
        else if (x == 10) {
            int i = 0;
            FILE* stream = fopen("database.csv", "r"); //open the database in read mode
            char line[1024]; //to store database line value
            while (fgets(line, 1024, stream)) { //loop database lines/rows one by one
                char* tmp = strdup(line);
                // NOTE strtok clobbers tmp
                accountNumber[i] = getfield(tmp, x); //get the required column value from the row/line then store to the array
                i++; //move to the next array feild
                free(tmp); //free the pointer declartion
            }
            fclose(stream); //close the file after saving all rows column values
        }
        else if (x == 11) {
            int i = 0;
            FILE* stream = fopen("database.csv", "r"); //open the database in read mode
            char line[1024]; //to store database line value
            while (fgets(line, 1024, stream)) { //loop database lines/rows one by one
                char* tmp = strdup(line);
                // NOTE strtok clobbers tmp
                cardStatus[i] = getfield(tmp, x); //get the required column value from the row/line then store to the array
                i++; //move to the next array feild
                free(tmp); //free the pointer declartion
            }
            fclose(stream); //close the file after saving all rows column values
        }
    }
}

void readCardlessServicesDatabase() { //function to retrive data from the database
    for (int x = 1; x <= 4; x++) { //x is the number of column
        if (x == 1) {
            int i = 0;
            FILE* stream = fopen("databaseCardless.csv", "r");//open the database in read mode
            char line[1024]; //to store database line value
            while (fgets(line, 1024, stream)) { //loop database lines/rows one by one
                char* tmp = strdup(line); //duplicate the string to the pointer to pass its location
                // NOTE strtok clobbers tmp
                phoneNumber[i] = getfield(tmp, x); //get the required column value from the row/line then store to the array
                i++; //move to the next array feild
                free(tmp); //free the pointer declartion
            }
            fclose(stream); //close the file after saving all rows column values
        }
        else if (x == 2) {
            int i = 0;
            FILE* stream = fopen("databaseCardless.csv", "r");//open the database in read mode
            char line[1024]; //to store database line value
            while (fgets(line, 1024, stream)) { //loop database lines/rows one by one
                char* tmp = strdup(line); //duplicate the string to the pointer to pass its location
                // NOTE strtok clobbers tmp
                walletID[i] = getfield(tmp, x); //get the required column value from the row/line then store to the array
                i++; //move to the next array feild
                free(tmp); //free the pointer declartion
            }
            fclose(stream); //close the file after saving all rows column values
        }
        else if (x == 3) {
            int i = 0;
            FILE* stream = fopen("databaseCardless.csv", "r");//open the database in read mode
            char line[1024]; //to store database line value
            while (fgets(line, 1024, stream)) { //loop database lines/rows one by one
                char* tmp = strdup(line); //duplicate the string to the pointer to pass its location
                // NOTE strtok clobbers tmp
                walletBalance[i] = getfieldFloat(tmp, x); //get the required column value from the row/line then store to the array
                i++; //move to the next array feild
                free(tmp); //free the pointer declartion
            }
            fclose(stream); //close the file after saving all rows column values
        }
        else if (x == 4) {
            int i = 0;
            FILE* stream = fopen("databaseCardless.csv", "r");//open the database in read mode
            char line[1024]; //to store database line value
            while (fgets(line, 1024, stream)) { //loop database lines/rows one by one
                char* tmp = strdup(line); //duplicate the string to the pointer to pass its location
                // NOTE strtok clobbers tmp
                walletStatus[i] = getfield(tmp, x); //get the required column value from the row/line then store to the array
                i++; //move to the next array feild
                free(tmp); //free the pointer declartion
            }
            fclose(stream); //close the file after saving all rows column values
        }
    }
}

void writeCardServicesDatabase() { //function to inform the database with the data updates
    FILE* clear = fopen("database.csv", "w"); //open the database in write mode then close it to blank it
    fclose(clear); //close the database
    FILE* append = fopen("database.csv", "a"); //open the database in append mode
    for (int z = 0; z < 1024; z++) { //append values to database from values stored in the arrays row by row
        if (visaNumber[z] == 0) {
            break;
        }
        else {
            fprintf(append, "%lld,%d,%d,%d,%.2f,%d,%s,%s,%d,%lld,%d\n", visaNumber[z], xpMonth[z], xpYear[z], CVV[z], accountBalance[z], PIN[z], name[z], bankName[z], passPIN[z], accountNumber[z], cardStatus[z]);
        }
    }
    fclose(append);
}

void writeCardlessServicesDatabase() { //function to inform the database with the data updates
    FILE* clear = fopen("databaseCardless.csv", "w"); //open the database in write mode then close it to blank it
    fclose(clear); //close the database
    FILE* append = fopen("databaseCardless.csv", "a"); //open the database in append mode
    for (int z = 0; z < 1024; z++) { //append values to database from values stored in the arrays row by row
        if (phoneNumber[z] == 0) {
            break;
        }
        else {
            fprintf(append, "%lld,%lld,%.2f,%d\n", phoneNumber[z], walletID[z], walletBalance[z], walletStatus[z]);
        }
    }
    fclose(append);
}

void consoleClear() { //function that clear console then print logo
    system("CLS");
    printf("MMMNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNMMM\nMM+ .............................................................................................+MM\nMM/             `/yyoyho.         ////////ohhh+///////:      .hhyyh+.           .ohshhh`         /MM\nMM/           -smms- .omNh/`              +MMM-              yMMs.omNy:`      .+hmy:`NMM+        /MM\nMM/        .+dNdh+/////+ydNms-            +MMM-             .MMM-   `:yNmo. :ymh+.    sMMm       /MM\nMM/      .odmy:`         `-oddy:          /mmm-             smmy       .oddydo-       .mmm:      /MM\nMM+ ...........-- - ................--........-- - ............--......................-- - .....+MM\nMMMNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNMMM\n\n\n\n\n");
}

//prototypes for used functions
void start();
void cardlessServices();
void walletIDHandler();
void walletService();
void cardService();
void cardChecker();
void walletServicesUserInfoCheck();
void cardCheckerErrorHandler();
void cardPinHandler();
void withdraw();
void widthdrawErrorHandler();
void anotherTransactionHandler();
void unexpectedInputHandler();
void walletServicesUserInfoCheckErrorHandler();
void withdrawWallet();
void widthdrawWalletErrorHandler();
void anotherWalletTransactionHandler();
void deposit();
void donate();
void balance();
void installments();
void depositWallet();
void balanceWallet();
void accountChecker();
void accountPinHandler();
void cardlessDeposit();
void anotherCardlessDeposit();
void accountCheckerErrorHandler();

int main() {
    system("color 1e");
    readCardServicesDatabase();
    readCardlessServicesDatabase();
    start();
}

void start() { //function that start ATM execution
    consoleClear();
    printf("\t\t\t\t************WELCOME************\n\n");
    invalidTries = 0;
    int serviceChoice;
    printf("1-Cardless service\t\t\t\t\t\t\t\t");
    printf("2-Card service\n");
    scanf_s("%d", &serviceChoice);
    unexpectedInputHandler();
    if (serviceChoice == 1)
    {
        cardlessServices();
    }
    else if (serviceChoice == 2) {
        cardChecker();
    }
    else { //repromote the user to enter value again if value was incorrect
        printf("Invalid choice, Enter a correct option\n");
        Sleep(1000);
        start();
    }
}

void cardlessServices() { //function that dispaly cardless services menu
    int serviceChoice; //choice handler
    invalidTries = 0;
    printf("Choose your cardless service\n");
    Sleep(1);
    printf("1-Personal account deposit\n");
    printf("2-Smart wallet services\n");
    printf("3-Return to main menu\n");
    scanf_s("%d", &serviceChoice);
    unexpectedInputHandler();
    if (serviceChoice == 1) {
        accountChecker();
    }
    else if (serviceChoice == 2) {
        walletServicesUserInfoCheck();
    }
    else if (serviceChoice == 3) {
        start();
    }
    else { //repromote the user to enter value again if value was incorrect
        printf("Invalid choice, Please enter a correct option\n");
        Sleep(1000);
        cardlessServices();
    }
}

void cardService() {//function that dispaly card services menu
    int serviceChoice;
    printf("\t\t\t\t**************Choose your option**************\n");
    printf("\t\t\t\t\t\t1-Withdraw \n");
    printf("\t\t\t\t\t\t2-Deposite \n");
    printf("\t\t\t\t\t\t3-Balance view\n");
    printf("\t\t\t\t\t\t4-Pay bills , eui installments \n");
    printf("\t\t\t\t\t\t5-Donate to charities\n");
    printf("\t\t\t\t\t\t6-Account details view\n");
    printf("\t\t\t\t\t\t7-Return to main menu\n");
    scanf_s("%d", &serviceChoice);
    unexpectedInputHandler();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
    if (serviceChoice == 1) {
        withdraw();
    }
    else if (serviceChoice == 2) {
        deposit();
    }
    else if (serviceChoice == 3) {
        balance();
    }
    else if (serviceChoice == 4) {
        installments();
    }
    else if (serviceChoice == 5) {
        donate();
    }
    else if (serviceChoice == 6) {
        printf("Owner name = %s\n", name[currentUser]);
        printf("Bank nmae = %s\n", bankName[currentUser]);
        printf("Account number = %lld\n", accountNumber[currentUser]);
        printf("Account Balance = % .2f\n", accountBalance[currentUser]);
        anotherTransactionHandler();
    }
    else if (serviceChoice == 7) {
        start();
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
        printf("Invalid choice, Please enter a correct option\n");
        Sleep(1000);
        cardService();
    }


}

void cardChecker() { //function that handle visa number and pin flow
    long long int visaNumberInput; //user visa number input handler
    readCardServicesDatabase(); //retrive latest database updates
    printf("Enter your visa card number\n");
    scanf_s("%lld", &visaNumberInput);
    unexpectedInputHandler();
    for (int i = 0; i < 1024; i++) {
        if (visaNumber[i] == 0) { //if reached anything after the last visa number in the array, then visa card number is invald or doesn't exist in the database
            printf("Invalid visa card number\n");
            Sleep(1000);
            cardCheckerErrorHandler(); //parse case to error handler
        }
        else if (visaNumberInput == visaNumber[i]) { //if visa card found in the database complete program flow
            currentUser = i; //help retrive the correct data for the entered visa card
            if (cardStatus[currentUser] == 1) { //check if visa is disabled before or not
                printf("your card is disabled please visit the nearest bank branch to reactivate it\n");
                Sleep(1000);
                start();
            }
            else { //promote the user to input visa pin after passing all the previous checks
                cardPinHandler();
            }
        }
    }

}

void walletServicesUserInfoCheck() {
    readCardlessServicesDatabase(); //retrive latest database updates
    long long int phoneNumberInput;
    printf("Enter your phone number\n");
    scanf_s("%lld", &phoneNumberInput);
    unexpectedInputHandler();
    for (int i = 0; i < 1024; i++) {
        if (phoneNumber[i] == 0) { //if reached anything after the last phone number in the array, then phone number is invald or doesn't exist in the database
            printf("Invalid phone number\n");
            Sleep(1000);
            walletServicesUserInfoCheckErrorHandler(); //parse case to error handler
        }
        else if (phoneNumberInput == phoneNumber[i]) { //if phone number found in the database complete program flow
            currentUser = i; //help retrive the correct data for the entered phone number
            if (walletStatus[currentUser] == 1) { //check if wallet is disabled before or not
                printf("your wallet is disabled please visit the nearest service provider to reactivate it\n");
                Sleep(1000);
                cardlessServices();
            }
            else { //promote the user to input wallet ID after passing all the previous checks
                walletIDHandler();
            }
        }
    }
}

void walletIDHandler() {
    if (invalidTries == 3) { //if user inputed 3 invalid pins, disable the visa card
        walletStatus[currentUser] = 1;
        printf("Your wallet has been disabled due to too many invalid tries, Please visit nearest service provider to reactivate it\n");
        Sleep(1000);
        writeCardlessServicesDatabase(); //inform the database with the data updates
        cardlessServices(); //return to main menu
    }
    else {
        long long int walletIDInput; //user pin input handler
        printf("Enter your wallet ID\n");
        scanf_s("%lld", &walletIDInput);
        unexpectedInputHandler();
        if (walletIDInput == walletID[currentUser]) { //if pin is correct redirect the user to card services transactions menu
            walletService();
        }
        else { //if pin is invalid less than 3 times repromote the user to enter it again
            invalidTries = invalidTries + 1;
            printf("Invalid wallet ID\n");
            Sleep(1000);
            walletIDHandler();
        }
    }
}

void walletServicesUserInfoCheckErrorHandler() {
    int rechoice;
    printf("Please Enter a correct choice\n");
    Sleep(1000);
    printf("1-ReEnter your phone number\n2-Return to cardless services menu\n");
    scanf_s("%d", &rechoice);
    unexpectedInputHandler();
    if (rechoice == 1) {
        walletServicesUserInfoCheck();
    }
    else if (rechoice == 2) {
        cardlessServices();
    }
    else {
        cardCheckerErrorHandler();
    }
}

void walletService() {//function that dispaly wallet services menu
    int serviceChoice; //user input handler
    printf("Choose your option\n");
    printf("1-Withdraw\n");
    printf("2-Deposite\n");
    printf("3-Balance view\n");;
    printf("4-Return to cardless services menu\n");
    scanf_s("%d", &serviceChoice);
    unexpectedInputHandler();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
    if (serviceChoice == 1) {
        withdrawWallet();
    }
    else if (serviceChoice == 2) {
        depositWallet();
    }
    else if (serviceChoice == 3) {
        balanceWallet();
    }
    else if (serviceChoice == 4) {
        cardlessServices();
    }
    else { //repromote the user to enter value again if value was incorrect
        printf("Invalid choice, Please enter a correct option\n");
        Sleep(1000);
        walletService();

    }
}

void cardCheckerErrorHandler() { //function that handle errors than may happen while checking visa card numbers
    int rechoice;
    printf("Please Enter a correct choice\n");
    Sleep(1000);
    printf("1-ReEnter your visa card number\n2-Return to main menu\n");
    scanf_s("%d", &rechoice);
    unexpectedInputHandler();
    if (rechoice == 1) {
        cardChecker();
    }
    else if (rechoice == 2) {
        start();
    }
    else {
        cardCheckerErrorHandler();
    }
}

void cardPinHandler() { //function that handle user pin of the card
    if (invalidTries == 3) { //if user inputed 3 invalid pins, disable the visa card
        cardStatus[currentUser] = 1;
        printf("Your card has been disabled due to too many invalid tries, Please visit nearest bank branch to reactivate it\n");
        Sleep(1000);
        writeCardServicesDatabase(); //inform the database with the data updates
        start(); //return to main menu
    }
    else {
        int visaPIN; //user pin input handler
        printf("Enter your visa card PIN:\n");
        scanf_s("%d", &visaPIN);
        unexpectedInputHandler();
        if (visaPIN == PIN[currentUser]) { //if pin is correct redirect the user to card services transactions menu
            cardService();
        }
        else { //if pin is invalid less than 3 times repromote the user to enter it again
            invalidTries = invalidTries + 1;
            printf("Invalid PIN\n");
            Sleep(1000);
            cardPinHandler();
        }
    }
}

void withdraw() { //function that control flow of withdrawing money
    long long int amountToWidthdraw; //user input handler
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
    printf("\t\t\tPlease enter amount to withdraw: ");
    scanf_s("%lld", &amountToWidthdraw);
    unexpectedInputHandler();
    PlaySound(TEXT("atm sound"), NULL, SND_SYNC);
    if (amountToWidthdraw < 1) { //check if the amount to widthraw is valid value
        printf("Invalid amount to withdraw\n");
        Sleep(1000);
        widthdrawErrorHandler(); //pare the problem to the error handler
    }
    else { //complete flow if user passed previous checks
        if (amountToWidthdraw > accountBalance[currentUser]) { //check if the user is tring to withdraw more than money avilable in his account
            printf("There is no suffient funds in your account");
            Sleep(1000);
            // ask them for another transaction
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
            anotherTransactionHandler(); //promote the user if he needs another transaction
        }
        else { //if not previous case then user has sufficient amounts to withdraw
            accountBalance[currentUser] = accountBalance[currentUser] - amountToWidthdraw; //update account balance
            writeCardServicesDatabase(); //inform the database with the data updates
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
            PlaySound(TEXT("ad"), NULL, SND_SYNC); //simulate withdrawing money from dispenser
            printf("You have withdrawn %lld and your new balance is %.2f ", amountToWidthdraw, accountBalance[currentUser]); //inform user with withdrawn amount and current account balance
            Sleep(1000);
            anotherTransactionHandler(); //promote the user if he needs another transaction
        }
    }
}

void withdrawWallet() { //function that control flow of withdrawing money
    long long int amountToWidthdraw; //user input handler
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
    printf("\t\t\tPlease enter amount to withdraw: ");
    scanf_s("%lld", &amountToWidthdraw);
    unexpectedInputHandler();
    PlaySound(TEXT("atm sound"), NULL, SND_SYNC);
    if (amountToWidthdraw > 20000) { //check if the use try to withdraw more than the maximum limit
        printf("Can't Widthdraw more than 20K\n");
        Sleep(1000);
        widthdrawWalletErrorHandler(); //pare the problem to the error handler
    }
    else if (amountToWidthdraw < 1) { //check if the amount to widthraw is valid value
        printf("Invalid amount to withdraw\n");
        Sleep(1000);
        widthdrawWalletErrorHandler(); //pare the problem to the error handler
    }
    else { //complete flow if user passed previous checks
        if (amountToWidthdraw > walletBalance[currentUser]) { //check if the user is tring to withdraw more than money avilable in his account
            printf("There is no suffient funds in your account");
            Sleep(1000);
            // ask them for another transaction
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
            anotherWalletTransactionHandler(); //promote the user if he needs another transaction
        }
        else { //if not previous case then user has sufficient amounts to withdraw
            walletBalance[currentUser] = walletBalance[currentUser] - amountToWidthdraw; //update account balance
            writeCardlessServicesDatabase(); //inform the database with the data updates
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
            PlaySound(TEXT("ad"), NULL, SND_SYNC); //simulate withdrawing money from dispenser
            printf("You have withdrawn %lld and your new balance is %.2f ", amountToWidthdraw, walletBalance[currentUser]); //inform user with withdrawn amount and current account balance
            Sleep(1000);
            anotherWalletTransactionHandler(); //promote the user if he needs another transaction
        }
    }
}

void widthdrawErrorHandler() { //function that handle errors that can happen when withdrawing money
    int userInput; //user input handler
    printf("Enter a correct option:\n");
    Sleep(1000);
    printf("1-ReEnter widthdraw amount\n2-Return to transactions menu\n"); //promote the user to decide what to do next
    scanf_s("%d", &userInput);
    unexpectedInputHandler();
    if (userInput == 1) {
        withdraw();
    }
    else if (userInput == 2) {
        cardService();
    }
    else { //repromote the user to decide what to do if input was invalid
        widthdrawErrorHandler();
    }
}

void widthdrawWalletErrorHandler() {
    int userInput; //user input handler
    printf("Enter a correct option:\n");
    Sleep(1000);
    printf("1-ReEnter widthdraw amount\n2-Return to wallet menu\n"); //promote the user to decide what to do next
    scanf_s("%d", &userInput);
    unexpectedInputHandler();
    if (userInput == 1) {
        withdrawWallet();
    }
    else if (userInput == 2) {
        walletService();
    }
    else { //repromote the user to decide what to do if input was invalid
        widthdrawWalletErrorHandler();
    }
}

void anotherTransactionHandler() { //function that handle another transaction promotion
    int anotherTransaction; //user input handler
    printf("\nDo you want another transaction?\n");
    Sleep(1000);
    printf("1-Yes\n2-No, Return to main menu\n");
    scanf_s("%d", &anotherTransaction);
    unexpectedInputHandler();
    if (anotherTransaction == 1) {
        cardService();
    }
    else if (anotherTransaction == 2) {
        int userChoice; //user input handler
        printf("do you want a validation recipt?\n");
        printf("1-Yes\n2-No\n");
        scanf_s("%d", &userChoice);
        unexpectedInputHandler();
        if (userChoice == 1) {
            time_t t;
            time(&t);
            printf("\nThis transaction has been done at (date and time): %s\n", ctime(&t));
            Sleep(4000);
            start();
        }
        else if (userChoice == 2) {
            start();
        }
        else {
            printf("Invalid Input");
            anotherTransactionHandler();
        }
    }
    else { //repromote the user to enter choice again if choice was invalid
        printf("Incorrect choice, Please enter a correct option:\n");
        Sleep(1000);
        anotherTransactionHandler();
    }
}

void anotherWalletTransactionHandler() { //function that handle another transaction promotion
    int anotherTransaction; //user input handler
    printf("\nDo you want another transaction?\n");
    Sleep(1000);
    printf("1-Yes\n2-No, Return to main menu\n");
    scanf_s("%d", &anotherTransaction);
    unexpectedInputHandler();
    if (anotherTransaction == 1) {
        walletService();
    }
    else if (anotherTransaction == 2) {
        int userChoice; //user input handler
        printf("do you want a validation recipt?\n");
        printf("1-Yes\n2-No\n");
        scanf_s("%d", &userChoice);
        unexpectedInputHandler();
        if (userChoice == 1) {
            time_t t;
            time(&t);
            printf("\nThis transaction has been done at (date and time): %s\n", ctime(&t));
            Sleep(4000);
            start();
        }
        else if (userChoice == 2) {
            start();
        }
        else {
            printf("Invalid Input");
            anotherWalletTransactionHandler();
        }
    }
    else { //repromote the user to enter choice again if choice was invalid
        printf("Incorrect choice, Please enter a correct option:\n");
        Sleep(1000);
        anotherWalletTransactionHandler();
    }
}

void unexpectedInputHandler() { //function that clear stdin buffer from garbage values
    if (NULL == fgets(trash, sizeof(trash), stdin)) {
        exit((fprintf(stderr, "Unexpected EOF or error!"), 1));
    }
    Sleep(500);
}

void deposit() {
    // DEPOSIT

    int amountToDeposit;
    printf("Please enter amount to deposit: ");
    scanf_s("%d", &amountToDeposit);
    unexpectedInputHandler();
    PlaySound(TEXT("atm sound"), NULL, SND_SYNC);
    if (amountToDeposit > 0) {
        // now that you have deposited something, update the balance variable

        accountBalance[currentUser] = amountToDeposit + accountBalance[currentUser];
        writeCardServicesDatabase();
        printf("Thank you for depositing, new balance is: %f", accountBalance[currentUser]);

        // request for another transaction
        anotherTransactionHandler();
    }
    else {
        printf("Invalid amount to deposite, process will terminate");
        anotherTransactionHandler(); // request for another transaction
    }

}

void balance() {


    PlaySound(TEXT("atm sound"), NULL, SND_SYNC);
    printf("Your bank balance is: %f", accountBalance[currentUser]);

    // request for another transaction
    anotherTransactionHandler();
}

void donate() {
    // this function to donate charities
    int amountToWidthdraw;
    int charity;
    printf("choose the charity that you want to donate ?\n");
    printf("1-resala\n");
    printf("2-misralkhier\n");
    scanf_s("%d", &charity);
    unexpectedInputHandler();
    printf("\t\t\tPlease enter amount to donate: ");
    scanf_s("%d", &amountToWidthdraw);
    unexpectedInputHandler();
    PlaySound(TEXT("atm sound"), NULL, SND_SYNC);
    if (amountToWidthdraw < 1) {
        printf("Invalid amount to withdraw, process will terminate\n");
        anotherTransactionHandler();
    }
    else {
        if (amountToWidthdraw > accountBalance[currentUser]) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
            printf("There is no insuffient funds in your account\n");
            // ask them for another transaction

            anotherTransactionHandler();
        }
        else {
            // this means account has something
            // so withdraw amount and update the balance variable 
            accountBalance[currentUser] = accountBalance[currentUser] - amountToWidthdraw;
            writeCardServicesDatabase();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
            printf("You have donated %d and your new balance is %.2f \n", amountToWidthdraw, accountBalance[currentUser]);
            if (charity == 1)
                printf("you donated to resala\n");
            else if (charity == 2)
                printf("you donated to misralkhir\n");
            anotherTransactionHandler();
        }
    }
}

void installments() {
    // this function to pay expense
    int amountToWidthdraw;
    int eui;
    printf("choose the number of expenses ?\n");
    printf("1-installment 1\n");
    printf("2-installment 2\n");
    scanf_s("%d", &eui);
    unexpectedInputHandler();
    printf("\t\t\tPlease entre the ammount you want to pay: ");
    scanf_s("%d", &amountToWidthdraw);
    unexpectedInputHandler();
    PlaySound(TEXT("atm sound"), NULL, SND_SYNC);
    if (amountToWidthdraw < 1) {
        printf("Invalid amount to withdraw\n");
        anotherTransactionHandler();
    }
    else {
        if (amountToWidthdraw > accountBalance[currentUser]) {
            printf("There is no insuffient funds in your account\n");
            // ask them for another transaction

            anotherTransactionHandler();
        }
        else {
            // this means account has something
            // so withdraw amount and update the balance variable 
            accountBalance[currentUser] = accountBalance[currentUser] - amountToWidthdraw;
            writeCardServicesDatabase();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
            printf("You have paid %d and your new balance is %f\n ", amountToWidthdraw, accountBalance[currentUser]);
            if (eui == 1)
                printf("you paid this amount %d in the frist installments\n", amountToWidthdraw);
            else if (eui == 2)
                printf("you paid this amount %d in the second expense\n", amountToWidthdraw);
            anotherTransactionHandler();
        }
    }
}

void depositWallet() {
    // DEPOSIT

    int amountToDeposit;
    printf("Please enter amount to deposit: ");
    scanf_s("%d", &amountToDeposit);
    unexpectedInputHandler();
    PlaySound(TEXT("atm sound"), NULL, SND_SYNC);
    PlaySound(TEXT("ad"), NULL, SND_SYNC);
    if (amountToDeposit > 0) {
        // now that you have deposited something, update the balance variable

        walletBalance[currentUser] = amountToDeposit + walletBalance[currentUser];
        writeCardlessServicesDatabase();
        printf("Thank you for depositing, new balance is: %.2f\n", walletBalance[currentUser]);

        // request for another transaction
        anotherWalletTransactionHandler();
    }
    else {
        printf("Invalid amount to deposite, process will terminate\n");
        anotherWalletTransactionHandler(); // request for another transaction
    }

}

void balanceWallet() {


    printf("Your wallet balance is: %f\n", walletBalance[currentUser]);

    // request for another transaction
    anotherWalletTransactionHandler();
}

void accountChecker() { //function that handle account number and passpin flow
    long long int accountNumberInput; //user visa number input handler
    readCardServicesDatabase(); //retrive latest database updates
    printf("Enter your account number\n");
    scanf_s("%lld", &accountNumberInput);
    unexpectedInputHandler();
    for (int i = 0; i < 1024; i++) {
        if (visaNumber[i] == 0) { //if reached anything after the last account number in the array, then account number is invald or doesn't exist in the database
            printf("Invalid account number\n");
            Sleep(1000);
            accountCheckerErrorHandler(); //parse case to error handler
        }
        else if (accountNumberInput == accountNumber[i]) { //if account found in the database complete program flow
            currentUser = i; //help retrive the correct data for the entered account number
            if (cardStatus[currentUser] == 1) { //check if account is disabled before or not
                printf("your account is disabled please visit the nearest bank branch to reactivate it\n");
                Sleep(1000);
                start();
            }
            else { //promote the user to input visa pin after passing all the previous checks
                accountPinHandler();
            }
        }
    }

}

void accountPinHandler() { //function that handle user passpin of the account
    if (invalidTries == 3) { //if user inputed 3 invalid pins, disable the account
        cardStatus[currentUser] = 1;
        printf("Your card has been disabled due to too many invalid tries, Please visit nearest bank branch to reactivate it\n");
        Sleep(1000);
        writeCardServicesDatabase(); //inform the database with the data updates
        start(); //return to main menu
    }
    else {
        int passPINInput; //user pass pin input handler
        printf("Enter your account  passPIN:\n");
        scanf_s("%d", &passPINInput);
        unexpectedInputHandler();
        if (passPINInput == passPIN[currentUser]) { //if pin is correct redirect the user to card services transactions menu
            cardlessDeposit();
        }
        else { //if pass pin is invalid less than 3 times repromote the user to enter it again
            invalidTries = invalidTries + 1;
            printf("Invalid pass PIN\n");
            Sleep(1000);
            accountPinHandler();
        }
    }
}

void cardlessDeposit() {
    int amountToDeposit;
    printf("Please enter amount to deposit: ");
    scanf_s("%d", &amountToDeposit);
    unexpectedInputHandler();
    PlaySound(TEXT("atm sound"), NULL, SND_SYNC);
    if (amountToDeposit > 6000) {
        printf("Can't deposit more than 6K, process will terminate");
        anotherCardlessDeposit();
    }
    if (amountToDeposit > 0 && amountToDeposit <= 6000) {
        // now that you have deposited something, update the balance variable

        accountBalance[currentUser] = amountToDeposit + accountBalance[currentUser];
        writeCardServicesDatabase();
        printf("Thank you for depositing, new balance is: %f", accountBalance[currentUser]);

        // request for another transaction
        anotherTransactionHandler();
    }
    else {
        printf("Invalid amount to deposite, process will terminate");
        anotherTransactionHandler(); // request for another transaction
    }
}

void anotherCardlessDeposit() {
    int anotherDeposit; //user input handler
    printf("\nDo you want another Deposit?\n");
    Sleep(1000);
    printf("1-Yes\n2-No, Return to cardless services menu\n");
    scanf_s("%d", &anotherDeposit);
    unexpectedInputHandler();
    if (anotherDeposit == 1) {
        cardlessDeposit();
    }
    else if (anotherDeposit == 2) {
        int userChoice; //user input handler
        printf("do you want a validation recipt?\n");
        printf("1-Yes\n2-No\n");
        scanf_s("%d", &userChoice);
        unexpectedInputHandler();
        if (userChoice == 1) {
            time_t t;
            time(&t);
            printf("\nThis transaction has been done at (date and time): %s\n", ctime(&t));
            Sleep(4000);
            cardlessServices();
        }
        else if (userChoice == 2) {
            cardlessServices();
        }
        else {
            printf("Invalid Input");
            anotherCardlessDeposit();
        }
    }
    else { //repromote the user to enter choice again if choice was invalid
        printf("Incorrect choice, Please enter a correct option:\n");
        Sleep(1000);
        anotherCardlessDeposit();
    }
}

void accountCheckerErrorHandler() { //function that handle errors than may happen while checking visa card numbers
    int rechoice;
    printf("Please Enter a correct choice\n");
    Sleep(1000);
    printf("1-ReEnter your visa card number\n2-Return to cardless services menu\n");
    scanf_s("%d", &rechoice);
    unexpectedInputHandler();
    if (rechoice == 1) {
        accountChecker();
    }
    else if (rechoice == 2) {
        cardlessServices();
    }
    else {
        accountCheckerErrorHandler();
    }
}

