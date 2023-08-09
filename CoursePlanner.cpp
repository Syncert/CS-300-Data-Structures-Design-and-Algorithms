//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Nicholas Kreuziger
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include "CSVparser.hpp"
#include <vector> // to use the vector data structure
#include <algorithm> // to use the sort function

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold course information
struct Course {
    string courseID; // unique identifier
    string courseName;
    vector<string> prerequisites; //hold pre-requisites information

    Course() = default;

    Course(string number, string name, vector<string> prereqs) {
        courseID = number;
        courseName = name;
        prerequisites = prereqs;
    }
};

//forward declaration to display courses
void displayCourse(Course course);

//forward declaration to split pre-requisities 
vector<string> splitPrerequisites(const string& prereqs, char delimiter);


// Internal structure for tree node
struct Node {
    Course course;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
            Node() {
        course = aCourse;
    }
};


//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* minValueNode(Node* node);
    Node* removeNode(Node* node, string courseID);
    Node* addNode(Node* node, Course acourse);
    bool nodeExists(Node* node, string courseID);
    void inOrder(Node* node);
    void inOrderSampleSchedule(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);


public:
    BinarySearchTree();
    Node* sortedArrayToBST(Course arr[], int start, int end);
    Node* root;
    virtual ~BinarySearchTree();
    void InOrder();
    void InOrderSampleSchedule();
    void PreOrder();
    void PostOrder();
    void Insert(Course course);
    void Remove(string courseID);
    Course Search(string courseID);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // FixMe (1): initialize housekeeping variables
    //root is equal to nullptr
    root = nullptr;

}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    //FixMe(1): Complete Destructor 
    // recurse from root deleting every node
    root = removeNode(root, "");

}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // FixMe (2): In order root
    // call inOrder fuction and pass root 
    inOrder(root);
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrderSampleSchedule() {
    // FixMe (2): In order root
    // call inOrder fuction and pass root 
    inOrderSampleSchedule(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // postOrder root
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // preOrder root
    preOrder(root);
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course acourse) {
    // if root equal to null ptr
    root = addNode(root, acourse);  // 
}

/**
 * Remove a course
 */
void BinarySearchTree::Remove(string courseID) {
    // remove node root courseID
    root = removeNode(root, courseID);
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseID) {
    // set current node equal to root
    Node* node = root;
    // keep looping downwards until bottom reached or matching courseID found
    while (node != nullptr) {
        // if match found, return current course
        if (node->course.courseID.compare(courseID) == 0) {
            return node->course;
        }     
        // if course is smaller than current node then traverse left
        else if (node->course.courseID.compare(courseID) > 0) {
        node = node->left;
        }
        //if course is larger than current node traverse right
        else {
            node = node->right;
        }
    }
    //Return empty course object if not found
    return Course();
}


/**
 * Traverse the binary search tree to check if a node with a specific courseID exists.
 * @param node the starting point for the traversal.
 * @param courseID the courseID to be searched in the tree.
 * @return true if a node with the matching courseID is found, false otherwise.
 */
bool BinarySearchTree::nodeExists(Node* node, string courseID) {
    if (node == nullptr) { // Base case: node is null
        return false;
    }
    if (node->course.courseID.compare(courseID) == 0) { // If courseID is found
        return true;
    }
    if (node->course.courseID.compare(courseID) > 0) { // If courseID is less, search left subtree
        return nodeExists(node->left, courseID);
    }
    else { // If courseID is greater, search right subtree
        return nodeExists(node->right, courseID);
    }
}



/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Course to be added
 * @return the new node pointer
 */
Node* BinarySearchTree::addNode(Node* node, Course course) {
    // If node is nullptr, create a new node and return it
    if (node == nullptr) {
        return new Node(course);
    }

    // If courseID is less than the current node's courseID, add it to the left sub-tree
    if (node->course.courseID.compare(course.courseID) > 0) {
        node->left = addNode(node->left, course);
    }
    // If courseID is equal to the current node's courseID, overwrite the course in the current node
    else if (node->course.courseID.compare(course.courseID) == 0) {
        node->course = course;
    }
    // If courseID is greater or equal to the current node's courseID, add it to the right sub-tree
    else {
        node->right = addNode(node->right, course);
    }

    // Return the node pointer
    return node;
}

/**
 * Traverse and print the binary search tree in order (left-root-right), starting from the input node.
 * This function will display each course's information as it traverses the tree.
 * @param node the starting point for the in-order traversal.
 */
void BinarySearchTree::inOrder(Node* node) {

    if (node != nullptr) {
        //InOrder not left
        inOrder(node->left);
        //output courseID, title, amount, fund
        displayCourse(node->course);
        //InOder right
        inOrder(node->right);
        //if node is not equal to null ptr

    }
}

/**
 * Traverse and print the binary search tree in order (left-root-right), starting from the input node.
 * This function will display each course's information as it traverses the tree.
 * @param node the starting point for the in-order traversal.
 */
void BinarySearchTree::inOrderSampleSchedule(Node* node) {

    if (node != nullptr) {
        //InOrder not left
        inOrderSampleSchedule(node->left);
        //output courseID and courseName
        cout << node->course.courseID << ", " << node->course.courseName << endl;
        //InOder right
        inOrderSampleSchedule(node->right);
        //if node is not equal to null ptr

    }
}

/**
 * Traverse and print the binary search tree in post-order (left-right-root), starting from the input node.
 * This function will display each course's information as it traverses the tree.
 * @param node the starting point for the post-order traversal.
 */
void BinarySearchTree::postOrder(Node* node) {
 
        //if node is not equal to null ptr
    if (node != nullptr) {
        //postOrder left
        postOrder(node->left);
        //postOrder right
        postOrder(node->right);
        //output courseID, title, amount, fund
        displayCourse(node->course);
    }
}

/**
 * Traverse and print the binary search tree in pre-order (root-left-right), starting from the input node.
 * This function will display each course's information as it traverses the tree.
 * @param node the starting point for the pre-order traversal.
 */
void BinarySearchTree::preOrder(Node* node) {
      // FixMe (11): Pre order root
      //if node is not equal to null ptr
    if (node != nullptr) {
        //output courseID, title, amount, fund 
        displayCourse(node->course);
        //preOrder left
        preOrder(node->left);
        //preOrder right 
        preOrder(node->right);
    }
}

/**
 * Given a binary search tree (or a subtree), find and return the node with the minimum value.
 * Since this is a binary search tree, the minimum value is located at the left-most node.
 * @param node the root of the tree (or subtree) to search.
 * @return a pointer to the Node that contains the minimum value in the tree.
 */
Node* BinarySearchTree::minValueNode(Node* node) {
    Node* current = node;
    // loop down to find the leftmost leaf
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}


/**
 * Removes a node with a specific courseID from the binary search tree. This function will recursively
 * search the tree for the node with the given courseID. Once found, it removes this node following the
 * rules of binary search tree deletion: If the node is a leaf, it's simply removed. If the node has one
 * child, replace it with its child. If the node has two children, replace it with its in-order successor.
 * @param node the starting point for the removal operation.
 * @param courseID the courseID of the course that should be removed.
 * @return a pointer to a Node, representing the new subtree after removal.
 */
Node* BinarySearchTree::removeNode(Node* node, string courseID) {
    if (node == nullptr) { // Base case: node is null
        cout << "Failed to remove: No node found with course ID " << courseID << endl;
        return node;
    }

    // Recursive calls for left and right subtrees
    if (courseID.compare(node->course.courseID) < 0) { // Search left subtree
        node->left = removeNode(node->left, courseID);
    }
    else if (courseID.compare(node->course.courseID) > 0) { // Search right subtree
        node->right = removeNode(node->right, courseID);
    }
    else { // Node with matching courseID found
        // Node with only one child or no child
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            cout << "Successfully removed node with course ID " << courseID << endl;
            return temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            cout << "Successfully removed node with course ID " << courseID << endl;
            return temp;
        }

        // Node with two children: get the inorder successor (smallest in the right subtree)
        Node* temp = minValueNode(node->right);

        // Copy the inorder successor's content to this node
        node->course = temp->course;

        // Delete the inorder successor
        node->right = removeNode(node->right, temp->course.courseID);

        cout << "Successfully removed node with course ID " << courseID << endl;
    }

    return node; // Return the new subtree
}


