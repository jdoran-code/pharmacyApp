
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
using namespace std;

vector<string> info;
vector<string> prescriptions;
vector<time_t> prescriptionTimes;
vector<string> drugs;
vector<string> maxDosages;
string name;
int nameIndex;
string status = "0";

//Todo

//Begins the account registration process for all users
void registerAccount();

//Completes the account registration process for patients
void patientReg();

//Completes the account registration process for pharmacists
void pharmacistReg();

//Completes the account registration process for doctors
void doctorReg();

//Logs in the user
void logIn();

//Displays the main menu and allows the user to choose functions
void mainMenu();

//Enables the user to change their passcode
void changePasscode();

//Enables patients and doctors to change their information
void changeInfo();

//Enables pharmacists and doctors to view the information of patients and doctors
void viewInfo();

//Enables doctors to fill a prescription
void fillPrescription();

//Enables doctors and pharmacists to view the prescriptions of their patients
void viewPrescription(string patient);

//Enables pharmacists to confirm that they have fulfilled a patient's prescription
void fulfillPrescription();

//Enables pharmacists to confirm that they have refilled a patient's prescription
void refillPrescription();

//Enables patients to see whether they have any refills available
void Notifications();

//Holds the information of the current function until the user chooses to return to the main menu
void finish();

//Determines the index of an input element in an input array; returns -1 if the element is not in the array
int findIndex(string elem, vector<string> array = info);

//Determines whether a prescription is legal given an input dosage and input rate of doses per day
bool underMaxDosage(int times, int dosage, string elem);

int main() {
    fstream file;
    file.open("drugs.txt", ios::in);
    string line;
    while (getline(file, line)) {
        drugs.push_back(line);
    }
    file.close();

    file.open("maxDosages.txt", ios::in);
    while (getline(file, line)) {
        maxDosages.push_back(line);
    }
    file.close();

    info.assign(1, "0");
    int choice = 0;
    while (choice != 3) {
        cout << "1. Log in\n";
        cout << "2. Register an account\n";
        cout << "3. Shut down program\n";
        cout << "Select a number:" << endl;
        cin >> choice;
        if (choice == 1) {
            logIn();
        }
        else if (choice == 2) {
            registerAccount();
        }
    }
    cout << "Program shut down" << endl;
}

void registerAccount() {
    getline(cin, name);
    cout << "What is your name?\n";
    getline(cin, name);
    info.push_back(name);
    nameIndex = findIndex(name);

    while (status != "patient" and status != "pharmacist" and status != "doctor") {
        cout << "Are you a patient, pharmacist, or doctor?\n";
        getline(cin, status);
        info.push_back(status);
    }

    if (status == "patient") {
        patientReg();
    }
    else if (status == "pharmacist") {
       pharmacistReg();
    }
    else {
        doctorReg();
    }
}

void patientReg() {
    string questions[4] = {"What is your address?","What is your date of birth?",
                           "List any allergies.","Set a passcode:"};
    string response;
    for (int i = 0; i <= 3; i++) {
        cout << questions[i] << "\n";
        if (i == 2) {
            cout << "Enter 'None' if you do not have any:\n";
        }
        getline(cin, response);
        info.push_back(response);
    }
    mainMenu();
}

void pharmacistReg() {
    string response;
    cout << "Set a passcode:\n";
    getline(cin, response);
    info.push_back(response);
    mainMenu();
}

void doctorReg() {
    string questions[4] = {"What is your office's address?","What is your license number?",
                           "Set a passcode:"};
    string response;
    for (int i = 0; i <= 2; i++) {
        cout << questions[i] << "\n";
        getline(cin, response);
        info.push_back(response);
    }
    mainMenu();
}

void logIn () {
    string passcode;
    int logIns = 1;
    getline(cin, name);

    cout << "What is your name?\n";
    getline(cin, name);
    nameIndex = findIndex(name);
    if (nameIndex == -1) {
        cout << "Username not on file.\n";
        cout << "\n";
        return;
    }

    while (true) {
        logIns++;
        cout << "Enter your passcode:\n";
        getline(cin, passcode);
        status = info[nameIndex + 1];
        if (status == "patient" and passcode == info[nameIndex + 5]) {
            break;
        }
        else if (status == "pharmacist" and passcode == info[nameIndex + 2]){
            break;
        }
        else if (status == "doctor" and passcode == info[nameIndex + 4]) {
            break;
        }
        else if (logIns <= 3) {
            cout << "Wrong passcode, try again.\n";
        }
        else {
            cout << "Wrong passcode.\n";
            cout << "\n";
            return;
        }
    }
    mainMenu();
}

