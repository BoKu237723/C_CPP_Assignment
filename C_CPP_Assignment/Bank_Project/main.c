#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define USERSIZE 1000
#define DATA_COUNT 20
#define BANK_ACCOUNT_FIELDS 19

// function declaration 
int check_input(char input[2]);
void rEgister();
void login();
void loading_from_file();
void main_menu();
void space_counter();
int char_counting(char my_char[50]);
void printing_all_data();
void email_validation(char to_check[50]);
void email_exit_checking(char email[50]);
void compare_two_charArray(char first[200], char second[200]);
void nrc_validation(char nrc[20]);
void strong_pass_validation(char pass[50]);
void phone_validation(unsigned int phone);
void encryption_key_validation(char eKey[30]);
void recovery_key_validation(char reKey[30]);
void copy_two_char_array(char reciver[200], char transmitter[200]);
void user_sector();
void phone_number_finding(unsigned int to_find_ph);
void transfer_moeny();
void user_sector();
void money_transaction(int transmit, int receiver,unsigned int amount);
void printing_specific_data(int user);
void user_withdraw();
void recording_all_data_to_file();
void get_time();
void transaction_record(int userDBindex, int uFound, char who, unsigned int amount);
void integer_to_charArrayFun(unsigned int integer);
unsigned int char_to_integer_fun(char char_array[50]);
void time_class_last_record(int user_index);
void time_class(int user_index);
void time_class_get_date(char last_record[]);
//function declaration


//global variable
int G_index=0;
int email_found = -1;
int space_array[DATA_COUNT];
int email_valid = -1;
int nrc_valid = -1;
int two_charArray = -1;
int strong_pass_valid = -1;
int phone_valid = -1;
int eKey_valid = -1;
int reKey_valid = -1;
int phone_found = -1;

char int_to_charArray[15];
char month[3];
char day[2];
char year[4];
//end of global variable

struct trans{
    char note[200];
};

struct info{
    unsigned int id;
    char name[50];
    char nrc[20];
    char email[50];
    char password[50];
    unsigned int phoneNumber;
    char ecnryption_key[6];
    char recovery_key[10];
    char account_status[10];
    int account_type;
    int account_level;
    int minimum_opening_deposit;
    char currency[5];
    unsigned long long int current_amount;
    char loanStatus[1];
    unsigned int monthly_income;
    unsigned int loan_amount;
    float loan_rate;
    char address[100];
    int trans_amount_limit_perday;

    struct trans tr[300]; //transaction
};
struct myTime{
    char current_time[25];
};
struct myTime getCTime[1];
struct info db[USERSIZE];

//%u %s %s %s %s %u %s %s %s %d %d %d %s %llu %s %u %u %f %s

void main_menu(){
    char input[2];
    printf("Welcome to our Online Bank - NCC!\n");
    printf("Press 1 to Login!\nPress 2 to Register!\nPress 3 to Exit!>>:");
    scanf("%2s", input); //edit [1]
    getchar();
    int option = check_input(input);
    if(option == 49){
        login();
    }else if(option == 50){
        rEgister();
    }else if(option == 51){
        recording_all_data_to_file();
        printf("Exit\n");
        exit(2);
    }else{
        main_menu();
    }
}

void login() {
    char l_email[50];
    char l_pass[50];
    email_found = -1;
    two_charArray = -1;

    while (email_found == -1 || two_charArray == -1) { 
        printf("This is Online Bank Login!\n");
        printf("Enter your email to login!>>:");
        scanf(" %[^\n]", l_email);
        printf("Enter your password to login >>:");
        scanf(" %[^\n]", l_pass);

        email_exit_checking(l_email);
        // email_exit_checking(l_email);
        // compare_two_charArray(db[email_found].password, l_pass); 
        // if (email_found == -1 || two_charArray == -1) { 
        //     printf("Your Login credential incorrect!\n");
        //     continue; 
        // }

        if (email_found == -1) { 
            printf("Your Login credential incorrect!\n");
            continue; 
        }

        compare_two_charArray(db[email_found].password, l_pass); 
        if (two_charArray == -1) {
            printf("Your Login credential incorrect!\n");
            email_found = -1; 
            continue;
        }
        user_sector();
    }
}

