%% Compile

if exist('hdp_ourf_iterate') ~= 3 %#ok<EXIST> % 3 means MEX function
    addpath distributions/ourf;
    cd distributions/ourf;
    try
        mex hdp_ourf_iterate.c
    catch ME
        cd ../..;
        rethrow(ME);
    end
end

%% Read preprocessed data

%% Setup parameters

%% Sampling

% run testbars first to get the data for now

[hdp sample lik predlik] = hdp_ourf(hh,[1 1],[1 1],15,...
    trainss,testss,1000,10,100,500,1000,15,1,1);


