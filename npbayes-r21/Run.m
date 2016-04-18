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

nYear = 2;
startYear = 1995;

trainss = cell(nYear, 1);
for y = 1:nYear
    fname = ['year' num2str(startYear + y - 1)];
    mn = load(['../data/' fname '.meta']);
    ijv = load(['../data/' fname '.sparse']);
    trainss{y} = full(sparse(ijv(:, 2), ijv(:, 1), ijv(:, 3), mn(2), mn(1)));
end

% concatenate just for now
trainss = [trainss{:}];

%% Setup parameters

hh = ones(mn(2), 1);

%% Sampling

% run testbars first to get the data for now

[hdp, sample, lik] = hdp_ourf(hh,[1 1],[1 1],15,...
    trainss,1000,10,100,15,1);


