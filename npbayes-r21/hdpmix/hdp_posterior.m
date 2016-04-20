function [sample,hdp,lik]=hdp_posterior(hdp,numburnin,numsample,numspace,...
                                        doconparam,dolik,dodebug, bEvo)
% runs hdp, gets samples for classqq, totalnt.  These are enough to form
% predictive likelihoods for unseen data.

totiter = numburnin + numsample*numspace;
sample  = cell(1,numsample);
lik     = zeros(1,numburnin+numsample*numspace);

assert(all(hdp.base.classqq(:) >= 0));
[hdp, ll] = hdp.func.iterate(hdp,numburnin,doconparam,dolik,dodebug, bEvo);
lik(1:numburnin) = ll;
for samp = 1:numsample
  [hdp, ll] = hdp.func.iterate(hdp,numspace,doconparam,dolik,dodebug, bEvo);
  lik(numburnin+(samp-1)*numspace+(1:numspace)) = ll;
  sample{samp} = hdp_getstate(hdp);
end