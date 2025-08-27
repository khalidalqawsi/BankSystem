#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;

class clsFindUserScreen : protected clsScreen
{
private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.GetFirstName();
        cout << "\nLastName    : " << User.GetLastName();
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.GetEmail();
        cout << "\nPhone       : " << User.GetPhone();
        cout << "\nUser Name   : " << User.GetUserName();
        cout << "\nPassword    : " << User.GetPassword();
        cout << "\nPermissions : " << User.GetPermissions();
        cout << "\n___________________\n";
    }

public:
    static void ShowFindUserScreen()
    {
        clsScreen::_DrawScreenHeader("\t Find User Screen");

        cout << "\nPlease, Enter User Name: ";
        string UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "User is not found , choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);

        if (!User.IsEmpty())
        {
            cout << "\nUser Found";
            _PrintUser(User);
        }
        else
        {
            cout << "\nUser Was not Found";
        }
    }
};
