<div align="center">

<br>

# 🚖 Advanced Console Taxi Management System

**A comprehensive console-based ride-hailing simulation written entirely in pure C**
> *Think of it as a mini Snapp / Uber — no frameworks, no databases, just raw C and file I/O*

<br>

[![C](https://img.shields.io/badge/Language-C99%2FC11-00599C?style=for-the-badge&logo=c&logoColor=white)]()
[![Windows](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)]()
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg?style=for-the-badge)]()
[![Status](https://img.shields.io/badge/Status-Active-brightgreen?style=for-the-badge)]()
[![Made with ❤️](https://img.shields.io/badge/Made%20with-%E2%9D%A4%EF%B8%8F-red?style=for-the-badge)]()

<br>

> 🔐 **Default Admin Credentials → Username:** `admin` **/** **Password:** `2026`

</div>

---

## 📑 Table of Contents

- [📖 About the Project](#-about-the-project)
- [✨ Features](#-features)
- [🏗️ System Architecture](#️-system-architecture)
- [📂 Project Structure](#-project-structure)
- [🧩 Data Structures](#-data-structures)
- [⚙️ Core Modules](#️-core-modules)
- [📸 Screenshots](#-screenshots)
- [🛠️ Tech Stack](#️-tech-stack)
- [🚀 Getting Started](#-getting-started)
- [🎮 Default Credentials](#-default-credentials)
- [🔄 System Flow](#-system-flow)
- [⚠️ Known Limitations](#️-known-limitations)
- [🔮 Future Roadmap](#-future-roadmap)
- [👨‍💻 Author](#-author)

---

## 📖 About the Project

The **Advanced Console Taxi Management System** is a structured, menu-driven C application that simulates the core operations of a modern ride-hailing platform. It models three distinct user roles — **Admin**, **Driver**, and **Passenger** — each with dedicated menus, permission levels, and data operations.

The project emphasizes:

- **Procedural programming** principles in pure C
- **File-based persistence** using plain text `.txt` files as a lightweight database
- **Role-based access control** with credential validation
- **Real-time status tracking** for passengers and drivers
- **Location-based ride matching** — drivers only see passengers in the same location zone

This project was developed as a **university-level console application** and demonstrates how complex systems can be built with minimal dependencies using the C standard library.

---

## ✨ Features

### 🛡️ Admin Panel
| Capability | Details |
|:-----------|:--------|
| Register Drivers | Add new drivers with username, 4-digit password, ID, location, and block status |
| Register Passengers | Add new passengers with unique credentials and initial state |
| Update Driver/Passenger | Modify username, password, balance, status, or location of any account |
| View All Drivers | Tabular display of every driver's full profile |
| View All Passengers | Tabular display of every passenger's full profile |
| View All Rides | Complete ride log with IDs, parties involved, fare, and completion status |
| Duplicate Prevention | Rejects registration of usernames that already exist |
| Block/Unblock Accounts | Administrators can restrict driver access at any time |

### 🚗 Driver Dashboard
| Capability | Details |
|:-----------|:--------|
| View Wallet Balance | Displays current earnings balance |
| Accept a Ride | Lists nearby (same-location) waiting passengers; driver selects one to accept |
| Manage Active Rides | View and complete ongoing trips; triggers fare transfer |
| Change Password | Secure 4-digit password update with old-password verification |
| Change Status | Toggle between `block` / `unblock` |
| Change Location | Update current zone for accurate ride matching |

### 🧍 Passenger Dashboard
| Capability | Details |
|:-----------|:--------|
| View Wallet Balance | Shows available funds |
| Request a Ride | Sets status to `Waiting`; requires balance ≥ 10.0 |
| Cancel Ride | Reverts status to `None` if in waiting state |
| Change Password | 4-digit password update with verification |
| Change Location | Update pickup zone |

### 💡 System-Wide Features
- 💰 **Automatic Wallet Transactions** — fare deducted from passenger, credited to driver upon ride completion
- 📍 **Location-based Matching** — only passengers in the driver's current zone are shown
- 💾 **Persistent Storage** — all data survives application restarts via `.txt` flat files
- 🎨 **Windows Console Colors** — distinct color-coding per role and message type
- 🔊 **Audio Feedback** — distinct beep sequences for success, error, and ride booking events
- 🔒 **Basic Security** — 4-digit PIN system, blocked account enforcement, no duplicate usernames

---

## 🏗️ System Architecture

```
┌─────────────────────────────────────────────────────────┐
│                        main()                           │
│                     [Entry Point]                       │
└───────────┬────────────────────────────────┬────────────┘
            │                                │
     ┌──────▼──────┐                  ┌──────▼──────┐
     │ loadData()  │                  │ saveData()  │
     │ [File I/O]  │                  │ [File I/O]  │
     └─────────────┘                  └─────────────┘
            │
     ┌──────▼──────────────────────────────────────┐
     │                 MAIN MENU                   │
     └──────┬──────────────┬──────────────┬────────┘
            │              │              │
     ┌──────▼──────┐ ┌─────▼──────┐ ┌────▼────────┐
     │ adminMenu() │ │driverMenu()│ │passengerMenu│
     │             │ │            │ │    ()       │
     │  - Register │ │ - Wallet   │ │ - Request   │
     │  - Update   │ │ - Accept   │ │ - Cancel    │
     │  - View     │ │ - Complete │ │ - Balance   │
     └─────────────┘ └────────────┘ └─────────────┘
```

---

## 📂 Project Structure

```
taxi-system/
│
├── main.c                  ← All program logic in a single translation unit
│
├── drivers.txt             ← Auto-generated; stores driver records (space-separated)
├── passengers.txt          ← Auto-generated; stores passenger records
├── rides.txt               ← Auto-generated; stores ride history
│
├── README.md               ← You are here 📍
└── .gitignore              ← Excludes compiled binaries and temp files
```

> **Note:** The `.txt` files are created automatically on first run. Do not manually edit them unless you understand the exact field order used by `fscanf` / `fprintf`.

---

## 🧩 Data Structures

The application defines three core `struct` types:

### `struct driver`
```c
struct driver {
    char username[50];      // Unique login name
    char password[20];      // 4-digit PIN
    int  id;                // 4-digit numeric identifier
    char status[50];        // "block" or "unblock"
    float balance;          // Earnings wallet
    int  trips;             // Completed trip counter
    char location[100];     // Current zone/area
    bool is_logged_in;      // Session flag (not persisted)
};
```

### `struct passenger`
```c
struct passenger {
    char username[50];      // Unique login name
    char password[20];      // 4-digit PIN
    int  id;                // 4-digit numeric identifier
    float balance;          // Payment wallet
    int  trips;             // Completed trip counter
    char status[50];        // "None", "Waiting", or "inRide"
    char location[100];     // Pickup zone
    bool is_logged_in;      // Session flag (not persisted)
};
```

### `struct ride`
```c
struct ride {
    int   id;               // Auto-incremented ride ID
    int   passenger_id;     // References passenger's ID
    int   driver_id;        // References driver's ID
    char  pickup[100];      // Pickup location (from passenger)
    char  destination[100]; // Destination entered by driver
    float fare;             // Trip cost entered by driver
    bool  completed;        // Completion flag
};
```

**Global arrays:**
```c
struct driver    drivers[1404];    // MAX_USER = 1404
struct passenger passengers[1404];
struct ride      rides[200];       // MAX_RIDES = 200
```

---

## ⚙️ Core Modules

### 🗄️ File Handling — `loadData()` / `saveData()`
Data persistence is handled via `fscanf` (read) and `fprintf` (write) on three plain-text files. Each record occupies one line with space-separated fields. The `is_logged_in` flag is runtime-only and not persisted.

**Format — `drivers.txt`:**
```
<username> <password> <id> <status> <balance> <trips> <location>
```

**Format — `passengers.txt`:**
```
<username> <password> <id> <status> <balance> <trips> <location>
```

**Format — `rides.txt`:**
```
<id> <passenger_id> <driver_id> <pickup> <destination> <fare> <completed>
```

> ⚠️ Because space is the field delimiter, **location names and usernames must not contain spaces**.

---

### 🔐 Authentication Flow
- **Admin:** hardcoded credentials (`admin` / `2026`) — no file dependency
- **Driver:** matched against `drivers[]` array + must have `status == "unblock"`
- **Passenger:** matched against `passengers[]` array (no block check)

---

### 🗺️ Location-based Matching Algorithm
When a driver attempts to accept a ride:
1. The system iterates all passengers
2. Filters for `status == "Waiting"`
3. Filters for `location == drivers[driver_idx].location` (exact string match)
4. Filters for `balance >= 10.0`
5. Only qualifying passengers are displayed to the driver

---

### 💳 Fare Transfer Logic
Upon ride completion (`Manage Active Rides → Complete`):
```
passenger.balance  -=  ride.fare
driver.balance     +=  ride.fare
passenger.trips    ++
driver.trips       ++
passenger.status    =  "None"
ride.completed      =  true
```
All changes are immediately persisted via `saveData()`.

---

## 📸 Screenshots

<div align="center">
  <table>
    <tr>
      <td align="center"><b>🏠 Main Menu</b></td>
      <td align="center"><b>🚗 Driver Accepting Ride</b></td>
    </tr>
    <tr>
      <td><img width="320" alt="Main Menu" src="https://github.com/user-attachments/assets/396aa9a0-b251-4057-a3d5-f6abb1671449" /></td>
      <td><img width="320" alt="Driver Accepting Ride" src="https://github.com/user-attachments/assets/cc19ed4c-3dba-4252-b267-3cf376b6f526" /></td>
    </tr>
    <tr>
      <td align="center"><b>🛡️ Admin — View Rides</b></td>
      <td align="center"><b>🧍 Passenger Request</b></td>
    </tr>
    <tr>
      <td><img width="320" alt="Admin View Rides" src="https://github.com/user-attachments/assets/33582c3b-5322-4d60-a46b-df5665c852c3" /></td>
      <td>
        <img width="320" alt="Passenger Request 1" src="https://github.com/user-attachments/assets/f1380430-f970-4637-83b5-758288d40d2f" />
        <img width="320" alt="Passenger Request 2" src="https://github.com/user-attachments/assets/7c0bd964-095c-4f4e-a714-57e2d57e0803" />
      </td>
    </tr>
  </table>
</div>

---

## 🛠️ Tech Stack

| Component | Details |
|:----------|:--------|
| **Language** | C99 / C11 |
| **Platform** | Windows (x86 / x64) |
| **Compiler** | GCC (MinGW) / MSVC |
| **Storage** | Plain-text flat files (`.txt`) |
| **UI** | Windows Console API (colors + `Beep`) |
| **Dependencies** | `stdio.h` · `stdlib.h` · `string.h` · `stdbool.h` · `windows.h` |

### Color Scheme (Windows Console Attributes)
| Color | Code | Usage |
|:------|:-----|:------|
| `CYAN` | 11 | Headers, section titles |
| `MAGENTA` | 13 | Menu titles |
| `YELLOW` | 14 | Sub-section headers, input prompts |
| `GREEN` | 10 | Success messages |
| `RED` | 12 | Error messages |
| `RESET` | 7 | Default text |

---

## 🚀 Getting Started

### ✅ Prerequisites

- **OS:** Windows 7 or later (required for `windows.h` — colors & sound)
- **Compiler:** [MinGW-w64](https://www.mingw-w64.org/) or any GCC distribution for Windows
- **Optional:** [VSCode](https://code.visualstudio.com/) + C/C++ Extension, or [Code::Blocks](https://www.codeblocks.org/)

### 🔧 Build & Run

```bash
# 1. Clone the repository
git clone https://github.com/xedi1/Taxi-System-snap.git
cd Taxi-System-snap

# 2. Compile with GCC
gcc main.c -o taxi_system.exe

# 3. Run
./taxi_system.exe
# or simply double-click taxi_system.exe in Windows Explorer
```

> 💡 **Tip:** The first run creates `drivers.txt`, `passengers.txt`, and `rides.txt` automatically in the same directory. Keep all files together.

---

## 🎮 Default Credentials

| Role | Username | Password | Notes |
|:-----|:---------|:---------|:------|
| 👑 Admin | `admin` | `2026` | Hardcoded — full system control |
| 🚗 Driver | *(registered by admin)* | 4 digits | Must have `status = unblock` |
| 🧍 Passenger | *(registered by admin)* | 4 digits | Must have `balance ≥ 10.0` to request |

---

## 🔄 System Flow

```
Program Start
     │
     ▼
 loadData()   ← reads .txt files into memory arrays
     │
     ▼
┌─ MAIN MENU ──────────────────┐
│  1. Admin Login               │
│  2. Driver Login              │
│  3. Passenger Login           │
│  4. Exit → saveData() + quit  │
└──────────────────────────────┘
     │
     ├─► [Admin]
     │       Register Driver / Passenger
     │       Update Accounts
     │       View Drivers / Passengers / Rides
     │
     ├─► [Driver]
     │       View Balance
     │       See Nearby Waiting Passengers (location match)
     │       Accept Ride → creates ride record
     │       Complete Ride → triggers fare transfer
     │       Change Password / Status / Location
     │
     └─► [Passenger]
             View Balance
             Request Ride → status = "Waiting"
             Cancel Ride  → status = "None"
             Change Password / Location
```

---

## ⚠️ Known Limitations

| # | Issue | Impact |
|:--|:------|:-------|
| 1 | Location matching uses **exact string comparison** | Spaces in location names will break matching |
| 2 | Passwords stored in **plaintext** in `.txt` files | Not suitable for production environments |
| 3 | No **input sanitization** on string fields | Long inputs may cause buffer overflows (`NAME_LEN = 50`) |
| 4 | `windows.h` dependency | Not portable to Linux/macOS without modification |
| 5 | No **logout** mechanism — session ends only when returning to main menu | Minor UX concern |
| 6 | Flat-file storage with space delimiters | Multi-word fields (e.g. location names) are unsupported |
| 7 | Admin credentials hardcoded in source | Must recompile to change admin password |

---

## 🔮 Future Roadmap

- [ ] 📏 Distance-based dynamic fare calculation
- [ ] 📜 Per-user ride history log
- [ ] 🔐 Basic password hashing (e.g. SHA-1 or XOR obfuscation)
- [ ] 🔄 Proper logout and session invalidation
- [ ] 🐧 Linux/macOS support via ANSI escape codes
- [ ] 🖥️ ncurses / PDCurses — real TUI interface
- [ ] 📊 Admin dashboard with ride statistics and earnings reports
- [ ] 📁 CSV export for ride history and financial summaries
- [ ] 🌐 Multi-word location support (quoted strings or underscore convention)
- [ ] 🧾 Receipt generation per completed ride
- [ ] 🔔 Driver notification when a new passenger requests in the same zone

---

## 👨‍💻 Author

<div align="center">

**Made with ❤️ by EDi (Hadi Gholipour _ AxGooD)**

*A university / personal project that evolved into a fully functional console application.*

<br>

⭐ **Star this repo** if you found it useful!
🍴 **Fork** → contribute → grow together

<br>

[![GitHub](https://img.shields.io/badge/GitHub-xedi1-181717?style=for-the-badge&logo=github)](https://github.com/xedi1)

</div>
