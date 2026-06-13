# Bank-Project-OOP
I have rebuilt this project entirely from scratch, in order to revise previously taken concepts and apply new ones (OOP).
The project has some core classes, including: clsBankClient, clsBankUser, clsCurrency, clsPerson, clsScreen, and the clsMainScreen.
The class named Global contains the user who is currently logged in. It is used to display the logged in user on all screens, through class inheritence from the class clsScreen.
The class clsScreen displays the header of the screen and checks the permission to access each element on the main screen.
New screens that were added to this version are:
1. Manage users: to add new, delete, find, update users.

<img width="871" height="493" alt="image" src="https://github.com/user-attachments/assets/17288c5e-a07e-4b01-bc0b-c9fddd2950a4" />

2. Login register: to show all login operations that have been done from users.

<img width="945" height="685" alt="image" src="https://github.com/user-attachments/assets/37fe8dd3-ad61-4267-a740-99644554bc01" />

3. Currency exchange: to show inforamtion of currencies in the world, find a currency by its country or code, update the rate of a currency, and exchange a certain amount of money from one currency to another.

<img width="874" height="469" alt="image" src="https://github.com/user-attachments/assets/fa7b2ba8-e791-4438-b180-e4b7534db5d7" />

Another important part is creating libraries, such: clsDate to manipulate dates, clsString for operations on string data type, clsInputValidate to check and validate data entry from user, and clsUtil for other useful functions.
In the library clsInputValidate we used template functions to reduce the number of overloaded functions. 

<img width="1733" height="747" alt="image" src="https://github.com/user-attachments/assets/93fcf028-1aaf-474f-a715-104a55a2c3f2" />

A final touch is encrypting the data before saving it to files. However, when using the system, you'll find it decrypted.
For exmaple the file containing the information of the users of the system:

<img width="922" height="34" alt="image" src="https://github.com/user-attachments/assets/159c1fa9-c104-418d-86b9-92fa192b03a6" />

The real password of admin is admin:

<img width="960" height="371" alt="image" src="https://github.com/user-attachments/assets/6d3d2b5d-f845-42fc-acbf-07aa91de09a6" />

Inside the system:

<img width="1442" height="405" alt="image" src="https://github.com/user-attachments/assets/a759bc47-04ba-4ac0-b5df-ff287d9078f4" />

Permissions are using bitwise operators to give access to the users. It is 'Binary Data Structure'.

## 🛠️ Installation & Setup

To run this project locally on your machine, follow these simple steps:

### Prerequisites
* **Visual Studio 2022** (or newer) with the desktop development workload installed.
* **Git** installed on your system.

### Step-by-Step Guide

1. **Clone the repository:**
   Open your terminal or Git Bash and run the following command:
```bash
   git clone https://github.com/husem213/Bank-Project-OOP.git
```
2. Navigat to the project folder:
```bash
  cd Bank-Project-OOP
```
3. Open the project on VS code and run it.
