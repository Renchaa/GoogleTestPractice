#ifndef MD5_APPLICATION_H
#define MD5_APPLICATION_H

#include <iostream>
#include <string>
#include <regex>
#include <unordered_map>
#include <limits>
using namespace std;

struct User {
    string email;
    string username;
    string password;
    string bio;
    int type;
};

extern unordered_map<string, User> userDatabase;

bool is_email_valid(const string& email);
bool is_username_taken(const string& username);
void runUserRegistration(istream& in, ostream& out);

#endif 
