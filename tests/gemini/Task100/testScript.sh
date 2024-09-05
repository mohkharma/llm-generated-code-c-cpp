#!/bin/bash

# Color codes
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Test file name
FILE="testSentences.txt"

# Check if test file exists
if [ ! -f "$FILE" ]; then
  echo -e "${YELLOW}$FILE not found!${NC}"
  exit 1
fi

# Compile the C++ program
g++ -o a.out Task100_test.cpp

# Check if compilation was successful
if [ $? -ne 0 ]; then
  echo -e "${YELLOW}Compilation failed!${NC}"
  exit 1
fi

# Test cases with different regular expressions
echo -e "${YELLOW}Running 10 test cases...${NC}"

# Test case 1: Search for the word "Python"
echo -e "${YELLOW}Test case 1: Search for 'Python'${NC}"
./a.out "Python" "$FILE"

# Test case 2: Search for the word "line"
echo -e "${YELLOW}Test case 2: Search for 'line'${NC}"
./a.out "line" "$FILE"

# Test case 3: Search for email addresses
echo -e "${YELLOW}Test case 3: Search for email addresses${NC}"
./a.out "[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}" "$FILE"

# Test case 4: Search for numbers
echo -e "${YELLOW}Test case 4: Search for numbers${NC}"
./a.out "[0-9]+" "$FILE"

# Test case 5: Search for sentences starting with "The"
echo -e "${YELLOW}Test case 5: Search for lines starting with 'The'${NC}"
./a.out "^The" "$FILE"

# Test case 6: Search for sentences ending with exclamation mark
echo -e "${YELLOW}Test case 6: Search for lines ending with '!'${NC}"
./a.out "!$" "$FILE"

# Test case 7: Search for the word "fox"
echo -e "${YELLOW}Test case 7: Search for 'fox'${NC}"
./a.out "fox" "$FILE"

# Test case 8: Search for the word "pattern"
echo -e "${YELLOW}Test case 8: Search for 'pattern'${NC}"
./a.out "pattern" "$FILE"

# Test case 9: Search for the word "random"
echo -e "${YELLOW}Test case 9: Search for 'random'${NC}"
./a.out "random" "$FILE"

# Test case 10: Search for the word "jumps"
echo -e "${YELLOW}Test case 10: Search for 'jumps'${NC}"
./a.out "jumps" "$FILE"

# Clean up the compiled file
#rm -f a.out

echo -e "${YELLOW}All test cases completed.${NC}"
