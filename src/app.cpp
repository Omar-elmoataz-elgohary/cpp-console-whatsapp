#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// ========================
//       USER CLASS
// ========================
class User {
private:
    string username;
    string password;
    string phoneNumber;
    string status;
    string lastSeen;
    
public:
    User() {
        // TODO: Implement default constructor
    }
    
    User(string uname, string pwd, string phone) {
        // TODO: Implement parameterized constructor
    }
    
    string getUsername() const {
        // TODO: Implement getter
        return "";
    }
    
    string getPhoneNumber() const {
        // TODO: Implement getter
        return "";
    }
    
    string getStatus() const {
        // TODO: Implement getter
        return "";
    }
    
    string getLastSeen() const {
        // TODO: Implement getter
        return "";
    }
    
    void setStatus(string newStatus) {
        // TODO: Implement setter
    }
    
    void setPhoneNumber(string phone) {
        // TODO: Implement setter
    }
    
    void updateLastSeen() {
        // TODO: Implement last seen update
    }
    
    bool checkPassword(string pwd) const {
        // TODO: Implement password check
        return false;
    }
    
    void changePassword(string newPwd) {
        // TODO: Implement password change
    }
};

// ========================
//      MESSAGE CLASS
// ========================
class Message {
private:
    string sender;
    string content;
    string timestamp;
    string status;
    Message* replyTo;
    
public:
    Message() {
        // TODO: Implement default constructor
    }
    
    Message(string sndr, string cntnt) {
        // TODO: Implement parameterized constructor
    }
    
    string getContent() const {
        // TODO: Implement getter
        return "";
    }
    
    string getSender() const {
        // TODO: Implement getter
        return "";
    }
    
    string getTimestamp() const {
        // TODO: Implement getter
        return "";
    }
    
    string getStatus() const {
        // TODO: Implement getter
        return "";
    }
    
    Message* getReplyTo() const {
        // TODO: Implement getter
        return nullptr;
    }
    
    void setStatus(string newStatus) {
        // TODO: Implement setter
    }
    
    void setReplyTo(Message* msg) {
        // TODO: Implement setter
    }
    
    void updateTimestamp() {
        // TODO: Implement timestamp update
    }
    
    void display() const {
        // TODO: Implement message display
    }
    
    void addEmoji(string emojiCode) {
        // TODO: Implement emoji support
    }
};

// ========================
//       CHAT CLASS (BASE)
// ========================
class Chat {
protected:
    vector<string> participants;
    vector<Message> messages;
    string chatName;
    
public:
    Chat() {
        // TODO: Implement default constructor
    }
    
    Chat(vector<string> users, string name) {
        // TODO: Implement parameterized constructor
    }
    
    void addMessage(const Message& msg) {
        // TODO: Implement message addition
    }
    
    bool deleteMessage(int index, const string& username) {
        // TODO: Implement message deletion
        return false;
    }
    
    virtual void displayChat() const {
        // TODO: Implement chat display
    }
    
    vector<Message> searchMessages(string keyword) const {
        // TODO: Implement message search
        return {};
    }
    
    void exportToFile(const string& filename) const {
        // TODO: Implement export to file
    }
};

// ========================
//     PRIVATE CHAT CLASS
// ========================
class PrivateChat : public Chat {
private:
    string user1;
    string user2;
    
public:
    PrivateChat(string u1, string u2) {
        // TODO: Implement constructor
    }
    
    void displayChat() const override {
        // TODO: Implement private chat display
    }
    
    void showTypingIndicator(const string& username) const {
        // TODO: Implement typing indicator
    }
};

// ========================
//      GROUP CHAT CLASS
// ========================
class GroupChat : public Chat {
private:
    vector<string> admins;
    string description;
    
public:
    GroupChat(vector<string> users, string name, string creator) {
        // TODO: Implement constructor
    }
    
    void addAdmin(string newAdmin) {
        // TODO: Implement add admin
    }
    
    bool removeParticipant(const string& admin, const string& userToRemove) {
        // TODO: Implement remove participant
        return false;
    }
    
    bool isAdmin(string username) const {
        // TODO: Implement admin check
        return false;
    }
    
    bool isParticipant(string username) const {
        // TODO: Implement participant check
        return false;
    }
    
    void setDescription(string desc) {
        // TODO: Implement set description
    }
    
    void displayChat() const override {
        // TODO: Implement group chat display
    }
    
