function saveresult(sample, startYear, outDir)

if ~exist(outDir, 'dir')
    mkdir(outDir);
end

n = length(sample);

for i = 1:n
    datacc = sample{i}.datacc{2}';
    k = sample{i}.numclass;
    clusterdd = cell(k, 1);
    fileID = fopen(fullfile(outDir, sprintf('clusterdd_%d.txt', startYear + i - 1)), 'w');
    for j = 1:k
        clusterdd{j} = find(datacc == j);
        ndd = numel(clusterdd{j});
        fprintf(fileID, '%d\t', ndd);
        fprintf(fileID, '%d\t', clusterdd{j});
        fprintf(fileID, '\n');
    end
    fclose(fileID);
    if i ~= 1
        lambda = sample{i}.lambda;
        lambda = lambda ./ repmat(sum(lambda, 1),  size(lambda, 1), 1);
        dlmwrite(fullfile(outDir, sprintf('lambda_%d.txt', startYear + i - 1)), lambda, '\t');
    end
end

