#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

struct Node {
    Course data;
    Node* left;
    Node* right;
    Node(Course c) : data(c), left(nullptr), right(nullptr) {}
};

class CourseBST {
private:
    Node* root;

    void insertNode(Node*& node, Course c) {
        if (!node) node = new Node(c);
        else if (c.courseNumber < node->data.courseNumber)
            insertNode(node->left, c);
        else
            insertNode(node->right, c);
    }

    void inOrder(Node* node) {
        if (!node) return;
        inOrder(node->left);
        printCourse(node->data);
        inOrder(node->right);
    }

    Course* search(Node* node, string courseNumber) {
        if (!node) return nullptr;
        if (node->data.courseNumber == courseNumber) return &node->data;
        else if (courseNumber < node->data.courseNumber)
            return search(node->left, courseNumber);
        else
            return search(node->right, courseNumber);
    }

public:
    CourseBST() : root(nullptr) {}

    void insert(Course c) { insertNode(root, c); }

    void printAll() { inOrder(root); }

    Course* find(string courseNumber) { return search(root, courseNumber); }

    void printCourse(Course c) {
        cout << c.courseNumber << ", " << c.name << endl;
        cout << "Prerequisites: ";
        if (c.prerequisites.empty()) cout << "None";
        else for (string p : c.prerequisites) cout << p << " ";
        cout << endl;
    }
};

// ========== LOAD COURSES ==========
CourseBST loadCourses(string filename) {
    CourseBST bst;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Course course;
        getline(ss, course.courseNumber, ',');
        getline(ss, course.name, ',');
        while (getline(ss, token, ',')) {
            if (!token.empty()) course.prerequisites.push_back(token);
        }
        bst.insert(course);
    }
    return bst;
}

// ========== MAIN MENU ==========
int main() {
    CourseBST bst;
    string filename;
    bool loaded = false;
    int choice;
    cout << "Welcome to the ABCU Course Advising System" << endl;

    do {
        cout << "\n1. Load course data\n";
        cout << "2. Print all courses (sorted)\n";
        cout << "3. Print course details\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter file name: ";
            cin >> filename;
            bst = loadCourses(filename);
            loaded = true;
            cout << "Courses loaded successfully." << endl;
        }
        else if (choice == 2) {
            if (!loaded) cout << "Please load data first.\n";
            else bst.printAll();
        }
        else if (choice == 3) {
            if (!loaded) cout << "Please load data first.\n";
            else {
                string cnum;
                cout << "Enter course number: ";
                cin >> cnum;
                Course* c = bst.find(cnum);
                if (c) bst.printCourse(*c);
                else cout << "Course not found.\n";
            }
        }
        else if (choice != 9) cout << "Invalid option.\n";

    } while (choice != 9);

    cout << "Goodbye!\n";
    return 0;
}