/*myreadwrite.hpp
Nathan Damon
4/17/2021
This is the hpp file for the Template Read() and Write() program
*/

#ifndef MYREADWRITE_HPP
#define MYREADWRITE_HPP

#include <ostream>
#include <fstream>
using std::ifstream;
using std::ios;

template <typename T>
 void myWrite(std::ofstream& ofs, const T& write)
 {
     ofs.write(reinterpret_cast<const char*>(&write), sizeof(T));
 }

 template <typename T>
 void myRead(std::ifstream& ifs, T& read)
 {
     ifs.read(reinterpret_cast<char*>(&read), sizeof(T));
 }

#endif // !MYREADWRITE_HPP

