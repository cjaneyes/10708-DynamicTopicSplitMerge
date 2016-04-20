bDebugMex = 1;

cd distributions/ourf;
try
    if bDebugMex
        mex -g hdp_ourf_iterate.c
    else
        mex hdp_ourf_iterate.c
    end
catch ME
    cd ../..;
    rethrow(ME);
end
cd ../../utilities;
try
    if bDebugMex
        mex -g randgamma.c
        mex -g randnumtable.c
    else
        mex randgamma.c
        mex randnumtable.c
    end
catch ME
    cd ..
    rethrow(ME);
end
cd ..

