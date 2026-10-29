## Gym Membership Tracker

A console-based C++ application designed to manage gym operations, member registrations, subscriptions, trainer assignments, and BMI tracking with file persistence.

Features

- Member Registration: Register new gym members with automatically generated IDs, height, weight, and subscription types (Monthly or Yearly).
- Subscription Tracking: Monitor membership statuses and check expiry dates based on local system time.
- Trainer Management: Assign members to specialized trainers (Strength, Cardio, Health, Bodybuilding) and view trainer member lists.
- BMI Calculator: Calculate member Body Mass Index and evaluate physical status.
- File Persistence: Automatically saves and loads member records using text file operations (Gym_Members.txt).

Tech Stack

- Language: C++
- File Handling: Standard C++ fstream library for data persistence
- Environment: Any C++ IDE or compiler (Visual Studio, Code::Blocks, or GCC) supporting C++11 or higher.

Setup and Running Instructions

Follow these steps to compile and run the project locally on your machine:

1. Prerequisites
- C++ Compiler: Ensure a standard C++ compiler (like MinGW GCC or MSVC) is installed.
- IDE: Open the project in an IDE like Visual Studio, Code::Blocks, or VS Code.

2. Clone the Repository
Open your terminal and clone the repository to your local machine:
git clone https://github.com/eyad-salem/Gym-Membership-Project.git

3. Compile and Run
- Open the source file (`Gym-Membership`) in your chosen IDE or compile it via terminal:
  g++ "Gym-Membership" -o gym_app
- Execute the compiled program to interact with the console menu.
