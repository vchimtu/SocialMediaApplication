#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

// User class definition
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

// Message class definition
class Message {
public:
    string sender;
    string receiver;
    string content;
    time_t timestamp;

    Message() {};

    Message(string sender, string receiver, string content) {
        this->sender = sender;
        this->receiver = receiver;
        this->content = content;
        this->timestamp = time(0);
    }

    void displayMessage() {
        cout << "Sender: " << sender << ", Receiver: " << receiver << ", Content: " << content << ", Timestamp: " << ctime(&timestamp);
    }
};

// SocialGroup class definition
class SocialGroup {
public:
    string groupName;
    vector<pair<string, string>> messages;
    set<string> members;

    SocialGroup() {};

    SocialGroup(string groupName) {
        this->groupName = groupName;
    }

    void addMember(string userName) {
        members.insert(userName);
    }

    void addMessage(string userName, string content) {
        messages.push_back({userName, content});
    }

    void displayMessages() {
        cout << "Messages in Group: " << groupName << "\n";
        for (auto &msg : messages) {
            cout << "User: " << msg.first << ", Message: " << msg.second << "\n";
        }
    }
};

// Global variables
map<string, User> mapUserName;
map<string, set<string>> Friends;

// Function to add a user
void addUser(string userName, User user) {
    if (mapUserName.find(userName) == mapUserName.end()) {
        mapUserName[userName] = user;
    } else {
        cout << "Username Already Taken\n";
    }
}

// Function to make two users friends
void makeThemFriend(string userName1, string userName2) {
    if (mapUserName.find(userName1) != mapUserName.end() && mapUserName.find(userName2) != mapUserName.end()) {
        Friends[userName1].insert(userName2);
        Friends[userName2].insert(userName1);
    } else {
        cout << "One or both usernames do not exist\n";
    }
}

// Function to display all users
void displayAllUsers() {
    for (auto &i : mapUserName) {
        cout << "Username: " << i.first << ", Name: " << i.second.firstName << " " << i.second.lastName << "\n";
    }
}

// Function to display all friendships
void displayAllFriendships() {
    for (auto &i : Friends) {
        cout << i.first << " is friends with: ";
        for (auto &j : i.second) {
            cout << j << " ";
        }
        cout << "\n";
    }
}

// Function to display mutual friends
void displayMutualFriends(string userName1, string userName2) {
    if (mapUserName.find(userName1) == mapUserName.end() || mapUserName.find(userName2) == mapUserName.end()) {
        cout << "One or both usernames do not exist.\n";
        return;
    }

    set<string> friends1 = Friends[userName1];
    set<string> friends2 = Friends[userName2];

    cout << "Mutual friends between " << userName1 << " and " << userName2 << ":\n";

    for (const auto &friend1 : friends1) {
        if (friends2.find(friend1) != friends2.end()) {
            cout << "- " << friend1 << "\n";
        }
    }
}

// Main function
int main() {
    int choice;
    string userName, firstName, lastName, gender;
    int age;
    string userName1, userName2;
    User newUser;
    Message message;
    SocialGroup group("Goa Trip");

    while (true) {
        cout << "1. Add User\n2. Make Friends\n3. Display All Users\n4. Display All Friendships\n5. Display Mutual Friends\n6. Send Message\n7. Add Group Member\n8. Display Group Messages\n9. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Username: ";
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
            cout << "Enter First Username: ";
            cin >> userName1;
            cout << "Enter Second Username: ";
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
            cout << "Enter First Username: ";
            cin >> userName1;
            cout << "Enter Second Username: ";
            cin >> userName2;
            displayMutualFriends(userName1, userName2);
            break;
        case 6:
            cout << "Enter Sender Username: ";
            cin >> userName1;
            cout << "Enter Receiver Username: ";
            cin >> userName2;
            cout << "Enter Message Content: ";
            cin.ignore();
            getline(cin, message.content);
            message = Message(userName1, userName2, message.content);
            message.displayMessage();
            group.addMessage(userName1, message.content);
            break;
        case 7:
            cout << "Enter Username to add to group: ";
            cin >> userName;
            group.addMember(userName);
            break;
        case 8:
            group.displayMessages();
            break;
        case 9:
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}
