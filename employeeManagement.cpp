#include<bits/stdc++.h>
using namespace std;
 
int ID = 1;
vector<pair<int,string>> requests;
// Base class: Person
class Person {
protected:
    string name;
    int age;
    string role;

public:
    Person(string name, int age, string role) : name(name), age(age), role(role) {}

    virtual void displayProfile() const {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Role: " << role << endl;
    }

    virtual ~Person() {}
};

// Derived class: Employee
class Employee : public Person {
private:
    int employeeID;
    string department;
    string password;

public:
    Employee(string name, int age, int employeeID, string department, string password)
        : Person(name, age, "Employee"), employeeID(employeeID), department(department), password(password) {}

    bool authorize(const string& inputPassword) const {
        return inputPassword == password;
    }

    void changePassword(const string& oldPassword, const string& newPassword) {
        if (authorize(oldPassword)) {
            password = newPassword;
            cout << "Password updated successfully!" << endl;
        } else {
            cout << "Incorrect old password. Password change failed." << endl;
        }
    }

    void displayProfile() const override {
        Person::displayProfile();
        cout << "Employee ID: " << employeeID << endl;
        cout << "Department: " << department << endl;
    }

    void updateDetails(string newName, int newAge, string newDepartment)
    {
        name = newName;
        age = newAge;
        department = newDepartment;
    }

    int getEmployeeID() const {
        return employeeID;
    }

    int getAge(){
        return age;
    }

    string getName() const {
        return name;
    }

    string getDepartment()
    {
        return department;
    }
};

// Derived class: Manager
class Manager : public Person {
private:
    string password;

public:
    Manager(string name, int age, string password)
        : Person(name, age, "Manager"), password(password) {}

    bool authorize(const string& inputPassword) const {
        return inputPassword == password;
    }

    void addEmployee(vector<Employee>& employeeList, const Employee& emp) {
        employeeList.push_back(emp);
        cout << "Employee " << emp.getName() << " added successfully!" << endl;
    }

    void removeEmployee(vector<Employee>& employeeList, int employeeID) {
        for (auto it = employeeList.begin(); it != employeeList.end(); ++it) {
            if (it->getEmployeeID() == employeeID) {
                cout << "Employee " << it->getName() << " removed successfully!" << endl;
                employeeList.erase(it);
                return;
            }
        }
        cout << "Employee with ID " << employeeID << " not found." << endl;
    }

    void updateEmployeeDetails(vector<Employee>& employeeList, int employeeID) {
        for (auto& emp : employeeList) {
            if (emp.getEmployeeID() == employeeID) {
                string newName, newDepartment;
                int newAge;
                cout << "Enter new details:\n";
                cout << "Enter Name: "; cin >> ws; getline(cin, newName);
                cout << "Enter Age: "; cin >> newAge;
                cout << "Enter Department: "; cin >> ws; getline(cin, newDepartment);
                emp.updateDetails(newName, newAge, newDepartment);

                cout << "Employee " << emp.getName() << "'s details updated to " << endl;
                emp.displayProfile();
                return;
            }
        }
        cout << "Employee with ID " << employeeID << " not found." << endl;
    }

    void viewAllEmployees(const vector<Employee>& employeeList) const {
        if (employeeList.empty()) {
            cout << "No employees to display." << endl;
            return;
        }

        cout << "\nEmployee List:\n";
        for (const auto& emp : employeeList) {
            emp.displayProfile();
            cout << "-------------------" << endl;
        }
    }

    void handleRequests(vector<Employee>& employeeList)
    {
        if(requests.empty()){
            cout << "No requests to show!" << endl;
            return;
        }
        vector<int> deletedRequests;
        cout << "\nRequests:\n";
        int totalRequests = requests.size();
        for(int i = 0; i < totalRequests; i++)
        {
            string oldDepartment;
            for(auto &emp: employeeList){
                if(emp.getEmployeeID() == requests[i].first){
                    oldDepartment = emp.getDepartment();
                    break;
                }
            }
            cout << "Employee ID: " << requests[i].first << '\n';
            cout << "Current Department: " << oldDepartment << '\n';
            cout << "Requested Department: " << requests[i].second;

            int choice;
            while(true){
                cout << "\n\nPress 1 to approve request\n";
                cout << "Press 2 to deny request\n";
                cout << "Press 3 to move to next request\n";
                cout << "Press 4 to exit\n\n";
                cout << "Enter your choice: ";
                cin >> choice;

                if(choice == 1){
                    for(auto &emp: employeeList){
                        if(emp.getEmployeeID() == requests[i].first){
                            emp.updateDetails(emp.getName(), emp.getAge(), requests[i].second);
                            break;
                        }
                    }
                    // requests.erase(requests.begin() + i);
                    deletedRequests.push_back(i);
                    break;
                }
                else if(choice == 2){
                    cout << "Request denied\n\n";
                    // requests.erase(requests.begin() + i);
                    deletedRequests.push_back(i);
                    break;
                }
                else if(choice == 3){
                    break;
                } 
                else if(choice == 4){
                    cout << "Exiting\n\n";
                    return;
                } else{
                    cout << "Invalid Input\n\n";
                }
            }
        }

        int deleted = 0;
        for(auto dr: deletedRequests){
            requests.erase(requests.begin() + dr - deleted);
            deleted++;
        }

        cout << "\nRequests Over!\n";
    }

