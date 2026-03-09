#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

// Helper function to get the current timestamp as a string
string getCurrentTimeStr() {
    time_t now = time(0);
    string dt = ctime(&now);
    dt.pop_back(); // Remove the trailing newline added by ctime
    return dt;
}

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
        username = "";
        password = "";
        phoneNumber = "";
        status = "Offline";
        lastSeen = getCurrentTimeStr();
    }
    
    User(string uname, string pwd, string phone) {
        username = uname;
        password = pwd;
        phoneNumber = phone;
        status = "Online";
        lastSeen = getCurrentTimeStr();
    }
    
    string getUsername() const { return username; }
    string getPhoneNumber() const { return phoneNumber; }
    string getStatus() const { return status; }
    string getLastSeen() const { return lastSeen; }
    
    void setStatus(string newStatus) { status = newStatus; }
    void setPhoneNumber(string phone) { phoneNumber = phone; }
    
    void updateLastSeen() {
        lastSeen = getCurrentTimeStr();
    }
    
    bool checkPassword(string pwd) const {
        return password == pwd;
    }
    
    void changePassword(string newPwd) {
        if (newPwd.length() >= 6) { //
            password = newPwd;
        } else {
            cout << "Password must be at least 6 characters." << endl;
        }
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
        sender = "";
        content = "";
        timestamp = getCurrentTimeStr();
        status = "sent";
        replyTo = nullptr;
    }
    
    Message(string sndr, string cntnt) {
        sender = sndr;
        content = cntnt;
        timestamp = getCurrentTimeStr();
        status = "sent";
        replyTo = nullptr;
    }
    
    string getContent() const { return content; }
    string getSender() const { return sender; }
    string getTimestamp() const { return timestamp; }
    string getStatus() const { return status; }
    Message* getReplyTo() const { return replyTo; }
    
    void setStatus(string newStatus) { status = newStatus; }
    void setReplyTo(Message* msg) { replyTo = msg; }
    void updateTimestamp() { timestamp = getCurrentTimeStr(); }
    
    void display() const {
        cout << "[" << timestamp << "] " << sender << ": ";
        if (replyTo != nullptr) {
            cout << "(Replying to: " << replyTo->getContent() << ") ";
        }
        cout << content << " (" << status << ")" << endl;
    }
    
    void addEmoji(string emojiCode) { //
        // Basic find-and-replace for emojis
        string replaced = content;
        size_t pos;
        while ((pos = replaced.find(":)")) != string::npos) replaced.replace(pos, 2, "😊");
        while ((pos = replaced.find(":(")) != string::npos) replaced.replace(pos, 2, "☹️");
        while ((pos = replaced.find(":D")) != string::npos) replaced.replace(pos, 2, "😄");
        while ((pos = replaced.find("<3")) != string::npos) replaced.replace(pos, 2, "❤️");
        while ((pos = replaced.find(":thumbsup:")) != string::npos) replaced.replace(pos, 10, "👍");
        content = replaced;
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
        chatName = "";
    }
    
    Chat(vector<string> users, string name) {
        participants = users;
        chatName = name;
    }
    
    virtual ~Chat() {} // Virtual destructor for memory safety
    
    string getChatName() const { return chatName; }
    
    bool hasParticipant(const string& username) const {
        return find(participants.begin(), participants.end(), username) != participants.end();
    }

    void addMessage(const Message& msg) {
        messages.push_back(msg);
    }
    
    bool deleteMessage(int index, const string& username) {
        if (index >= 0 && index < messages.size()) {
            if (messages[index].getSender() == username) { //
                messages.erase(messages.begin() + index);
                return true;
            }
        }
        return false;
    }
    
    virtual void displayChat() const {
        cout << "\n=== " << chatName << " ===" << endl;
        if (messages.empty()) {
            cout << "No messages yet." << endl;
        } else {
            for (int i = 0; i < messages.size(); i++) {
                cout << i << ". ";
                messages[i].display();
            }
        }
    }
    
    vector<Message> searchMessages(string keyword) const {
        vector<Message> results;
        for (const auto& msg : messages) {
            if (msg.getContent().find(keyword) != string::npos) {
                results.push_back(msg);
            }
        }
        return results;
    }
    
    void exportToFile(const string& filename) const {
        cout << "Exporting to file not supported in memory-only mode." << endl; //
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
    PrivateChat(string u1, string u2) : Chat({u1, u2}, "Chat between " + u1 + " and " + u2) {
        user1 = u1;
        user2 = u2;
    }
    
    void displayChat() const override {
        Chat::displayChat();
    }
    
    void showTypingIndicator(const string& username) const {
        cout << "\n[" << username << " is typing...]" << endl;
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
    GroupChat(vector<string> users, string name, string creator) : Chat(users, name) {
        admins.push_back(creator);
        if (!hasParticipant(creator)) {
            participants.push_back(creator);
        }
        description = "A new group chat";
    }
    
    void addAdmin(string newAdmin) {
        if (hasParticipant(newAdmin) && !isAdmin(newAdmin)) {
            admins.push_back(newAdmin);
        }
    }
    
    bool removeParticipant(const string& admin, const string& userToRemove) {
        if (isAdmin(admin) && hasParticipant(userToRemove)) {
            participants.erase(remove(participants.begin(), participants.end(), userToRemove), participants.end());
            admins.erase(remove(admins.begin(), admins.end(), userToRemove), admins.end());
            return true;
        }
        return false;
    }
    
    bool isAdmin(string username) const {
        return find(admins.begin(), admins.end(), username) != admins.end();
    }
    
    bool isParticipant(string username) const {
        return hasParticipant(username);
    }
    
    void setDescription(string desc) {
        description = desc;
    }
    
    void displayChat() const override {
        cout << "\n=== Group: " << chatName << " ===" << endl;
        cout << "Description: " << description << endl;
        cout << "Participants: " << participants.size() << endl;
        Chat::displayChat();
    }
    
    void sendJoinRequest(const string& username) {
        cout << username << " has requested to join the group " << chatName << "." << endl;
    }
};

// ========================
//    WHATSAPP APP CLASS
// ========================
class WhatsApp {
private:
    vector<User> users;
    vector<Chat*> chats;
    int currentUserIndex;

    int findUserIndex(string username) const {
        for (int i = 0; i < users.size(); i++) {
            if (users[i].getUsername() == username) return i;
        }
        return -1;
    }
    
    bool isLoggedIn() const {
        return currentUserIndex != -1;
    }
    
    string getCurrentUsername() const {
        if (isLoggedIn()) return users[currentUserIndex].getUsername();
        return "";
    }
    
public:
    WhatsApp() : currentUserIndex(-1) {}
    
    ~WhatsApp() {
        for (Chat* chat : chats) {
            delete chat; // Prevent memory leaks
        }
    }
    
    void signUp() {
        string uname, pwd, phone;
        cout << "Enter username: ";
        cin >> uname;
        
        if (findUserIndex(uname) != -1) { //
            cout << "Error: Username already exists.\n";
            return;
        }
        
        cout << "Enter password (min 6 chars): ";
        cin >> pwd;
        if (pwd.length() < 6) { //
            cout << "Error: Password too short.\n";
            return;
        }
        
        cout << "Enter phone number: ";
        cin >> phone;
        
        users.push_back(User(uname, pwd, phone));
        cout << "Registration successful!\n";
    }
    
    void login() {
        string uname, pwd;
        cout << "Enter username: ";
        cin >> uname;
        cout << "Enter password: ";
        cin >> pwd; // (Note: hiding password in standard console requires OS-specific libs, standard cin is used for simplicity per constraints)
        
        int idx = findUserIndex(uname);
        if (idx != -1 && users[idx].checkPassword(pwd)) {
            currentUserIndex = idx;
            users[currentUserIndex].setStatus("Online");
            cout << "Login successful. Welcome, " << uname << "!\n";
        } else {
            cout << "Invalid username or password.\n";
        }
    }
    
    void startPrivateChat() {
        string target;
        cout << "Enter username to chat with: ";
        cin >> target;
        
        if (findUserIndex(target) == -1) {
            cout << "User not found.\n";
            return;
        }
        if (target == getCurrentUsername()) {
            cout << "You cannot chat with yourself.\n";
            return;
        }
        
        chats.push_back(new PrivateChat(getCurrentUsername(), target));
        cout << "Private chat started with " << target << ".\n";
    }
    
    void createGroup() {
        string name, participant;
        vector<string> participants;
        participants.push_back(getCurrentUsername());
        
        cout << "Enter group name: ";
        cin.ignore();
        getline(cin, name);
        
        cout << "Enter participant usernames (type 'done' to finish): \n";
        while (true) {
            cin >> participant;
            if (participant == "done") break;
            if (findUserIndex(participant) != -1) {
                participants.push_back(participant);
                cout << participant << " added.\n";
            } else {
                cout << "User not found.\n";
            }
        }
        
        if (participants.size() >= 2) { //
            chats.push_back(new GroupChat(participants, name, getCurrentUsername()));
            cout << "Group created successfully.\n";
        } else {
            cout << "Group needs at least 2 participants.\n";
        }
    }
    
    void viewChats() {
        vector<Chat*> myChats;
        cout << "\n--- Your Chats ---\n";
        for (Chat* chat : chats) {
            if (chat->hasParticipant(getCurrentUsername())) {
                myChats.push_back(chat);
                cout << myChats.size() << ". " << chat->getChatName() << "\n";
            }
        }
        
        if (myChats.empty()) {
            cout << "You have no active chats.\n";
            return;
        }
        
        cout << "Enter chat number to open (0 to cancel): ";
        int choice;
        cin >> choice;
        
        if (choice > 0 && choice <= myChats.size()) {
            Chat* selectedChat = myChats[choice - 1];
            chatInteractionLoop(selectedChat);
        }
    }
    
    void chatInteractionLoop(Chat* chat) {
        while (true) {
            chat->displayChat();
            cout << "\n1. Send Message\n2. Delete Message\n3. Back\nChoice: ";
            int choice;
            cin >> choice;
            
            if (choice == 1) {
                // Simulate typing indicator for private chats
                PrivateChat* pc = dynamic_cast<PrivateChat*>(chat);
                if (pc) pc->showTypingIndicator(getCurrentUsername());
                
                string content;
                cout << "Enter message: ";
                cin.ignore();
                getline(cin, content);
                
                Message msg(getCurrentUsername(), content);
                msg.addEmoji(content); // Apply emojis
                chat->addMessage(msg);
            } 
            else if (choice == 2) {
                int index;
                cout << "Enter message ID to delete: ";
                cin >> index;
                if (chat->deleteMessage(index, getCurrentUsername())) {
                    cout << "Message deleted.\n";
                } else {
                    cout << "Failed to delete message. (You can only delete your own messages).\n"; //
                }
            } 
            else if (choice == 3) {
                break;
            }
        }
    }
    
    void logout() {
        if (isLoggedIn()) {
            users[currentUserIndex].updateLastSeen(); //
            users[currentUserIndex].setStatus("Offline");
            currentUserIndex = -1;
            cout << "Logged out successfully.\n";
        }
    }
    
    void run() {
        cout << "======================================\n";
        cout << "   WHATSAPP-LIKE MESSAGING SYSTEM\n";
        cout << "======================================\n";
        
        while (true) {
            if (!isLoggedIn()) {
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";
                int choice;
                if (!(cin >> choice)) { // Clear bad input
                    cin.clear();
                    cin.ignore(10000, '\n');
                    continue;
                }
                
                if (choice == 1) login();
                else if (choice == 2) signUp();
                else if (choice == 3) break;
            }
            else {
                cout << "\nLogged in as: " << getCurrentUsername() << "\n";
                cout << "1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Logout\nChoice: ";
                int choice;
                if (!(cin >> choice)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    continue;
                }
                
                if (choice == 1) startPrivateChat();
                else if (choice == 2) createGroup();
                else if (choice == 3) viewChats();
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