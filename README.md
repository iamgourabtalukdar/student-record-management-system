# 🎓 Student Record Management System (C)

A simple **Student Record Management System** written in C that allows users to **add, view, search, and delete student records**.  
The program uses a **binary file (`students.dat`)** for persistent storage of student details.

---

## 📌 Features

- **Add Student Record** – Store roll number, name, and marks.
- **Display All Records** – View all student details in a tabular format.
- **Search Student by Roll Number** – Quickly find a student’s record.
- **Delete Student Record** – Remove a student's entry by roll number.
- **Persistent Storage** – Records are stored in a binary file for future access.

---

## 📂 Project Structure

```
.
├── main.c         # Source code
├── students.dat   # Binary data file (auto-created)
└── README.md      # Documentation
```

---

## ⚙️ How to Compile and Run

### Using GCC:

```bash
# Compile
gcc main.c -o student_mgmt

# Run
./student_mgmt
```

### On Windows (MinGW / Visual Studio Developer Command Prompt):

```bash
gcc main.c -o student_mgmt.exe
student_mgmt.exe
```

---

## 📋 Usage Guide

When you run the program, you will see a command menu like this:

```
--- Student Record System ---
  add      - Add a new student record
  display  - Display all student records
  search   - Search for a student by roll number
  delete   - Delete a student record by roll number
  exit     - Exit the program
-----------------------------
```

### Example Workflow:

1. Enter **`add`** → Input roll number, name, and marks.
2. Enter **`display`** → View all stored students.
3. Enter **`search`** → Find a student by roll number.
4. Enter **`delete`** → Remove a student by roll number.
5. Enter **`exit`** → Quit the program.

---

## 💾 Data Storage

- Student records are stored in **`students.dat`** (binary format).
- Each record contains:
  - `rollNumber` (int)
  - `name` (string)
  - `marks` (float)

---

## 🔮 Possible Improvements

- Update student details (edit feature).
- Sort records by roll number or marks.
- Export records to a text/CSV file.
- Add error checking for duplicate roll numbers.

---

## 👨‍💻 Author

- Developed by _Gourab Talukdar_
- A beginner-friendly C project to understand file handling and structures.
