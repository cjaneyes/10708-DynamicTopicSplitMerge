function [old_M, old_beta, old_k] = hdp_record(sample)

old_k = sample{1,1}.numclass;

old_beta = sample{1,1}.beta{2};
old_beta = old_beta(1,1:old_k);
old_beta = old_beta / sum(old_beta);

old_M = sample{1,1}.classnt{2};
old_M = old_M(1,1:old_k);