//user choice

void user_sector(){
    printf("\nWelcome Mr/s: %s\n", db[email_found].name);
    printf("Your Current Amount: %llu\n", db[email_found].current_amount);
    char user_option[2];
    printf("Press 1 to Transfer money:\nPress 2 to Witthdraw:\nPress 3 to Cash in:\nPress 4 to get your transaction record:\nPress 5 to Loan:\nPress 6 to go back to main menu:\nPress 7 to Exit:\n");
    printf("Enter your option: ");
    scanf(" %[^\n]",&user_option[0]);
    int option = check_input(user_option);
    if(option == 49){
        transfer_moeny();
    }else if(option == 50){
        user_withdraw();
    }else if(option == 55){
        printf("Exiting...\n");
        recording_all_data_to_file();
        main_menu();
    }
}

void user_withdraw(){
    char with_pass[50];
    unsigned int withdraw_amount = 0;
    printf("Your current amount is : %s : %llu\n\n",db[email_found].name, db[email_found].current_amount);
    printf("Enter amount to withdraw : ");
    scanf("%u",&withdraw_amount);
    if(withdraw_amount < db[email_found].current_amount - 1000){
        printf("Enter your password to proceed withdraw : ");
        scanf(" %[^\n]",&with_pass[0]);
        two_charArray = -1;
        compare_two_charArray(db[email_found].password, with_pass);
        if(two_charArray == 1){
            printf("Get your withdraw amount : %u\n",withdraw_amount);
            printf("Your current amount : %llu",db[email_found].current_amount - withdraw_amount);
            user_sector();
        }else{
            printf("Wrong credential!\n");
            user_withdraw();
        }
    }else{
        printf("Insufficient Balance\n");
        user_sector();
    }
}

void transfer_moeny(){
    unsigned int amount_toTrans = 0;
    unsigned int receiver_phone = 0;
    char trans_pass[50];
    phone_found = -1;
    while(phone_found == -1){
        printf("Enter receiver phone number: ");
        scanf("%u",&receiver_phone);
        phone_number_finding(receiver_phone);
        if(phone_found == -1){
            printf("Phone number not found!\n");
        }
    }
    while (1) {
        printf(" Enter amount to send for %s :  %s >>: ", db[phone_found].name, db[phone_found].email);
        scanf("%u", &amount_toTrans);

        if(amount_toTrans < db[email_found].current_amount-1000){
            break;
        }
    }
    two_charArray=-1;
    int wrong_counter=0;
    while (two_charArray==-1){
        printf("Your current amount %llu\nTransfer amount %u :\n",db[email_found].current_amount,amount_toTrans);
        printf("Enter your password to confirm for transaction>>:");
        scanf(" %[^\n]",&trans_pass[0]);

        compare_two_charArray(db[email_found].password,trans_pass);
        if(two_charArray==-1){
            wrong_counter++;
            if(wrong_counter==3){
                transfer_moeny();
                break;
            }
        }
    }
    money_transaction(email_found,phone_found,amount_toTrans);
}

void money_transaction(int transmit, int receiver,unsigned int amount){
    printf("This is from money transaction!\n");
    unsigned long long int total_transaction_today = 0;
    //calculate
    for (int i = 0; i < space_array[transmit] - 20; i++) {
        if (db[transmit].tr[i].note[0] == 'F') { // Check
            unsigned int transaction_amount = char_to_integer_fun(&db[transmit].tr[i].note[char_counting(db[transmit].tr[i].note) - 1]);
            total_transaction_today += transaction_amount;
        }
    }
    if (total_transaction_today + amount > db[transmit].trans_amount_limit_perday) {
        printf("Transaction limit exceeded! You can only transact up to %d today.\n", db[transmit].trans_amount_limit_perday);
        user_sector();
    }
    //complete calculate

    db[transmit].current_amount = db[transmit].current_amount - amount;
    db[receiver].current_amount = db[receiver].current_amount + amount;
    printf("Transaction complete \n");
    printf("Your current amount is : %s : %llu\n\n",db[transmit].name, db[transmit].current_amount);
    transaction_record(transmit,receiver,'t',amount);
    transaction_record(transmit,receiver,'r',amount);
    printing_specific_data(transmit);
    printf("\n\n\n");
    printing_all_data();
    user_sector();
}

