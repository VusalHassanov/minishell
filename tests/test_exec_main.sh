#!/usr/bin/env bash
# Automated tests for exec_main (resolve_path helper)
# Place this in the project root under tests/ and run: ./tests/test_exec_main.sh

set -u
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
EXEC="$PROJECT_ROOT/exec_main"

compile() {
  echo "Compiling exec_main..."
  cc -I"$PROJECT_ROOT/includes" -I"$PROJECT_ROOT/libraries/libft/includes" \
    "$PROJECT_ROOT/sources/execution/main.c" \
    "$PROJECT_ROOT/sources/execution/execute_helper/search.c" \
    "$PROJECT_ROOT/sources/built-in/built-in_helpers/helper.c" \
    "$PROJECT_ROOT/libraries/libft/libft.a" -o "$EXEC"
  if [ ! -x "$EXEC" ]; then
    echo "Compilation failed." >&2
    return 1
  fi
}

pass=0
fail=0

check() {
  local name="$1"; shift
  echo -n "[TEST] $name... "
  if "$@"; then
    echo "PASS"
    pass=$((pass+1))
  else
    echo "FAIL"
    fail=$((fail+1))
  fi
}

# Test 1: resolve a common command (ls). Check output path exists and is executable.
test_ls() {
  out="$($EXEC ls 2>&1)" || true
  path=$(echo "$out" | sed -n "s/.*resolved to: \(.*\)/\1/p")
  [ -n "$path" ] || return 1
  [ -x "$path" ]
}

# Test 2: nonexistent command
test_nonexistent() {
  out="$($EXEC some_command_that_does_not_exist 2>&1)" || true
  echo "$out" | grep -q "not found in PATH."
}

# Test 3: PATH unset (env -i)
test_path_unset() {
  out="$(env -i PATH= $EXEC ls 2>&1)" || true
  echo "$out" | grep -q "not found in PATH."
}

# Test 4: argument with slash returns the argument back
test_contains_slash() {
  out="$($EXEC ./this/has/slash 2>&1)" || true
  echo "$out" | grep -q "resolved to: ./this/has/slash"
}

# Test 5: file in PATH without +x then with +x
test_permission() {
  tmpdir=$(mktemp -d)
  trap 'rm -rf "$tmpdir"' RETURN
  cmdname=mytmpcmd
  touch "$tmpdir/$cmdname"
  PATH="$tmpdir:$PATH" "$EXEC" "$cmdname" > /tmp/exec_main_test.out 2>&1 || true
  # should not be found (no execute permission)
  if grep -q "resolved to:" /tmp/exec_main_test.out; then
    return 1
  fi
  chmod +x "$tmpdir/$cmdname"
  out=$(PATH="$tmpdir:$PATH" "$EXEC" "$cmdname" 2>&1) || true
  path=$(echo "$out" | sed -n "s/.*resolved to: \(.*\)/\1/p")
  [ -n "$path" ] || return 1
  [ -x "$path" ]
}

main() {
  compile || return 1

  check "resolve existing command (ls)" test_ls
  check "nonexistent command" test_nonexistent
  check "PATH unset" test_path_unset
  check "argument with slash" test_contains_slash
  check "permission check (no +x then +x)" test_permission

  echo
  echo "Results: $pass passed, $fail failed"
  if [ "$fail" -ne 0 ]; then
    return 2
  fi
}

main "$@"
