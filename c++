#include <iostream>
#include <string>
#include <vector>
#include <sstream>


using namespace std;

class Member {
public:
    int id;
    string name;
    string surname; 
    int subscription_months;
    Member(int id, string name, string surname): id(id), name(name), surname(surname), subscription_months(0) {}
};

vector<Member> member_list;

void print_member_list() {
    if (member_list.empty()) {
        cout << "No members in the system" << endl;
    } else {
        for (const Member& member : member_list) {
            cout << "Member " << member.id << " : " << member.name
                 << " "<< member.surname << ", subscription valid for " << member.subscription_months << " months" << endl;
        }
    }
}

void create_member(int id, string name, string surname) {
    if (member_list.size() >= 10) {
        cout << "Cannot perform this operation. Maximum number of members reached." << endl;
        return;
    }
    if (id == 0) {
        cout << "Cannot perform this operation. Invalid member ID." << endl;
        return;
    }
    for (const Member& member : member_list) {
        if (member.id == id) {
            cout << "Cannot perform this operation. Member with this ID already exists." << endl;
            return;
        }
    }
    member_list.push_back(Member(id, name, surname));
    print_member_list();
}

void delete_member(int id) {
    if (id == 0) {
        cout << "Cannot perform this operation. Invalid member ID." << endl;
        return;
    }
    for (auto it = member_list.begin(); it != member_list.end(); ++it) {
        if (it->id == id) {
            member_list.erase(it);
            print_member_list();
            return;
        }
    }
    cout << "Cannot perform this operation. Member with this ID does not exist." << endl;
}

void extend_subscription(int id, int n) {
    if (id == 0) {
        cout << "Cannot perform this operation. Invalid member ID." << endl;
        return;
    }
    for (auto& member : member_list) {
        if (member.id == id) {
            member.subscription_months += n;
            print_member_list();
            return;
        }
    }
    cout << "Cannot perform this operation. Member with this ID does not exist." << endl;
}

void cancel_subscription(int id) {
    if (id == 0) {
        cout << "Cannot perform this operation. Invalid member ID." << endl;
        return;
    }
    for (auto& member : member_list) {
        if (member.id == id) {
            member.subscription_months = 0;
            print_member_list();
            return;
        }
    }
    cout << "Cannot perform this operation. Member with this ID does not exist." << endl;
}

int main() {
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        string command;
        ss >> command;
        if (command == "create") {
        int id;
        string name;
        string surname;
        ss >> id >> name>>surname;
        create_member(id, name, surname);
    } else if (command == "delete") {
        int id;
        ss >> id;
        delete_member(id);
    } else if (command == "extend") {
        int id, n;
        ss >> id >> n;
        extend_subscription(id, n);
    } else if (command == "cancel") {
        int id;
        ss >> id;
        cancel_subscription(id);
    } else if (command == "quit") {
        cout << "Exiting program." << endl;
        break;
    } else {
        cout << "Invalid command. Please try again." << endl;
    }
}
return 0;
}
