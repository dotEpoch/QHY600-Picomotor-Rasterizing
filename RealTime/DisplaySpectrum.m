function DisplaySpectrum(frame)
    

%% Realigned spectro 2024-08-16, T=-7C, texp=40s, Ext Fullwell Mode, Gain 26
%Rstack=fitsread("Stack_16bits_5frames_200s.fits");
Rsing=fitsread("Capture_00008.fits");

%% Rotating frame
%Rstack=imrotate(Rstack,-0.15,'crop');
Rsing=imrotate(Rsing,-0.15,'crop');

%% Median filtering over 3x3 region
%Rstack=nanmedfilt2(Rstack,3);
Rsing=nanmedfilt2(Rsing,3);

%% Spectrum average - Background
%Ramanstack=mean(Rstack(560:565,:))-mean(Rstack(540:555,:));
Ramansing=mean(Rsing(560:565,:))-mean(Rsing(540:555,:));

%% Spectra plots
hold on
plot(Ramansing,'.-')
%plot(Ramanstack,'k.-')
% @@@@@@@@@@@ %

%  % create a figure
% axh = axes('Parent',fgh); % create axes
% X = 0:0.1:pi;
% Y = sin(X);
% lnh = plot(axh,X,Y); % plot in those axes
% pause(0.1)
% set(lnh,'XData',[0,1,2],'YData',[1,2,1]) % change the line data

% realignedspectro
%pause(0.1) % 0.1 second long ticks for optimization

end