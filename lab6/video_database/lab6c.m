clear;clc;

% Reading Tank images
for j=1:9
 s=sprintf('tank_0%d.raw',j);
 fid=fopen(s,'r');
 tank(:,:,j)=(fread(fid,[486,486],'uchar'))';
 fclose(fid);
end

% Pyramid decomposition

%*******************************************************************************
% Your code goes in here.
% Generate the coded and diff images and display them 
% after appropriate intensity rescaling
%*******************************************************************************

% Conceptually, if images have to be transmitted, the following frames will be sent:
% coded(:,:,k); k=1,5,9 and diff(:,:,k); k=2,3,4,6,7,8.

%*******************************************************************************
% Your code goes in here
% Getting back the data (decoding)
% recon=coded+diff;
% Check for Perfect Reconstruction by computing MSE:
%*******************************************************************************

for j=1:9
    if mod(j,2)~=1
        difference(:,:,j) = tank(:,:,j) - (tank(:,:,j-1) + tank(:,:,j+1))/2;
    end
end

for j=1:9
    if mod(j,2)~=0 && mod(j-1,4) && j~=9
        difference(:,:,j) = tank(:,:,j) - (tank(:,:,j-2) + tank(:,:,j+2))/2;
    end
end

for j=1:9
    if mod(j+1, 4) == 0
        temp(:,:,j) = (tank(:,:,j-2) + tank(:,:,j+2))/2;
        recon(:,:,j) = temp(:,:,j) + difference(:,:,j);
    else 
        recon(:,:,j) = tank(:,:,j);
    end
end

for j=1:9
    if mod(j,2) == 0
        temp(:,:,j) = (recon(:,:,j-1) + recon(:,:,j+1))/2;
        recon(:,:,j) = temp(:,:,j) + difference(:,:,j);
    end

end

MSE=0;
for j=1:9
 MSE=MSE+norm(recon(:,:,j)-tank(:,:,j),'fro')^2;
end
MSE % Should be zero
