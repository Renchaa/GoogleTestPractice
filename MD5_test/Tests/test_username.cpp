#include "C:\Users\renar\OneDrive\Dators\MD5_test\pch.h"
#include "gtest/gtest.h"
#include "C:\Users\renar\OneDrive\Dators\MD5_application\main_application.h"

// Testē, ka tiek ievadīts brīvs lietotājvārds pirmajā reizē
//`is_username_taken()` atgriež false, cikls tiek izpildīts tikai vienu rei
TEST(UsernameInputTest, ValidUsernameFirstTry) {
    userDatabase.clear();
    std::istringstream input(
        "user@example.com\n"    
        "freeuser\n"            // username (brīvs uzreiz)
        "pass\n"
        "bio\n"
        "1\n"
        "0\n"
    );
    std::ostringstream output;

    runUserRegistration(input, output);
    std::string outStr = output.str();
    // Sagaidām, ka tiek parādīts "enter username"
    EXPECT_NE(outStr.find("enter username"), std::string::npos);
    // Sagaidām, ka username ir korekti saglabāts
    EXPECT_TRUE(userDatabase["user@example.com"].username == "freeuser");
}
// Testē, ka pirmais ievadītais username jau ir aizņemts
// Pēc kļūdas lietotājs ievada brīvu username
TEST(UsernameInputTest, TakenThenValidUsername) {
    userDatabase.clear();
    userDatabase["other@example.com"] = { "other@example.com", "takenUser", "pass", "bio", 0 };

    std::istringstream input(
        "user@example.com\n"     
        "takenUser\n"            // aizņemts
        "newuser\n"              // brīvs
        "pass\n"
        "bio\n"
        "0\n"
        "0\n"
    );
    std::ostringstream output;

    runUserRegistration(input, output);
    std::string outStr = output.str();
    // Sagaidām, ka tiek izvadīts "username taken"
    EXPECT_NE(outStr.find("username taken"), std::string::npos);
    // Pārbaudām, ka pareizais username beigās tika saglabāts
    EXPECT_TRUE(userDatabase["user@example.com"].username == "newuser");
}
