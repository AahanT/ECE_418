clear;clc;
fid = fopen('lena.raw', 'r'); 
lena = fread(fid, [512, 512]); 
lena = lena' / 255; 
lena_g = imnoise(lena, 'gaussian'); 
lena_s = imnoise(lena, 'salt & pepper');
 
figure;
subplot(1,2,1), imshow(lena_g);
subplot(1,2,2), imshow(lena_s);

h_gauss = fspecial ('gaussian', 5, 0.25); 
h_log = fspecial ('log', 5, 1);

lena_g_smoothed = filter2 (h_gauss, lena_g); 
lena_s_smoothed = filter2 (h_gauss, lena_s); 
lena_g_logged = filter2 (h_log, lena_g); 
lena_s_logged = filter2 (h_log, lena_s);

figure;
subplot(2,2,1), imshow(lena_g_smoothed);
subplot(2,2,2), imshow(lena_s_smoothed);
subplot(2,2,3), imshow(lena_g_logged);
subplot(2,2,4), imshow(lena_s_logged);

lena_s_median = medfilt2 (lena_s, [3 3]);

figure;
imshow(lena_s_median);

for a = 0:50
    lena_s_median = medfilt2(lena_s_median, [3 3]);
end

figure;
imshow(lena_s_median);