void phone_number_finding(unsigned int to_find_ph){
for(int i=0; i<G_index; i++){

        if(to_find_ph == db[i].phoneNumber){
            phone_found=i;
            break;
        }
    }
}

//end of user choice

//time
void get_time()
{
    time_t tm;
    time(&tm);
    int time_space_counter = 0;

    printf("Current Date/Time = %s",ctime(&tm));
    FILE *fptr = fopen("mytime.txt","w");
    fprintf(fptr,"%s",ctime(&tm));
    int index = 0;
    fclose(fptr);
    getCTime[0].current_time[index] = '-';

    FILE *fptr2 = fopen("mytime.txt","r");
    char c = fgetc(fptr2);
    while(!feof(fptr2)){
        if(c == ' '){
            time_space_counter++;
            if(time_space_counter == 1){
                getCTime[0].current_time[index] = '!';
                c = fgetc(fptr2);
                index++;
            }else if(time_space_counter == 4){
                getCTime[0].current_time[index] = '@';
                c = fgetc(fptr2);
                index++;
            }else{
                getCTime[0].current_time[index] = '-';
                c = fgetc(fptr2);
                index++;
            }
            
        }else{
            getCTime[0].current_time[index] = c;
            c = fgetc(fptr2);
            index++;
        }
    }
    fclose(fptr2);
    printf("removed space : %s",getCTime[0].current_time);
}

void time_class(int user_index){
    time_class_last_record(user_index);
}

void time_class_last_record(int user_index){
    int last = 0;
    int records = space_array[user_index] - 19;
    for(int i = 0; i<records; i++){
        last = i;
    }
    printf("\nUser last record : %s\n",db[user_index].tr[last].note);
    time_class_get_date(db[user_index].tr[last].note);
}

void time_class_get_date(char last_record[]){
    // month, day, year
    int last_record_counter = char_counting(last_record);
    int i = 0;
    for (i = 0; i < last_record_counter; i++) {

        if (last_record[i] == '!') {
            break;
        }
    }
    i++;
    for (int a = 0; a < 3; a++) {
        month[a] = last_record[i];
        i++;
    }
    printf("\nMonth : %s\n", month);
    day[0] = last_record[i + 1];
    day[1] = last_record[i + 2];
    unsigned int get_day = char_to_integer_fun(day);
    printf("Day : %d\n", get_day);

    int z = 0;

    // for (z = 0; z < last_record_counter; z++) {
    //     if (last_record[z] == '@') {
    //         break;
    //     }
    // }
    // for (int x = 0; x < 4; x++) {
    //     z++;
    //     year[x] = last_record[z];
    // }
    // unsigned int get_year = char_to_integer_fun(year);
    // printf("year :%d\n", get_year);
    
    for (z = 0; z < last_record_counter; z++) {
        if (last_record[z] == '@') {
            z++;
            break;
        }
    }
    for (int x = 0; x < 4; x++) {
        year[x] = last_record[z++];
    }
    year[4] = '\0'; //remove
    unsigned int get_year = char_to_integer_fun(year);

    printf("year: %d\n", get_year);

}

//end of time

void integer_to_charArrayFun(unsigned int integer){
    for(int i = 0; i<15; i++){
        int_to_charArray[i]='\0';
    }
    int index = 0;
    FILE *fptr = fopen("whw.txt","w");
    if(fptr == NULL){
        printf("Could not open file");
    }else{
        fprintf(fptr,"%d",integer);
    }
    fclose(fptr);
    FILE *fptr2 = fopen("whw.txt","r");
    char c = fgetc(fptr2);
    while(!feof(fptr2)){
        int_to_charArray [index] = c;
        c = fgetc(fptr2);
        index++;
    }
    fclose(fptr2);
}

unsigned int char_to_integer_fun(char char_array[50]){
    unsigned int char_to_int_data = 0;
    FILE *fptr = fopen("whw.txt","w");
    if(fptr==NULL){
        printf("Error \n");
    }else{
        fprintf(fptr,"%s",char_array);
    }
    fclose(fptr);
    FILE *fptr2 = fopen("whw.txt","r");
    if(fptr2 == NULL){
        printf("Error\n");
    }else{
        fscanf(fptr,"%d",&char_to_int_data);
    }
    return char_to_int_data;
}

