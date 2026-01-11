# cdiag

`cdiag` is a deterministic command-line tool that explains noisy C compiler diagnostics by identifying the most likely root cause, collapsing error cascades, and providing human readable explanations with actionable next steps.

It is designed to help developers understand why the compiler is confused, not to guess code fixes or replace the compiler.

## Motivation

C compilers (GCC / Clang) often emit long cascades of diagnostics for a single mistake:

```text
error: expected ';' before 'int'
error: unknown type name 'foo'
warning: implicit declaration of function 'bar'
note: each undeclared identifier is reported only once
```

In practice:

- Most of these are secondary effects
- The real issue is often one earlier mistake
- Developers waste time chasing downstream noise

`cdiag` addresses this by:

- Grouping related diagnostics
- Detecting known cascade patterns
- Selecting the first meaningful failure
- Explaining why that failure causes many follow-up errors
- 

## How it works

The pipeline is intentionally simple and transparent:
```text
stdin (compiler output)
↓
Parser          → structured diagnostics
↓
Normalizer      → stable error categories
↓
Grouper         → collapse cascades, attach notes
↓
Root selector   → choose first meaningful failure
↓
Explanation     → human readable reasoning
```

No C code is parsed. All reasoning is based on compiler diagnostic behavior, not program semantics.

## Usage

### Basic usage

```bash
gcc main.c 2>&1 | cdiag explain
```

### Example output
```bash
Likely root cause
-----------------
Missing semicolon after declaration

Why this happens:
  C requires declarations to end with a semicolon. When it is missing,
  the compiler merges multiple declarations and loses track of structure.

What to check next:
  • Check the line immediately before the reported error
  • Ensure struct, enum, and typedef definitions end with ';'
  • Look for macro expansions that may remove a semicolon

Confidence:
  High — this error commonly triggers cascading diagnostics.

Suppressed diagnostics: 7
```

## Supported diagnostics (MVP)
The current MVP focuses on high-impact, cascade-prone errors:
- Missing semicolon (EXPECTED_SEMICOLON)
- Missing closing brace (EXPECTED_CLOSING_BRACE)
- Implicit function declaration
- Conflicting types
- Unknown type name

Unsupported patterns fall back to a conservative explanation with low confidence.

## Testing
```cdiag``` uses end-to-end golden tests that validate real behavior.
```bash
scripts/run_tests.sh
```
Tests assert that:
- The correct root cause is selected
- Known cascades are handled properly
- Output remains stable across refactors

No testing frameworks are used, tests run the actual binary.

## Design principles
- Determinism over cleverness
- Collapse noise, don’t amplify it
- Explain compiler confusion, not programmer intent
- Prefer under-explaining to hallucinating
- Small, composable rules over large heuristics


## Build
```bash
cmake -S . -B build
cmake --build build
```
Binary will be at:
```bash
./build/cdiag
```

## License
MIT