
cd hdpmix
try
  mex hdpMultinomial_iterate.c
  mex hdpMultinomial_predict.c
catch ME
    cd ..
    rethrow(ME);
end
cd ..
