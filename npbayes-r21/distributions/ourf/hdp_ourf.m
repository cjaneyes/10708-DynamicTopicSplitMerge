function [hdp, sample, lik] = hdp_ourf(hh,alphaa,alphab,...
    numclass,trainss,...
    trainnumburnin,trainnumsample,trainnumspace,...
    trainconparam,fid)

func = ourf_bundle_func;

hdp = hdp_init(func,0,1,hh,alphaa,alphab); 
[hdp trainindex] = hdp_adddp(hdp,length(trainss),1,2);

hdp = hdp_setdata(hdp,trainindex,trainss);

hdp = dp_activate(hdp,[1 trainindex],numclass);

[sample hdp lik] = hdp_posterior(hdp,trainnumburnin,trainnumsample,...
                   trainnumspace,trainconparam,1,0,fid);
hdp = dp_freeze(hdp,trainindex); 
