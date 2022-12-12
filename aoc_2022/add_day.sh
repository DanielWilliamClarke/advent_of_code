#!/bin/bash

DAY=$1
FILE="./src/days/day_$DAY.rs"
MOD="day_$DAY"
STRUCT="Day$DAY"
INPUT_FILE="day_$DAY.txt"
INPUT="./src/days/input/$INPUT_FILE"
MAIN="./src/main.rs"

# copy template
cp ./src/days/day_00.rs $FILE
cp ./src/days/input/day_0.txt $INPUT

# rename struct
sed -i '' -e "s/Day00/$STRUCT/g" $FILE
sed -i '' -e "s/day_0.txt/$INPUT_FILE/g" $FILE

# add mod
echo "
mod $MOD;
pub use $MOD::$STRUCT;" >> ./src/days/mod.rs

# add use in main
USE="$STRUCT\, \/\*USE\*\/"
sed -i '' -e "s:\/\*USE\*\/:$USE:g" $MAIN

# add printer to vec
PRINTER="\&Printer\($STRUCT\)\, \n\
        \/\*PRINTER\*\/"
sed -i '' -e "s:\/\*PRINTER\*\/:$PRINTER:g" $MAIN