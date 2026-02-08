<div align="center">

# 🚖 Advanced Console Taxi Management System

**A powerful console-based ride-hailing simulation**  
(like a mini Snapp / Uber built entirely in pure C)

[![C](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)]
[![Windows](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)]
![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)
![Status](https://img.shields.io/badge/Status-Active-blue?style=for-the-badge)

</div>

<br>

## ✨ Features

| Feature                              | Description                                                                 |
|:-------------------------------------|:----------------------------------------------------------------------------|
| 🛡️ Admin Panel                       | Register / edit / block drivers & passengers, view all rides & logs         |
| 👤 Driver Dashboard                  | Accept nearby waiting rides, complete trips, update location & status       |
| 👩‍🦰 Passenger Dashboard             | Request ride, cancel request, change location, view balance                 |
| 💰 Wallet & Transactions             | Automatic fare deduction from passenger → added to driver balance           |
| 📍 Location-based Matching           | Drivers only see passengers in the **same location**                        |
| 💾 Persistent Storage                | All data saved to `drivers.txt`, `passengers.txt`, `rides.txt`              |
| 🎨 Colored Console UI                | Beautiful menus with Windows console colors                                 |
| 🔊 Sound Effects                     | Success / error / ride booked beeps (Windows only)                         |
| 🔒 Basic Security                    | 4-digit passwords, blocked accounts, duplicate username prevention          |

<br>

## 📸 Screenshots

<div align="center">
  <table>
    <tr>
      <td><b>Main Menu</b></td>
      <td><b>Driver Accepting Ride</b></td>
    </tr>
    <tr>
      <td><img src="https://via.placeholder.com/600x350/1e1e2e/00ff9f?text=Main+Menu+Screenshot" alt="Main Menu" width="300"/></td>
      <td><img src="https://via.placeholder.com/600x350/1e1e2e/ff9f00?text=Driver+Accept+Ride" alt="Driver Accept" width="300"/></td>
    </tr>
    <tr>
      <td><b>Admin View Rides</b></td>
      <td><b>Passenger Request</b></td>
    </tr>
    <tr>
      <td><img src="https://via.placeholder.com/600x350/1e1e2e/9f00ff?text=Admin+Rides+List" alt="Admin Rides" width="300"/></td>
      <td><img src="https://via.placeholder.com/600x350/1e1e2e/00d4ff?text=Request+Sent" alt="Passenger Request" width="300"/></td>
    </tr>
  </table>
</div>

> **Note:** Replace the placeholder image URLs with real screenshots after you take them!

<br>

## 🛠️ Tech Stack

- **Language** → C99 / C11
- **Platform** → Windows (colored output + Beep sound)
- **Storage** → Plain text files (.txt)
- **Libraries used**:
  - `<windows.h>` — console colors & sound
  - `<stdio.h>`, `<string.h>`, `<stdlib.h>`, `<stdbool.h>`

<br>

## 🚀 Getting Started

### Prerequisites

- GCC or MinGW (Windows)
- Windows OS (for colors & sound)

### Build & Run

```
# 1. Clone the repo
git clone https://github.com/YOUR_USERNAME/taxi-system.git
cd taxi-system

# 2. Compile
gcc -o taxi main.c

# 3. Run
./taxi
# or just double-click taxi.exe on Windows
```

🎮 Default Credentials





























RoleUsernamePasswordNotesAdminadmin2026Full controlDriver(any registered)4 digitsMust be unblockedPassenger(any registered)4 digits—


📂 Project Structure
texttaxi-system/
├── main.c                ← Main program + all logic
├── drivers.txt           ← Auto-generated
├── passengers.txt        ← Auto-generated
├── rides.txt             ← Auto-generated
├── README.md             ← You are here
└── .gitignore


🔮 Future Improvements (Roadmap)

 Distance-based fare calculation
 Ride history per user/driver
 Logout & session management
 Simple password hashing
 Linux/macOS support (ANSI colors)
 ncurses / PDCurses → real TUI interface
 Export reports to CSV




Made with ❤️ by EDi
A university / personal project that turned into something quite powerful!


Star ⭐ if you like it!
Fork → contribute → learn together

```
