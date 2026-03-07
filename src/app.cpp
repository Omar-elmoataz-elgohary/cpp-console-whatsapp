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
    //checks if there is less than 2 members then create the group
    //admin appears in admins and participants
    GroupChat(vector<string> users, string name, string creator) {
    if(users.size()<2){
    cout<<"Insufficient amount of members";
    }
    else{
        for(int i=0;i<users.size();i++){
            participants.push_back(users[i]);
            }
        chatName=name;
        participants.push_back(creator);
        admins.push_back(creator);
        } //handel lower than 2 participants
    }
    // checks if the member is already an admin then adds him
    void addAdmin(string newAdmin) {
       if(isParticipant(newAdmin)==true){
        if(isAdmin(newAdmin)==false){
            admins.push_back(newAdmin);
        }else{cout<<"Is already admin .";}
       } else{cout<<"Not in groupchat .";}
    }
    // checks if the admin and member are in the group
    // may have a run time problem due to multiple for loops needs to check if helper functions (is admin , is participant) is used else where before modifing
    // admin removing admin not mentioned so it wont work here
    // when true writes the member as 0 becuase the delete function have time problems

    bool removeParticipant(const string& admin, const string& userToRemove) {

        if(isAdmin(admin)==1 && isParticipant(userToRemove)==1){
            for(int i=0;i<participants.size();i++){
                if(participants[i]==userToRemove){
                    participants[i]='0';
                    return true;
                }
            }
        }


        return false;
        //false=didn't remove   true=removed
    }
    // checks with tome o(n)

    bool isAdmin(string username) const {
         for(int i=0;i<admins.size();i++){
                if(admins[i]==username){
                    return true;
                }
            }

        return false;
        // true = is admin   false = not admin
    }
     // checks with tome o(n)

    bool isParticipant(string username) const {
        for(int i=0;i<participants.size();i++){
                if(participants[i]==username){
                    return true;
                }
            }

        return false;
        // true = is member   false = not member
    }
    //normal setter

    void setDescription(string desc) {
        description=desc;
    }
    // display in format of  admins:
    //                       {....,....,...}
    //                       participants:
    //                       {...,...,...}
    //                       description:
    //                       .........
    //                       --chatname--
    //                       messages

    void displayChat() const override {
        cout<<"Admins :\n"<<"{";
        for(int i=0;i<admins.size() ;i++){
            cout<<admins[i];
            if(i<admins.size()-1){cout<<" , ";}
        }
        cout<<"}\n"<<"Participants :\n"<<"{";

        for(int i=0;i<participants.size() ;i++){
            cout<<participants[i];
            if(i<participants.size()-1){cout<<" , ";}
        }
        cout<<"}\n";
        cout<<"Description :\n"<<description<<"\n";
        for(int i=0 ;i<messages.size();i++){

        }

      Chat::displayChat();

    }
     // solution i came up with is to create a private chat between the owner and requester
     // send a formated message saying "i would like to join the group chat"
     // modifing the function to return the chat address so we .push_back it to the chats vector
    PrivateChat* sendJoinRequest(const string& username) {
        string content ="i would like to join the group chat";
        PrivateChat* cformat= new PrivateChat(username,admins[0]);
        Message formated(username,content);
        cformat->addMessage(formated);
        return cformat ;
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
        // TODO: Implement user search
        return -1;
    }

    bool isLoggedIn() const {
        // TODO: Implement login check
        return false;
    }

    string getCurrentUsername() const {
        // TODO: Implement get current user
        return "";
    }

public:
    WhatsApp() : currentUserIndex(-1) {}

    void signUp() {
        // TODO: Implement user registration
    }

    void login() {
        // TODO: Implement user login
    }

    void startPrivateChat() {
        // TODO: Implement private chat creation
    }

    void createGroup() {
        // TODO: Implement group creation
    }

    void viewChats() const {
        // TODO: Implement chat viewing
    }

    void logout() {
        // TODO: Implement logout
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
