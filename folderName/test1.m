t = string(datetime('now','Format','yyyy-MM-dd_HH_mm_ss'));
lpath = "C:\Users\User\Documents\QHY600-Capture\SingleCapture\";
fName = strcat(string(t),"/");
sprintf('%s',t);
mkdir(fullfile(lpath,t));
txtName = fullfile(fName,'Capturedata.txt');
txtFile = fopen(fullfile(lpath,txtName),'wt');                   
fprintf(txtFile,'test\n');
fclose(txtFile);                   
imName = fullfile(fName,'Capture.fits');                   
fitswrite(ImgData,fullfile(lpath,imName));                   
fprintf(txtFile,'test\n');             
fclose(txtFile);
                    