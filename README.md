# Group_K_Project_2

We implemented DPLL with UP and PLE. There are four heuristics available: INC->0, DLIS->1, DLCS->2, JW->3 . We combined both _sat_ and _unsat_ competition files into a _comp_ folder (t = test, c = comp), where they can be recognized by their affix (u = unsat, s = sat).

## Build + Run
To build the project enter `make`. To run the solver on a test file enter `./main [testfile] [heur]`, i.e. `./main c1 2`. 

Optionally, to build and run immediately, enter `make run arg=[testfile] [heur]`.

If compiled, you can run a chosen set of test or comp files at once with either all heuristics `.\runAll.ps1 -type [char] -start [int] -end [int]` or a chosen heuristic `.\run.ps1 -type [char] -start [int] -end [int] -heur [int]`.

Examples: 
```
.\runAll.ps1 -type 'c' -start 1 -end 50
.\run.ps1 -type 't' -start 1 -end 30 -heur 1
```









