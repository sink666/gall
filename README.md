## gall
game of life implementation that had some shenanigans to do with unix pipes and bash
going on during testing.

to use, make a file with your beginning state and **cat foo | ./gall 10**. gall takes
an argument to determine simulation speed.

input files need to be formatted specifically with full-stop and crunch characters,
dots representing dead cells and crunches representing live ones. width and
height must equal whatever is set in the file, by default 30x30.

#### future updates?
* file output
* arguments for size of simulation grid