/**
 * Convert sorted array to balanced BST
 *
 * @param arr[] Sorted array of Course
 * @param start Starting index
 * @param end Ending index
 * @return root of the constructed balanced BST
 */
Node* BinarySearchTree::sortedArrayToBST(Course arr[], int start, int end)
{
    // Base Case
    if (start > end)
        return nullptr;

    // Get the middle element and make it root
    int mid = (start + end) / 2;
    Node* node = new Node(arr[mid]);

    // Recursively construct the left subtree and make it
    // left child of root
    node->left = sortedArrayToBST(arr, start, mid - 1);

    // Recursively construct the right subtree and make it
    // right child of root
    node->right = sortedArrayToBST(arr, mid + 1, end);

    return node;
}


//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the course information to the console (std::out)
 *
 * @param acourse struct containing the course info
 */
void displayCourse(Course acourse) {
    cout << acourse.courseID << ": " << acourse.courseName << " | Pre-requisites: ";

    // Loop through the prerequisites vector and display each one
    for (size_t i = 0; i < acourse.prerequisites.size(); ++i) {
        cout << acourse.prerequisites[i];
        if (i < acourse.prerequisites.size() - 1) { // Add comma separator except for the last element
            cout << ", ";
        }
    }

    cout << endl; // End the line after printing all prerequisites
    return;
}

