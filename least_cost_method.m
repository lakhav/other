cost= [2,7,4;3,3,1;5,5,4;1,6,2]
A=[5,8,7,14]
B= [7,9,18]



if sum(A)==sum(B)
    fprintf('Given TP is balanced\n')
else 
    fprintf('Given TP is unbalanced\n')
    if sum(A)<sum(B)  %% add dummy row
        cost(end+1,:)=zeros(1,size(cost,2));
        A(end+1)=sum(B)-sum(A);
    elseif sum(A)>sum(B) %% add dummy col 
        cost(:,end+1)=zeros(size(cost,1),1);
        B(end+1)=sum(A)-sum(B);
    end
end


initial_cost = cost;
X= zeros(size(cost));
[m n] = size(cost);
BFS = m+n-1;

for i=1:size(cost,1)
    for j=1:size(cost,2)

        ll = min(min(cost));
        [row_ind col_ind] = find(ll == cost)
        x11 = min(A(row_ind) , B(col_ind));
        [val ind] = max(x11)
        ii = row_ind(ind)
        jj = col_ind(ind)

        y11=min(A(ii),B(jj))

        X(ii,jj)= y11

        A(ii) = A(ii) -y11
        B(jj) = B(jj) -y11
        cost(ii,jj) = inf;


    end
end


total_bfs = length(nonzeros(X))

if total_bfs == BFS
    disp('Non_deg')
else
    disp('deg')
end

cost= sum(sum(initial_cost .* X))
