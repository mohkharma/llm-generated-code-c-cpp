import os
import subprocess
from pathlib import Path

def compile_files(source_dir, output_dir):
    # Ensure the output directory exists
    os.makedirs(output_dir, exist_ok=True)

    # Walk through the source directory to find C/C++ files
    for root, dirs, files in os.walk(source_dir):
        for file in files:
            if file.endswith('.c') or file.endswith('.cpp'):
                source_file = os.path.join(root, file)
                relative_path = os.path.relpath(root, source_dir)
                output_path = os.path.join(output_dir, relative_path)
                os.makedirs(output_path, exist_ok=True)
                output_file = os.path.join(output_path, os.path.splitext(file)[0])

                if file.endswith('.c'):
                    compiler = 'D:/Program/JetBrains/CLion 2024.1.4/bin/mingw/bin/gcc.exe'
                elif file.endswith('.cpp'):
                    compiler = 'D:/Program/JetBrains/CLion 2024.1.4/bin/mingw/bin/g++.exe'

                command = [compiler, source_file, '-o', output_file]

                try:
                    print(f"Compiling {source_file} to {output_file}")
                    result = subprocess.run(command, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    print(f"Compilation successful: {output_file}")
                except subprocess.CalledProcessError as e:
                    print(f"Compilation failed for {source_file}:")
                    print(e.stderr.decode())
                    continue


if __name__ == "__main__":
    source_directory = "C:/sourceCode/PhD/llm-generated-code-c-cpp/source/output/CLAUDE_claude-3-5-sonnet-20240620"  # Replace with the path to your source directory
    output_directory = "C:/sourceCode/PhD/llm-generated-code-c-cpp/out"  # Replace with the path to your output directory
    compile_files(source_directory, output_directory)
