#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <fstream> 
#include <sstream> 
#include <algorithm> 

using namespace std;

class EmployeePayments {
private:
    double* salaries;
    int size;
    int capacity;
    string employeeName;

    void resize() {
        capacity *= 2;
        double* newSalaries = new double[capacity];
        for (int i = 0; i < size; ++i) {
            newSalaries[i] = salaries[i];
        }
        delete[] salaries;
        salaries = newSalaries;
    }

public:
    EmployeePayments()
        : size(1), capacity(1), employeeName("") {
        salaries = new double[1];
        salaries[0] = 910.00;
    }

    EmployeePayments(const double* initSalaries, int initSize, int initCapacity, const string& name)
        : size(initSize), capacity(initCapacity), employeeName(name) {
        if (initSize > initCapacity) {
            throw invalid_argument("Size more than capasity!");
        }
        salaries = new double[capacity];
        for (int i = 0; i < size; ++i) {
            if (initSalaries[i] < 910.00 || initSalaries[i] > 2500.00) {
                delete[] salaries;
                throw invalid_argument("Err salary value.");
            }
            salaries[i] = initSalaries[i];
        }
    }

    EmployeePayments(const EmployeePayments& other)
        : size(other.size), capacity(other.capacity), employeeName(other.employeeName) {
        salaries = new double[capacity];
        for (int i = 0; i < size; ++i) {
            salaries[i] = other.salaries[i];
        }
    }

    EmployeePayments& operator=(const EmployeePayments& other) {
        if (this == &other) {
            return *this;
        }
        delete[] salaries;
        size = other.size;
        capacity = other.capacity;
        employeeName = other.employeeName;
        salaries = new double[capacity];
        for (int i = 0; i < size; ++i) {
            salaries[i] = other.salaries[i];
        }
        return *this;
    }

    ~EmployeePayments() {
        delete[] salaries;
    }

    double* getSalaries() const {
        return salaries;
    }

    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }

    string getEmployeeName() const {
        return employeeName;
    }

    void addSalary(double salary) {
        if (salary < 910.00 || salary > 2500.00) {
            throw invalid_argument("<err salary value.");
        }
        if (size == capacity) {
            resize();
        }
        salaries[size++] = salary;
    }
};

class Person {
private:
    string name;
    int age;

    static int totalEmployees;
    static int totalManagers;

public:
    Person(const string& name, int age) {
        if (name.empty()) {
            throw invalid_argument("Name cannot be mpty.");
        }
        if (age < 0 || age > 65) {
            throw invalid_argument("Age is negative or over 65");
        }
        this->name = name;
        this->age = age;
    }

    Person(const Person& other) {
        name = other.name;
        age = other.age;
    }

    Person& operator=(const Person& other) {
        if (this == &other) {
            return *this;
        }
        name = other.name;
        age = other.age;
        return *this;
    }

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    static int getTotalEmployees() {
        return totalEmployees;
    }

    static int getTotalManagers() {
        return totalManagers;
    }

protected:
    static void incrementEmployeeCount() {
        ++totalEmployees;
    }

    static void incrementManagerCount() {
        ++totalManagers;
    }
};

int Person::totalEmployees = 0;
int Person::totalManagers = 0;

class Employee : public Person {
    string position;
    int experience;
    EmployeePayments salaries;

public:
    Employee(const string& name, int age, const string& position, int experience, const EmployeePayments& salaries)
        : Person(name, age), position(position), experience(experience), salaries(salaries) {
        if (position.empty()) {
            throw invalid_argument("Empty string for position.");
        }
        if (experience < 1) {
            throw invalid_argument("Exp is too low.");
        }
        incrementEmployeeCount();
    }

    Employee(const Employee& other)
        : Person(other), position(other.position), experience(other.experience), salaries(other.salaries) {
        incrementEmployeeCount();
    }

    Employee& operator=(const Employee& other) {
        if (this == &other) {
            return *this;
        }
        Person::operator=(other);
        position = other.position;
        experience = other.experience;
        salaries = other.salaries;
        return *this;
    }

    string getPosition() const {
        return position;
    }

    int getExperience() const {
        return experience;
    }

    EmployeePayments getSalaries() const {
        return salaries;
    }

    double calculateAverageSalary() const {
        double total = 0;
        int count = salaries.getSize();
        for (int i = 0; i < count; ++i) {
            total += salaries.getSalaries()[i];
        }
        return count > 0 ? total / count : 0;
    }

    friend ostream& operator<<(ostream& os, const Employee& employee) {
        os << "Employee: " << employee.getName() << "\n"
           << "Age: " << employee.getAge() << "\n"
           << "Position: " << employee.position << "\n"
           << "Experience: " << employee.experience << "\n"
           << "Average Salary: " << employee.calculateAverageSalary() << "\n";
        return os;
    }

    friend istream& operator>>(istream& is, Employee& employee) {
        string name;
        int age;
        string position;
        int experience;
        if (is >> name >> age >> position >> experience) {
            EmployeePayments salaries;
            employee = Employee(name, age, position, experience, salaries);
        }
        return is;
    }
};

