#include "main_application.h"

unordered_map<string, User> userDatabase;

bool is_email_valid(const string& email) {
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(email, pattern);
}

bool is_username_taken(const string& username) {
    for (const auto& pair : userDatabase) {
        if (pair.second.username == username) {
            return true;
        }
    }
    return false;
}

void runUserRegistration(istream& in, ostream& out) {
    int ok;
    do {
        string email, username, password, bio;
        do {
            out << "enter email: ";
            in >> email;
            if (userDatabase.find(email) != userDatabase.end()) {
                out << "user already exists" << endl;
            }
            else if (!is_email_valid(email)) {
                out << "invalid input" << endl;
            }
            else {
                break;
            }
        } while (true);

        do {
            out << "enter username: ";
            in >> username;
            if (is_username_taken(username)) {
                out << "username taken" << endl;
            }
            else {
                break;
            }
        } while (true);

        out << "enter password: ";
        in >> password;
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        out << "enter bio: ";
        getline(in, bio);

        int type;
        out << "enter type: 0 - venue; 1 - artist: ";
        in >> type;
        if (in.fail()) {
            out << "not int" << endl;
            in.clear();
            in.ignore(numeric_limits<streamsize>::max(), '\n');
            in >> type;
        }
        while (type < 0 || type > 1) {
            out << "invalid" << endl;
            out << "enter type 0 - venue; 1 - artist: ";
            in >> type;
        }
        userDatabase[email] = { email, username, password, bio, type };
        out << "User registered successfully!" << endl;
        out << "make another user? (1 - yes, 0 - no): ";
        in >> ok;
    } while (ok == 1);
}