void mainMenu() {
    int choice = 0;
    while (choice != 1) {
        cout << "Main Menu: Select a number\n";
        cout << "1. Log out\n";
        cout << "2. Change passcode\n";

        if (status == "patient") {
            cout << "3. Change personal info\n";
        }
        else {
            cout << "3. View patient or doctor info\n";
        }

        if (status == "patient") {
            cout << "4. View my prescriptions\n";
        }
        else {
            cout << "4. View patient prescriptions\n";
        }

        if (status == "pharmacist") {
            cout << "5. Fulfill prescription\n";
        }
        else if (status == "doctor") {
            cout << "5. Fill out prescription\n";
        }
        else {
            cout << "5. Check my notifications\n";
        }

        if (status == "pharmacist") {
            cout << "6. Refill prescription\n";
        }
        cin >> choice;

        if (choice == 2) {
            changePasscode();
        }
        else if (choice == 3) {
            if (status == "patient") {
                changeInfo();
            }
            else {
                viewInfo();
            }
        }
        else if (choice == 4) {
            if (status == "patient") {
                viewPrescription(name);
            }
            else {
                string myPatient;
                getline(cin, myPatient);
                cout << "Name of patient:\n";
                getline(cin, myPatient);
                viewPrescription(myPatient);
            }
        }
        else if (choice == 5) {
            if (status == "pharmacist") {
                fulfillPrescription();
            }
            else if (status == "doctor") {
                fillPrescription();
            }
            else {
                Notifications();
            }
        }
        else if (choice == 6 and status == "pharmacist") {
            refillPrescription();
        }
    }
    status = "0";
}

void changePasscode() {
    string passcode;
    getline(cin, passcode);
    cout << "Enter new passcode:\n";
    getline(cin, passcode);

    if (status == "patient") {
        info[nameIndex + 5] = passcode;
    }
    else if (status == "pharmacist") {
        info[nameIndex + 2] = passcode;
    }
    else {
        info[nameIndex + 4] = passcode;
    }
    cout << "Passcode updated.\n";
    finish();
}

void changeInfo() {
    int choice;

    cout << "1. Address\n";
    cout << "2. Date of birth\n";
    cout << "3. Allergies\n";
    cout << "Select number of the info you would like to change:\n";

    cin >> choice;
    choice += 1;
    getline(cin, info[nameIndex + choice]);
    cout << "Enter new info:\n";
    getline(cin, info[nameIndex + choice]);
    cout << "Info updated.\n";
    finish();
}

void viewInfo() {
    string user;
    getline(cin, user);
    int index;

    cout << "Enter name of patient or doctor:\n";
    getline(cin, user);
    index = findIndex(user);
    if (index != -1 and info[index + 1] == "patient") {
        cout << "Patient " << user << "\n";
        cout << "Address: " << info[index + 2] << "\n";
        cout << "Date of birth: " << info[index + 3] << "\n";
        cout << "Allergies: " << info[index + 4] << "\n";
    }
    else if (index != -1 and info[index + 1] == "doctor") {
        cout << "Doctor " << user << "\n";
        cout << "Office Address: " << info[index + 2] << "\n";
        cout << "License Number: " << info[index + 3] << "\n";
    }
    else {
        cout << "Patient or doctor not on file.\n";
    }
    finish();
}

void fillPrescription() {
    string elem;
    int elemIndex;
    int times;
    int dosage;
    int attempts = 1;
    string dateTime;

    getline(cin, elem);
    cout << "Name of patient:\n";
    getline(cin, elem);
    elemIndex = findIndex(elem);
    if (elemIndex != -1 and info[elemIndex += 1] == "patient") {
        prescriptions.push_back(elem);
    }
    else {
        cout << "Patient not on file.\n";
        finish();
        return;
    }

    while (true) {
        attempts++;
        cout << "Name of drug:\n";
        getline(cin, elem);
        elemIndex = findIndex(elem, drugs);
        if (elemIndex != -1) {
            prescriptions.push_back(elem);
            attempts = 1;
            break;
        }
        else if (attempts <= 3) {
            cout << "Drug not on file, try again.\n";
        }
        else {
            cout << "Drug not on file.\n";
            prescriptions.pop_back();
            finish();
            return;
        }
    }

    while (true) {
        attempts++;
        cout << "Number of doses per day:\n";
        cin >> times;
        cout << "Dosage:\n";
        cin >> dosage;
        if (underMaxDosage(times, dosage, maxDosages[elemIndex])) {
            prescriptions.push_back(to_string(times));
            prescriptions.push_back(to_string(dosage));
            break;
        }
        else if (attempts <= 3) {
            cout << "Illegal dosage, try again.\n";
        }
        else {
            cout << "Illegal dosage.\n";
            prescriptions.pop_back();
            prescriptions.pop_back();
            finish();
            return;
        }
    }

    getline(cin, elem);
    cout << "Duration of prescription in days:\n";
    getline(cin, elem);
    prescriptions.push_back(elem);
    cout << "Number of refills:\n";
    getline(cin, elem);
    prescriptions.push_back(elem);

    prescriptions.push_back(name);
    prescriptions.push_back("unfulfilled");
    time_t ct = time(0);
    prescriptionTimes.push_back(ct);
    cout << "Prescription filled.\n";
    finish();
}

