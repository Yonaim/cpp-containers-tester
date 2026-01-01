# cpp-containers-tester

Interactive test runner for C++ container implementations

# Overview

This repository provides an interactive CLI-based test runner to validate and compare custom STL-like container implementations against the standard library (`std`).

The runner is designed to support three different categories of tests:

* **basic** tests focus on correctness and behavior
* **stress** tests focus on robustness
* **perf** tests focus on performance characteristics

(Currently, only basic tests available)

# Required Configuration

Before using this runner, **you must configure the path to your own container implementation**.

In the Makefile (or related configuration files), you will find a section similar to:

```make
# TODO: include your implemented containers path
```

You must update this to point to the directory containing your container headers (for example, your `ft/` implementation):

```make
YOUR_IMPL_PATH = /path/to/your/containers/include
```

Without this configuration, the runner cannot build or test your implementation correctly.

# Usage

Build the runner:

```bash
make
```

Run from the repository root:

```bash
./containers-tester
```
