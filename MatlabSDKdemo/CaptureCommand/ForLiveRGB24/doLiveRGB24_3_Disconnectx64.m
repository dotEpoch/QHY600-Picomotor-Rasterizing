cd '..\..\CompileMexFiles\output\x64';

global ret
global camID

if(ret == 0)
    ret = QHY_11_CloseCamera(camID);
    fprintf("Close Camera ret = %d\n", ret);
end