    void displayProfile() const override {
        Person::displayProfile();
    }
};

// Utility functions
void managerMenu(Manager& manager, vector<Employee>& employeeList) {
    string password;
    cout << "\nEnter Manager Password to Proceed: ";
    cin >> password;

    if (!manager.authorize(password)) {
        cout << "Authorization Failed. Returning to Main Menu.\n";
        return;
    }

    int choice;
    while (true) {
        cout << "\nManager Menu:\n";
        cout << "1. Add Employee\n";
        cout << "2. Remove Employee\n";
        cout << "3. Update Employee Details\n";
        cout << "4. View All Employees\n";
        cout << "5. View Profile\n";
        cout << "6. View Requests\n";
        cout << "7. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, department, password;
                int age, id;

                cout << "Enter Employee Name: ";
                cin >> ws;
                getline(cin, name);
                cout << "Enter Employee Age: ";
                cin >> age;
                id = ID;
                ID++;
                cout << "Enter Department: ";
                cin >> ws;
                getline(cin, department);
                cout << "Set Employee Password: ";
                cin >> password;

                Employee emp(name, age, id, department, password);
                manager.addEmployee(employeeList, emp);
                break;
            }
            case 2: {
                int id;
                cout << "Enter Employee ID to Remove: ";
                cin >> id;
                manager.removeEmployee(employeeList, id);
                break;
            }
            case 3: {
                int id;
                cout << "Enter employee id to update: "; cin >> id;
                manager.updateEmployeeDetails(employeeList, id);
                break;
            }
            case 4:
                manager.viewAllEmployees(employeeList);
                break;

            case 5:
                manager.displayProfile();
                break;

            case 6: {
                manager.handleRequests(employeeList);
                break;
            }

            case 7:
                cout << "Logging out...\n";
                return;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

void employeeMenu(const vector<Employee>& employeeList) {
    int id;
    string password;
    cout << "\nEnter Employee ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> password;

    for (const auto& emp : employeeList) {
        if (emp.getEmployeeID() == id) {
            if (emp.authorize(password)) {
                int choice;
                while (true) {
                    cout << "\nEmployee Menu:\n";
                    cout << "1. View Profile\n";
                    cout << "2. Change Password\n";
                    cout << "3. Request department change\n";
                    cout << "4. Logout\n";
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            emp.displayProfile();
                            break;

                        case 2: {
                            string oldPassword, newPassword;
                            cout << "Enter Old Password: ";
                            cin >> oldPassword;
                            cout << "Enter New Password: ";
                            cin >> newPassword;
                            const_cast<Employee&>(emp).changePassword(oldPassword, newPassword); // Modify password
                            break;
                        }

                        case 3:{
                            string newDepartment;
                            cout << "Enter new department: "; cin >> ws; getline(cin,newDepartment);
                            requests.push_back(make_pair(id, newDepartment));
                            cout << "Request Made!\nThe changes will be done once approved by your manager\n";
                            break;
                        }

                        case 4:
                            cout << "Logging out...\n";
                            return;

                        default:
                            cout << "Invalid choice. Try again.\n";
                    }
                }
            } else {
                cout << "Incorrect Password.\n";
            }
            return;
        }
    }
    cout << "Employee ID not found.\n";
}

int main() {
    Manager manager("Alice", 40, "manager123");
    vector<Employee> employeeList; // Shared employee list
    Employee e1("yashraj", 23, 1, "eng", "emp1");
    Employee e2("shreyansh", 24, 2, "hr", "emp2");
    Employee e3("anshul", 25, 3, "testing", "emp3");
    employeeList.push_back(e1);
    employeeList.push_back(e2);
    employeeList.push_back(e3);

    requests.push_back({1, "consult"});
    requests.push_back({2, "entertainment"});
    requests.push_back({3, "security"});

    int choice;
    while (true) {
        cout << "\nEmployee Management System\n";
        cout << "1. Manager Login\n";
        cout << "2. Employee Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                managerMenu(manager, employeeList);
                break;

            case 2:
                employeeMenu(employeeList);
                break;

            case 3:
                cout << "Exiting the system. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
