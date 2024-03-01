#!/bin/bash

make all

# Define test functions
test1() {
    echo "Running Test 1..."
    ./program 20 8 100 1 10 4 random
}

test2() {
    echo "Running Test 2..."
    ./program 20 8 100 1 10 4 random
}

test3() {
    echo "Running Test 3..."
    ./program 20 10 1000 3 10 4 lifo
}

test4() {
    echo "Running Test 4..."
    ./program 20 10 1000 3 10 4 random
}

# Main function to select and run tests
main() {
    case $1 in
        test1)
            test1
            ;;
        test2)
            test2
            ;;
        test3)
            test3
            ;;
        test4)
            test4
            ;;
        all)
            test1
            test2
            test3
            test4
            ;;
        *)
            echo "Invalid test target. Usage: $0 {1|2|3|4|all}"
            ;;
    esac
}

# Call main function with command-line arguments
main "$@"

make clean
