// Project UID db1f506d06d84ab787baf250c265e24e
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <utility>
#include <cmath>
#include "csvstream.h"

using namespace std; 
//using Pair_type = std::pair<string, string>;

//template <typename Key_type, typename Elem_type>
class Classifier{
    private: 
    map<string, map<string, int> > training_map; 
    map<string, int> label_map;
    map<string, int> word_map;
    map<string, float> prob_map; 
    int num_posts = 0;
    set<string> all_words;
    


    //Map<pair<string,string>, int> test_map; 
    public:
    //Big 3 

    // EFFECTS: Returns a set containing the unique "words" in the original
    //          string, delimited by whitespace.
    set<string> unique_words(const string &str) {
        istringstream source(str);
        set<string> words;
        string word;

        // Read word by word from the stringstream and insert into the set
        while (source >> word) {
            words.insert(word);
        }
        return words;
    }

    //Effects: Takes in string and edits map w/ training_data
    //Modifies: training_map
    void training_map_intake(std::istream& fin, bool debug){
        string junk;
        string label; 
        string words;
        while (getline(fin, junk)) {
            label = ""; words = "";
            getline(fin, junk, ',');
            getline(fin, junk, ',');
            getline(fin, label, ',');
            getline(fin, words, '\n');
            

            cout << "   label = " << label << ", content = " << words << endl; 
            
            set<string> unique = unique_words(words); 
            set<string>::iterator it = unique.begin();
            while (it != unique.end()){
                training_map[label][*it]++;
                //word_map[*it] = word_map[*it] + 1; 
                it++;
            }
            
            //to keep track of all unique words
            all_words.insert(unique.begin(), unique.end()); 
            




            // label_map[label] = label_map[label] + 1;
            

            ++num_posts;
            //training_log_prob(label);
        }

        cout << "trained on " << num_posts << " examples" << endl;
        if (debug){
            cout << "vocabulary size = " << all_words.size() << endl; 
        }
        cout << endl; 

        // if (debug){
        //     cout << "classes: " << endl; 
        //     map<string, int> ::iterator it;
        //     map<string, int> ::iterator ite;
        //     for (it = word_map.begin(); it != word_map.end(); it++){
        //         cout << "    " << it->first << ", " << it->second 
        //<< "examples, log-prior = "
        //         << log_prior(it->first) << endl;
        //     }

        //     cout << "classifier parameters: " << endl; 
        //     for (it = word_map.begin(); it != word_map.end(); it++){
        //         for (ite = training_map[it->first].begin(); ite 
        //!= training_map[it->first].end(); ite++){
        //             cout << it->first << ":" << ite->first << ", count = " 
        //<< ite->second << 
        //             ", log_likelihood = " << training_log_prob(it->first) << endl; 
        //         }
        //     }
        //     cout << endl; 
            
        //}
    }

    float log_prior(string label) {
        int posts_with_c = label_map[label];
        float log_prior = log(posts_with_c/num_posts);
        return log_prior;
    }

    float training_log_prob(string label){

        int posts_with_c = label_map[label];
        float log_prior = log(posts_with_c/num_posts);

        float log_likelihood = 0;
        map<string, int>::iterator it;// = training_map[label].begin(); 
        //map<string, map<string, int> >::iterator it; 


        for (it = training_map[label].begin(); it != training_map[label].end(); it++){
            //this word is connected to the label
            int posts_with_w = it->second;
            log_likelihood += log(posts_with_w/num_posts);
        }

        //word not connected to label 
        for (it = word_map.begin(); it != word_map.end(); it++){
            if (training_map[label].find(it->first) == training_map[label].end()){
                log_likelihood += log(1/num_posts);
            }
            
        }

        float prob = log_prior + log_likelihood;
        prob_map[label] = prob;
        return prob; 

    }

    void all_training(){
        map<string, map<string, int> >::iterator it;
        for (it = training_map.begin(); it != training_map.end(); it++){
            training_log_prob(it->first);
        }
    }





};

int main(int argc, char const *argv[]){
    cout.precision(3);
    bool debug = false; 
    string s = argv[3];
    int isdebug = s.compare("--debug");
    //error checking
    if (argc > 4){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 1;
    }

    else if ((argc > 3) && (isdebug != 0)){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 1;
    }

    else if (isdebug == 0){
        debug = true; 
    }

    Classifier machine; 
    //read in files 
    string training_data = argv[1];
    ifstream fin(training_data);
    if (!fin.is_open()) {
        std::cout << "Error opening file: " << training_data << endl;
        return 1;
    }

    cout << "training data: " << endl; 
    machine.training_map_intake(fin, debug);

    
    


    
}