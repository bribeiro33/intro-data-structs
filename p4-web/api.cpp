// Project UID c1f28c309e55405daf00c565d57ff9ad

#include <list>
#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <utility>
#include <algorithm>
#include "json.hpp"
using namespace std;
using nlohmann::json;


class OHQueue {
public:
    OHQueue () {
        size = 0;
    }
    
    //GET REQUESTS
    void urls_supported () {
        string version;
        string content_type1;
        string content_type2;
        string filler;
        cin >> version >> filler >> filler >> filler >> content_type1 >> content_type2 >>
        filler >> filler;
        string print_info[] = {version, content_type1, content_type2};
        
        json output = {
            {"queue_head_url", "http://localhost/queue/head/"},
            {"queue_list_url", "http://localhost/queue/"},
            {"queue_tail_url", "http://localhost/queue/tail/"},
        };
        print(output, print_info, 200, "OK");
    }
    
    void head_of_queue() {
        if (size <= 0) {
            error_print(true);
        }
        else {
            string version;
            string content_type1;
            string content_type2;
            string filler;
            cin >> version >> filler >> filler >> filler >> content_type1 >> content_type2
            >> filler >> filler;
            string print_info[] = {version, content_type1, content_type2};
            Student first = queue.front();
            json front = {
                {"location", first.location},
                {"position", first.position},
                {"uniqname", first.uniqname},
            };
            print(front, print_info, 200, "OK");
        }
    }
    
    void all_of_queue() {
        string version;
        string content_type1;
        string content_type2;
        string filler;
        cin >> version >> filler >> filler >> filler >> content_type1 >> content_type2 >>
        filler >> filler;
        string print_info[] = {version, content_type1, content_type2};
        
        json array;
        std::list<Student>::iterator s;
        for (s = queue.begin(); s != queue.end(); ++s) {
            json next = {
                {"location", s->location},
                {"position", s->position},
                {"uniqname", s->uniqname},
            };
            array.push_back(next);
        }
        json output = {
            {"count", size},
            {"results", array},
        };
        print(output, print_info, 200, "OK");
    }
    
    // POST REQUEST
    void create_student() {
        string version;
        string content_type1;
        string content_type2;
        string filler;
        cin >> version >> filler >> filler >> filler >> content_type1 >> content_type2 >>
        filler >> filler;
        string print_info[] = {version, content_type1, content_type2};
        
        json input;
        cin >> input;
        int position = size + 1;
        add_student(input["uniqname"], input["location"], position);
        json output = {
            {"location", input["location"]},
            {"position", position},
            {"uniqname", input["uniqname"]},
        };
        print (output, print_info, 201, "Created");
    }
    
    // DELETE REQUESTS
    void delete_student() {
        if (size > 0) {
            queue.pop_back();
            size--;
            string version;
            string content_type1;
            string content_type2;
            string filler;
            cin >> version >> filler >> filler >> filler >> content_type1 >> content_type2
            >> filler >> filler;
            string print_info[] = {version, content_type1, content_type2};
            json output = {};
            print(output, print_info, 204, "No Content");
        }
        else {
            error_print(false);
        }
    }
    
    void error_print(bool empty) {
        string version;
        string content_type1;
        string content_type2;
        int length;
        string filler;
        cin >> version >> filler >> filler >> filler >> content_type1 >> content_type2 >>
        filler >> length;
        json error;
        if (length > 2) {
            cin >> error;
        }
        else if (length > 0) {
            char in;
            cin >> in >> in;
        }
        cout << version << " 400 Bad Request" << endl;
        cout << "Content-Type: " << content_type1 << " " << content_type2 << endl;
        cout << "Content-Length: 0" << endl << endl;
    }
    
private:
    struct Student {
        string uniqname;
        string location;
        int position;
        
        Student(string uniqname_in, string location_in, int position_in) {
            uniqname = uniqname_in;
            location = location_in;
            position = position_in;
        }
    };
    list<Student> queue;
    int size;
    
    
    void add_student(string uniqname, string location, int position) {
        Student s (uniqname, location, position);
        queue.push_back(s);
        size++;
    }
    
    void print(json output, string print_info[], int code, string name) {
        string json_print = output.dump(4) + "\n";
        size_t length = json_print.length();
        cout << print_info[0] << " " << code << " " << name << endl;
        cout << "Content-Type: " << print_info[1] << " " << print_info[2] << endl;
        if (code != 204) {
            cout << "Content-Length: " << length << endl << endl;
            cout << json_print;
        }
        else {
            cout << "Content-Length: 0" << endl << endl;
        }
    }
};

int main() {
    OHQueue office;
    string method;
    string endpoint;
    
    while (cin >> method >> endpoint) {
        if (method == "POST" && endpoint == "/api/queue/tail/") {
            office.create_student();
        }
        else if (method == "GET") {
            if (endpoint == "/api/"){
                office.urls_supported();
            }
            else if (endpoint == "/api/queue/head/") {
                office.head_of_queue();
            }
            else if (endpoint == "/api/queue/") {
                office.all_of_queue();
            }
            else {
                office.error_print(false);
            }
        }
        else if (method == "DELETE" && endpoint == "/api/queue/head/") {
            office.delete_student();
        }
        else {
            office.error_print(false);
        }
    }
    return 0;
}
