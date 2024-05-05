%%Steepest Descent

syms x1 x2 
f1= x1 - x2 + 2*x1^2 +2*x1*x2 +x2^2;

x0=[1 1];
maxiter=4;
iter=0;
tol=0.01;
X=[];
fx=inline(f1);
fobj=@(x) fx(x(:,1),x(:,2));
grad=gradient(f1);
g=inline(grad);
gradx=@(x) g(x(:,1),x(:,2));
h1=hessian(f1);
hx=inline(h1);
while norm(gradx(x0))>tol && iter<maxiter
    X=[X x0];
    s=-gradx(x0);
    h=hx(x0);
    lamda= s'*s./(s'*h*s);
    newx=x0+lamda.*s';
    x0=newx;
    iter=iter+1;
end
fprintf('the values of x are \n%f \n%f\n',x0(1) ,x0(2));
fprintf('\nthe value is %f',fobj(x0));

