#include <cmath>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <rime/dict/table.h>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifdef _WIN32
#include <windows.h>
#endif

void outCode(rime::Table* table, const rime::Code code, std::ofstream& fout) {
  if (code.empty()) {
    return;
  }
  auto item = code.begin();
  fout << table->GetSyllableById(*item);
  item++;
  for (; item != code.end(); ++item) {
    fout << " ";
    fout << table->GetSyllableById(*item);
  }
  return;
}

void access(rime::Table* table,
            rime::TableAccessor accessor,
            std::ofstream& fout) {
  while (!accessor.exhausted()) {
    auto word = table->GetEntryText(*accessor.entry());
    fout << word << "\t";
    outCode(table, accessor.code(), fout);

    auto weight = accessor.entry()->weight;
    if (weight >= 0) {
      fout << "\t" << exp(weight);
    }
    fout << std::endl;
    accessor.Next();
  }
}

// recursively traverse table
void recursion(rime::Table* table,
               rime::TableQuery* query,
               std::ofstream& fout) {
  for (int i = 0; i < table->metadata_->num_syllables; i++) {
    auto accessor = query->Access(i);
    access(table, accessor, fout);
    if (query->Advance(i)) {
      if (query->level() < 3) {
        recursion(table, query, fout);
      } else {
        auto accessor = query->Access(0);
        access(table, accessor, fout);
      }
      query->Backdate();
    }
  }
}

void traversal(rime::Table* table, std::ofstream& fout) {
  auto metadata = table->metadata_;
  std::cout << "num_syllables: " << metadata->num_syllables << std::endl;
  std::cout << "num_entries: " << metadata->num_entries << std::endl;

  fout << std::fixed;
  fout << std::setprecision(0);
  rime::TableQuery query(table->metadata_->index.get());
  recursion(table, &query, fout);
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: rime_table_decompiler <rime-table-file> [save-path]"
              << std::endl;
    std::cout
        << "Example: rime_table_decompiler pinyin.table.bin pinyin.dict.yaml"
        << std::endl;
    return 0;
  }

#ifdef _WIN32
  SetConsoleOutputCP(65001);
#endif
  std::string fileName(argv[1]);
  rime::Table table(fileName);
  bool success = table.Load();
  if (!success) {
    std::cerr << "Failed to load table." << std::endl;
    return 1;
  }

  // Remove the extension ".table.bin" if present.
  const size_t table_bin_idx = fileName.rfind(".table.bin");
  if (std::string::npos != table_bin_idx) {
    fileName.erase(table_bin_idx);
  }
  const std::string outputName =
      (argc == 3) ? argv[2]: fileName + ".yaml";

  std::ofstream fout;
  fout.open(outputName);
  if (!fout.is_open()) {
    std::cerr << "Failed to open file " << outputName << std::endl;
    return 1;
  }

  // schema id
  const size_t last_slash_idx = fileName.find_last_of("\\/");
  if (std::string::npos != last_slash_idx) {
    fileName.erase(0, last_slash_idx + 1);
  }

  // clang-format off
  fout << "# Rime dictionary\n\n";
  fout << "---\n"
          "name: " << fileName << "\n"
          "version: \"1.0\"\n"
          "...\n\n";
  // clang-format on
  traversal(&table, fout);
  std::cout << "Save to: " << outputName << std::endl
       << std::endl
       << "作者: 单单 <me@nopdan.com>" << std::endl
       << "更新日期: 2023-9-5" << std::endl
       << "项目地址: https://github.com/nopdan/rime-table-decompiler" << std::endl;
  system("pause");
  return 0;
}
