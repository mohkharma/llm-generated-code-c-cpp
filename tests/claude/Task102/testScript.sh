#!/bin/bash

# Compile the C++ program
g++ -o password_manager Task102_test.cpp -L/usr/local/openssl-1.1.1/lib -I/usr/local/openssl-1.1.1/include -lssl -lcrypto -lsqlite3

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed. Please check your C++ code and try again."
    exit 1
fi

# Run the compiled program 10 times with different usernames and passwords
for i in $(seq 1 10); do
    username="user$i"
    password="password$i"
    
    echo "Testing with username: $username and password: $password"
    
    # Run the C++ program with the provided username and password
    echo -e "$username\n$password" | ./password_manager
done

echo "Testing completed."
