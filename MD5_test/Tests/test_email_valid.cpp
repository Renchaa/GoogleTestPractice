#include "C:\Users\renar\OneDrive\Dators\MD5_test\pch.h"
#include "gtest/gtest.h"
#include "C:\Users\renar\OneDrive\Dators\MD5_application\main_application.cpp" 


// Testē derīgus e-pastus, kuri atbilst regex šablonam
// Sagaidām, ka `is_email_valid()` atgriež TRUE
TEST(EmailValidationTest, ValidEmails) {
    EXPECT_TRUE(is_email_valid("john.doe@example.com"));
    EXPECT_TRUE(is_email_valid("user_123@domain.com"));
}
// Testē nederīgus e-pastus, kuri neatbilst regex šablonam
// Sagaidām, ka `is_email_valid()` atgriež FALSE
TEST(EmailValidationTest, InvalidEmails) {
    EXPECT_FALSE(is_email_valid("plainaddress"));
    EXPECT_FALSE(is_email_valid("john@.com"));
}
