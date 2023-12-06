#include <memory>

#include "main/solution/day.h"
#include "main/days/00/day_00.h"
#include "main/days/01/day_01.h"
#include "main/days/02/day_02.h"
#include "main/days/03/day_03.h"
#include "main/days/04/day_04.h"
#include "main/days/05/day_05.h"
#include "main/days/06/day_06.h"

int main () 
{
    std::vector<std::shared_ptr<RunnableDay>> days = {
        std::make_shared<Day00>(),
        std::make_shared<Day01>(),
        std::make_shared<Day02>(),
        std::make_shared<Day03>(),
        std::make_shared<Day04>(),
        std::make_shared<Day05>(),
        std::make_shared<Day06>(),
    };

    std::ranges::for_each(days, [=] (auto day) { day->run(); });
}