#ifndef READER_H
#define READER_H
#pragma once

class Reader {
public: 
   virtual std::vector<std::string> readInput () const = 0;
};

#endif // READER_H