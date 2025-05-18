#include "C:\Users\renar\OneDrive\Dators\MD5_test\pch.h"
#include "gtest/gtest.h"
#include "C:\Users\renar\OneDrive\Dators\MD5_application\main_application.h"

// Testē gadījumu, kad lietotājvārds jau ir datubāzē
// Funkcijai jāatgriež TRUE
TEST(UsernameCheckTest, UsernameTaken) {
    userDatabase.clear();
    userDatabase["test@example.com"] = {
        "test@example.com", "testuser", "pass", "bio", 1
    };
    EXPECT_TRUE(is_username_taken("testuser"));
}

// Testē gadījumu, kad lietotājvārds nav datubāzē
// Funkcijai jāatgriež FALSE
TEST(UsernameCheckTest, UsernameNotTaken) {
    userDatabase.clear();
    userDatabase["test@example.com"] = {
        "test@example.com", "testuser", "pass", "bio", 0
    };
    EXPECT_FALSE(is_username_taken("bob"));
}