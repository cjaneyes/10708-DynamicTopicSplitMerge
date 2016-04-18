function qq = ourf_additems(hh,qq,cc,ss);

%sc = sparse(ss,cc,ones(size(ss)),size(qq,1),size(qq,2));
%qq = qq + sc;

if numel(ss) == 0
    return
end

[W, D] = size(ss);
row = 1:D;
for ii=1:W
    sc = sparse(row, cc, ss(ii,:), size(qq,1), size(qq,2));
    qq = qq + sc;
end

