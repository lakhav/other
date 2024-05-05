format short
clear all
clc


M=1000;

cost =[-2 -1 0 0 -M -M 0];

a=[3  1  0  0  1  0;
   4  3 -1  0  0  1;
   1  2  0  1  0  0];


b = [3 ;6 ;3];
artifical_var=[5 6];
 BV=[5 6 4 ];
 A=[a b];


Var={'x1','x2','s2','s3','A1','A2','sol'};
%calculate zj-cj
zjcj = cost(BV)*A -cost;

%print the table
zcj=[zjcj ; A]

simplexTable = array2table(zcj,'VariableNames',Var);



%check if any negative value there
% Simplex Table start
run =true;
iteration =1;
while run

    if any(zjcj(1:end-1) <0)
        
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
        
        table=array2table(zcj,'VariableNames',Var)
        
        
        
        BFS = zeros(1,size(A,2));
    
        BFS(BV) = A(:,end);
    
        BFS(end) =sum(BFS .* cost);
    
        current_BFS = array2table(BFS,'VariableNames',Var);
        
    
        
        iteration = iteration+ 1;
   
%
    else
        run = false;
        if any(BV==artifical_var(1))
        error('Infeasible solution');
        else
        fprintf('The table is optimal \n');
        end
    
        Obj_value=zjcj(end);
    
        fprintf('The final optimal value is % f \n',Obj_value);

        disp('*******************************************')
        disp('=========Current BFS is optimal============');
        fprintf('\nCurrentIteration is : %d \n',iteration);
    end
    
end