// Define a comparator for sorting courses by courseID
bool compareCourses(Course a, Course b)
{
    return a.courseID < b.courseID;
}

// Parsing prerequisites (example to be used inside the loop)
vector<string> splitPrerequisites(const string& prereqs, char delimiter) {
    stringstream ss(prereqs);
    string prereq;
    vector<string> prerequisites;

    while (getline(ss, prereq, delimiter)) {
        prerequisites.push_back(prereq);
    }

    return prerequisites;
}


/**
 * Load a CSV file containing courses into a Binary Search Tree (BST)
 *
 * @param csvPath the path to the CSV file to load
 * @param bst a pointer to the Binary Search Tree where the courses will be loaded into
 *
 * This function does not return anything. It modifies the passed Binary Search Tree
 * to include the courses read from the CSV file. The courses are stored in a sorted order
 * according to their courseID to create a balanced BST.
 */
void loadCourses(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    // Create a vector to store the Courses
    vector<Course> courses;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of courses
            Course acourse;
            acourse.courseID = file[i][0];
            acourse.courseName = file[i][1];

            // Check if the prerequisites field is empty or not
            string prerequisites_str = file[i][2];
            if (!prerequisites_str.empty()) {
                acourse.prerequisites = splitPrerequisites(prerequisites_str, ',');
            }

            // Print what's being loaded
            cout << "CourseID: " << acourse.courseID << ", Course Name: " << acourse.courseName; // Fixed this line
            if (!prerequisites_str.empty()) {
                cout << ", Pre-requisites: " << prerequisites_str; // Use prerequisites_str to print prerequisites as a string
            }
            cout << endl;

            // push this course to the end of the vector
            courses.push_back(acourse);
        }

        // Sort the vector of courses by courseId
        sort(courses.begin(), courses.end(), compareCourses);

        // Convert the sorted vector to a balanced BST
        bst->root = bst->sortedArrayToBST(courses.data(), 0, courses.size() - 1); 
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, courseKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        courseKey = "98129";
        break;
    case 3:
        csvPath = argv[1];
        courseKey = argv[2];
        break;
    default:
        csvPath = "course_info.csv";
        courseKey = "98129";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all courses
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course acourse;

    cout << "Welcome to the course planner." << endl;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            //TIMING TESTING
            // Initialize a timer variable before loading courses
            //ticks = clock();

            // Complete the method call to load the Courses
            loadCourses(csvPath, bst);

            //TESTING SIZE OF FILE
            //cout << bst->Size() << " courses read" << endl;

            //TIMING TESTING
            // Calculate elapsed time and display result
            //ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            //cout << "time: " << ticks << " clock ticks" << endl;
            //cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 2:
            cout << "Here is a sample schedule:" << endl << endl;
            bst->InOrderSampleSchedule();
            break;

        case 3:

            //ask user for a course
            cout << "What course do you want to know about? ";
            cin >> courseKey;
            cin.ignore(); // to clear the newline character from the input buffer

            //convert courseKey to uppercase
            transform(courseKey.begin(), courseKey.end(), courseKey.begin(), ::toupper);


            //TIMING TESTING
            //ticks = clock();

            acourse = bst->Search(courseKey);

            //TIMING TESTING
            //ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!acourse.courseID.empty()) {
                displayCourse(acourse);
            } else {
            	cout << "Course Id " << courseKey << " not found." << endl;
            }

            //TIMING TESTING
            //cout << "time: " << ticks << " clock ticks" << endl;
            //cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;
        
        case 9: 
            cout << "Thank you for using the course planner" << endl;
            break;

        default: 
            cout << "Invalid option. Please choose a valid menu item." << endl;
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
