#include <iostream>
#include <string>
using namespace std;

class Stack {
private:
    struct Node {
        string data;
        Node* next;
    };
    Node* top;
    
public:
    Stack() {
        top = NULL;
    }
    
    void push(string value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }
    
    string pop() {
        if (isEmpty()) {
            return "";
        }
        string value = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return value;
    }
    
    bool isEmpty() {
        return top == NULL;
    }
    
    string peek() {
        if (!isEmpty()) {
            return top->data;
        }
        return "";
    }
};

class Queue {
private:
    struct Node {
        int data;
        Node* next;
    };
    Node* front;
    Node* rear;
    
public:
    Queue() {
        front = NULL;
        rear = NULL;
    }
    
    void enqueue(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = NULL;
        
        if (rear == NULL) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }
    
    int dequeue() {
        if (isEmpty()) {
            return -1;
        }
        int value = front->data;
        Node* temp = front;
        front = front->next;
        if (front == NULL) {
            rear = NULL;
        }
        delete temp;
        return value;
    }
    bool isEmpty() {
        return front == NULL;
    }
};
class Student {
public:
    int id;
    string name;
    string section;
    int semester;
    double pendingFees;
    Student* next;
    
    Student() {
        id = 0;
        name = "";
        section = "";
        semester = 1;
        pendingFees = 0.0;
        next = NULL;
    }
    
    Student(int i, string n, string s, int sem, double fees) {
        id = i;
        name = n;
        section = s;
        semester = sem;
        pendingFees = fees;
        next = NULL;
    }
};

// Teacher class
class Teacher {
public:
    int id;
    string name;
    string course;
    Teacher* left;
    Teacher* right;
    
    Teacher() {
        id = 0;
        name = "";
        course = "";
        left = NULL;
        right = NULL;
    }
    
    Teacher(int i, string n, string c) {
        id = i;
        name = n;
        course = c;
        left = NULL;
        right = NULL;
    }
};

// Course class
class Course {
public:
    string courseName;
    string courseCode;
    int semester;
    
    Course() {
        courseName = "";
        courseCode = "";
        semester = 1;
    }
    
    Course(string name, string code, int sem) {
        courseName = name;
        courseCode = code;
        semester = sem;
    }
};

// Student Linked List Management
class StudentManager {
private:
    Student* head;
    Stack recentActions;
    
public:
    StudentManager() {
        head = NULL;
        initializeDefaultStudents();
    }
    
    void initializeDefaultStudents() {
        // Pre-load 10 students
        addStudent(1001, "Ahmed Ali", "A", 1, 15000.0);
        addStudent(1002, "Fatima Khan", "B", 2, 8000.0);
        addStudent(1003, "Hassan Ahmed", "A", 1, 12000.0);
        addStudent(1004, "Ayesha Malik", "C", 3, 5000.0);
        addStudent(1005, "Omar Sheikh", "B", 2, 20000.0);
        addStudent(1006, "Zainab Ali", "A", 4, 0.0);
        addStudent(1007, "Bilal Ahmad", "C", 1, 18000.0);
        addStudent(1008, "Mariam Qureshi", "B", 3, 7500.0);
        addStudent(1009, "Usman Tariq", "A", 2, 11000.0);
        addStudent(1010, "Sana Riaz", "C", 4, 3000.0);
    }
    
    void addStudent(int id, string name, string section, int semester, double fees) {
        Student* newStudent = new Student(id, name, section, semester, fees);
        if (head == NULL) {
            head = newStudent;
        } else {
            Student* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newStudent;
        }
        recentActions.push("Added student: " + name);
    }
    
    void addStudentMenu() {
        int id, semester;
        string name, section;
        double fees;
        
        cout << "\n=== Add New Student ===\n";
        cout << "Enter Student ID: ";
        cin >> id;
        cout << "Enter Student Name: ";
        cin >> name;
        cout << "Enter Section: ";
        cin >> section;
        cout << "Enter Semester (1-4): ";
        cin >> semester;
        cout << "Enter Pending Fees: ";
        cin >> fees;
        
        addStudent(id, name, section, semester, fees);
        cout << "Student added successfully!\n";
    }
    
