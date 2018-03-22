x = 0:0.05:10;
y = sin(100*pi*x);

plot(x,y);

N=200;
ft=852;

q_0=0;
q_1=0;
q_2=0;

%coeff = ;

for n = 0:N
    q_0 = 2*cos(0.214*n) * q_1 - q_2 + y(n+1);
    q_2 = q_1;
    q_1 = q_0;
    disp(q_0);
end

magnitude_to_2 = q_1*q_1 + q_2*q_2 - q_1*q_2*q_0;


