#!/bin/bash

echo "Testing lexer with quote handling..."

# Function to run a test case
run_test() {
    input="$1"
    echo "Input: $input"
    echo "Output:"
    echo "$input" | ./minishell 2>/dev/null
    echo "------------------------"
}

# Test cases
run_test "echo 'hello'"
run_test "echo \"world\""
run_test "echo \"hello world\""
run_test "cat 'file*.txt'"
run_test "echo \"\" ''"
run_test "echo \"hi\" > 'file.txt' | wc"
run_test "echo \"a\"\"b\" 'c''d'"
run_test "echo hello\"world\""
run_test "echo \"hello" # Should print error
run_test "cat << 'EOF' \"file.txt\" | grep \"pattern\""

echo "Running valgrind to check memory..."
{
    echo "echo 'hello'"
    echo "echo \"world\""
    echo "echo \"hello world\""
    echo "cat 'file*.txt'"
    echo "echo \"\" ''"
    echo "echo \"hi\" > 'file.txt' | wc"
    echo "echo \"a\"\"b\" 'c''d'"
    echo "echo hello\"world\""
    echo "echo \"hello"
    echo "cat << 'EOF' \"file.txt\" | grep \"pattern\""
    echo "exit"
} | valgrind --leak-check=full ./minishell 2>&1 | grep -E "ERROR SUMMARY|LEAK SUMMARY|definitely lost|still reachable"

echo "Tests complete."
