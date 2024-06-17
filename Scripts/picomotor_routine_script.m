%Thanks to Adriaan Taal for very helpful MATLAB functions:
    %https://www.mathworks.com/matlabcentral/fileexchange/64704-newport-serial-device-communcation
    
    %Most of the following code is from the above link but slightly modified for the New Focus 8742.


%BEFORE RUNNING THE SCRIPTS -> Make sure the proper driver are installed on
%                              your device (Use the USB key provided)
%                           -> Plug the power connector on the right (opposite of left) DC slot
%                           -> Hit the power switch
%                           -> Connect our device using the USB cable


%Set the number of steps here -> This scripts will for now perform a loop
%-> x steps in x-axis, y steps in y-axis, then -x steps in x-axis, and -y
%steps in y-axis
xaxis_steps = 10000;
yaxis_steps = 10000;
USBADDR = 1; %Set in the menu of the device, only relevant if multiple are attached

NPasm = NET.addAssembly('C:\Program Files (x86)\New Focus\New Focus Picomotor Application\Bin\UsbDllWrap.dll'); %load UsbDllWrap.dll library (Path may change from one device to another)
    
NPASMtype = NPasm.AssemblyHandle.GetType('Newport.USBComm.USB'); %Get a handle on the USB class

NP_USB = System.Activator.CreateInstance(NPASMtype); %launch the class USB, it constructs and allows to use functions in USB.h
    
NP_USB.OpenDevices();  %Open the USB device
   
 %The Query method sends the passed in command string to the specified device and reads the response data.
querydata = System.Text.StringBuilder(36);
NP_USB.Query(USBADDR, '*IDN?', querydata);
devInfo = char(ToString(querydata));
fprintf(['Device attached is ' devInfo '\n']); %display device ID to make sure it's recognized OK
    
 %now do some controlling with serial commands given in
 %8742_User_Manual_revB.PDF (page 60)

cmd_xaxis1 = strcat('1PR',num2str(xaxis_steps));
cmd_yaxis1 = strcat('2PR',num2str(yaxis_steps));
cmd_xaxisneg = strcat('1PR', num2str(-xaxis_steps));
cmd_yaxisneg = strcat('2PR',num2str(-yaxis_steps));


NP_USB.Write(USBADDR,[cmd_yaxisneg]); %e.g. relative move by 10000 steps on the x-axis (1 in 1PR stands for Motor 1)
pause(6);
NP_USB.Write(USBADDR,[cmd_yaxis1]);
[is_moving,qstatus] = picomotor_is_moving(2,NP_USB,USBADDR);
% fprintf(['1 \n']);
% 
% test = System.Text.StringBuilder(1);
% NP_USB.Query(USBADDR,'1MD?',test);
% fprintf([char(toString(test))]);
% 
% 
% 
% cmd_yaxis1 = strcat('2PR',num2str(yaxis_steps));
% NP_USB.Write(USBADDR,[cmd_yaxis1]); %e.g. relative move by 10000 steps on the y-axis (2 stand for Motor 2)
% fprintf(['2 \n']);
% cmd_xaxis2 = strcat('1PR', num2str(-xaxis_steps));
% NP_USB.Write(USBADDR,[cmd_xaxis2]); %e.g. relative move by -10000 steps on the x-axis (1 in 1PR stands for Motor 1)
% fprintf(['3 \n']);
% cmd_yaxis2 = strcat('2PR',num2str(-yaxis_steps));
% NP_USB.Write(USBADDR,[cmd_yaxis2]); %e.g. relative move by -10000 steps on the y-axis (2 stand for Motor 2)
% fprintf(['4 \n']);

