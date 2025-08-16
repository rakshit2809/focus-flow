    #include <iostream>
    #include <vector>
    #include <string>
    #include <fstream>
    #include <ctime>
    #include <conio.h>

    using namespace std;

    class login {
    public:
        string username;
        string password;
        login() {}
        login(string a, string b): username(a), password(b) {}
        ~login() {}
    };

    class account : public login {
    public: 
        string name;
        string phone;
        account(): login() {}
        account(string a, string b, string c, string d): name(a), phone(b), login(c, d) {}
        ~account() {}
    };

    void registerAccount(account& o1) {
        login o2(o1.username, o1.password);
        ofstream outFile("password.dat", ios::out | ios::app);
        if (outFile.is_open()) {
            outFile << o2.username << " " << o2.password << endl;
            outFile.close();
        } else {
            cout << "error while opening file";
            return;
        }

        string fileName = o1.username + ".dat";
        outFile.open(fileName, ios::out | ios::app);  
        if (outFile) {
            outFile << o1.name << " " << o1.phone << " " << o1.username << " " << o1.password << endl;
        } else {
            cerr << "Error creating file!" << endl;
        }
        outFile.close();
    }

    bool loginUser() {
        string username, password;
        cout << "Enter your username: ";
        cin>>username;
        cout << "Enter your password: ";
        cin >> password;

        ifstream inFile("password.dat");
        if (!inFile.is_open()) {
            cout << "error while opening file. please register first" << endl;
            return false;
        }

        string u, p;
        bool found = false;
        while (inFile >> u >> p) {
            if (u == username && p == password) {
                cout << "Login successful. Welcome, " << username << "!" << endl;
                found = true;
                break;
            }
        }
        inFile.close();
        if (!found) {
            cout << "Invalid username or password." << endl;
        }
        return found;
    }

    void RegisterUser() {
        string a, b, c, d;
        cin.ignore();
        cout << "Enter your Name: ";
        cin>>a;
        cout << "Enter your Phone: ";
        cin>>b;
        cout << "Enter a Username: ";
        cin>>c;
        cout << "Enter a Password: ";
        cin>>d;

        account o(a, b, c, d);
        registerAccount(o);
    }

    class Task {
    private:
        int id;
        string title;
        string description;
        bool isCompleted;
        string dueDate;
        string category; 
    public:
        Task(int _id, string _title, string _description, string _dueDate)
            : id(_id), title(_title), description(_description), isCompleted(false), dueDate(_dueDate) ,category("Uncategorized") {}

        void markCompleted() { isCompleted = true; }
        void displayTask() {
            cout << "ID: " << id << endl;
            cout << "Title: " << title << endl;
            cout << "Description: " << description << endl;
            cout << "Due Date: " << dueDate << endl;
            cout << "Status: " << (isCompleted ? "Completed" : "Pending") << endl;
            cout << "Category: " << category << endl;
            cout << "------------------------" << endl;
        }

        int getId() { return id; }
        bool getStatus() { return isCompleted; }
        string getTitle() { return title; }
        string getDescription() { return description; }
        string getDueDate() { return dueDate; }
        void setCategory(const string& cat) { category = cat; }
        string getCategory() { return category; }

    };


 class EisenhowerMatrix {
public:
    void categorizeTask(Task &task, int priority) {
        switch(priority) {
            case 1:
                task.setCategory("Urgent & Important");
                break;
            case 2:
                task.setCategory("Not Urgent but Important");
                break;
            case 3:
                task.setCategory("Urgent but Not Important");
                break;
            case 4:
                task.setCategory("Not Urgent and Not Important");
                break;
            default:
                cout << "Invalid input" << endl;
                break;
        }
    }



};



class ToDoList {
private:
    string listName;
    vector<Task> tasks;
    int nextId;
    string username;  
    EisenhowerMatrix matrix; 
public:
    ToDoList(string name, string user) : listName(name), username(user), nextId(1) {}  

    void addTask(string title, string description, string dueDate)
     {
    Task newTask(nextId++, title, description, dueDate);
    
    int priority;
    cout << "Enter priority (1: Urgent & Important, 2: Not Urgent but Important, 3: Urgent but Not Important, 4: Not Urgent and Not Important): ";
    cin >> priority;
    
    matrix.categorizeTask(newTask, priority); 
    tasks.push_back(newTask);
    saveTasksToFile();
    cout << "Task added successfully";
    cout<<endl;
}




