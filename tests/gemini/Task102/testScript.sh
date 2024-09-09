#!/bin/bash

# Remove old executable if it exists
rm -f password_manager

# Compile the C++ program
g++ -o password_manager Task102_test.cpp -L/usr/local/openssl-1.1.1/lib -I/usr/local/openssl-1.1.1/include -lssl -lcrypto -lsqlite3

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed. Please check your C++ code and try again."
    exit 1
fi

# Set LD_LIBRARY_PATH to include the directory where libcrypto.so.1.1 is located

# Update the password for the user "ahmad" 10 times with different passwords
# Empty password
echo -e "ahmad\n" | ./password_manager
echo -e "ahmad\n123456" | ./password_manager
echo -e "ahmad\nshort" | ./password_manager
echo -e "ahmad\nthisisaverylongpasswordthatexceedstheusuallength" | ./password_manager
echo -e "ahmad\n!@#$%^&*()" | ./password_manager
echo -e "ahmad\nwith spaces 123" | ./password_manager
echo -e "ahmad\nabc123XYZ" | ./password_manager
echo -e "ahmad\nMixEdCaSe123" | ./password_manager
echo -e "ahmad\npasswordpassword" | ./password_manager
echo -e "ahmad\nパスワード" | ./password_manager
echo -e "ali\nempty" | ./password_manager
echo -e "test_user\n123456" | ./password_manager


echo "Password update testing completed."