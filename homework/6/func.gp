set terminal tikz
set output "eg3.tex"
set title  '$x^2+1$'
set xlabel "$x$ axis"
set ylabel "$y$ axis" 
set arrow from -2,0 to 2,0
plot [-2:2] [-1:4] x*x+1
