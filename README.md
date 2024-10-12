# Checkpoint
**Checkpoint** (LANL code number O4800) is a C++ code designed
to facilitate checkpointing a program (i.e., saving its state)
and resuming it from the saved state.

# Example
In the `src/` directory compile and run the demo.
```
make
./chkpt options.txt
./chkpt options.txt 1
./chkpt options.txt 2
```

# Testing
In the `src/` directory compile and run the tests.
```
make tests
./tests fast # to include only tests that run quickly
./tests all verbose # to include additional tests that take a while to run
```
