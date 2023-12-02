#ifndef AOC_2023_DAY_H
#define AOC_2023_DAY_H

#include "constraints.h"
#include "reader.h"
#include "printer.h"

class RunnableDay
{
public:
    virtual void run () const = 0;
};

template <Streamable Output1, Streamable Output2 = Output1>
class Day :
    public SolutionPrinter<Output1, Output2>,
    public FileInputReader,
    public RunnableDay
{
public:
    void run () const override;
};

template <Streamable Output1, Streamable Output2>
void Day<Output1, Output2>::run() const {
    auto input = this->readInput();
    this->print(input);
}

#endif //AOC_2023_DAY_H
