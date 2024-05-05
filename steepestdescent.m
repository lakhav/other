%steepest
clc 
clear all
f = @(x,y)(x^2 - x*y + y^2);
grad_f = @(x,y)[2*x-y, -x+2*y];
X0 = [1, 0.5];
for i = 1:4
    X1 = X0 - 2/3*(grad_f(X0(1), X0(2)))
    if abs(f(X1(1), X1(2)) - f(X0(1), X0(2))) < 0.01
        fprintf('ans found ')
        break; 
    end
    X0 = X1;
end
X0
f(X0(1),X0(2))
