%% Compile

bRecompile = 1; 
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

hh = ones(25, 1)/5;
load ourdata trainss testss;

%% Setup parameters

%% Sampling

% run testbars first to get the data for now

[hdp, sample, lik] = hdp_ourf(hh,[1 1],[1 1],15,...
    trainss,1000,10,100,15,1);


