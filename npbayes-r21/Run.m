% if it is time series
bEvo = 1;

% fix rand seed
rng('default');

%% Setup path & compile as needed

addpath distributions/ourf;
addpath utilities;
addpath hdpmix;

if exist('hdp_ourf_iterate') ~= 3 %#ok<EXIST> % 3 means MEX function
    Make
end

%% Read preprocessed data

nYear = 5;
startYear = 1996;

ourdata = cell(nYear, 1);
for y = 1:nYear
    fname = ['year' num2str(startYear + y - 1)];
    mn = load(['../data/' fname '.meta']);
    ijv = load(['../data/' fname '.sparse']);
    ourdata{y} = full(sparse(ijv(:, 2), ijv(:, 1), ijv(:, 3), mn(2), mn(1)));
%     ourdata{y} = ourdata{y}(1:300, 1:300);
end

if bEvo
    trainss = ourdata;
else
    ourdata = [ourdata{:}];
    trainss = cell(1);
    trainss{1} = ourdata;
end

% Vocabulary size
lenV = mn(2); % 3
% lenV = 3;

%% Setup parameters

% iterations and sample extraction
numburnin   = 1000;
numsample   = 1;
numinterval = 5;

% whether to sample concentration parameters:
%    If doconparam>0 then also samples concentration
%    parameters, for doconparam number of iterations each time.
doconparam = 0;

% common vague gamma prior for all concentration parameters
alphaa = 1;
alphab = 1;
% if sampling is not used, alpha = alphaa / alphab

% H for G0
hh = ones(lenV, 1);
% hh = ones(300, 1);

% expected number of classes/mixtures/topics
numclass = 6;

verbosity = 2;

%% Sampling

tStart = tic;
[hdp, sample, lik] = hdp_ourf(bEvo, hh, alphaa, alphab, numclass, ...
    trainss, numburnin, numsample, numinterval, doconparam, verbosity);
tElapsed = toc(tStart);
fprintf('The sampling process completes in %gs.\n', tElapsed);

%% Saving result

saveresult(sample, startYear, '../out');
save('../out/raw.mat', 'hdp', 'sample');