    void deleteTask(int id) {
        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i].getId() == id) {
                tasks.erase(tasks.begin() + i);
                saveTasksToFile();
                cout << "Task deleted successfully";
                cout<<endl;
                return;
            }
        }
        cout << "Task not found"<<endl;
    }

    void showAllTasks() {
        if (tasks.empty()) {
            cout << "No Tasks Found";
            cout<<endl;
            return;
        }
        for (int i = 0; i < tasks.size(); i++) {
            tasks[i].displayTask();
        }
        cout<<endl;
        cout<<"PRIORITY INDEX:";
        cout<<endl;
        cout<<"1: Urgent & Important";
        cout<<endl;
        cout<<"2: Not Urgent but Important";
        cout<<endl;
        cout<<"3: Urgent but Not Important";
        cout<<endl;
        cout<< "4: Not Urgent and Not Important";
        cout<<endl;
    }

    void showPendingTasks() {
        bool found = false;
        for (int i = 0; i < tasks.size(); i++) {
            if (!tasks[i].getStatus()) {
                tasks[i].displayTask();
                found = true;
            }
        }
        if (!found) {
            cout << "No pending tasks.";
            cout<<endl;
        }
    }

    void showCompletedTasks() {
        bool found = false;
        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i].getStatus()) {
                tasks[i].displayTask();
                found = true;
            }
        }
        if (!found) {
            cout << "No completed tasks.";
            cout<<endl;
        }
    }

    void markTaskCompleted(int id) {
        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i].getId() == id) {
                tasks[i].markCompleted();
                saveTasksToFile();
                cout << "Task marked as completed!\n";
                return;
            }
        }
        cout << "Task not found!\n";
    }
void saveTasksToFile() {
    ofstream outFile(username + ".dat");
    if (!outFile.is_open()) {
        cout << "Error opening file for saving tasks.\n";
        return;
    }

    for (Task& task : tasks) {
        outFile << task.getId() << "|"
                << (task.getStatus() ? 1 : 0) << "|"
                << task.getTitle() << "|"
                << task.getDescription() << "|"
                << task.getDueDate() << "|"
                << task.getCategory() << endl;  
    }
    outFile.close();
}