void transaction_record(int userDBindex, int uFound, char who, unsigned int amount){ //t or r in 'who'

    //userDBindex = transmitter
    //uFound = receiver

    integer_to_charArrayFun(amount);
    int transfer = char_counting(db[userDBindex].name);
    int accept = char_counting(db[uFound].name);
    int money_quant_counter = char_counting(int_to_charArray); //here

    if(who == 't'){
        char toInsert1[5] = {'F','r','o','m',':'};
        char toInsert2[4] = {':','t','o',':'};
        int indexPoint = 0;
        for(int x = indexPoint; x<5; x++){
            db[userDBindex].tr[space_array[userDBindex]-19].note[x]=toInsert1[x];
            indexPoint++;
        }
        int nameIndex = 0;
        int endPoint = indexPoint + transfer;
        for(int x = indexPoint; x<endPoint; x++){
            db[userDBindex].tr[space_array[userDBindex]-19].note[indexPoint] = db[userDBindex].name[nameIndex];
            nameIndex++;
            indexPoint++; 
        }
        nameIndex = 0;
        endPoint = indexPoint+4;
        for(int x = indexPoint; x<endPoint; x++){
            db[userDBindex].tr[space_array[userDBindex]-19].note[indexPoint] = toInsert2[nameIndex];
            nameIndex++;
            indexPoint++;
        }
        nameIndex = 0;
        endPoint = indexPoint+accept;
        for(int x = indexPoint; x<endPoint; x++){
            db[userDBindex].tr[space_array[userDBindex]-19].note[indexPoint] = db[uFound].name[nameIndex];
            nameIndex++;
            indexPoint++;
        }
        nameIndex = 0;
        get_time();

        db[userDBindex].tr[space_array[userDBindex]-19].note[endPoint] = ':';
        endPoint++;
        for(int win=endPoint; win<24+endPoint; win++){
            db[userDBindex].tr[space_array[userDBindex]-19].note[win] = getCTime[0].current_time[nameIndex];
            nameIndex++;
        }

        endPoint = endPoint + 24;
        db[userDBindex].tr[space_array[userDBindex]-19].note[endPoint] = '$';
        endPoint++;
        
        nameIndex = 0;
        for(int wa = endPoint; wa<endPoint+money_quant_counter; wa++){
            db[userDBindex].tr[space_array[userDBindex]-19].note[wa] = int_to_charArray[nameIndex];
            nameIndex++;
        }
        db[userDBindex].tr[space_array[userDBindex]-19].note[endPoint + money_quant_counter] = '-';
        space_array[userDBindex] = space_array[userDBindex]+1;
    }else{
        char receiveFrom[14] = {'-','R','e','c','e','i','v','e','-','F','r','o','m','-'};
        int indexPoint = 0;
        int endPoint = 0;
        int reIndex = 0;
        for(int i=0; i<accept; i++){
            db[uFound].tr[space_array[uFound]-19].note[i] = db[uFound].name[i];
            indexPoint++;
        }
        endPoint = accept + 14;
        for(int i=indexPoint; i<endPoint; i++){
            db[uFound].tr[space_array[uFound]-19].note[i] = receiveFrom[reIndex];
            reIndex++;
        }
        reIndex = 0;
        int toendpoint = endPoint + transfer;
        for(int a = endPoint; a<toendpoint; a++){
            db[uFound].tr[space_array[uFound]-19].note[a] = db[userDBindex].name[reIndex];
            reIndex ++;
        }
        reIndex = 0;
        get_time();
        for(int win = toendpoint; win<24+toendpoint; win++){
            db[uFound].tr[space_array[uFound]-19].note[win] = getCTime[0].current_time[reIndex];
            reIndex++;
        }
        toendpoint = 24+ toendpoint;
        db[uFound].tr[space_array[uFound]-19].note[toendpoint] = '$';
        toendpoint++;
        for(int gcc = 0; gcc < money_quant_counter;gcc++){
            db[uFound].tr[space_array[uFound]-19].note[toendpoint] = int_to_charArray[gcc];
            toendpoint++;
        }
        db[uFound].tr[space_array[uFound]-19].note[toendpoint] = '-';;
        space_array[uFound] = space_array[uFound]+1;

    }
}

