#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

class User {
public:
    string firstName;
    string lastName;
    int age;
    string gender;

    User() {};

    User(string firstName, string lastName, int age, string gender) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->age = age;
        this->gender = gender;
    }
};

map<string, User> mapUserName;
map<string, set<string>> Friends;

void addUser(string userName, User user) {
    if (mapUserName.find(userName) == mapUserName.end()) {
        mapUserName[userName] = user;
    } else {
        cout << "UserName Already Taken\n";
    }
}

void makeThemFriend(string userName1, string userName2) {
    if (mapUserName.find(userName1) != mapUserName.end() && mapUserName.find(userName2) != mapUserName.end()) {
        Friends[userName1].insert(userName2);
        Friends[userName2].insert(userName1);
    } else {
        cout << "One or both usernames do not exist\n";
    }
}

void displayAllUsers() {
    for (auto i : mapUserName) {
        cout << "UserName: " << i.first << ", Name: " << i.second.firstName << " " << i.second.lastName << "\n";
    }
}

void displayAllFriendships() {
    for (auto i : Friends) {
        cout << i.first << " is friends with: ";
        for (auto j : i.second) {
            cout << j << " ";
        }
        cout << "\n";
    }
}

void displayMutualFriends(string userName1, string userName2) {
    if (mapUserName.find(userName1) == mapUserName.end() || mapUserName.find(userName2) == mapUserName.end()) {
        cout << "One or both usernames do not exist." << endl;
        return;
    }

    set<string> friends1 = Friends[userName1];
    set<string> friends2 = Friends[userName2];

    cout << "Mutual friends between " << userName1 << " and " << userName2 << ":" << endl;

    for (const auto& friend1 : friends1) {
        if (friends2.find(friend1) != friends2.end()) {
            cout << "- " << friend1 << endl;
        }
    }
}

int main() {
    int choice;
    string userName, firstName, lastName, gender;
    int age;
    string userName1, userName2;
    User newUser;

    while (true) {
        cout << "1. Add User\n2. Make Friends\n3. Display All Users\n4. Display All Friendships\n5. Display Mutual Friends\n6. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter UserName: ";
            cin >> userName;
            cout << "Enter First Name: ";
            cin >> firstName;
            cout << "Enter Last Name: ";
            cin >> lastName;
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Gender: ";
            cin >> gender;
            newUser = User(firstName, lastName, age, gender);
            addUser(userName, newUser);
            break;
        case 2:
            cout << "Enter First UserName: ";
            cin >> userName1;
            cout << "Enter Second UserName: ";
            cin >> userName2;
            makeThemFriend(userName1, userName2);
            break;
        case 3:
            displayAllUsers();
            break;
        case 4:
            displayAllFriendships();
            break;
        case 5:
            cout << "Enter First UserName: ";
            cin >> userName1;
            cout << "Enter Second UserName: ";
            cin >> userName2;
            displayMutualFriends(userName1, userName2);
            break;
        case 6:
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}
