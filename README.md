🏦 Advanced Bank Management System (C++)
This project is a robust, command-line-based Banking Application developed in C++ as part of my CodeAlpha internship. It goes beyond basic arithmetic to simulate a real-world banking experience with a focus on Object-Oriented Programming (OOP), Security, and Data Integrity.

🛠️ Core Features & Logic
Secure Authentication System:

Implements a PIN-based login.

Security Logic: Features an "Account Lock" mechanism that freezes the account after 3 consecutive failed attempts to prevent unauthorized access.

Comprehensive Transaction Handling:

Deposits: Provides real-time balance updates and generates a unique Transaction ID (TXN ID) for every successful entry.

Diverse Withdrawal Methods: Users can choose between ATM, Bank Counter, Cheque, or POS. Each method triggers specific logic and safety notifications.

Real-World Financial Rules:

Daily Limits: Enforces a $20,000 daily withdrawal limit.

Minimum Balance Protection: If the balance drops below $500, the system automatically applies a $50 service charge, simulating real banking penalties.

Interest Crediting: Includes a function to simulate an annual interest credit of 4% to the current balance.

Data Logging & Statements:

Dynamic History: Uses a std::vector to store a timestamped log of every action.

Mini Statement: A filtered view showing only the last 5 transactions for quick reference.

💻 Technical Implementation
Object-Oriented Design: The entire system is encapsulated within a BankAccount class, ensuring data privacy through private members for balance and PIN.

Standard Template Library (STL): Utilizes std::vector for dynamic data storage and std::algorithm for efficient data handling.

Time Library (<ctime>): All transactions are logged with high-precision timestamps using system time.

Formatted UI: Uses <iomanip> to ensure all financial figures are displayed in a clean, two-decimal currency format.

🚀 How to Run
Compile the Code: Use any C++ compiler (Visual Studio or GCC).

Run the Executable: Follow the on-screen menu instructions.

Default PIN: Use the PIN 99 to access the system.
