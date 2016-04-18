function qq = ourf_additems(hh,qq,cc,ss)

%sc = sparse(ss,cc,ones(size(ss)),size(qq,1),size(qq,2));
%qq = qq + sc;

if numel(ss) == 0
    return
end

K = size(qq, 2);
W = size(ss, 1);

for ii = 1:W
    am = accumarray(cc', ss(ii, :)', [K 1])';
    qq(ii, :) = qq(ii, :) + am;
end

% [W, D] = size(ss);
% row = 1:D;
%     sc = sparse(row, cc, ss(ii,:), size(qq,1), size(qq,2));
%     qq = qq + sc;