    void removeStudent() {
        if (head == NULL) {
            cout << "No students to remove!\n";
            return;
        }
        
        int id;
        cout << "Enter Student ID to remove: ";
        cin >> id;
        
        if (head->id == id) {
            Student* temp = head;
            head = head->next;
            recentActions.push("Removed student: " + temp->name);
            delete temp;
            cout << "Student removed successfully!\n";
            return;
        }
        
        Student* current = head;
        while (current->next != NULL && current->next->id != id) {
            current = current->next;
        }
        
        if (current->next != NULL) {
            Student* temp = current->next;
            current->next = temp->next;
            recentActions.push("Removed student: " + temp->name);
            delete temp;
            cout << "Student removed successfully!\n";
        } else {
            cout << "Student not found!\n";
        }
    }
    
    void searchStudent() {
        int id;
        cout << "Enter Student ID to search: ";
        cin >> id;
        
        Student* current = head;
        while (current != NULL) {
            if (current->id == id) {
                cout << "\n=== Student Details ===\n";
                cout << "ID: " << current->id << endl;
                cout << "Name: " << current->name << endl;
                cout << "Section: " << current->section << endl;
                cout << "Semester: " << current->semester << endl;
                cout << "Pending Fees: $" << current->pendingFees << endl;
                return;
            }
            current = current->next;
        }
        cout << "Student not found!\n";
    }
    
    void checkPendingFees() {
        int id;
        cout << "Enter Student ID to check fees: ";
        cin >> id;
        
        Student* current = head;
        while (current != NULL) {
            if (current->id == id) {
                cout << "\n=== Fee Details ===\n";
                cout << "Student: " << current->name << endl;
                cout << "Pending Fees: $" << current->pendingFees << endl;
                if (current->pendingFees == 0) {
                    cout << "All fees are paid!\n";
                } else {
                    cout << "Payment is due!\n";
                }
                return;
            }
            current = current->next;
        }
        cout << "Student not found!\n";
    }
    
    void displayRecentActions() {
        cout << "\n=== Recent Actions ===\n";
        Stack temp;
        int count = 0;
        while (!recentActions.isEmpty() && count < 5) {
            string action = recentActions.pop();
            cout << (count + 1) << ". " << action << endl;
            temp.push(action);
            count++;
        }
        while (!temp.isEmpty()) {
            recentActions.push(temp.pop());
        }
    }
};

// Teacher BST Management
class TeacherManager {
private:
    Teacher* root;
    Stack updateHistory;
    
    Teacher* insertTeacher(Teacher* root, int id, string name, string course) {
        if (root == NULL) {
            Teacher* newTeacher = new Teacher(id, name, course);
            return newTeacher;
        }
        
        if (id < root->id) {
            root->left = insertTeacher(root->left, id, name, course);
        } else if (id > root->id) {
            root->right = insertTeacher(root->right, id, name, course);
        }
        return root;
    }
    
    Teacher* searchTeacher(Teacher* root, int id) {
        if (root == NULL || root->id == id) {
            return root;
        }
        
        if (id < root->id) {
            return searchTeacher(root->left, id);
        }
        return searchTeacher(root->right, id);
    }
    
    Teacher* findMin(Teacher* root) {
        while (root && root->left) {
            root = root->left;
        }
        return root;
    }
    
    Teacher* deleteTeacher(Teacher* root, int id) {
        if (root == NULL) {
            return root;
        }
        
        if (id < root->id) {
            root->left = deleteTeacher(root->left, id);
        } else if (id > root->id) {
            root->right = deleteTeacher(root->right, id);
        } else {
            if (root->left == NULL) {
                Teacher* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == NULL) {
                Teacher* temp = root->left;
                delete root;
                return temp;
            }
            
            Teacher* temp = findMin(root->right);
            root->id = temp->id;
            root->name = temp->name;
            root->course = temp->course;
            root->right = deleteTeacher(root->right, temp->id);
        }
        return root;
    }
    