void viewPrescription(string patient) {
    int numPres = 0;
    int loops = 0;
    string dateTime;

    for (int i = 0; i <= prescriptions.size() - 1; i += 8) {
        if (prescriptions[i] == patient) {
            numPres++;
            string categories[7] = {"Drug: ", "Dosages per day: ",
                                    "Dosages: ", "Duration in days: ",
                                    "Number of refills: ","Doctor: ",
                                    "Status: "};
            for (int j = 1; j <= 7; j++) {
                cout << categories[j - 1] << prescriptions[i + j] << "\n";
            }

            dateTime = ctime(&prescriptionTimes[loops]);
            cout << "Date: " << dateTime << "\n";
        }
        loops++;
    }

    if (numPres == 0) {
        cout << "No prescriptions on file.\n";
    }
    finish();
}

void fulfillPrescription() {
    string patient;
    string drug;
    getline(cin, patient);

    cout << "Name of patient:\n";
    getline(cin, patient);
    cout << "Name of drug:\n";
    getline(cin, drug);

    int max = prescriptions.size() - 1;
    for (int i = 0; i <= max; i += 8) {
        if (prescriptions[i] == patient and prescriptions[i + 1] == drug) {
            prescriptions[i + 7] = "fulfilled";
            cout << "Prescription fulfilled.\n";
            break;
        }

        if (i + 8 > max) {
            cout << "Prescription not on file.\n";
        }
    }
    finish();
}

void refillPrescription() {
    string patient;
    string drug;
    int duration;
    int refills;
    int loops = 0;
    getline(cin, patient);

    cout << "Name of patient:\n";
    getline(cin, patient);
    cout << "Name of drug:\n";
    getline(cin, drug);
    time_t ct = time(0);
    int max = prescriptions.size() - 1;

    for (int i = 0; i <= max; i += 8) {
        duration = stoi(prescriptions[i + 4]);
        refills = stoi(prescriptions[i + 5]);
        if (prescriptions[i] == patient and prescriptions[i + 1] == drug and difftime(ct, prescriptionTimes[loops]) >= (double)duration * 86400.0 and refills != 0) {
            cout << "Prescription refilled\n";
            refills -= 1;
            prescriptions[i + 5] = to_string(refills);
            prescriptionTimes[loops] = ct;
            break;
        }

        if (i + 8 > max) {
            cout << "No refill available.\n";
        }
        loops++;
    }
    finish();
}

void Notifications() {
    int numRefills = 0;
    int loops = 0;
    int duration;
    time_t ct = time(0);

    for (int i = 0; i <= prescriptions.size() - 1; i += 8) {
        duration = stoi(prescriptions[i + 4]);

        if (prescriptions[i] == name and difftime(ct, prescriptionTimes[loops]) >= (double)duration * 86400.0 and stoi(prescriptions[i + 5]) != 0) {
            if (numRefills == 0) {
                cout << "You can now obtain refills on the following prescriptions:\n";
            }
            cout << prescriptions[i + 1] << "\n";
            numRefills++;
        }
        loops++;
    }

    if (numRefills == 0) {
        cout << "No notifications at this time.\n";
    }
    finish();
}

void finish() {
    int choice = 0;
    while (choice != 1) {
        cout << "Enter 1 to return to the main menu.\n";
        cin >> choice;
    }
}

int findIndex(string elem, vector<string> array) {
    for (int i = 0; i <= array.size() - 1; i++) {
        if (array[i] == elem) {
            return i;
        }
    }
    return -1;
}

bool underMaxDosage(int times, int dosage, string elem) {
    int test = stoi(elem);
    if (dosage * times <= test) {
        return true;
    }
    else {
        return false;
    }
}




