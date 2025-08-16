# focus-flow
FOCUSFLOW is a C++ console-based task manager with a secure login system. Users can register, log in, and manage personalized to-do lists. Tasks include title, description, due date, and are categorized using the Eisenhower Matrix. Data is saved in user-specific files for persistence.
# FOCUSFLOW 📝✨
*A Console-Based Task Management and Productivity System in C++*

## 📌 Overview
FOCUSFLOW is a simple and efficient console application built in C++ to help users **organize and manage tasks**.  
It combines a **secure login system** with a **to-do list manager**, following the **Eisenhower Matrix** principle of task prioritization.

Each registered user has a **separate data file**, ensuring personalized and persistent task storage.

---

## 🚀 Features
- 🔑 **User Authentication**
  - Register new accounts with username, password, name, and phone number.
  - Login with credential verification.
  - Each user has their own task data file.

- ✅ **Task Management**
  - Add tasks with title, description, and due date.
  - Categorize tasks into four Eisenhower Matrix priorities:
    1. Urgent & Important  
    2. Not Urgent but Important  
    3. Urgent but Not Important  
    4. Not Urgent and Not Important  
  - View all, pending, or completed tasks.
  - Delete tasks by ID.
  - Mark tasks as completed.

- 💾 **Data Persistence**
  - `password.dat` → Stores all registered usernames & passwords.
  - `<username>.dat` → Stores individual user’s task details.

---

## 🛠️ Installation & Usage

### 1. Clone the repository
```bash
git clone https://github.com/your-username/FOCUSFLOW.git
cd FOCUSFLOW
