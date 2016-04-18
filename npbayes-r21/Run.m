%% Compile

bRecompile = 0; 
bDebugMex = 1;

if bRecompile || exist('hdp_ourf_iterate') ~= 3 %#ok<EXIST> % 3 means MEX function
    addpath distributions/ourf;
    addpath utilities;
    addpath hdpmix;
    cd distributions/ourf;
    try
        if bDebugMex
            mex -g hdp_ourf_iterate.c
        else
            mex hdp_ourf_iterate.c
        end
    catch ME
        cd ../..;
        rethrow(ME);
    end
    cd ../../utilities;
    try
        if bDebugMex
            mex -g randgamma.c
            mex -g randnumtable.c
        else
            mex randgamma.c
            mex randnumtable.c
        end
    catch ME
        cd ..
        rethrow(ME);
    end
    cd ..
end

%% Read preprocessed data

nYear = 2;
startYear = 1995;

ourdata = cell(nYear, 1);
for y = 1:nYear
    fname = ['year' num2str(startYear + y - 1)];
    mn = load(['../data/' fname '.meta']);
    ijv = load(['../data/' fname '.sparse']);
    ourdata{y} = full(sparse(ijv(:, 2), ijv(:, 1), ijv(:, 3), mn(2), mn(1)));
end

% concatenate just for now
ourdata = [ourdata{:}];
trainss = cell(1);
trainss{1} = ourdata;

%% Setup parameters

% iterations and sample extraction
numburnin   = 1000;
numsample   = 10;
numinterval = 100;

% whether to sample concentration parameters:
%    If doconparam>0 then also samples concentration
%    parameters, for doconparam number of iterations each time.
doconparam = 15;

% common vague gamma prior for all concentration parameters
alphaa = 1;
alphab = 1;

% H for G0
hh = ones(mn(2), 1);

% expected number of classes/mixtures/topics
numclass = 15;

%% Sampling

[hdp, sample, lik] = hdp_ourf(hh, alphaa, alphab, numclass, ...
    trainss, numburnin, numsample, numinterval, doconparam);


