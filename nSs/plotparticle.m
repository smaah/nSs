
clc
clf
clear all
close all

 k=['particl' 'e' '.dat'];
 
load(k);
x=particle(:,1);
y=particle(:,2);

[m,~]=size(x);

x=reshape(x,20,m/20);
y=reshape(y,20,m/20);


figure(1)
for i=1:20
plot(x(i,:),y(i,:),'-');
hold on;
end