    void inorderDisplay(Teacher* root) {
        if (root != NULL) {
            inorderDisplay(root->left);
            cout << "ID: " << root->id << ", Name: " << root->name 
                 << ", Course: " << root->course << endl;
            inorderDisplay(root->right);
        }
    }
    
public:
    TeacherManager() {
        root = NULL;
        initializeDefaultTeachers();
    }
    
    void initializeDefaultTeachers() {
        // Pre-load 10 teachers
        addTeacher(2001, "Dr_Muhammad_Asif", "Data_Structures");
        addTeacher(2002, "Prof_Sarah_Khan", "Mathematics");
        addTeacher(2003, "Dr_Ali_Raza", "Physics");
        addTeacher(2004, "Ms_Farah_Ahmed", "Chemistry");
        addTeacher(2005, "Mr_Hassan_Ali", "English");
        addTeacher(2006, "Dr_Amna_Malik", "Computer_Science");
        addTeacher(2007, "Prof_Tariq_Shah", "Statistics");
        addTeacher(2008, "Ms_Zara_Qureshi", "Biology");
        addTeacher(2009, "Dr_Umar_Farooq", "Algorithms");
        addTeacher(2010, "Mr_Adeel_Ahmad", "Database_Systems");
    }
    
    void addTeacher(int id, string name, string course) {
        root = insertTeacher(root, id, name, course);
        updateHistory.push("Added teacher: " + name);
    }
    
    void addTeacherMenu() {
        int id;
        string name, course;
        
        cout << "\n=== Add New Teacher ===\n";
        cout << "Enter Teacher ID: ";
        cin >> id;
        cout << "Enter Teacher Name: ";
        cin >> name;
        cout << "Enter Course: ";
        cin >> course;
        
        addTeacher(id, name, course);
        cout << "Teacher added successfully!\n";
    }
    
    void removeTeacher() {
        int id;
        cout << "Enter Teacher ID to remove: ";
        cin >> id;
        
        Teacher* teacher = searchTeacher(root, id);
        if (teacher != NULL) {
            updateHistory.push("Removed teacher: " + teacher->name);
            root = deleteTeacher(root, id);
            cout << "Teacher removed successfully!\n";
        } else {
            cout << "Teacher not found!\n";
        }
    }
    
    void searchTeacherMenu() {
        int id;
        cout << "Enter Teacher ID to search: ";
        cin >> id;
        
        Teacher* teacher = searchTeacher(root, id);
        if (teacher != NULL) {
            cout << "\n=== Teacher Details ===\n";
            cout << "ID: " << teacher->id << endl;
            cout << "Name: " << teacher->name << endl;
            cout << "Course: " << teacher->course << endl;
        } else {
            cout << "Teacher not found!\n";
        }
    }
    
    void updateTeacherInfo() {
        int id;
        cout << "Enter Teacher ID to update: ";
        cin >> id;
        
        Teacher* teacher = searchTeacher(root, id);
        if (teacher != NULL) {
            string oldInfo = teacher->name + " - " + teacher->course;
            
            cout << "Current Info - Name: " << teacher->name << ", Course: " << teacher->course << endl;
            cout << "Enter new name: ";
            string newName;
            cin >> newName;
            teacher->name = newName;
            
            cout << "Enter new course: ";
            string newCourse;
            cin >> newCourse;
            teacher->course = newCourse;
            
            updateHistory.push("Updated teacher: " + oldInfo + " -> " + teacher->name + " - " + teacher->course);
            cout << "Teacher information updated successfully!\n";
        } else {
            cout << "Teacher not found!\n";
        }
    }
    
    void displayAllTeachers() {
        cout << "\n=== All Teachers ===\n";
        inorderDisplay(root);
    }
};

// Course Tree Management
class CourseManager {
private:
    Course courses[4][6]; // 4 semesters, 6 courses each
    Stack courseHistory;
    
public:
    CourseManager() {
        initializeDefaultCourses();
    }
    
