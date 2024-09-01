Change the following:

    logfile = "claude_syntax_and_compliation_cpp_log.log"  # Replace with the path to your source directory
    source_directory = "./source/output/CLAUDE_claude-3-5-sonnet-20240620/cpp"  # Replace with the path to your source directory
    output_directory = "./out"  # Replace with the path to your output directory

Then Run:
```
python compiler.py
```
```

find ./ -type f > list
```
```
build-wrapper-linux-x86-64 --out-dir bw-output cmake --build cmake-build-debug
cd bw-output
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
cd ..
sonar-scanner
```

