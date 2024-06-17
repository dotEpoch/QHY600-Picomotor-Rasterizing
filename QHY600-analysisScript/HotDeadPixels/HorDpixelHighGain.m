%20 frames: high gain mode - gain 56, offset 40, temp below -7, so
%neglectable dark current exp time of 0.001 ms
% sum of histogram -> average, get distribution, find std deviation -> from
% paper, get a map of when pixel value are below/above 7 std a lot. out of
% 20 frames -> above more than 10 times (subject to discussion) -> consider a dead/hot pixel

%get first image -> follow this path -> image 00001 to 00020
cd 'C:\Users\User\Desktop\SharpCap Captures\2024-02-21\Capture\11_07_41';
I0 = fitsread("Capture_00001.fits");

for i=2:20
    
    if i<10
        filename = strcat("Capture_0000",num2str(i),".fits");
        
    else
        filename = strcat("Capture_000",num2str(i),".fits");
        
    end 
    
    Itemp = fitsread(filename);
    I0(:,:,i)=Itemp;
    

    %I0 = I0 + Itemp;
end
Imean_2 = mean(I0,3);
Istd_2  = std(I0,0,3);

standarddev_2 = mean(Istd_2,'all');
stdofstd_2 = std(Istd_2,0,'all');

I_filter_std_2 = Istd_2;
neg_lim_std_2 = standarddev_2 - 2*stdofstd_2;
pos_lim_std_2  = standarddev_2 + 2*stdofstd_2;

I_filter_std_2(or(I_filter_std_2 < neg_lim_std_2, I_filter_std_2 > pos_lim_std_2)) = 0;
I_filter_std_2(and(I_filter_std_2 >= neg_lim_std_2, I_filter_std_2 <= pos_lim_std_2)) = 1;

stdofmean_2 = std(Imean_2,0,'all');


I_filt_hg = fitsread("Capture_00001.fits");
I_filt_hg(I_filt_hg < neg_lim_2) = -1;
I_filt_hg(I_filt_hg > pos_lim_2) = 1;
I_filt_hg(I_filt_hg >= neg_lim_2 & I_filt_hg <= pos_lim_2) = 0;

for i=2:20
    
    if i<10
        filename = strcat("Capture_0000",num2str(i),".fits");
        
    else
        filename = strcat("Capture_000",num2str(i),".fits");
        
    end 
    Itemp = fitsread(filename);
    Itemp(Itemp<neg_lim_2) = -1;
    Itemp(Itemp > pos_lim_2) = 1;
    Itemp(and(Itemp >= neg_lim_2,Itemp <= pos_lim_2)) = 0;
    I_filt_hg = I_filt_hg + Itemp;
end
