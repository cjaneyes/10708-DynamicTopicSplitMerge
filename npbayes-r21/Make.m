bDebugMex = 0;

cd distributions/ourf;
try
    if bDebugMex
        mex -g hdp_ourf_iterate.cpp
    else
        mex hdp_ourf_iterate.cpp
    end
catch ME
    cd ../..;
    rethrow(ME);
end
cd ../../utilities;
try
    if bDebugMex
        mex -g randgamma.cpp
        mex -g randnumtable.cpp
    else
        mex randgamma.cpp
        mex randnumtable.cpp
    end
catch ME
    cd ..
    rethrow(ME);
end
cd ..

