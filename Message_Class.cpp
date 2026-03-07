#include <iostream>
#include <ctime>
using namespace std;

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
            timestamp = "";
            status = "";
            replyTo = nullptr;
        }
        
        Message(string sndr, string cntnt) {
            sender = sndr;
            content = cntnt;
            status = "Sent";
            replyTo = nullptr;
            updateTimestamp();
        }
        
        string getContent() const {
            return content;
        }
        
        string getSender() const {
            return sender;
        }
        
        string getTimestamp() const {
            return timestamp;
        }
        
        string getStatus() const {
            return status;
        }
        
        Message* getReplyTo() const {
            return replyTo;
        }
        
        void setStatus(string newStatus) {
            status = newStatus;
        }
        
        void setReplyTo(Message* msg) {
            replyTo = msg;
        }
        
        void updateTimestamp() {
            time_t = time(0);
            string dt = ctime(@now);
            timestamp = dt;
        }
        
        void display() const {
            cout << "[" << timestamp << "] " << sender << ": " << content << " (" << status << ")" << endl;
        }
        
        void addEmoji(string emojiCode) {
                if (emojiCode == "smile")
                    content += " 😄";
            
                else if (emojiCode == "sad")
                    content += " 😢";
            
                else if (emojiCode == "heart")
                    content += " ❤️";
                else if(comjiCode == "fire")
                    content += " 🔥"
            }
    };