// void limit_transaction_amount_per_day(unsigned int amount){ //testing!
//     unsigned long long int total_transaction_today = 0;
//     //calculate
//     for (int i = 0; i < space_array[email_found] - 20; i++) {
//         if (db[email_found].tr[i].note[0] == 'F') { // Check if it's a transaction record
//             unsigned int transaction_amount = char_to_integer_fun(&db[email_found].tr[i].note[char_counting(db[email_found].tr[i].note) - 1]);
//             total_transaction_today += transaction_amount;
//         }
//     }
//     if (total_transaction_today + amount > db[email_found].trans_amount_limit_perday) {
//         printf("Transaction limit exceeded! You can only transact up to %d today.\n", db[email_found].trans_amount_limit_perday);
//         return;
//     }
// }

void rEgister() {
    char re_email[50];
    char re_name[50];
    char re_nrc[20];
    char re_pass[50];
    char re_encrypt_key[30];
    char re_recovery_key[30];
    char re_currency[5];
    unsigned int re_monthly_income = 0;
    char re_adddress[50];
    char re_note[200];
    unsigned long long int re_current_amount;
    unsigned int re_phone=0;

    email_valid = -1; 
    while (email_valid == -1) {
        printf("Enter your email to register>>:");
        scanf(" %[^\n]", re_email);
        email_validation(re_email);
        if (email_valid == -1) {
            printf("Your email format was not valid\n");
        }
    }
    //printf("Your email form was valid:\n");
    email_found = -1;
    email_exit_checking(re_email);
    if(email_found != -1){
        printf("Your email was already register!\n");
        rEgister();
    }else{
        printf("Your email was saved!\n");
        printf("Enter your user Name: ");
        scanf("%50s",re_name);
        nrc_valid = -1;
        while(nrc_valid == -1){
            printf("Enter your NRC information : ");
            scanf(" %50s", re_nrc);
            nrc_validation(re_nrc);
            if(nrc_valid==-1){
                printf("Your NRC format was not valid\n");
            }
        }
        printf("Your NRC format was correct\n");
        strong_pass_valid = -1;
        while(strong_pass_valid == -1){
            printf("Enter your password :");
            scanf("%50s,",&re_pass);
            strong_pass_validation(re_pass);
            if(strong_pass_valid == -1){
                printf("Your password format was too weak! Try again! \n");
            }
        }

        printf("Your password format was correct and was saved!\n");
        phone_valid = -1;
        while(phone_valid == -1){
            printf("Enter your phone number : ");
            scanf ("%u",&re_phone);
            phone_validation(re_phone);
            if(phone_valid == -1){
                printf("Your phone number is alredy registered\n");
            }
        }
        printf("Your phone is correct and saved!\n");
        printf("Enter your Encryption Key (From 4 to 6 char) : ");
        scanf(" %[^\n]", &re_encrypt_key);

        while(eKey_valid == -1){
            printf("Your phone is correct and saved!\n");
            printf("Enter your Encryption Key (From 4 to 6 char) : ");
            scanf(" %[^\n]", &re_encrypt_key);
            encryption_key_validation(re_encrypt_key);
            if(eKey_valid == -1){
                printf("Your Encryption Key do not correspond with our pattern\n");
            }
        }
        printf("Your encryption key was valid and saved.\n");
        while (reKey_valid==-1){
            printf("[X]Enter your Recover Key carefully:");
            scanf(" %[^\n]",&re_recovery_key[0]);
            recovery_key_validation(re_recovery_key);
            if(reKey_valid==-1){
                printf("[-]Your recovery Key do not correspond with our pattern:\n");
            }
        }
        printf("[+]Your recover key was saved!\n");
        printf("Your recovery key was saved\n");
        printf("Enter your currency to use: ");
        scanf(" %[^\n]", &re_currency);
        printf("Enter your current amount: ");
        scanf(" %llu", &re_current_amount);
        printf("Enter your monthly income: ");
        scanf(" %u", &re_monthly_income);
        printf("Enter your address: ");
        scanf(" %[^\n]",&re_adddress);
        printf("Enter your opening note: ");
        scanf(" %[^\n]",&re_note);

        db[G_index].id = G_index+1;
        copy_two_char_array(db[G_index].email,re_email);
        copy_two_char_array(db[G_index].nrc,re_nrc);
        copy_two_char_array(db[G_index].name,re_name);
        copy_two_char_array(db[G_index].password,re_pass);
        db[G_index].phoneNumber = re_phone;
        copy_two_char_array(db[G_index].ecnryption_key, re_encrypt_key);
        copy_two_char_array(db[G_index].recovery_key, re_recovery_key);
        copy_two_char_array(db[G_index].currency,re_currency); 
        db[G_index].current_amount = re_current_amount;
        db[G_index].monthly_income = re_monthly_income;
        copy_two_char_array(db[G_index].address, re_adddress);
        copy_two_char_array(db[G_index].tr[0].note, re_note);
        copy_two_char_array(db[G_index].account_status,db[2].account_status);
        db[G_index].account_level = db[2].account_level;

        copy_two_char_array(db[G_index].account_status,db[2].account_status);
        db[G_index].account_level=db[2].account_level;
        db[G_index].account_type = db[2].account_type;
        db[G_index].minimum_opening_deposit=db[2].minimum_opening_deposit;
        copy_two_char_array(db[G_index].loanStatus,db[2].loanStatus);
        db[G_index].loan_amount = db[2].loan_amount;
        db[G_index].loan_rate = db[2].loan_rate;

        space_array[G_index]=20;
        space_array[G_index] = 19;
        G_index++;
        printing_all_data();
        printf("Registration Success Mr/s %s\n",re_name);
        main_menu();
    }
}

