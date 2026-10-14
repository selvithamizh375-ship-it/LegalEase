#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <ctime>
using namespace std;

string currentDate() {
    time_t now = time(nullptr);
    tm *local = localtime(&now);
    char buffer[20];
    if (local) strftime(buffer, sizeof(buffer), "%d-%m-%Y", local);
    else return "Date unavailable";
    return buffer;
}

int main() {
    int choice;
    string name, recipient, details, documentTitle, filename;

    cout << "==============================================\n";
    cout << "                 LegalEase\n";
    cout << "     AI-Powered Legal Document Generator\n";
    cout << "==============================================\n";
    cout << "1. Complaint Letter\n";
    cout << "2. Legal Notice Draft\n";
    cout << "3. Rental Agreement Draft\n";
    cout << "4. Affidavit Draft\n";
    cout << "Choose document type (1-4): ";

    if (!(cin >> choice)) {
        cout << "Invalid input. Please enter a number.\n";
        return 1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
        case 1: documentTitle = "COMPLAINT LETTER"; filename = "Complaint_Letter.txt"; break;
        case 2: documentTitle = "LEGAL NOTICE - DRAFT"; filename = "Legal_Notice.txt"; break;
        case 3: documentTitle = "RENTAL AGREEMENT - DRAFT"; filename = "Rental_Agreement.txt"; break;
        case 4: documentTitle = "AFFIDAVIT - DRAFT"; filename = "Affidavit.txt"; break;
        default:
            cout << "Invalid choice. Please run the program again and choose 1-4.\n";
            return 1;
    }

    cout << "Enter your full name: ";
    getline(cin, name);
    cout << "Enter recipient / other party name: ";
    getline(cin, recipient);
    cout << "Describe the matter (one or more lines; finish with a line containing END):\n";
    string line;
    while (getline(cin, line) && line != "END") {
        details += line + "\n";
    }

    if (name.empty() || recipient.empty() || details.empty()) {
        cout << "Name, recipient, and matter details are required. No document was saved.\n";
        return 1;
    }

    ofstream file(filename);
    if (!file) {
        cout << "Could not create the output file. Check folder permissions.\n";
        return 1;
    }

    file << "==================================================\n";
    file << "                    LegalEase\n";
    file << "       AI-Powered Legal Document Generator\n";
    file << "==================================================\n\n";
    file << documentTitle << "\n";
    file << "Date: " << currentDate() << "\n\n";
    file << "From: " << name << "\n";
    file << "To: " << recipient << "\n\n";
    file << "Subject: " << documentTitle << "\n\n";
    file << "Dear Sir/Madam,\n\n";
    file << details << "\n";
    file << "I request that this matter be reviewed and that an appropriate response or resolution be provided.\n\n";
    file << "Yours faithfully,\n" << name << "\n\n";
    file << "IMPORTANT DISCLAIMER\n";
    file << "This is a general sample draft, not legal advice. It may not meet all legal requirements for your situation. Please have it reviewed by a qualified legal professional before signing, sending, or filing it.\n";
    file.close();

    cout << "\nDocument draft generated successfully.\n";
    cout << "Saved in the current working folder as: " << filename << "\n";
    cout << "Note: This prototype uses templates and does not connect to an AI model.\n";
    return 0;
}
