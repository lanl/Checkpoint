# Checkpoint-restart
**Checkpoint** (LANL code number O4800) is a C++ code designed
to facilitate checkpointing a program (i.e., saving its state)
and resuming it from the saved state.

# Example
In the `src/` directory compile and run the demo.

(assumes `g++`; see `common/makefile` for other options)
```
make
./chkpt options.txt
./chkpt options.txt 1
./chkpt options.txt 2
```

# Testing
In the `src/` directory compile and run the tests using the following options:

`fast:` to include only tests that run quickly

`all verbose:` to include additional tests that take a while to run
```
make tests
./tests fast
./tests all verbose
```