void copy_two_char_array(char receiver[200], char transmitter[200]){
//    for(register int i=0; i<200; i++){
//        receiver[i]='\0';
//    }

    int transmit_counter =char_counting(transmitter);
    for(int i=0; i<transmit_counter; i++){

        receiver[i] = transmitter[i];
    }
}

void recovery_key_validation(char reKey[30]){
    int reKey_couunter = char_counting(reKey);
    if(reKey_couunter >=6 && reKey_couunter<=10){
        reKey_valid=1;
    }
}

void encryption_key_validation(char eKey[30]){
    int eKey_counter = char_counting(eKey);
    if(eKey_counter >= 4 && eKey_counter <=6){
        eKey_valid = 1;
    }
}

void phone_validation(unsigned int phone){
    int phone_counter = 0;
    for(int i = 0; i<G_index; i++){
        if(phone != db[i].phoneNumber){
            phone_counter++;
        }else{
            phone_valid = -1;
            break;
        }
    }
    if (phone_counter == G_index){
        phone_valid = 1;
    }
}

void strong_pass_validation(char pass[50]){
    int pass_counter = char_counting(pass);
    int i=0;
    int special = 0;
    int number = 0;
    int small = 0;
    int cap = 0;
    if(pass_counter >= 6){
        while (strong_pass_valid == -1){
            if (i == pass_counter){
                strong_pass_valid = -1;
                break;
            }

            if (pass[i] >= 33 && pass[i] <= 42){
                special ++;
            }else if(pass[i] >= 48 && pass[i] <= 57){
                number++;
            }else if(pass[i] >= 97 && pass[i] <= 122){
                small++;
            }else if(pass[i] >= 65 && pass[i] <= 90){
                cap++;
            }
            i++;
            if(special >= 1 && number >= 1 && small >= 1 && cap >= 1){
                strong_pass_valid = 1;
            }
        }
    }else{
        printf (">>  Your password must be at least 6 characters long\n");
        strong_pass_valid = -1;
    }
}

void nrc_validation(char nrc[20]){
    int nrc_counter = char_counting(nrc);
    for(int i=0; i<4; i++){
        two_charArray = -1;
        compare_two_charArray(nrc,db[i].nrc);
        if(two_charArray == 1){
            nrc_valid = 1;
            break;
        }
    }
}

void compare_two_charArray(char first[200], char second[200]){
    int first_counter = char_counting(first);
    int second_counter = char_counting(second);
    int same_counter = 0;
    if(first_counter == second_counter){
        for(register int i=0; i<first_counter; i++){
            if(first[i] != second[i]){
                break;
            }
            same_counter++;
        }

        if(first_counter == same_counter){
            two_charArray = 1;
        }
    }
}

