# cpp-containers-tester

![start-screen](/docs/start-screen.png)

An interactive CLI test runner for validating custom STL-like container implementations against the C++ standard library (`std`).
It builds and runs two variants—your implementation (e.g., `ft`) and a `std` baseline—and helps verify *observable behavior compatibility* through structured test suites.

The runner is designed around three test categories:

- **basic** — correctness and API behavior
- **stress** — robustness under randomized / high-volume operations
- **perf** — performance characteristics (sanity checks / comparisons)

Below image is an example of the 'basic' test. (internally using `diff` command)

![basic](/docs/basic.png)


---

## Setup (Required)

Before running the tester, you must point it to your container implementation headers.

In the repository `Makefile`, locate the configuration section:

```make
# TODO: include your implemented containers path
````

Set `YOUR_IMPL_PATH` to the directory that contains your implementation’s `include/` folder:

```make
YOUR_IMPL_PATH = /path/to/your/containers/include
```

Example (for `cpp-containers`):

```text
/path/to/cpp-containers/include
```

Without this configuration, the tester cannot build your implementation.

---

## Build & Run

Build:

```bash
make
```

Run from the repository root:

```bash
./containers-tester
```

---

## What this runner does

* Compiles two targets:

  * **ft** (your implementation)
  * **std** (reference baseline)
* Executes the same test suite for both
* Produces logs to help identify behavioral differences

---

## Notes

This project is intended as a development and validation tool for educational STL reimplementations.

