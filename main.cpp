#include <iostream>
#include <string>
#include "table.h"
#include <map>
#include <iterator>

using namespace std;

multimap<string, string> word2codeMap;
multimap<string, string> code2wordMap;
set<string> codeSet;

void querySyllable(rime::Table& table, uint32_t synLen) {
    for(int i=0; i<synLen; i++) {
        rime::TableAccessor v = table.QueryWords(i);
        if(!v.exhausted()) {
            string code = table.GetSyllableById(i);
            do {
                rime::string str = table.GetEntryText(*v.entry());
                word2codeMap.insert(pair<string, string>(str, code));
                code2wordMap.insert(pair<string, string>(code, str));
                codeSet.insert(code);
            }while(v.Next());
        }
    }
}

void insertMap(string code, string str) {
    word2codeMap.insert(pair<string, string>(str, code));
    code2wordMap.insert(pair<string, string>(code, str));
    codeSet.insert(code);
}

void addEntries(rime::Table& table, string code, const rime::List<rime::table::Entry>& entries) {
    for(int i=0; i<entries.size; i++) {
        rime::table::Entry* p = entries.at.get();
        rime::table::Entry entry1 = p[i];
        string text1 = table.GetEntryText(entry1);
        insertMap(code, text1);
    }
}

void queryCode(rime::Table& table) {
    rime::table::Index* lv1_index = table.index_;

    for(auto lv1=0; lv1<lv1_index->size; lv1++) {
        auto node1 = &lv1_index->at[lv1];

        //handle this code
        string c1 = table.GetSyllableById(lv1);
        addEntries(table, c1, node1->entries);

        //handle second level
        if (!node1->next_level)
            continue;
        rime::table::TrunkIndex* lv2_index = &node1->next_level->trunk();
        for(auto lv2Node : *lv2_index) {
            string c2 = table.GetSyllableById(lv2Node.key);
            string fullCode2 = c1 + " "+c2;
            addEntries(table, fullCode2, lv2Node.entries);

            //handle third level
            if(!lv2Node.next_level)
                continue;
            rime::table::TrunkIndex* lv3_index = &lv2Node.next_level->trunk();
            for(auto lv3Node: *lv3_index) {
                string c3 = table.GetSyllableById(lv3Node.key);
                string fullCode3 = fullCode2 + " "+c3;
                addEntries(table, fullCode3, lv3Node.entries);

                //handle 4th level
                if(!lv3Node.next_level)
                    continue;
                rime::table::TailIndex* lv4_index = &lv3Node.next_level->tail();
                for(auto longEntry: *lv4_index) {
                    string fullCode4 = fullCode3;
                    for(auto s: longEntry.extra_code)
                        fullCode4 += " "+table.GetSyllableById(s);
                    string text4 = table.GetEntryText(longEntry.entry);
                    insertMap(fullCode4, text4);
                }
            }
        }
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
    const char* f = argv[1];
    string fileName(f);

    rime::Table table(fileName);
    table.Load();
    if(table.index_== nullptr) {
        cerr << "ERROR: Can't find INDEX section for table.bin file."<<endl;
        exit(1);
    }

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

    cout << table.metadata_->num_syllables << endl;
    queryCode(table);

    printW2CTable();
    return 0;
}