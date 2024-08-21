clear; close all
%% Realigned spectro 2024-08-16, T=-7C, texp=40s, Ext Fullwell Mode, Gain 26
Rstack=fitsread("Capture_00008.fits");
Rsing=fitsread("Capture_00008.fits");
%% Rotating frame   
Rstack=imrotate(Rstack,-0.15,'crop');
Rsing=imrotate(Rsing,-0.15,'crop');
%% Median filtering over 3x3 region
Rstack=nanmedfilt2(Rstack,3);
Rsing=nanmedfilt2(Rsing,3);
%% Spectrum average - Background
Ramanstack=mean(Rstack(560:565,:))-mean(Rstack(540:555,:));
Ramansing=mean(Rsing(560:565,:))-mean(Rsing(540:555,:));
%% Spectra plots
hold on
%plot(Ramansing,'.-')
plot(Ramanstack,'k.-')
%% Crude estimate of spectro scaling/calib, Normalized plots
x=linspace(498,648,9576);
x=1e7.*(1/532-1./x);
%%
hold on
plot(x,Ramansing)
plot(x,Ramanstack,'k.-')
%% Surface plots of various peaks 
Las=Rstack(540:580,1700:2700);
Si=Rstack(550:580,2600:3600);
TAmaybe=Rstack(550:570,2000:3000);
G=Rstack(550:580,4600:5600);
twoD=Rstack(550:580,7100:8100);
%%
figure()
subplot(221);
surf(Las);
title('Laser')
shading interp
subplot(222);
surf(Si);
title('Si')
shading interp
subplot(223);
surf(G);
title("G peak")
shading interp
subplot(224);
surf(twoD);
title('2D peak')
shading interp
%%
[pks,locs]=findpeaks(Ramanstack,'MinPeakDistance',8,'MinPeakHeight',20);
%%
numPeaks = length(pks);
initialParams = [];
for i = 1:numPeaks
    initialParams = [initialParams pks(i) x(locs(i)) 30]; % Assuming initial width of 30
end
%%
options = optimset('Display','off');
[fittedParams, resnorm] = lsqcurvefit(@multiGauss, initialParams, x, Ramanstack, [], [], options);
%%
%xt=linspace(1,length(CombSpec),10*length(CombSpec));
fittedY = multiGauss(fittedParams, x);
plot(x, Ramanstack, '.', 'DisplayName', 'Original Data');
hold on;
plot(x, fittedY, 'k', 'DisplayName', 'Fitted Curve');
legend show;
%% Fitting confidence for G peak only test
RamanGpeak=Ramanstack(4800:5600);
xG=x(4800:5600);
plot(xG,RamanGpeak,'.')
plot(xG,fittedY)



%%
Rstacktrim=Rstack(540:590,:);
xT=linspace(1,length(twoD),length(twoD));
yT=linspace(1,height(twoD),height(twoD));

%%
function y = multiGauss(params, x)
    nGaussians = length(params) / 3;
    y = zeros(size(x));
    for i = 1:nGaussians
        a = params(3*i-2);
        b = params(3*i-1);
        c = params(3*i);
        y = y + a * exp(-(x - b).^2 / (2 * c^2));
    end
end

function y = Gauss(params, x)
        a = params(3*i-2);
        b = params(3*i-1);
        c = params(3*i);
        y = y + a * exp(-(x - b).^2 / (2 * c^2));
end