void loadTasksFromFile() {
    ifstream inFile(username + ".dat");
    if (!inFile.is_open()) {
        cout << "No tasks found for this user yet.\n";
        return;
    }

    tasks.clear();
    nextId = 1;

    string line;
    while (getline(inFile, line)) {
        try {
            int id, isCompletedInt;
            string title, description, dueDate, category;

            int pos = 0;
            pos = line.find("|");
            id = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            pos = line.find("|");
            isCompletedInt = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            pos = line.find("|");
            title = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find("|");
            description = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find("|");
            dueDate = line.substr(0, pos);
            line.erase(0, pos + 1);

            category = line;

            Task newTask(id, title, description, dueDate);
            newTask.setCategory(category);  

            if (isCompletedInt) newTask.markCompleted();
            tasks.push_back(newTask);

            if (id >= nextId) nextId = id + 1;
        } catch (const invalid_argument& e) {
            cout << "Skipping invalid task data: " << line << endl;
            continue;
        } catch (const out_of_range& e) {
            cout << "Skipping out-of-range task data: " << line << endl;
            continue;
        }
    }
    inFile.close();
}

};
    class ToDoApp {
    private:
        ToDoList list;

    public:
        ToDoApp(string name, string username) : list(name, username) {  
            list.loadTasksFromFile();
        }

        void run() {
            int choice;
            while (true) {
                showMenu();
                cin >> choice;
                cin.ignore();
                if (choice == 1) {
                    string title, desc, due;
                    cout << "Enter title: "; getline(cin, title);
                    cout << "Enter description: "; getline(cin, desc);
                    cout << "Enter due date: "; getline(cin, due);
                    list.addTask(title, desc, due);
                } else if (choice == 2) {
                    list.showAllTasks();
                } else if (choice == 3) {
                    int id;
                    cout << "Enter task ID to delete: "; cin >> id;
                    list.deleteTask(id);
                } else if (choice == 4) {
                    int id;
                    cout << "Enter task ID to mark completed: "; cin >> id;
                    list.markTaskCompleted(id);
                } else if (choice == 5) {
                    list.showPendingTasks();
                } else if (choice == 6) {
                    list.showCompletedTasks();
                } else if (choice == 0) {
                    cout << "Exiting To-Do App.\n";
                    break;
                } else {
                    cout << "Invalid choice.\n";
                }
            }
        }

        void showMenu() {
            cout << "\n====== To-Do Menu ======" << endl;
            cout << "1. Add Task" << endl;
            cout << "2. Show All Tasks" << endl;
            cout << "3. Delete Task" << endl;
            cout << "4. Mark Task Completed" << endl;
            cout << "5. Show Pending Tasks" << endl;
            cout << "6. Show Completed Tasks" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter your choice: ";
        }
    };

    class pomodoro {
    protected:
        int min;
        float min1;
        int count;
    public:
        bool force_stop;
        pomodoro(){}    
        pomodoro(int min) {
            force_stop = false;
            if (min > 50 || min < 25)
                cout << "Timer shouldn't be more than 50 mins or less than 25 mins! RETRY!" << endl;
            else {
                this->min = min;
                min1 = (min / (double)25) * 5;
                count = 0;
            }
        }
        void timerP() {
            time_t t = time(NULL);
            int x = t;
            int s = 1;
            while (true) {
                t = time(NULL);
                if (kbhit()) {
                    char c = getch();
                    if (c == 'q' || c == 'Q') {
                        cout <<endl<< "Pomodoro forcefully stopped!" << endl;
                        force_stop = true;
                        break;
                    }
                }
                if (t == x + s) {
                    cout << s/60 << ":";
                    if (s - (s/60)*60 <= 9) cout << "0";
                    cout << s - (s/60)*60 << flush;
                    cout << "\b\b\b\b" << flush;
                    s++;
                }
                if (t == x + min*60 || force_stop) break;
            }
            count++;
        }

        float reTime() { return min1; }

        void timerB() {
            time_t t = time(NULL);
            int x = t;
            int s = 1;
            while (true) {
                t = time(NULL);
                if (kbhit()) {
                    char c = getch();
                    if (c == 'q' || c == 'Q') {
                        cout << "\nBreak forcefully stopped!" << endl;
                        force_stop = true;
                        break;
                    }
                }
                if (t == x + s) {
                    cout << s/60 << ":";
                    if (s - (s/60)*60 <= 9) cout << "0";
                    cout << s - (s/60)*60 << flush;
                    cout << "\b\b\b\b" << flush;
                    s++;
                }
                if (t == x + min1*60 || force_stop) break;
            }
            if (count == 4) min1 = min;
        }

        string currentT() {
            time_t t = time(NULL);
            tm* timeinfo = localtime(&t);
            return asctime(timeinfo);
        }
    };

    void startpomo() {
        pomodoro pomo;
        int Ptime, x = 0;
        do {
            cout << "Enter setup time (25-50 min): ";
            cin >> Ptime;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                x = 0;
                cout << "Wrong data type inputted. Please Try again" << endl;
            } else {
                x = 1;
                pomo = pomodoro(Ptime);
            }
        } while ((Ptime > 50 || Ptime < 25) || x == 0);

        cout << "Break time set to: " << pomo.reTime() << " minutes" << endl;

        for (int i = 0; i < 4; i++) {
            cout << "Starting Pomodoro Timer:" << endl;
            pomo.timerP();
            if (pomo.force_stop) return;
            cout << "Starting Break:" << endl;
            pomo.timerB();
            if (pomo.force_stop) return;
            cout << "Pomodoro-" << i+1 << " ended at: " << pomo.currentT();
        }

        cout << "Starting Long Break:" << endl;
        pomo.timerB();
    }

    int main() {
        int choice;
        while (true) {
            cout << endl << "====== Welcome ======" << endl;
            cout << "1. Register" << endl;
            cout << "2. Login" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                RegisterUser();
            } else if (choice == 2) {
                if (loginUser()) {
                    string username;
                    cout << "Enter your username again to confirm: ";
                    cin >> username; 
                    int innerChoice;
                    while (true) {
                        cout<<endl;
                        cout << "----------------------------" << endl;
                        cout << "1. Open To-Do List" << endl;
                        cout << "2. Start Pomodoro Timer" << endl;
                        cout << "0. Logout" << endl;
                        cout << "Enter your choice: ";
                        cin >> innerChoice;
                        if (innerChoice == 1) {
                            ToDoApp app("My Tasks", username); 
                            app.run();
                        } else if (innerChoice == 2) {
                            startpomo();
                        } else if (innerChoice == 0) {
                            cout << "Logging out..."<<endl;
                            break;
                        } else {
                            cout << "Invalid option!";
                            cout<<endl;
                        }
                    }
                }   
            } else if (choice == 0) {
                cout << "Goodbye" << endl;
                break;
            } else {
                cout << "Invalid choice, try again."<<endl;
            }
        }
        return 0;
    }
