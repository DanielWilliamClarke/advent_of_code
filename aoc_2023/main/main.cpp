#include <memory>

#include "main/solution/day.h"
#include "main/days/N01/day_N01.h"
#include "main/days/01/day_01.h"
#include "main/days/02/day_02.h"
#include "main/days/03/day_03.h"
#include "main/days/04/day_04.h"
#include "main/days/05/day_05.h"
#include "main/days/06/day_06.h"
#include "main/days/07/day_07.h"
#include "main/days/08/day_08.h"
#include "main/days/09/day_09.h"
#include "main/days/10/day_10.h"
#include "main/days/11/day_11.h"
#include "main/days/12/day_12.h"
//NEW_DAY_HEADER

int main ()
{
    std::ranges::for_each(
        std::vector<std::shared_ptr<RunnableDay>> {
            std::make_shared<DayN01>(),
            std::make_shared<Day01>(),
            std::make_shared<Day02>(),
            std::make_shared<Day03>(),
            std::make_shared<Day04>(),
            std::make_shared<Day05>(),
            std::make_shared<Day06>(),
            std::make_shared<Day07>(),
            std::make_shared<Day08>(),
            std::make_shared<Day09>(),
            std::make_shared<Day10>(),
            std::make_shared<Day11>(),
            std::make_shared<Day12>(),
            //NEW_DAY_PTR,
        },
        [=] (auto day) { day->run(); }
    );
}