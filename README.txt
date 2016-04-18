HDP Code:
http://www.cs.berkeley.edu/~jordan/hdp/

Dataset:
https://aminer.org/DBLP_Citation


Notation table:
hh: base distribution of size (H x 1)

Sampling scheme:

First run 'numburnin' iterations and then take one sample every other 'numspace' iterations
until we have 'numsample' samples.
Thus the total number of iterations is:
totiter = numburnin + numsample*numspace

hdp.func          = func; % operations for F
hdp.numdp         = length(ppindex); % # of DP s
hdp.numconparam   = length(alphaa); % # of concentration parameters
hdp.base.hh       = hh; % 
hdp.base.classqq  = feval(hdp.func.newclass,hdp.base.hh);
hdp.base.numclass = 0;
hdp.conparam      = cell(1,hdp.numconparam);
hdp.dp            = cell(1,hdp.numdp);
hdp.dpstate       = HELDOUT*ones(1,hdp.numdp);
hdp.ppindex       = ppindex; % parent pointers, define the entire tree structure of the model
hdp.cpindex       = cpindex; 
hdp.ttindex       = zeros(1,hdp.numdp);