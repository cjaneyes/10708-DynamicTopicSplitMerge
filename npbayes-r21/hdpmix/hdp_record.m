function [old_M, old_beta, old_k] = hdp_record(sample)

old_beta = sample{1,1}.beta(2);
old_M = sample{1,1}.classnt(2);
old_k = sample{1,1}.numclass;