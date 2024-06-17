function [position,qstatus] = picomotor_get_postion(motor_num,NP_USB, USBADDR)

querydata2 = System.Text.StringBuilder(4);
cmd = strcat(num2str(motor_num),'TP?');
qstatus = NP_USB.Query(USBADDR, cmd , querydata2);
position = str2num(char(ToString(querydata2)));


end