#!/usr/bin/env bash

set -e

BIN=./build/cdiag
FAILED=0

run_test() {
    name="$1"
    expected="$2"

    echo "Running $name..."

    output=$($BIN explain < "tests/fixtures/$name.log")

    if echo "$output" | grep -q "$expected"; then
        echo "  ✔ PASS"
    else
        echo "  ✘ FAIL"
        echo "Expected to find: $expected"
        echo "Actual output:"
        echo "$output"
        FAILED=1
    fi
}

run_test "missing_semi" "Missing semicolon"
run_test "missing_brace" "Missing closing brace"
run_test "implicit_decl" "Function used without a prior declaration"

if [ $FAILED -eq 0 ]; then
    echo "All tests passed."
else
    echo "Some tests failed."
    exit 1
fi
