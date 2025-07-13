#!/bin/bash

# Define colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# File name
FILE="script.sh"

# Cleanup previous files if they exist
rm -f "$FILE"

g++ Task101_test.cpp
# Test 1: File Creation Test
echo -e "${GREEN}Running File Creation Test...${NC}"
./a.out
if [ -f "$FILE" ]; then
    echo -e "${GREEN}File Creation Test Passed.${NC}"
else
    echo -e "${RED}File Creation Test Failed: $FILE not found.${NC}"
fi

# Test 2: File Content Test
echo -e "${GREEN}Running File Content Test...${NC}"
EXPECTED_CONTENT="#!/bin/bash
echo \"Hello from script.sh!\""
ACTUAL_CONTENT=$(cat "$FILE")
if [ "$ACTUAL_CONTENT" == "$EXPECTED_CONTENT" ]; then
    echo -e "${GREEN}File Content Test Passed.${NC}"
else
    echo -e "${RED}File Content Test Failed: Content does not match.${NC}"
    echo "Expected: $EXPECTED_CONTENT"
    echo "Actual: $ACTUAL_CONTENT"
fi

# Test 3: File Permissions Test
echo -e "${GREEN}Running File Permissions Test...${NC}"
PERMISSIONS=$(ls -l "$FILE" | awk '{print $1}')
if [[ "$PERMISSIONS" == "-rwxr-xr-x" ]]; then
    echo -e "${GREEN}File Permissions Test Passed.${NC}"
else
    echo -e "${RED}File Permissions Test Failed: Permissions are not correct.${NC}"
    echo "Permissions: $PERMISSIONS"
fi

# Test 4: File Write Failure Test
echo -e "${GREEN}Running File Write Failure Test...${NC}"
# Attempt to create a file in a directory without write permissions
DIR="/root/test_dir"
mkdir -p "$DIR"
chmod 555 "$DIR" # Remove write permissions
echo -e "echo 'This should fail'" > "$DIR/test_script.sh" 2>/dev/null
if [ -f "$DIR/test_script.sh" ]; then
    echo -e "${RED}File Write Failure Test Failed: File created despite lack of permissions.${NC}"
else
    echo -e "${GREEN}File Write Failure Test Passed.${NC}"
fi
# Cleanup
chmod 755 "$DIR" # Restore permissions
rm -rf "$DIR"

# Test 5: File Overwrite Test
echo -e "${GREEN}Running File Overwrite Test...${NC}"
echo "echo 'Different content'" > "$FILE"
./a.out
ACTUAL_CONTENT=$(cat "$FILE")
if [ "$ACTUAL_CONTENT" == "$EXPECTED_CONTENT" ]; then
    echo -e "${GREEN}File Overwrite Test Passed.${NC}"
else
    echo -e "${RED}File Overwrite Test Failed: Content does not match after overwrite.${NC}"
    echo "Expected: $EXPECTED_CONTENT"
    echo "Actual: $ACTUAL_CONTENT"
fi

# Test 6: Executable Test
echo -e "${GREEN}Running Executable Test...${NC}"
OUTPUT=$(./"$FILE")
if [ "$OUTPUT" == "Hello from script.sh!" ]; then
    echo -e "${GREEN}Executable Test Passed.${NC}"
else
    echo -e "${RED}Executable Test Failed: Script did not produce expected output.${NC}"
    echo "Output: $OUTPUT"
fi

# Cleanup
rm -f "$FILE"