    void sendJoinRequest(const string& username) {
        // TODO: Implement join request
    }
};

// ========================
//    WHATSAPP APP CLASS.   (DONE)
// ========================
class WhatsApp {
private:
    vector<User> users;
    vector<Chat*> chats;
    int currentUserIndex;
    
    int findUserIndex(string username) const {
        for (int i = 0; i < users.size(); i++) {
            if (users[i].getUsername()== username)
                return i ; 
        } 
        return -1;
    }
    
    bool isLoggedIn() const {
       if (currentUserIndex != -1)
            return true;
        return false;
    }
    
    string getCurrentUsername() const {
        if (isLoggedIn())
            return users[currentUserIndex].getUsername();
        return "";
    }
    
public:
    WhatsApp() : currentUserIndex(-1) {}
    
    void signUp() {
        cout << "=== Sign Up ===\n";
        string username, password , phone ;
        cout << "Enter username : ";
        cin >> username;

        if (findUserIndex(username) != -1){
            cout <<"Username already exists \n";
            return;    
        }
        cout <<"Enter password: ";
        cin >> password;

        if (password.length() < 6){
            cout <<"Password must be at least 6 characters long \n";
            return;
        }
        cout <<"Enter phone number:";
        cin >> phone;
        
        User newUser(username, password, phone);
        users.push_back(newUser);
        
        cout << "Account created successfully.\n";
    }
    
    void login() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        
        int index = findUserIndex(username);
        if (index != -1 && users[index].checkPassword(password)) {
            currentUserIndex = index;
            users[currentUserIndex].updateLastSeen();
            cout << "Login successful. Welcome, " << username << "!\n";
        }
        else {
            cout << "Invalid username or password.\n";
        }
    }
    
    void startPrivateChat() {
        string otherUsername;
        cout << "Enter the username of the person you want to chat with: ";
        cin >> otherUsername;
        
        int otherIndex = findUserIndex(otherUsername);
        if (otherIndex == -1) {
            cout << "User not found.\n";
            return;
        }
        
        PrivateChat* newChat = new PrivateChat(getCurrentUsername(), otherUsername);
        chats.push_back(newChat);
        
        cout << "Private chat started with " << otherUsername << ".\n";
    }
    
    void createGroup() {
        string groupName ;
        int numParticipants;
        
        cout << "Enter group name: ";
        cin >> groupName;
        cout << "Enter number of participants: ";
        cin >> numParticipants;
        
        vector<string> participants;
        participants.push_back(getCurrentUsername()); 
        
        for (int i = 0; i < numParticipants; i++) {
            string participantUsername;
            cout << "Enter username of participant " << (i + 1) << ": ";
            cin >> participantUsername;
            
            if (findUserIndex(participantUsername) == -1) {
                cout << "User " << participantUsername << " not found. Try again.\n";
                i--;
                continue;
            }
            participants.push_back(participantUsername);
        }
        
        GroupChat* newGroup = new GroupChat(participants, groupName, getCurrentUsername());

        chats.push_back(newGroup);
        
        cout << "Group chat '" << groupName << "' created successfully.\n";
    }
    
    /*
    void viewChats() const {
        string currentUser = getCurrentUsername();
        cout << "Your Chats:\n";
        int count = 0;
        for (int i =0 ; i < chats.size(); i++) {
            if (chats[i]->hasParticipant(currentUser)) {
                cout << (i + 1) << ". " << chats[i]->getName() << "\n";
                count++;
            }
        }
        if (count == 0) {
            cout << "No chats available.\n";
        }
    }
    */
    void logout() {
        if (isLoggedIn()) {
            users[currentUserIndex].updateLastSeen();
            currentUserIndex = -1;
            cout << "Logged out successfully.\n";
        }
        else {
            cout << "No user is currently logged in.\n";
        }
    }
    
    void run() {
        while (true) {
            if (!isLoggedIn()) {
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";
                int choice;
                cin >> choice;
                
                if (choice == 1) login();
                else if (choice == 2) signUp();
                else if (choice == 3) break;
            }
            else {
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Logout\nChoice: ";
                int choice;
                cin >> choice;
                
                if (choice == 1) startPrivateChat();
                else if (choice == 2) createGroup();
                //else if (choice == 3) viewChats();
                else if (choice == 4) logout();
            }
        }
    }
};

// ========================
//          MAIN
// ========================
int main() {
    WhatsApp whatsapp;
    whatsapp.run();
    return 0;
}
