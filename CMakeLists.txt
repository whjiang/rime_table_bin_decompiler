cmake_minimum_required(VERSION 3.13)
project(rime_table_bin_decompiler)

set(CMAKE_CXX_STANDARD 14)
find_package(Boost REQUIRED COMPONENTS system filesystem)

include_directories(.)
include_directories(marisa)
include_directories(marisa/grimoire)
include_directories(marisa/grimoire/algorithm)
include_directories(marisa/grimoire/io)
include_directories(marisa/grimoire/trie)
include_directories(marisa/grimoire/vector)
include_directories(thirdparty/marisa-trie/bindings)
include_directories(thirdparty/marisa-trie/bindings/perl)
include_directories(thirdparty/marisa-trie/bindings/python)
include_directories(thirdparty/marisa-trie/bindings/ruby)
include_directories(thirdparty/marisa-trie/lib)
include_directories(thirdparty/marisa-trie/lib/marisa)
include_directories(thirdparty/marisa-trie/lib/marisa/grimoire)
include_directories(thirdparty/marisa-trie/lib/marisa/grimoire/algorithm)
include_directories(thirdparty/marisa-trie/lib/marisa/grimoire/io)
include_directories(thirdparty/marisa-trie/lib/marisa/grimoire/trie)
include_directories(thirdparty/marisa-trie/lib/marisa/grimoire/vector)
include_directories(thirdparty/marisa-trie/tests)
include_directories(thirdparty/marisa-trie/tools)

add_executable(rime_table_bin_decompiler main.cpp mapped_file.cc table.cc vocabulary.cc
        string_table.cc
        thirdparty/marisa-trie/lib/marisa/grimoire/algorithm/sort.h
        thirdparty/marisa-trie/lib/marisa/grimoire/io/mapper.cc
        thirdparty/marisa-trie/lib/marisa/grimoire/io/mapper.h
        thirdparty/marisa-trie/lib/marisa/grimoire/io/reader.cc
        thirdparty/marisa-trie/lib/marisa/grimoire/io/reader.h
        thirdparty/marisa-trie/lib/marisa/grimoire/io/writer.cc
        thirdparty/marisa-trie/lib/marisa/grimoire/io/writer.h
        thirdparty/marisa-trie/lib/marisa/grimoire/trie/cache.h
        thirdparty/marisa-trie/lib/marisa/grimoire/trie/config.h
        thirdparty/marisa-trie/lib/marisa/grimoire/trie/entry.h
        thirdparty/marisa-trie/lib/marisa/grimoire/trie/header.h
        thirdparty/marisa-trie/lib/marisa/grimoire/trie/history.h
        thirdparty/marisa-trie/lib/marisa/grimoire/trie/key.h
        thirdparty/marisa-trie/lib/marisa/grimoire/trie/louds-trie.cc
        thirdparty/marisa-trie/lib/marisa/grimoire/trie/louds-trie.h
        thirdparty/marisa-trie/lib/marisa/grimoire/trie/range.h
        thirdparty/marisa-trie/lib/marisa/grimoire/trie/state.h
        thirdparty/marisa-trie/lib/marisa/grimoire/trie/tail.cc
        thirdparty/marisa-trie/lib/marisa/grimoire/trie/tail.h
        thirdparty/marisa-trie/lib/marisa/grimoire/vector/bit-vector.cc
        thirdparty/marisa-trie/lib/marisa/grimoire/vector/bit-vector.h
        thirdparty/marisa-trie/lib/marisa/grimoire/vector/flat-vector.h
        thirdparty/marisa-trie/lib/marisa/grimoire/vector/pop-count.h
        thirdparty/marisa-trie/lib/marisa/grimoire/vector/rank-index.h
        thirdparty/marisa-trie/lib/marisa/grimoire/vector/vector.h
        thirdparty/marisa-trie/lib/marisa/grimoire/algorithm.h
        thirdparty/marisa-trie/lib/marisa/grimoire/intrin.h
        thirdparty/marisa-trie/lib/marisa/grimoire/io.h
        thirdparty/marisa-trie/lib/marisa/grimoire/trie.h
        thirdparty/marisa-trie/lib/marisa/grimoire/vector.h
        thirdparty/marisa-trie/lib/marisa/agent.cc
        thirdparty/marisa-trie/lib/marisa/agent.h
        thirdparty/marisa-trie/lib/marisa/base.h
        thirdparty/marisa-trie/lib/marisa/exception.h
        thirdparty/marisa-trie/lib/marisa/iostream.h
        thirdparty/marisa-trie/lib/marisa/key.h
        thirdparty/marisa-trie/lib/marisa/keyset.cc
        thirdparty/marisa-trie/lib/marisa/keyset.h
        thirdparty/marisa-trie/lib/marisa/query.h
        thirdparty/marisa-trie/lib/marisa/scoped-array.h
        thirdparty/marisa-trie/lib/marisa/scoped-ptr.h
        thirdparty/marisa-trie/lib/marisa/mstdio.h
        thirdparty/marisa-trie/lib/marisa/trie.cc
        thirdparty/marisa-trie/lib/marisa/trie.h
        thirdparty/marisa-trie/lib/marisa.h
        )



link_directories(rime_table_bin_decompiler ${Boost_LIBRARY_DIRS})

target_link_libraries(rime_table_bin_decompiler ${Boost_LIBRARIES})