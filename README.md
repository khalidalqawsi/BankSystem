
# BankSystem

A C++-based console application simulating a comprehensive banking system. It provides account management, transactions, user management, and currency exchange features with text-based data storage.



## Features

### Account Management
- Create, view, update, search, and delete bank accounts  
- View full list of clients  
- Track account balances  

### Transaction Management
- Deposit and withdraw funds  
- Transfer between accounts  
- View transaction history  
- Maintain transfer logs  

### User Management
- Multi-user support with role-based permissions  
- Secure login and authentication system  
- User registration  
- Password encryption  
- Activity logging  

### Currency Exchange
- Support for multiple currencies  
- Currency conversion between accounts  
- Manage exchange rates  
- View global currencies and codes  



## Project Structure

```

BankSystem/
├── Project\_Files/
│   ├── Core Classes/
│   │   ├── clsBankClient.h        # Client account management
│   │   ├── clsUser.h              # User management & authentication
│   ├── Screens/
│   │   ├── clsLoginScreen.h       # Login interface
│   │   ├── clsMainScreen.h        # Main menu
│   │   ├── clsTransactionScreen.h # Transaction operations
│   │   └── \[Other screen classes]
│   └── Utilities/
│       ├── clsDate.h              # Date handling
│       ├── clsString.h            # String operations
│       └── clsUtil.h              # Utility functions

```

### Database Files
The system uses plain text files for data storage:  
- **Clients.txt** – Stores client account information  
- **Users.txt** – Stores user credentials and permissions  
- **Currencies.txt** – Stores currency exchange rates  
- **LoginRegister.txt** – Stores login activity logs  
- **TransferLog.txt** – Stores transfer history  



## File Formats

### Clients.txt
```

FirstName#//#LastName#//#Email#//#Phone#//#AccountNumber#//#PIN#//#Balance

```

Example:
```

Khalid#//#Alqawsi#//#[khalid@gmail.com](mailto:khalid@gmail.com)#//#772606316#//#A101#//#1234#//#9931.000000

```

### Currencies.txt
```

Country#//#CurrencyCode#//#CurrencyName#//#ExchangeRate

```

Example:
```

France#//#EUR#//#Euro#//#0.900000

````



## Security Features

### User Authentication
- Secure login system  
- Encrypted password storage  
- Login attempt tracking  

### Access Control
- Role-based permissions (Admin / Regular User)  
- Operation authorization checks  
- Activity logging  



## Example Code Usage

### Client Management
```cpp
// Create new client
clsBankClient::GetAddNewClientObject(AccountNumber);

// Find client
clsBankClient::Find(AccountNumber);

// Update client
client.Save();

// Delete client
client.Delete();
````

### Transaction Operations

```cpp
// Deposit
client.Deposit(Amount);

// Withdraw
client.Withdraw(Amount);

// Transfer
client.Transfer(Amount, DestinationClient, UserName);
```

### Currency Exchange

```cpp
// Convert currency
Currency1.ConvertToOtherCurrency(Amount, Currency2);

// Update exchange rate
Currency.UpdateRate(NewRate);
```

### User Management

```cpp
// Create new user
clsUser::GetAddNewUserObject(UserName);

// Authenticate user
clsUser::Find(UserName, Password);

// Check permissions
User.CheckAccessPermission(Permission);
```



## Getting Started

1. Clone the repository:

   ```bash
   git clone https://github.com/username/BankSystem.git
   ```
2. Open the project in your C++ IDE (Code::Blocks, Visual Studio, or similar).
3. Ensure you have a C++11+ compiler.
4. Build and run `Project_Files/Bank.cpp`.
5. Log in with default credentials (see `Users.txt`).




## Screenshots

### Login Screen
![Login Screen](Resources/Login%20Screen.png)

### Main Menu Screen
![Main Menu](Resources/Main%20Screen.png)

### Client List Screen
![Client List](Resources/Cleint%20List.png)

### Transaction Screen
![Transaction Example](Resources/Transaction%20Screen.png)

### Currency Exchange Screen
![Currency Exchange](Resources/Currency%20Exchange.png)

### User Management Screen
![User Management](Resources/User%20Managment%20(2).png)



## Extending Functionality

* Implement `InterfaceCommunication` to enable Email, Fax, or SMS notifications.
* Expand client and currency datasets.
* Add new transaction types or reporting features.




## Author

**Khalid Alqawsi**
GitHub: [@khalidalqawsi](https://github.com/khalidalqawsi)
Email: khalidalqawsi@gmail.com


