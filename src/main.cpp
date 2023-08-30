#include "table.h"
#include <fstream>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;
ofstream fout;

string codeToString(rime::Table* table, const rime::Code code) {
  if (code.empty()) {
    return "";
  }
  auto item = code.begin();
  string str = table->GetSyllableById(*item);
  item++;
  for (; item != code.end(); ++item) {
    str += " ";
    str += table->GetSyllableById(*item);
  }
  return str;
}

void traversal(rime::Table* table, ofstream& fout) {
  auto metadata = table->metadata_;
  cout << "num_syllables: " << metadata->num_syllables << endl;
  cout << "num_entries: " << metadata->num_entries << endl;

  for (int i = 0; i < metadata->num_syllables; i++) {
    auto accessor = table->QueryWords(i);
    while (!accessor.exhausted()) {
      fout << table->GetEntryText(*accessor.entry()) << "\t";
      fout << codeToString(table, accessor.code()) << endl;
      accessor.Next();
    }
  }
}

int main(int argc, char* argv[]) {
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
  if (std::string::npos != period_idx) {
    fileName.erase(period_idx);
  }

  string outputName = fileName + ".txt";
  fout.open(outputName);
  // clang-format off
  fout << "# Rime dictionary\n\n";
  fout << "---\n"
          "name: " << fileName << "\n"
          "version: \"1.0\"\n"
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
          "      formula: \"AaBaCaCb\"\n"
          "    - length_in_range: [4, 10]\n"
          "      formula: \"AaBaCaZa\"\n"
          "...\n\n";

  traversal(&table, fout);
  return 0;
}
