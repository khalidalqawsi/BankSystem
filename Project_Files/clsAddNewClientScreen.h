#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient &Client)
    {
        cout << "\nEnter First Name: ";
        Client.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter Last Name: ";
        Client.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        Client.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone Number: ";
        Client.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter PinCode: ";
        Client.SetPinCode(clsInputValidate::ReadString());

        cout << "\nEnter Account Balance: ";
        Client.SetAccountBalance(clsInputValidate::ReadNumber<double>());
    }

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
    static void ShowAddNewClientScrenn()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;
        }
        clsScreen::_DrawScreenHeader("\t Add New Client Screen");

        string AccountNumber = "";
        cout << "Please, Enter Client Account Numebr";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount is Already used , choose another one:";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:

            cout << "\nClient  Added Successfully :-)\n";
            _PrintClietn(NewClient);
            break;

        case clsBankClient::enSaveResults::svFaildEmptyObject:

            cout << "\nError account was not saved because it's Empty";
            break;
        }
    }
};