    void initializeDefaultCourses() {
        // Semester 1 courses
        courses[0][0] = Course("Introduction_to_Programming", "CS101", 1);
        courses[0][1] = Course("Calculus_I", "MATH101", 1);
        courses[0][2] = Course("Physics_I", "PHY101", 1);
        courses[0][3] = Course("English_Composition", "ENG101", 1);
        courses[0][4] = Course("Chemistry", "CHEM101", 1);
        courses[0][5] = Course("Introduction_to_Psychology", "PSY101", 1);
        
        // Semester 2 courses
        courses[1][0] = Course("Object_Oriented_Programming", "CS201", 2);
        courses[1][1] = Course("Calculus_II", "MATH201", 2);
        courses[1][2] = Course("Physics_II", "PHY201", 2);
        courses[1][3] = Course("Technical_Writing", "ENG201", 2);
        courses[1][4] = Course("Statistics", "STAT201", 2);
        courses[1][5] = Course("Digital_Logic_Design", "CS202", 2);
        
        // Semester 3 courses
        courses[2][0] = Course("Data_Structures", "CS301", 3);
        courses[2][1] = Course("Linear_Algebra", "MATH301", 3);
        courses[2][2] = Course("Database_Systems", "CS302", 3);
        courses[2][3] = Course("Computer_Networks", "CS303", 3);
        courses[2][4] = Course("Software_Engineering", "CS304", 3);
        courses[2][5] = Course("Operating_Systems", "CS305", 3);
        
        // Semester 4 courses
        courses[3][0] = Course("Algorithms", "CS401", 4);
        courses[3][1] = Course("Artificial_Intelligence", "CS402", 4);
        courses[3][2] = Course("Computer_Graphics", "CS403", 4);
        courses[3][3] = Course("Web_Development", "CS404", 4);
        courses[3][4] = Course("Mobile_App_Development", "CS405", 4);
        courses[3][5] = Course("Final_Year_Project", "CS406", 4);
    }
    
    void displaySemesterCourses(int semester) {
        if (semester < 1 || semester > 4) {
            cout << "Invalid semester!\n";
            return;
        }
        
        cout << "\n=== Semester " << semester << " Courses ===\n";
        cout << "Course Code" << "     " << "Course Name" << endl;
        cout << "-------------------------------------------" << endl;
        
        for (int i = 0; i < 6; i++) {
            cout << courses[semester-1][i].courseCode << "         " << courses[semester-1][i].courseName << endl;
        }
    }
    
    void updateCourse() {
        int semester, courseIndex;
        
        cout << "Enter semester (1-4): ";
        cin >> semester;
        
        if (semester < 1 || semester > 4) {
            cout << "Invalid semester!\n";
            return;
        }
        
        displaySemesterCourses(semester);
        
        cout << "Enter course number to update (1-6): ";
        cin >> courseIndex;
        
        if (courseIndex < 1 || courseIndex > 6) {
            cout << "Invalid course number!\n";
            return;
        }
        
        courseIndex = courseIndex - 1; // Convert to 0-based index
        
        string oldCourse = courses[semester-1][courseIndex].courseName;
        
        cout << "Current course: " << courses[semester-1][courseIndex].courseName << endl;
        cout << "Enter new course name: ";
        string newName;
        cin >> newName;
        
        cout << "Enter new course code: ";
        string newCode;
        cin >> newCode;
        
        courses[semester-1][courseIndex].courseName = newName;
        courses[semester-1][courseIndex].courseCode = newCode;
        
        courseHistory.push("Updated course: " + oldCourse + " -> " + newName);
        cout << "Course updated successfully!\n";
    }
    
    void displayUpdateHistory() {
        cout << "\n=== Course Update History ===\n";
        Stack temp;
        int count = 0;
        while (!courseHistory.isEmpty() && count < 5) {
            string update = courseHistory.pop();
            cout << (count + 1) << ". " << update << endl;
            temp.push(update);
            count++;
        }
        while (!temp.isEmpty()) {
            courseHistory.push(temp.pop());
        }
    }
};

