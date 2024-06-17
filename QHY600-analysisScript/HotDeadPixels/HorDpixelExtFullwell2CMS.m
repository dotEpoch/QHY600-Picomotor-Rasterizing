%20 frames: extended fullwell 2CMS mode - gain 40, offset 40, temp below -7, so
%neglectable dark current exp time of 0.001 ms
% sum of histogram -> average, get distribution, find std deviation -> from
% paper, get a map of when pixel value are below/above 7 std a lot. out of
% 20 frames -> above more than 10 times (subject to discussion) -> consider a dead/hot pixel

%get first image -> follow this path -> image 00001 to 00020
cd 'C:\Users\User\Desktop\SharpCap Captures\2024-02-26\Capture\12_50_58';
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
Imean_4 = mean(I0,3);
Istd_4  = std(I0,0,3);

standarddev_4 = mean(Istd_4,'all');
stdofstd_4 = std(Istd_4,0,'all');

I_filter_std_4 = Istd_4;
neg_lim_std_4 = standarddev_4 - 2*stdofstd_4;
pos_lim_std_4  = standarddev_4 + 2*stdofstd_4;

I_filter_std_4(or(I_filter_std_4 < neg_lim_std_4, I_filter_std_4 > pos_lim_std_4)) = 0;
I_filter_std_4(and(I_filter_std_4 >= neg_lim_std_4, I_filter_std_4 <= pos_lim_std_4)) = 1;

stdofmean_4 = std(Imean_4,0,'all');

