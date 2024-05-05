format short
clear all
clc

%%input variables
c = [-1 3 -2];
info = [3 -1 2;-2  4  0;-4 3  8;]
b = [7; 12 ;10];


noOfVariables = size(info,1) 

s= eye(size(info,1))
A= [info s b]

cost = zeros(1,size(A,2));

cost(1 : noOfVariables) =c

%constraint basic variable
BV = noOfVariables+1 :size(A,2) -1

%calculate zj-cj
zjcj = cost(BV)*A -cost;

%print the table
zcj=[zjcj ; A]

simplexTable = array2table(zcj);

simplexTable.Properties.VariableNames(1:size(zcj,2)) ={'x1','x2','x3','s1','s2','s3','sol'}

%check if any negative value there
% Simplex Table start
run =true;
iteration =1;
while run

    if any(zjcj <0)
        
        disp(' The current BFS is not optimal ');
        fprintf('Current iteration is: %d\n', iteration)
        disp('=========Next iteration results============');
        
        disp('Old Basic Variables :');
        disp(BV);
        
        %finding the enetering variable
        
        ZC =zjcj(1:end-1);
        [enteringvalue pvtCol] = min(ZC);
        fprintf('Minimum value is %d and \npivot column is : %d  \n' ,enteringvalue,pvtCol);
        fprintf('entering variable is : %d \n',pvtCol);
        
        %finding leaving variable
        sol = A(:,end)
        Column = A(: , pvtCol);
        
        if all (Column <= 0)
            error('Lpp is unbounded, alll entries are <=0 in column %d', pvtCol);
        else
            
            for i=1 :size(Column,1)
                if Column(i) > 0
                    ratio(i) = sol(i)./Column(i);
                else
                    ratio(i) =inf;
                end
        
            end
        end
    
    %finding the minimum ratio pivot column
        
        [MinRatio ,pvtRow] = min(ratio);
    
        fprintf('Minimum Ratio corresponding to pivot row is %d \n', pvtRow);
        fprintf('Leaving Variable is :%d \n', BV(pvtRow));
        
        BV(pvtRow) =pvtCol;
        disp('New Basic Variables (BV) =');
        disp(BV);
    
        %% PIVOT KEY
        pvt_key =A(pvtRow,pvtCol);
    
        %update table for next iteration
    
        A(pvtRow,:)=A(pvtRow,:)./pvt_key;
        for i=1:size(A,1)
            if i~=pvtRow
                A(i,:)=A(i,:)-A(i,pvtCol)*A(pvtRow,:)
            end
        end
        
        zjcj=zjcj-zjcj(pvtCol)*A(pvtRow,:)
        zcj=[zjcj;A]
        
        table=array2table(zcj)
        
        table.Properties.VariableNames(1:size(zcj,2)) ={'x1','x2','x3','s1','s2','s3','sol'}
        
        BFS = zeros(1,size(A,2));
    
        BFS(BV) = A(:,end);
    
        BFS(end) =sum(BFS .* cost);
    
        current_BFS = array2table(BFS);
        
    
        current_BFS.Properties.VariableNames(1:size(zcj,2)) ={'x1','x2','x3','s1','s2','s3','sol'}
        
        iteration = iteration+ 1;
   
%
    else
        run =false;
        disp('*******************************************')
        disp('=========Current BFS is optimal============');
        fprintf('\nCurrentIteration is : %d \n',iteration);
    end;
    
end