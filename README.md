# Garbage-Collector-MarkAndSweep

A small C++ mark-and-sweep garbage collector project with:

- a core library in `src/`
- a runnable examples CLI in `examples/`
- compiled library artifacts in `artifacts/`

## Build

Build the library first:

```bash
cd src
make -j
```

Then build the examples app:

```bash
cd ../examples
make -j
```

For debug builds, run `make debug -j` in both `src/` and `examples/`.

## Run

You can run the example CLI from `examples/`:

```bash
./bin/gc_example --help
./bin/gc_example --list
./bin/gc_example basic
./bin/gc_example nested
./bin/gc_example gc-pause
./bin/gc_example retained
./bin/gc_example repeated
./bin/gc_example all
```

If you source `env.bash` from the project root, `gc_example` will be added to your `PATH`.

## Examples

- `basic`: small allocation flow
- `nested`: nested pair allocations
- `gc-pause`: forces collection with a low threshold
- `retained`: keeps a root alive across allocations
- `repeated`: runs multiple collection cycles
- `all`: runs everything

Each example prints a short summary and a final remaining-object count.

## Project Layout

- `src/`: garbage collector library
- `examples/`: example executable and scenarios
- `artifacts/`: compiled library outputs

## Resource

- [Baby's First Garbage Collector](https://journal.stuffwithstuff.com/2013/12/08/babys-first-garbage-collector/)
