#include <memory>

#include "main/solution/day.h"
#include "main/days/00/day_00.h"
#include "main/days/01/day_01.h"
#include "main/days/02/day_02.h"
#include "main/days/03/day_03.h"

int main () 
{
    std::vector<std::shared_ptr<RunnableDay>> days = {
        std::make_shared<Day00>(),
        std::make_shared<Day01>(),
        std::make_shared<Day02>(),
        std::make_shared<Day03>(),
    };

    std::ranges::for_each(days, [=] (auto day) { day->run(); });
}