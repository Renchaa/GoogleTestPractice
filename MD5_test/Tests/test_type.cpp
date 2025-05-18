#include "C:\Users\renar\OneDrive\Dators\MD5_test\pch.h"
#include "gtest/gtest.h"
#include "C:\Users\renar\OneDrive\Dators\MD5_application\main_application.h"
#include <sstream>

// Testē, ka `type = 1` tiek ievadīts korekti jau ar pirmo mēģinājumu
// `in.fail()` netiek aktivizēts, `while` netiek izpildīts
TEST(TypeInputTest, ValidTypeOne) {
    userDatabase.clear();
    std::istringstream input(
        "user@example.com\n"
        "user\n"
        "pass\n"
        "bio\n"
        "1\n"   // valid type
        "0\n"
    );
    std::ostringstream output;
    runUserRegistration(input, output);
    // Sagaidām, ka lietotāja tips = 1

    EXPECT_EQ(userDatabase["user@example.com"].type, 1);
}
//Testē, ka `type = 0` (venue) tiek ievadīts korekti jau ar pirmo mēģinājumu
//`in.fail()` netiek aktivizēts, `while` netiek izpildīts
TEST(TypeInputTest, ValidTypeZero) {
    userDatabase.clear();
    std::istringstream input(
        "venue@example.com\n"
        "venueuser\n"
        "securepass\n"
        "bio for venue\n"
        "0\n"   // type = 0 (venue)
        "0\n"   // end
    );
    std::ostringstream output;

    runUserRegistration(input, output);
    std::string outStr = output.str();

    //Sagaidām, ka datubāzē ir viens lietotājs
    EXPECT_EQ(userDatabase.size(), 1u);
    //Sagaidām, ka lietotāja tips ir 0
    EXPECT_EQ(userDatabase["venue@example.com"].type, 0);

    //Netika izvadīti kļūdu ziņojumi par formātu vai robežām
    EXPECT_EQ(outStr.find("not int"), std::string::npos);
    EXPECT_EQ(outStr.find("invalid"), std::string::npos);
}
//Testē, ka sākumā tiek ievadīts nederīgs formāts (piem. `abc`), kas aktivizē `in.fail()`
//Pēc tam tiek ievadīta derīga `type = 0`
TEST(TypeInputTest, InvalidFormatThenValidType) {
    userDatabase.clear();
    std::istringstream input(
        "user@example.com\n"
        "user\n"
        "pass\n"
        "bio\n"
        "abc\n"  // triggers in.fail()
        "0\n"    // valid
        "0\n"
    );
    std::ostringstream output;

    runUserRegistration(input, output);
    //Sagaidām, ka tips = 0 pēc format errora
    EXPECT_EQ(userDatabase["user@example.com"].type, 0);
}
//Testē, ka ievadīts derīgs skaitlis (piem. `3`), bet tas ir ārpus pieļaujamā intervāla (0–1)
//Aktivizējas `while`, pēc tam ievada korektu `type = 1`
TEST(TypeInputTest, InvalidValueThenValidType) {
    userDatabase.clear();
    std::istringstream input(
        "user@example.com\n"
        "user\n"
        "pass\n"
        "bio\n"
        "3\n"   // valid int, but out of range
        "1\n"   // valid
        "0\n"
    );
    std::ostringstream output;

    runUserRegistration(input, output);
    // Sagaidām, ka tips galu galā = 1
    EXPECT_EQ(userDatabase["user@example.com"].type, 1);
}
//  Testē kombo kļūdu ceļu:
// Sākumā format error (`abc`) → aktivizē `in.fail()`
// Tad ievadīts `5` (valid int, invalid range) → aktivizē `while`
// Pēc tam korekts `type = 1`
TEST(TypeInputTest, InvalidFormatThenInvalidValueThenValid) {
    userDatabase.clear();
    std::istringstream input(
        "user@example.com\n"
        "user\n"
        "pass\n"
        "bio\n"
        "abc\n"   // in.fail()
        "5\n"     // valid int, invalid range
        "1\n"     // valid
        "0\n"
    );
    std::ostringstream output;

    runUserRegistration(input, output);
    //Sagaidām, ka tips beigās = 1, pēc visu kļūdu iziešanas
    EXPECT_EQ(userDatabase["user@example.com"].type, 1);
}
