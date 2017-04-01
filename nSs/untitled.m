clc
clf
clear all

figure(2)
for i=0:727
    fil=['streak' num2str(i)];
    fil2=[fil '.dat'];
    kk=load(fil2);
    
    plot(kk(:,1),kk(:,2),'*');
  
    axis([0 30 0 4]);
    pause(0.1)
end