void email_validation(char to_check[50]){
    int space = 1;
    int format = 1;
    char valid_form[10] = {'@','g','m','a','i','l','.','c','o','m'};
    int check_counter = char_counting(to_check);
    int front_counter = check_counter-10;
    for(int i = 0; i<front_counter; i++){
        if(to_check[i] == ' '){
            printf(">>  Space detected!\n");
            space = -1;
            break;
        }
    }
    for (int f=0; f<10; f++){
        if(to_check[front_counter] != valid_form[f]){
            format=-1;
            break;
        }
        front_counter++;
    }
    if(space == 1 && format==1){
        email_valid=1;
    }
}

void email_exit_checking(char email[50]){
    int counter = char_counting(email);
    for(register int gcc = 0; gcc<G_index; gcc++){
        int db_email_count = char_counting(db[gcc].email);
        int same_counting = 0;
        if(counter == db_email_count){
            for (register int a=0; a<counter; a++){
                if(email[a] != db[gcc].email[a]){
                    break;
                }
                same_counting++;
            }
        }

        if(counter == same_counting){
            email_found = gcc;
            break;
        }
    }
}

void loading_from_file(){
    FILE *fptr = fopen("encrypted_data.txt","r");
    if(fptr != NULL){
        if(fptr != NULL){
            for(register int user = 0; user < USERSIZE; user++){
                fscanf(fptr,"%u %s %s %s %s %u %s %s %s %d %d %d %s %llu %s %u %u %f %s %d",
                &db[user].id,&db[user].name,&db[user].nrc,&db[user].email,
                &db[user].password,&db[user].phoneNumber,&db[user].ecnryption_key,
                &db[user].recovery_key,&db[user].account_status,
                &db[user].account_type,&db[user].account_level,
                &db[user].minimum_opening_deposit,&db[user].currency,
                &db[user].current_amount,&db[user].loanStatus,
                &db[user].monthly_income,&db[user].loan_amount,
                &db[user].loan_rate,&db[user].address,&db[user].trans_amount_limit_perday);

                for(register int trc = 0; trc <= space_array[user]-20; trc++){
                    fscanf(fptr,"%s",&db[user].tr[trc].note);
                }

                if(db[user].id == 0){
                    break;
                }

                G_index++;
            }
        }
    }else{
        printf("File opening error at Loading from file function!\n");
    }

    fclose(fptr);
}

// void recording_all_data_to_file(){
//     FILE *fptr = fopen("encrypted_data.txt","w");
//     if(fptr == NULL){
//         printf("File opening error at recording to file function!\n");
//     }else{
//         for(int user = 0; user < G_index; user++){
//             fprintf(fptr,"%u%c%s%c%s%c%s%c%s%c%u%c%s%c%s%c%s%c%d%c%d%c%d%c%s%c%llu%c%s%c%u%c%u%c%f%c%s%c%d%c",
//             db[user].id,' ',db[user].name,' ',db[user].nrc,' ',db[user].email,
//             ' ',db[user].password,' ',db[user].phoneNumber,' ',db[user].ecnryption_key,
//             ' ',db[user].recovery_key,' ',db[user].account_status,
//             ' ',db[user].account_type,' ',db[user].account_level,
//             ' ',db[user].minimum_opening_deposit,' ',db[user].currency,
//             ' ',db[user].current_amount,' ',db[user].loanStatus,
//             ' ',db[user].monthly_income,' ',db[user].loan_amount,
//             ' ',db[user].loan_rate,' ',db[user].address,' ',db[user].trans_amount_limit_perday);
//             for(register int trc = 0; trc <= space_array[user]-20; trc++){
//                 fprintf(fptr," %s",&db[user].tr[trc].note);
//             }
//             fprintf(fptr,"%c",'\n');
//         }
//     }
//     printf("Recording complete to 'encrypted_data.txt'\n");
// }

