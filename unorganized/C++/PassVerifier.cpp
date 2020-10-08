// PasswordVerifier.cpp
// This program verifies a password using C-strings.
// Passwords must be between 6 and 20 characters long and contain
// at least one lower case letter, one upper case letter, and one digit.

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class PasswordVerifier
{
private:
        string* password = nullptr;
public:
        static const int MINLENGTH = 6;  // Minimum length for password
        static const int MAXLENGTH = 20; // Maximum length for password
        // constructors
        PasswordVerifier() {}
        PasswordVerifier(string* password)
        {
                // allocate heap space and assign the password
                this->password = password;
        }

        // destructor
        ~PasswordVerifier()
        {
                // if password is not null, delete it
                if (this->password)
                {
                        delete[] this->password;
                        this->password = nullptr;
                }
        }

        // accessor
        const string* getPassword() { return this->password; }

        // mutator
        void setPassword(string* password)
        {
                // if current password is not null, need to delete it
                if (this->password)
                {
                        delete[] this->password;
                        this->password = nullptr;
                }

                // allocate heap space for the new password and assign it
                this->password = password;
        }

        // verification function prototypes
        bool isCorrectLength();
        bool hasDigit();
        bool hasUpperAndLowerCase();
        bool hasSymbol();
};

//****************************************************
// Check is string has a minimum length.
//****************************************************
bool PasswordVerifier::isCorrectLength()
{
        bool result = false;
        if ((password->length() >= MINLENGTH && password->length() <= MAXLENGTH))
                result = true;
        return result;
}

//****************************************************
// Check if string has at least one digit.
//****************************************************
bool PasswordVerifier::hasDigit()
{
        bool result = false;
        for (int k = 0; result == false && k < password->length(); k++)
        {
                if (isdigit(this->password[k]))
                        result = true;
        }
        return result;
}

//**************************************************************
// Check if a string has at least one upper case and at
// least one lower case letter.
//**************************************************************
bool PasswordVerifier::hasUpperAndLowerCase()
{
        bool hasUpperCase = false;
        bool hasLowerCase = false;
        bool result = false;
        for (int k = 0; result == false && k < password->length(); k++)
        {
                hasUpperCase = hasUpperCase || isupper(this->password[k]);
                hasLowerCase = hasLowerCase || islower(this->password[k]);
                if (hasUpperCase && hasLowerCase)
                        result = true;
        }
        return result;
}

//**************************************************************
// Check if a string has at least one one symbol
//**************************************************************

bool PasswordVerifier::hasSymbol()
{
        bool result = false;
        for (int k = 0; result == false && k < password->length(); k++)
        {

                if (ispunct(this->password[k]))
                        result = true;
        }
        return result;
}

int main()
{
        const char* STR_PROMPT_TRYAGAIN = "\nPlease try again.\n";
        char password[PasswordVerifier::MAXLENGTH+1];
        bool isValid = false;

        // start with an empty PasswordVerifier
        PasswordVerifier *pw = new PasswordVerifier();

        // Explain program to user and request a password
        cout << "This program checks passwords to see if they are secure.";

        while (isValid == false)
        {
                cout << "\nEnter a password to check: ";
                cin.getline(password, PasswordVerifier::MAXLENGTH);

                // got a string, verify it using the PasswordVerifier
                pw->setPassword(password);

                // Check the password
                if (pw->isCorrectLength())
                        isValid = true;
                else
                {
                        cout << "Password must be at least " <<
                                PasswordVerifier::MINLENGTH <<
                                " characters long and less than " <<
                                PasswordVerifier::MAXLENGTH <<
                                " characters long.";
                        cout << STR_PROMPT_TRYAGAIN << endl;
                }

                if (isValid == true)
                        if (pw->hasDigit())
                                isValid = true;
                        else
                        {
                                cout << "Password must have at least one digit.";
                                cout << STR_PROMPT_TRYAGAIN << endl;
                                isValid = false;
                        }

                if (isValid == true)
                        if (pw->hasUpperAndLowerCase())
                                isValid = true;
                        else
                        {
                                cout << "Password must have both lower case and upper case letters.";
                                cout << STR_PROMPT_TRYAGAIN << endl;
                                isValid = false;
                        }
                if (isValid == true)
                        if (pw->hasSymbol())
                                isValid = true;
                        else
                        {
                                cout << "Password must have at least one symbol.";
                                cout << STR_PROMPT_TRYAGAIN << endl;
                                isValid = false;
                        }
        }
        cout << "The password \"" << pw->getPassword() << "\" is valid.";
        delete pw;
        return 0;
}
