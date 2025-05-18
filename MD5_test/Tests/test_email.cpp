#include "C:\Users\renar\OneDrive\Dators\MD5_test\pch.h"
#include "gtest/gtest.h"
#include "C:\Users\renar\OneDrive\Dators\MD5_application\main_application.h"
#include <sstream>


//E-pasts jau eksistē
TEST(RegistrationFlow, EmailExistsTest) {
    userDatabase.clear();
    // Pievienojam jau esošu lietotāju
    userDatabase["alex@a.com"] = { "alex@a.com", "alex", "pass", "bio", 0 };

    std::istringstream input(
        "alex@a.com\n"           // jau eksistē -> "user already exists"
        "john.doe@example.com\n" // pēc tam derīgs e-pasts
        "testuser\n"
        "password\n"
        "some bio\n"
        "0\n"                    
        "0\n"                    
    );
    std::ostringstream output;

    runUserRegistration(input, output);
    std::string outStr = output.str();

    // Pārbaudām, vai izvada "user already exists"
    EXPECT_NE(outStr.find("user already exists"), std::string::npos);
    // Pārbaudām, vai jaunais lietotājs "john.doe@example.com" tomēr tika piereģistrēts
    EXPECT_TRUE(userDatabase.find("john.doe@example.com") != userDatabase.end());
}

//Nederīgs e-pasts
TEST(RegistrationFlow, EmailInvalidTest) {
    userDatabase.clear();

    // Pirmais mēģinājums: "invalid.com" -> "invalid input"
    // Tad ievadam pareizu e-pastu un turpinām
    std::istringstream input(
        "invalid.com\n"
        "john.doe@example.com\n"
        "testuser\n"
        "password\n"
        "some bio\n"
        "0\n"
        "0\n"
    );
    std::ostringstream output;

    runUserRegistration(input, output);
    std::string outStr = output.str();

    // Pārbaudām, vai izvada "invalid input"
    EXPECT_NE(outStr.find("invalid input"), std::string::npos);
}

//Pareizs e-pasts (veiksmīga reģistrācija)
TEST(RegistrationFlow, EmailValidTest) {
    userDatabase.clear();

    // Viss derīgs jau pirmajā piegājienā
    std::istringstream input(
        "john.doe@example.com\n"
        "testuser\n"
        "password\n"
        "some bio\n"
        "1\n"
        "0\n"  
    );
    std::ostringstream output;

    runUserRegistration(input, output);

    // Pārbaudām, vai lietotājs tika pievienots
    EXPECT_EQ(userDatabase.size(), 1u);
    EXPECT_TRUE(userDatabase.find("john.doe@example.com") != userDatabase.end());
    EXPECT_EQ(userDatabase["john.doe@example.com"].username, "testuser");
}
