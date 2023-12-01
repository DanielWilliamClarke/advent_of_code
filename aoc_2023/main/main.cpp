#include <memory>

#include "main/solution/day.h"
#include "main/days/00/day_00.h"
#include "main/days/01/day_01.h"

int main () 
{
    std::vector<std::shared_ptr<RunnableDay>> days = {
        std::make_shared<Day00>(),
        std::make_shared<Day01>()
    };

    std::ranges::for_each(days, [=] (auto day) { day->run(); });
}