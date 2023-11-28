#ifndef AOC_2023_DAY_H
#define AOC_2023_DAY_H

#include "constraints.h"
#include "reader.h"
#include "printer.h"

template <Readable Input, Streamable Output1, Streamable Output2 = Output1>
class Day :
    public FileInputReader<Input>,
    public PrintableSolution<Input, Output1, Output2> {
public:
    void run ();
};

template <Readable Input, Streamable Output1, Streamable Output2>
void Day<Input, Output1, Output2>::run() {
    auto input = this->readInput(this->filename());
    this->print(input);
}

#endif //AOC_2023_DAY_H
