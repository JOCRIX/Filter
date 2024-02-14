%LP prototype n = 5
clear
n = 5
%Finder poler
for k = 1:n
    P(k) = exp(j*(((2*k - 1)/(2*n))*pi + pi/2 ))
end

s = tf('s');
(s - P(1)) * (s - P(5))
Pconj1 = s^2 + 0.618*s + 1

(s - P(2)) * (s - P(4))
Pconj2 = s^2 + 1.618*s + 1

Pr = s + 1

H = (1 /( (Pconj1) * (Pconj2) * Pr ))
bodeplot(H)
grid('minor')
%pzplot(H)




