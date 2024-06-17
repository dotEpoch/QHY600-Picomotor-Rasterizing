cd '..\..\CompileMexFiles\output\x64';

global ret
global camID

[ret, camID] = QHY_1_SearchCamera();
if(ret == 0)
    ret = QHY_2_SetReadMode(camID, 0.0);
    if(ret == 0)
        ret = QHY_3_SetStreamMode(camID, 1.0);
        if(ret == 0)
            ret = QHY_4_InitCamera(camID);
            if(ret == 0)
                ret = QHY_5_SetFormat(camID, 'RAW8');
                if(ret == 0)
                    ret = QHY_5_SetBIN(camID, '1X1');
                    if(ret == 0)
                        fprintf("ret = %d\n", ret);
                    end
                end
            end
        end
    end
end
