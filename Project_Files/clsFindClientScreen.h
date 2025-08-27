#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindClientScreen : protected clsScreen
{
private:
    static void _PrintClietn(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.GetFirstName();
        cout << "\nLastName    : " << Client.GetLastName();
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.GetEmail();
        cout << "\nPhone       : " << Client.GetPhone();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.GetPinCode();
        cout << "\nBalance     : " << Client.GetAccountBalance();
        cout << "\n___________________\n";
    }

public:
    static void ShowFindClientScrenn()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
        {
            return;
        }
        clsScreen::_DrawScreenHeader("\t Find Clinet Screen");
        string AccountNumber = "";
        cout << "Please, Enter Client Account Numebr";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Not Found , choose another one:";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        if (!Client.IsEmpty())
        {
            cout << "\nClient Found";
        }
        else
        {
            cout << "\nClient  Not Found";
        }

        _PrintClietn(Client);
    }
};
