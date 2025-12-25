#include <bits/stdc++.h>
using namespace std;

struct Student {
    string name;
    string rollNo;
    string branch;
    float cgpa;
    Student* next;
};

struct Company {
    string name;
    string role;
    string branch;
    float minCgpa;
};

struct Candidate {
    string name;
    float cgpa;
};

class StudentList {
public:
    Student* head;

    StudentList() { head = NULL; }

    void addStudent(string name, string rollNo, string branch, float cgpa) {
        Student* temp = head;
    while (temp) {
        if (temp->rollNo == rollNo) {
            cout << "Error: Student with roll number " << rollNo << " already exists!\n";
            return;
        }
        temp = temp->next;
    }
        Student* newStudent = new Student{name, rollNo, branch, cgpa, NULL};
        if (!head) head = newStudent;
        else {
            Student* temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newStudent;
        }
    }

    void displayStudents() {
        if (!head) {
            cout << "No students available.\n";
            return;
        }
        cout << "\n--- Student List ---\n";
        Student* temp = head;
        while (temp) {
            cout << "Name: " << temp->name
                 << " | Roll No: " << temp->rollNo
                 << " | Branch: " << temp->branch
                 << " | CGPA: " << temp->cgpa << endl;
            temp = temp->next;
        }
    }
};

class CompanyList {
public:
    Company companies[20];
    int count;

    CompanyList() { count = 0; }

    void addCompany(string name, string role, string branch, float minCgpa) {
         string lowerName = toLowerCase(name);
    for (int i = 0; i < count; i++) {
        if (toLowerCase(companies[i].name) == lowerName) {
            cout << "Error: Company with name \"" << name << "\" already exists!\n";
            return;
        }
    }
        if (count < 20)
            companies[count++] = {name, role, branch, minCgpa};
        else
            cout << "Company list full!\n";
    }

    void displayCompanies() {
        if (count == 0) {
            cout << "No companies available.\n";
            return;
        }
        cout << "\n--- Company List ---\n";
        for (int i = 0; i < count; i++) {
            cout << "Name: " << companies[i].name
                 << " | Role: " << companies[i].role
                 << " | Branch: " << companies[i].branch
                 << " | Min CGPA: " << companies[i].minCgpa << endl;
        }
    }
};
bool compareByCGPA(Candidate a, Candidate b) {
             return a.cgpa > b.cgpa;
         }
class Scheduler {
public:
    queue<Candidate> interviewQueue;

    string toLowerCase(string str) {
        for (char &c : str)
            c = tolower(c);
        return str;
    }

    void makeSchedule(StudentList &students, CompanyList &companyList, string companyName) {
        companyName = toLowerCase(companyName);
        int index = -1;
        for (int i = 0; i < companyList.count; i++) {
            if (toLowerCase(companyList.companies[i].name) == companyName) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Company not found!\n";
            return;
        }

        Company comp = companyList.companies[index];
        while (!interviewQueue.empty()) interviewQueue.pop();

        vector<Candidate> eligible;
        Student* temp = students.head;

        while (temp) {
            if (comp.branch.find(temp->branch) != string::npos && temp->cgpa >= comp.minCgpa)
                eligible.push_back({temp->name, temp->cgpa});
            temp = temp->next;
        }

        if (eligible.empty()) {
            cout << "No eligible students for " << comp.name << ".\n";
            return;
        }

        

sort(eligible.begin(), eligible.end(), compareByCGPA);


        for (int i = 0; i < eligible.size(); i++) {
                interviewQueue.push(eligible[i]);
        }

        cout << "Interview queue created for " << comp.name << ".\n";
}


    void showSchedule(string companyName) {
        if (interviewQueue.empty()) {
            cout << "No schedule to show.\n";
            return;
        }

        cout << "\nInterview Queue for " << companyName << " ---\n";
        queue<Candidate> temp = interviewQueue;
        int i = 1;
        while (!temp.empty()) {
            Candidate c = temp.front();
            temp.pop();
            cout << i++ << ". " << c.name << " (CGPA: " << c.cgpa << ")\n";
        }
    }
};

int main() {
    StudentList students;
    CompanyList companies;
    Scheduler scheduler;
    int choice;
    string name, rollNo, branch, role, companyName;
    float cgpa, minCgpa;

    while (true) {
        cout << "\n===== Placement Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Show Students\n";
        cout << "3. Add Company\n";
        cout << "4. Show Companies\n";
        cout << "5. Create Schedule\n";
        cout << "6. Show Schedule\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter Student Name: ";
            getline(cin, name);
            cout << "Enter Roll No: ";
            getline(cin, rollNo);
            cout << "Enter Branch: ";
            getline(cin, branch);
            cout << "Enter CGPA: ";
            cin >> cgpa;
            students.addStudent(name, rollNo, branch, cgpa);
            break;

        case 2:
            students.displayStudents();
            break;

        case 3:
            cout << "Enter Company Name: ";
            getline(cin, name);
            cout << "Enter Role: ";
            getline(cin, role);
            cout << "Enter Eligible Branches (comma separated): ";
            getline(cin, branch);
            cout << "Enter Minimum CGPA: ";
            cin >> minCgpa;
            companies.addCompany(name, role, branch, minCgpa);
            break;

        case 4:
            companies.displayCompanies();
            break;

        case 5:
            cout << "Enter Company Name to Schedule: ";
            getline(cin, companyName);
            scheduler.makeSchedule(students, companies, companyName);
            break;

        case 6:
            cout << "Enter Company Name to View Schedule: ";
            getline(cin, companyName);
            scheduler.showSchedule(companyName);
            break;

        case 7:
            cout << "Exiting...\n";
            return 0;
        }
    }
}
