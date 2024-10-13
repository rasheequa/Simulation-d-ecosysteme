set title "Evolution des populations"
set xlabel "Nombre de générations"
set ylabel "Nombre d'individus"
set xrange [0:150]
set yrange [0:200]
set xtics 50

plot "Evol_Pop.txt" using 1:2 with lines title "Proies", \
     "Evol_Pop.txt" using 1:3 with lines title "Prédatset title "Evolution des populations"
set xlabel "Nombre de generations"
set ylabel "Nombre d'individus"
set xrange [0:100]
set yrange [0:1400]

plot "Evol_Pop.txt" using 1:2 with lines title "Proies", \
     "Evol_Pop.txt" using 1:3 with lines title "Predateurs"
eurs"
