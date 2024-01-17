<div style="text-align: justify;">

# Group_K_Project_2

This project implements the DPLL algorithm enhanced with Unit Propagation (UP) and Pure Literal Elimination (PLE).   
  
The solver offers four heuristic options: INC->0, DLIS->1, DLCS->2, JW->3. Both satisfiable and unsatisfiable competition files have been consolidated into a designated comp folder, identifiable by their affix (u = unsat, s = sat).

## Build + Run
To build the project enter `make`. To run the solver on a test file enter `./main [testfile] [heur]`, i.e. `./main c1 2`. 

Optionally, to build and run immediately, enter `make run arg=[testfile] [heur]`.

## Batch Execution
If compiled, you can run a chosen set of test or comp files at once with either all heuristics `.\runAll.ps1 -type [char] -start [int] -end [int]` 
   
or a chosen heuristic `.\run.ps1 -type [char] -start [int] -end [int] -heur [int]`.

Examples:  
   
`.\runAll.ps1 -type 'c' -start 1 -end 50`
    
`.\run.ps1 -type 't' -start 1 -end 30 -heur 1`

## Results

We plotted our runtimes by sorting them in increasing order using `mkplot`. For exact runtimes and plots with higher timeout, see folder `./solution/runtime` and `./cactus/` respectively.

![Alt text](cactus/cactusPlot60secs.png/?raw=true "Optional Title")

**Test Environment Specifications:**

- **Hardware:**
  - Processor: AMD Ryzen 7 5700U @ 1.80 GHz
  - Memory: 16 GB

- **Software:**
  - Operating System: Windows 11 Pro
  - Compiler: GCC 11.2.0

</div>






