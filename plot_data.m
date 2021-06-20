clear all; clc;

data = csvread("2021-05-25_125032.csv");

best = data(:, 1);

avgBest = zeros(size(best));
for i = 1:size(avgBest)
  for j = 1:i
    avgBest(i) += best(j);
  endfor
  avgBest(i) /= i;
endfor

bestFitness = data(:, 2);
avgBestFitness = zeros(size(bestFitness));
for i = 1:size(avgBestFitness)
  for j = 1:i
    avgBestFitness(i) += bestFitness(j);
  endfor
  avgBestFitness(i) /= i;
endfor


x = 1:size(best);

subplot(2, 1, 1);
ax = plotyy(x, best, x, avgBest);
title ("Evolution du score obtenu par le meilleur individu");
xlabel ("Génération");
ylabel (ax(1), "Score");
ylabel (ax(2), "Score Moyen");

subplot(2, 1, 2);
ax = plotyy(x, bestFitness, x, avgBestFitness);
title ("Différence entre le meilleur individu et la population");
xlabel ("Génération");
ylabel (ax(1), "Fitness");
ylabel (ax(2), "Fitness Moyenne");