function [is_moving,qstatus] = picomotor_is_moving(motor_num, NP_USB, USBADDR)
    
querydata = System.Text.StringBuilder(64);
cmd = strcat(num2str(motor_num),'MP?');
qstatus = NP_USB.Query(USBADDR, cmd , querydata);
is_moving = str2num(char(ToString(querydata)));


end

