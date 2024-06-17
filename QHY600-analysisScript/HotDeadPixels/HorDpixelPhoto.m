%20 frames: photographic mode - gain 26, offset 40, temp around -7, so
%neglectable dark current exp time of 0.001 ms
%gamma 1, brithness 0 contrast 0 binning 1x1 full ROI (6000x9600) color
%Space Mono16 (max information we can get)
% sum of histogram -> average, get distribution, find std deviation -> from
% paper, get a map of when pixel value are below/above 7 std a lot. out of
% 20 frames -> above more than 10 times (subject to discussion) -> consider a dead/hot pixel

%get first image -> follow this path -> image 00002 to 00021
cd 'C:\Users\User\Desktop\SharpCap Captures\2024-02-21\Capture\11_05_57';
I0 = fitsread("Capture_00001.fits");

for i=2:20
    
    if i<10
        filename = strcat("Capture_0000",num2str(i),".fits");
        
    else
        filename = strcat("Capture_000",num2str(i),".fits");
        
    end 
    Itemp = fitsread(filename);
    %Itemp = fitsread(filename,'PixelRegion',{[17 6405],[12 9588]});
    I0(:,:,i)=Itemp;
    

    %I0 = I0 + Itemp;
end
Imean = mean(I0,3);
Istd  = std(I0,0,3);

standarddev = mean(Istd,'all');
stdofstd = std(Istd,0,'all');

I_filter_std = Istd;
neg_lim_std = standarddev - 2*stdofstd;
pos_lim_std  = standarddev + 2*stdofstd;
neg_lim_std_7std = standarddev - 7*stdofstd;
pos_lim_std_7std  = standarddev + 7*stdofstd;


I_filter_std(or(I_filter_std < neg_lim_std, I_filter_std > pos_lim_std)) = 255;
I_filter_std(and(I_filter_std >= neg_lim_std, I_filter_std <= pos_lim_std)) = 0;

stdofmean = std(Imean,0,'all');
mean_of_all = mean(Imean,'all');


numofstd = 7;
neg_lim = Imean - numofstd*standarddev;
pos_lim = Imean + numofstd*standarddev;



filtered_std = filterwithmap(Imean,I_filter_std);



function filteredImage = filterwithmap(image,map)
    
    filteredImage = zeros(size(image));
    for i=1:6422
        for j=1:9600
            if map(i,j) == 0
                filteredImage(i,j) = 0; %Not sure what to do here -> average compared to the neighbour pixels?
            else
                filteredImage(i,j)= image(i,j);
            end
        end
    end

end



