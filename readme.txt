Team members:

1)Allen Chacko Johny  19XJ1A0505
2)Chaitanya K V       19XJ1A0583
3)Manish Reddy       19XJ1A0519


	Name of the file consisting of the program is 19XJ1A0505_19XJ1A0583_19XJ1A0519.c. It can be compiled in a c compiler using the command "gcc 19XJ1A0505_19XJ1A0583_19XJ1A0519.c" creating an executable a.out. We execute a.out  using ./a.out to run the code.

	The program has the following funtions:-

	1) void rankloop: This is used to compute the rank of the given tasks
	2) void sort: This sorts the rank value array in descending order
	3) int prede: This is used to calculate the (AFT+c) term
	4) void calc: Used to obtain the EST and EFT values of ecah task on each processor.


	The program first scan's the input file named "input.txt" and obtains the required values and the number of tasks and processors.It the proceeds to calculate the rank of each task using a recursive funtion rankloop (note: the first/entry rank in obtained prior to entering into the recursive function). After the ranks are obtained the tasks are scheduled in their descending rank. Their EST,EFT and AFT values and then calculated for each processor. The final schedule is obtained and the results are printed as output. 

note: Due to the use of 2d arrays without dynamic allocation the number of tasks may get limited as per the size of the matrix intialised. 
