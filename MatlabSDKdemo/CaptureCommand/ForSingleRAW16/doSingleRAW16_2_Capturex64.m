cd '..\..\CompileMexFiles\output\x64';

global ret
global camID

if(ret == 0)
    ret = QHY_6_SetExposeTime(camID, 20000.0);
    fprintf("Expose Time ret = %d\n", ret);
    ret = QHY_6_SetGain(camID, 10.0);
    fprintf("Gain ret = %d\n", ret);
    ret = QHY_6_SetOffset(camID, 10.0);
    fprintf("Offset ret = %d\n", ret);
    ret = QHY_6_SetDDR(camID, 1.0);
    fprintf("DDR ret = %d\n", ret);
    ret = QHY_9_BeginSingleExpose(camID);
    fprintf("Begin single expose ret = %d\n", ret);
    [ret, w, h, bpp, channels, ImgData] = QHY_9_GetOneSingleFrame(camID);
    fprintf("Get Single Frame ret = %d\n", ret);
    if(ret == 0)
        fprintf("w = %d h = %d bpp = %d channels = %d\n", w, h, bpp, channels);
        imwrite(ImgData,"C:\Users\User\Desktop\ImageMatlabTest\SingleCaptureTest\test1.png");
        imshow(ImgData);
    end
    ret = QHY_9_StopSingleCapture(camID);
    fprintf("Stop Single Capture ret = %d\n", ret);
end

clear QHY_6_SetExposeTime;
clear QHY_6_SetGain;
clear QHY_6_SetOffset;
clear QHY_6_SetDDR;
clear QHY_9_BeginSingleExpose;
clear QHY_9_GetOneSingleFrame;
clear QHY_9_StopSingleCapture;