void recording_all_data_to_file(){
    FILE *fptr = fopen("encrypted_data.txt","w");
    if(fptr == NULL){
        printf("File opening error at recording to file function():\n");
    } else{
        for(int user=0; user<G_index; user++){
            fprintf(fptr,"%u%c%s%c%s%c%s%c%s%c%u%c%s%c%s%c%s%c%d%c%d%c%d%c%s%c%llu%c%s%c%u%c%u%c%f%c%s%c%d",
            db[user].id ,' ',db[user].name ,' ',db[user].nrc,' ',db[user].email,' ',db[user].password,' ',
            db[user].phoneNumber,' ',db[user].ecnryption_key,' ',db[user].recovery_key,' ',db[user].account_status,' ',
            db[user].account_type,' ',db[user].account_level,' ',db[user].minimum_opening_deposit,' ',db[user].currency,' ',
            db[user].current_amount,' ',db[user].loanStatus,' ',db[user].monthly_income,' ',db[user].loan_amount,' ',
            db[user].loan_rate,' ',db[user].address,' ',db[user].trans_amount_limit_perday);
            for(register int trc=0; trc<= space_array[user]-20 ; trc++ ){
                fprintf(fptr , " %s",db[user].tr[trc].note);
            }
            fprintf(fptr,"%c",'\n');
        }
    }
    printf("Recording complete to 'encrypted_data.txt!' \n");
}

void printing_all_data(){
    for(int user = 0; user < G_index; user++){
        printf("%u-%s-%s-%s-%s-%u-%s-%s-%s-%d-%d-%d-%s-%llu-%s-%u-%u-%f-%s",
        db[user].id,db[user].name,db[user].nrc,db[user].email,
        db[user].password,db[user].phoneNumber,db[user].ecnryption_key,
        db[user].recovery_key,db[user].account_status,
        db[user].account_type,db[user].account_level,
        db[user].minimum_opening_deposit,db[user].currency,
        db[user].current_amount,db[user].loanStatus,
        db[user].monthly_income,db[user].loan_amount,
        db[user].loan_rate,db[user].address);

        for (int gcc=BANK_ACCOUNT_FIELDS; gcc < space_array[user]; gcc++){
            printf("-%s",db[user].tr[gcc - BANK_ACCOUNT_FIELDS].note);
        }
        printf("\n");
    }
}

void printing_specific_data(int user){
    printf("%u-%s-%s-%s-%s-%u-%s-%s-%s-%d-%d-%d-%s-%llu-%s-%u-%u-%f-%s-%d",
    db[user].id,db[user].name,db[user].nrc,db[user].email,
    db[user].password,db[user].phoneNumber,db[user].ecnryption_key,
    db[user].recovery_key,db[user].account_status,
    db[user].account_type,db[user].account_level,
    db[user].minimum_opening_deposit,db[user].currency,
    db[user].current_amount,db[user].loanStatus,
    db[user].monthly_income,db[user].loan_amount,
    db[user].loan_rate,db[user].address,db[user].trans_amount_limit_perday);

    for (int gcc = 0; gcc <= space_array[user] - 20; gcc++) {
        printf("-%s", db[user].tr[gcc].note);
    }
    printf("\n");
}

int char_counting(char my_char[50]){
    int count = 0;
    for(register int a = 0; a < 50; a++){
        if (my_char[a] == '\0'){
            break;
        }
        count++;
    }
    return count;
}

int check_input(char input[2]){
    if(input[0] >= 49 && input[0] <= 57 && input[1] == '\0'){
        return input[0];
    }else{
        return -1;
    }
}

void space_counter(){
    FILE *fptr = fopen("encrypted_data.txt","r");
    if (fptr != NULL){
        char c = fgetc(fptr);
        int index=0;
        while(!feof(fptr)){
            if (c != '\n'){
                if(c == ' '){
                    space_array[index] += 1;
                }
                c = fgetc(fptr);
            }else{
                index++;
                c = fgetc(fptr);
            }
        }
    }else{
        printf("\nFile opening error at space_counter function!\n");
    }
}

int main(){
    space_counter();
    loading_from_file();
    printing_all_data();
    main_menu();

    integer_to_charArrayFun(1500);
    printf("char array %s",int_to_charArray);

    char myarr[5] = {'1','2','5','0'};
    unsigned int data = char_to_integer_fun(myarr);
    printf("data : %u",data);
    return 0;

    // time_class(0);
    // return 0;
}



