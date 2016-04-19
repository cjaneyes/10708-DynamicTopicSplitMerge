function [hdp, sample, lik] = hdp_ourf(hh, alphaa, alphab,...
    numclass,trainss,...
    trainnumburnin,trainnumsample,trainnumspace,...
    trainconparam)

func = ourf_bundle_func;

hdp = hdp_init(func, [0 1], [1 1], hh, alphaa, alphab); 
hdp = hdp_setdata(hdp, 2, trainss);

% random initialization
hdp = dp_activate(hdp, [1 2], numclass);

[sample, hdp, lik] = hdp_posterior(hdp,trainnumburnin,trainnumsample,...
                   trainnumspace,trainconparam, 0, 4);

