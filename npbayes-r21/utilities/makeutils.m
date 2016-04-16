
cd utilities
try
  mex randgamma.c
  mex randnumtable.c
catch ME
    cd ..
    rethrow(ME);
end
cd ..
