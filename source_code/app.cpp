#define _CRT_SECURE_NO_WARNINGS
#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include    <string>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(const char*, BST*);

int menu();

int main() {
    BST bst;
    int choice;
    do {
        choice = menu();

        if (choice == 1) {
            readFile("student.txt", &bst);
        }
        else if (choice == 2) {
            if (!bst.deepestNodes())
                cout << "No tree!" << endl;
            cout << endl;
        }
        else if (choice == 3) {
            int order, source;
            cout << "(1) Ascending (2) Descending: ";
            cin >> order;
            cout << "(1) Screen (2) File: ";
            cin >> source;

            if (!bst.display(order, source))
                cout << "No tree!" << endl;

        }
        else if (choice == 4) {
            int targetId;
            cout << "Enter student ID to clone subtree: ";
            cin >> targetId;

            Student target;
            target.id = targetId;

            BST clonedTree;

            if (clonedTree.CloneSubtree(bst, target)) {
                cout << "\n--- Original tree (preorder) ---" << endl;
                bst.preOrderPrint();

                cout << "\n--- Cloned subtree (preorder) ---" << endl;
                clonedTree.preOrderPrint();
            }
            else {
                cout << "Cannot clone subtree. (Tree may be empty, ID not found, or current tree not empty?)" << endl;
            }

        }
        else if (choice == 5) {
            if (!bst.printLevelNodes())
                cout << "Tree is empty\n\n";
        }
        else if (choice == 6) {
            if (!bst.printPath())
                cout << "Tree is empty\n\n";
        }
        else if (choice == 7) {
            cout << "Exiting system\n\n";
            break;
        }
    } while (choice != 7);


    system("pause");
    return 0;
}

int menu() {
    int choice;

    while (true) {
        cout << "\n(1) Read data to BST";
        cout << "\n(2) Print deepest nodes";
        cout << "\n(3) Display student";
        cout << "\n(4) Clone Subtree";
        cout << "\n(5) Print Level Nodes";
        cout << "\n(6) Print Path";
        cout << "\n(7) Exit";
        cout << "\nEnter choice: (1-7) ";

        int choice;

        if (!(cin >> choice)) {
            cout << "Invalid choice. Try again\n\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice >= 1 && choice <= 7) {
            return choice;
        }
        cout << "Invalid choice. Try again\n";
    }

}

bool readFile(const char* filename, BST* t1) {

    if (t1->root != NULL) {
        Queue qClear;
        qClear.enqueue(t1->root);
        while (!qClear.empty()) {
            BTNode* temp;
            qClear.dequeue(temp);
            if (temp->left != NULL) qClear.enqueue(temp->left);
            if (temp->right != NULL) qClear.enqueue(temp->right);
            delete temp;
        }
        t1->root = NULL;
        t1->count = 0;
    }

    ifstream file(filename);

    if (!file) {
        cout << "Error: Cannot open file!" << endl;
        return false;
    }

    Student s;
    string line;
    int count = 0;

    while (getline(file, line)) {

        if (line.find("Student Id") != string::npos) {

            // ID 
            s.id = stoi(line.substr(line.find("=") + 2));

            // Name 
            getline(file, line);
            strcpy(s.name, line.substr(line.find("=") + 2).c_str());

            // ---- Address ----
            getline(file, line);
            strcpy(s.address, line.substr(line.find("=") + 2).c_str());

            // ---- DOB ----
            getline(file, line);
            strcpy(s.DOB, line.substr(line.find("=") + 2).c_str());

            // ---- Phone ----
            getline(file, line);
            strcpy(s.phone_no, line.substr(line.find("=") + 2).c_str());

            // ---- Course ----
            getline(file, line);
            strcpy(s.course, line.substr(line.find("=") + 2).c_str());

            // ---- CGPA ----
            getline(file, line);
            s.cgpa = stod(line.substr(line.find("=") + 2));

            // Insert into BST
            t1->insert(s);
            count++;
        }
    }

    cout << "Number of student records read: " << count << endl;

    file.close();
    return true;
}