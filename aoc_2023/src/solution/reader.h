#ifndef READER_H
#define READER_H
#pragma once

template <typename Data>
class Reader {
public: 
    Data read () const = 0;
};

#endif // READER_H