function [error_num,qstatus] = picomotor_get_error_stat(motor_num,NP_USB, USBADDR)

querydata = System.Text.StringBuilder(1);
cmd = strcat(num2str(motor_num),'TE?');
qstatus = NP_USB.Query(USBADDR, cmd , querydata);
error_num = str2num(char(ToString(querydata)));


end