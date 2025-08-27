#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
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

public:
    static void ShowUpdateClientScrenn()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;
        }
        clsScreen::_DrawScreenHeader("\t Update Clinet Screen");
        string AccountNumber = "";
        cout << "Please, Enter Client Account Numebr";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Not Found , choose another one:";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClietn(Client1);

        cout << "\nUpdate Client Info:";
        cout << "\n------------------:\n";

        _ReadClientInfo(Client1);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = Client1.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:

            cout << "\nAccount Updated Successfully :-)\n";
            _PrintClietn(Client1);
            break;

        case clsBankClient::enSaveResults::svFaildEmptyObject:

            cout << "\nError account was not saved because it's Empty";
            break;
        }
    }
};
