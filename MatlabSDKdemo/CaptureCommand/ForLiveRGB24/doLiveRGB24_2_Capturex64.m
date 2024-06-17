cd '..\..\CompileMexFiles\output\x64';

global ret
global camID
fprintf("ret = %d camID = %s\n", ret, camID);

if(ret == 0)
%     QHY_6_SetROI(camID, 100.0, 100.0, 1568.0, 1052.0);
    QHY_6_SetExposeTime(camID, 30000.0);
    QHY_6_SetGain(camID, 50.0);
    QHY_6_SetLiveWBR(camID, 50.0);
    QHY_6_SetLiveWBG(camID, 50.0);
    QHY_6_SetLiveWBB(camID, 50.0);
    QHY_6_SetOffset(camID, 50.0);
    QHY_6_SetLiveBrightness(camID, 0.0);
    QHY_6_SetLiveContrast(camID, 0.0);
    QHY_6_SetLiveGamma(camID, 1.0);
    
    [ret, format] = QHY_7_GetDebayer(camID);
    fprintf("ret = %d %s\n", ret, format);

    ret = QHY_10_BeginLiveExpose(camID);
    if(ret == 0)
        ret = QHY_6_SetDDR(camID, 1.0);
        if(ret == 0)
            %Get one image first
            [ret, w, h, bpp, channels, R, G, B] = QHY_10_GetOneLiveFrame(camID);
            if(ret==0)
                fprintf("QHY_10_GetOneLiveFrame returned ret = %d w = %d h = %d\n", ret, w, h);
                if(strcmp(format, "GBRG")==0)
                    RGB = cat(3, B, G, R);
                elseif(strcmp(format, "GRBG")==0)
                    RGB = cat(3, G, R, B);
                elseif(strcmp(format, "BGGR")==0)
                    RGB = cat(3, B, G, R);
                elseif(strcmp(format, "RGGB")==0)
                    RGB = cat(3, R, G, B);
                else
                    RGB = cat(3, R, G, B);
                end
                image(RGB);

                frameNum = 0;
                while(frameNum < 100)
                    tic

                    ret = QHY_6_SetDDR(camID, 1.0);
                    if(ret == 0)
                        [ret, w, h, bpp, channels, R, G, B] = QHY_10_GetOneLiveFrame(camID);
                        if(ret==0)
                            fprintf("QHY_10_GetOneLiveFrame returned ret = %d w = %d h = %d\n", ret, w, h);
                            if(strcmp(format, "GBRG")==0)
                                RGB = cat(3, B, G, R);
                            elseif(strcmp(format, "GRBG")==0)
                                RGB = cat(3, G, R, B);
                            elseif(strcmp(format, "BGGR")==0)
                                RGB = cat(3, R, G, B);
                            elseif(strcmp(format, "RGGB")==0)
                                RGB = cat(3, R, G, B);
                            else
                                RGB = cat(3, R, G, B);
                            end
                            imshow(RGB);
                            frameNum = frameNum + 1;
                            pause(0.01)
                        end %end get frame
                    end %end set DDR

                    toc
                end %end while
            end %end get live frame
        end %end set DDR
        QHY_10_StopLiveCapture(camID);
    end %end begin live
end %end ret

clear QHY_6_SetExposeTime;
clear QHY_6_SetGain;
clear QHY_6_SetOffset;
clear QHY_6_SetLiveBrightness;
clear QHY_6_SetLiveContrast;
clear QHY_6_SetLiveGamma;
clear QHY_6_SetDDR;
clear QHY_9_BeginLiveExpose;
clear QHY_9_GetOneLiveFrame;
clear QHY_9_StopLiveCapture;
