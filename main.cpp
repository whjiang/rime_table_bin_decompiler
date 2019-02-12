#include <iostream>
#include <string>
#include "table.h"
#include <map>
#include <iterator>

using namespace std;

multimap<string, string> word2codeMap;
multimap<string, string> code2wordMap;
set<string> codeSet;

void queryCode(rime::Table& table, int i0) {
    rime::TableAccessor v = table.QueryWords(i0);
    if(!v.exhausted()) {
        string code = table.GetSyllableById(i0);
        do {
            rime::string str = table.GetEntryText(*v.entry());
            unsigned char c = str[0];
            if(c < 20) {
                continue;
            }
            word2codeMap.insert(pair<string, string>(str, code));
            code2wordMap.insert(pair<string, string>(code, str));
            codeSet.insert(code);
        }while(v.Next());
    }
}

void printTable() {
    string prev = "";
    bool first = true;
    for(auto codeIt=codeSet.begin(); codeIt!=codeSet.end(); ++codeIt) {
        string code = *codeIt;
        string code2 = code.substr(0,4);
        if(prev!=code2) {
            if(first) {
                first = false;
            }else {
                cout << "\n";
            }
            cout << code2;
            prev = code2;
        }
        for(auto wordIt=code2wordMap.lower_bound(code); wordIt!=code2wordMap.upper_bound(code); ++wordIt) {
            string word = wordIt->second;
            cout << " " << word;
            //cout << word << "\t" << code << "\n";
            /*
            bool first = true;
            for(auto codeIt2=word2codeMap.lower_bound(word); codeIt2!=word2codeMap.upper_bound(word); ++codeIt2) {
                string code2 = codeIt2->second;
                if(first) {
                    first = false;
                }else {
                    cout << " ";
                }
                cout << code2;
            }
            cout << "\n";
             */
        }
    }
    cout << "\n";
}

void printW2CTable() {
    string prev = "";
    bool first = true;
    for(auto codeIt=codeSet.begin(); codeIt!=codeSet.end(); ++codeIt) {
        string code = *codeIt;
        for(auto wordIt=code2wordMap.lower_bound(code); wordIt!=code2wordMap.upper_bound(code); ++wordIt) {
            string word = wordIt->second;
            cout << word << "\t" << code << "\n";
        }
    }
}

int main(int argc, char *argv[]) {
    string fileName(argv[1]);

    rime::Table table(fileName);
    table.Load();

    // Remove directory if present.
    // Do this before extension removal incase directory has a period character.
    const size_t last_slash_idx = fileName.find_last_of("\\/");
    if (std::string::npos != last_slash_idx) {
        fileName.erase(0, last_slash_idx + 1);
    }

    // Remove extension if present.
    const size_t period_idx = fileName.find('.');
    if (std::string::npos != period_idx){
        fileName.erase(period_idx);
    }

    cout << "---\n"
            "name: ";
    cout << fileName;
    cout <<"\nversion: \"1.0\"\n"
            "sort: original\n"
            "columns:\n"
            "  - text\n"
            "  - code\n"
            "  - weight\n"
            "  - stem\n"
            "encoder:\n"
            "  rules:\n"
            "    - length_equal: 2\n"
            "      formula: \"AaAbBaBb\"\n"
            "    - length_equal: 3\n"
            "      formula: \"AaAbBaCa\"\n"
            "    - length_in_range: [4, 10]\n"
            "      formula: \"AaBaCaZa\"\n"
            "...\n";
    uint32_t synLen = table.metadata_->num_syllables;
    for(int i=0; i<synLen; i++) {
        queryCode(table, i);
    }
    printW2CTable();
    return 0;
}