# Garbage-Collector-MarkAndSweep

Mark and sweep garbage collector

## How to Build

### Release Build

- source env.bash found at Root of the project. to add exe to path (to be able to simply call "gc" ).
- `source env.bash`
- `cd src`
- Compile using make file found at src directory
- `make -j`

### Debug Build

- run `make debug -j`, with same steps used in release version

### Run

- run GC exe found in bin/ or just run GC command if env.bash was previously sourced
- `GC` for Release version OR `GC_g` for debug version

## Resources

- https://journal.stuffwithstuff.com/2013/12/08/babys-first-garbage-collector/
