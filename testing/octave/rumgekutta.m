


clear;
kilo =10^( 3);
mili =10^(-3);
micro=10^(-6);
nano =10^(-9);


time = 0.5*mili;    # input("Tiempo simulacion: ");
h    = 1*micro;     # input("Subdiv simulacion: ");
bits = 8;           # input("Bits del PWM: ");
Vhgh = 5;           # input("Vhgh del PWM: ");
freq = 34*kilo;     # input("Freq del PWM: ");
pwm  = 127;         # input("Val. del PWM: ");
ord  = 2 ;          # input("Ord. del filtro RC: ");
res  = 2*kilo;      # input("Res. del filtro RC: ");
cap  = 20*nano;     # input("Cap. del filtro RC: ");
N = floor(time/h);

V=zeros(ord+1,N+1);
t=zeros(  1,N+1);

# Pwm-Gemerator
#function [out] = generatepwm(N,)
for i=0:N
  t(1,i+1) = i*h;
  toFloor=t(1,i+1)*freq;
	if toFloor-floor(toFloor) < (pwm/(2^(bits)-1))
    V(1,i+1) = Vhgh;
	else
    V(1,i+1) = 0;
	end
end

# Rumge-Kutta
# for 0 to max time
# y'= f(x)
#
# V(t) =  Vr + Vc;
# V(t) = i*R + q/C;
# V(t) = q'*R + q/C;
#    q'= (V(t) - q/C) / R;
# x=V , y=q, y0=0;
#
# function [y] = rungekutta(@(x,y) f,x,h)
for j=1:ord
  C=cap;R=res;
  x=V(j,:);
	y=zeros(1,N+1);
  f= @(v,q) (v - q/C) / R;
	for i=1:N
		k1 = f (x(i)    , y(i));
		k2 = f (x(i)+h/2, y(i)+k1*h/2);
		k3 = f (x(i)+h/2, y(i)+k2*h/2);
		k4 = f (x(i)+h  , y(i)+k3*h  );
	  # y(x)
		y(i+1)=y(i) + (k1+2*(k2+k3)+k4) * h/6;
    V(j+1,i+1)=y(i+1)/C;
  end
end



plot(t,V(ord+1,:));