// Main School Management System
class SchoolManagementSystem {
private:
    StudentManager studentMgr;
    TeacherManager teacherMgr;
    CourseManager courseMgr;
    
public:
    void displayMainMenu() {
        cout << "\n==================================================\n";
        cout << "         SCHOOL MANAGEMENT SYSTEM\n";
        cout << "==================================================\n";
        cout << "1. Students\n";
        cout << "2. Teachers\n";
        cout << "3. Courses\n";
        cout << "4. Exit\n";
        cout << "==================================================\n";
        cout << "Enter your choice: ";
    }
    
    void displayStudentMenu() {
        cout << "\n========================================\n";
        cout << "         STUDENT MANAGEMENT\n";
        cout << "========================================\n";
        cout << "1. Add Student\n";
        cout << "2. Remove Student\n";
        cout << "3. Search Student\n";
        cout << "4. Check Pending Fees\n";
        cout << "5. View Recent Actions\n";
        cout << "6. Back to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";
    }
    
    void displayTeacherMenu() {
        cout << "\n========================================\n";
        cout << "         TEACHER MANAGEMENT\n";
        cout << "========================================\n";
        cout << "1. Add Teacher\n";
        cout << "2. Remove Teacher\n";
        cout << "3. Search Teacher\n";
        cout << "4. Update Teacher Info\n";
        cout << "5. View All Teachers\n";
        cout << "6. Back to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";
    }
    
    void displayCourseMenu() {
        cout << "\n========================================\n";
        cout << "         COURSE MANAGEMENT\n";
        cout << "========================================\n";
        cout << "1. Semester 1 Courses\n";
        cout << "2. Semester 2 Courses\n";
        cout << "3. Semester 3 Courses\n";
        cout << "4. Semester 4 Courses\n";
        cout << "5. Update Course\n";
        cout << "6. View Update History\n";
        cout << "7. Back to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";
    }
    
    void handleStudentMenu() {
        int choice;
        do {
            displayStudentMenu();
            cin >> choice;
            
            switch (choice) {
                case 1:
                    studentMgr.addStudentMenu();
                    break;
                case 2:
                    studentMgr.removeStudent();
                    break;
                case 3:
                    studentMgr.searchStudent();
                    break;
                case 4:
                    studentMgr.checkPendingFees();
                    break;
                case 5:
                    studentMgr.displayRecentActions();
                    break;
                case 6:
                    cout << "Returning to main menu...\n";
                    break;
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 6);
    }
    
    void handleTeacherMenu() {
        int choice;
        do {
            displayTeacherMenu();
            cin >> choice;
            
            switch (choice) {
                case 1:
                    teacherMgr.addTeacherMenu();
                    break;
                case 2:
                    teacherMgr.removeTeacher();
                    break;
                case 3:
                    teacherMgr.searchTeacherMenu();
                    break;
                case 4:
                    teacherMgr.updateTeacherInfo();
                    break;
                case 5:
                    teacherMgr.displayAllTeachers();
                    break;
                case 6:
                    cout << "Returning to main menu...\n";
                    break;
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 6);
    }
    
    void handleCourseMenu() {
        int choice;
        do {
            displayCourseMenu();
            cin >> choice;
            
            switch (choice) {
                case 1:
                case 2:
                case 3:
                case 4:
                    courseMgr.displaySemesterCourses(choice);
                    break;
                case 5:
                    courseMgr.updateCourse();
                    break;
                case 6:
                    courseMgr.displayUpdateHistory();
                    break;
                case 7:
                    cout << "Returning to main menu...\n";
                    break;
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 7);
    }
    
    void run() {
        int choice;
        cout << "Welcome to School Management System!\n";
        cout << "System initialized with 10 students and 10 teachers.\n";
        
        do {
            displayMainMenu();
            cin >> choice;
            
            switch (choice) {
                case 1:
                    handleStudentMenu();
                    break;
                case 2:
                    handleTeacherMenu();
                    break;
                case 3:
                    handleCourseMenu();
                    break;
                case 4:
                    cout << "Thank you for using School Management System!\n";
                    cout << "Goodbye!\n";
                    break;
                default:
                    cout << "Invalid choice! Please enter 1-4.\n";
            }
        } while (choice != 4);
    }
};

// Main function
int main() {
    SchoolManagementSystem sms;
    sms.run();
    return 0;
}
