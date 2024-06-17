cd '..\..\CompileMexFiles\output\x64';

global ret
global camID
fprintf("ret = %d camID = %s\n", ret, camID);

if(ret == 0)
    QHY_6_SetExposeTime(camID, 15000.0);
    QHY_6_SetGain(camID, 10.0);
    QHY_6_SetOffset(camID, 10.0);
    QHY_6_SetLiveBrightness(camID, 0.0);
    QHY_6_SetLiveContrast(camID, 0.0);
    QHY_6_SetLiveGamma(camID, 1.0);

    ret = QHY_10_BeginLiveExpose(camID);
    if(ret == 0)
        ret = QHY_6_SetDDR(camID, 1.0);
        if(ret == 0)
            %Get one image first
            [ret, w, h, bpp, channels, ImgData] = QHY_10_GetOneLiveFrame(camID);
            if(ret==0)
                fprintf("QHY_10_GetOneLiveFrame returned ret = %d w = %d h = %d\n", ret, w, h);
                imshow(ImgData);

                frameNum = 0;
                while(frameNum < 100)
                    tic

                    ret = QHY_6_SetDDR(camID, 1.0);
                    if(ret == 0)
                        [ret, w, h, bpp, channels, ImgData] = QHY_10_GetOneLiveFrame(camID);
                        if(ret==0)
                            fprintf("QHY_10_GetOneLiveFrame returned ret = %d w = %d h = %d\n", ret, w, h);
                            imshow(ImgData);
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
