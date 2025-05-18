#include "C:\Users\renar\OneDrive\Dators\MD5_test\pch.h"
#include "gtest/gtest.h"
#include "C:\Users\renar\OneDrive\Dators\MD5_application\main_application.h"
#include <sstream>

//Testē, ka `ok = 1` atkārto ciklu
// Tiek veikti divi reģistrācijas cikli: divi dažādi lietotāji
TEST(MainLoopTest, TwoRegistrationsWithRepeat) {
    userDatabase.clear();
    std::istringstream input(
        "user1@example.com\n"
        "user1\n"
        "pass1\n"
        "bio1\n"
        "1\n"
        "1\n"

        "user2@example.com\n"
        "user2\n"
        "pass2\n"
        "bio2\n"
        "0\n"
        "0\n" 
    );
    std::ostringstream output;

    runUserRegistration(input, output);
    // Sagaidām, ka datubāzē būs tieši divi lietotāji
    EXPECT_EQ(userDatabase.size(), 2u);
    // Sagaidām, ka abi lietotāji ir pareizi reģistrēti
    EXPECT_NE(userDatabase.find("user1@example.com"), userDatabase.end());
    EXPECT_NE(userDatabase.find("user2@example.com"), userDatabase.end());
}
//Testē, ka jebkura `ok` vērtība ≠ 1 (piem. 9) pārtrauc ciklu
//Pārbauda, ka "enter email" parādās tikai vienu reizi => cikls nav atkārtojies
TEST(MainLoopTest, OkValueStopsLoop) {
    userDatabase.clear();
    std::istringstream input(
        "user@example.com\n"
        "user\n"
        "pass\n"
        "bio\n"
        "1\n"
        "9\n" 
    );
    std::ostringstream output;

    runUserRegistration(input, output);
    std::string outStr = output.str();

    // Sagaidām, ka tika parādīts jautājums "make another user?"
    EXPECT_NE(outStr.find("make another user?"), std::string::npos);

    // Pārbaudām, ka "enter email:" parādījās tikai vienreiz
    size_t first = outStr.find("enter email:");
    size_t second = outStr.find("enter email:", first + 1);

    EXPECT_EQ(second, std::string::npos);
}