class Manager : public Person {
private:
    string department;

    void validateDepartment(const string& department) {
        static const vector<string> validDepartments = {"delivery", "marketing", "sales", "human resources"};
        if (find(validDepartments.begin(), validDepartments.end(), department) == validDepartments.end()) {
            throw invalid_argument("Invalid department!");
        }
    }

public:
    Manager(const string& name, int age, const string& department)
        : Person(name, age), department(department) {
        if (department.empty()) {
            throw invalid_argument("Department must not be an empty string.");
        }
        validateDepartment(department);
        incrementManagerCount();
    }

    Manager(const Manager& other)
        : Person(other), department(other.department) {
        incrementManagerCount();
    }

    Manager& operator=(const Manager& other) {
        if (this == &other) {
            return *this;
        }
        Person::operator=(other);
        department = other.department;
        return *this;
    }

    string getDepartment() const {
        return department;
    }

    void payEmployeeByName(const string& employeeName, vector<Employee>& employees, double salary) {
        for (auto& employee : employees) {
            if (employee.getName() == employeeName) {
                employee.getSalaries().addSalary(salary);
                cout << "Added salary " << salary << " to employee " << employeeName << endl;
                return;
            }
        }
        cout << "Name not found" << employeeName << endl;
    }

    friend ostream& operator<<(ostream& os, const Manager& manager) {
        os << "Manager: " << manager.getName() << "\n"
           << "Age: " << manager.getAge() << "\n"
           << "Department: " << manager.department << "\n";
        return os;
    }

    friend istream& operator>>(istream& is, Manager& manager) {
        string name;
        int age;
        string department;
        if (is >> name >> age >> department) {
            manager = Manager(name, age, department);
        }
        return is;
    }
};

class FileManager {
private:
    const string inputFileName;
    const string outputFileName;

public:
    FileManager(const string& inputFileName, const string& outputFileName)
        : inputFileName(inputFileName), outputFileName(outputFileName) {}

    void readData(vector<Employee>& employees, vector<Manager>& managers){
        ifstream inputFile(inputFileName);
        string type;
        while (inputFile >> type) {
            if(type == "e"){
                string name, name2, position;
                int age, experience;
                inputFile >> name >> name2 >> age >> position >> experience;
                name += name2;
                EmployeePayments salaries;
                Employee temp(name, age, position, experience, salaries);
                employees.push_back(temp);
            } else if(type == "m"){
                string name, name2, department, employeeName, employeeName2;
                int age;
                double salary;
                inputFile >> name >> name2 >> age >> department;
                if(department == "human"){
                    string temp;
                    inputFile >> temp;
                    department = department + " " + temp;
                }
                inputFile >> employeeName >> employeeName2 >> salary;
                name += name2;
                employeeName += employeeName2;
                Manager manager(name, age, department);
                manager.payEmployeeByName(employeeName, employees, salary);
                managers.push_back(manager);
            }
        }
        inputFile.close();
    }

    void writeData(const vector<Employee>& employees, const vector<Manager>& managers) {
        ofstream outputFile(outputFileName);
        if (!outputFile) {
            throw runtime_error("Could not open output file.");
        }

        for (const auto& employee : employees) {
            outputFile << employee << "\n";
        }

        for (const auto& manager : managers) {
            outputFile << manager << "\n";
        }
    }
};

int main() {
    try {
        vector<Employee> employees;
        vector<Manager> managers;
        EmployeePayments emp1Salaries;
//Towa e dopulnitelno
//////////////////////////////////////////////////////////////////////////////////
        emp1Salaries.addSalary(2200.0);
        emp1Salaries.addSalary(2300.0);
        Employee emp1("Max Verstapen", 32, "Project Manager", 6, emp1Salaries);
        employees.push_back(emp1);
        EmployeePayments emp2Salaries;
        emp2Salaries.addSalary(2500.0);
        emp2Salaries.addSalary(2400.0);
        Employee emp2("Charles Leclerc", 29, "Data Analyst", 4, emp2Salaries);
        employees.push_back(emp2);
        Manager mgr1("Carlos Sinz", 38, "human resources");
        mgr1.payEmployeeByName("Max Verstapen", employees, 2450.0);
        mgr1.payEmployeeByName("Charles Leclerc", employees, 2000.0);
        managers.push_back(mgr1);
        Manager mgr2("Lando Noris", 45, "sales");
        mgr2.payEmployeeByName("Max Verstapen", employees, 1400.0);
        managers.push_back(mgr2);
////////////////////////////////////////////////////////////////////////////////////////////////
        FileManager fileManager("input.txt", "output.txt");
        fileManager.readData(employees, managers);
        fileManager.writeData(employees, managers);
        cout << "Success!" << endl;
    } catch (const exception& e) {
        cerr << "Err: " << e.what() << endl;
    }

    return 0;
}
