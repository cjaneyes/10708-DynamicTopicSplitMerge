function [hdp, sample, lik] = hdp_ourf(bEvo, hh, alphaa, alphab,...
    numclass,trainss,...
    trainnumburnin,trainnumsample,trainnumspace,...
    trainconparam)

func = ourf_bundle_func;

if bEvo
    T = length(trainss);
    hdp = hdp_init(func, [0 1], [1 1], hh, alphaa, alphab); 
    hdp = hdp_setdata(hdp, 2, trainss{1});

    % random initialization
    hdp = dp_activate(hdp, [1 2], numclass);

    [sample, hdp, lik] = hdp_posterior(hdp,trainnumburnin,trainnumsample,...
                       trainnumspace,trainconparam, 0, 4, false);
    % get data from t-1
    
    %  hdp.base.??? = ?;
    % Record old statistics
    [old_classnt, old_beta, old_numclass] = hdp_record(sample);
    
    for t = 2:T
        hdp = hdp_init(func, [0 1], [1 1], hh, alphaa, alphab); 
        hdp = hdp_setdata(hdp, 2, trainss{1});
        
        % random initialization
        hdp = dp_activate(hdp, [1 2], numclass);
        hdp.base.old_classnt = old_classnt;
        hdp.base.old_beta = old_beta;
        hdp.base.old_numclass = old_numclass;
        
        [sample, hdp, lik] = hdp_posterior(hdp,trainnumburnin,trainnumsample,...
                           trainnumspace,trainconparam, 0, 4, true);
         % Record old statistics
        [old_classnt, old_beta, old_numclass] = hdp_record(sample);
    end
else
    hdp = hdp_init(func, [0 1], [1 1], hh, alphaa, alphab); 
    hdp = hdp_setdata(hdp, 2, trainss);

    % random initialization
    hdp = dp_activate(hdp, [1 2], numclass);

    [sample, hdp, lik] = hdp_posterior(hdp,trainnumburnin,trainnumsample,...
                       trainnumspace,trainconparam, 0, 4);

end

