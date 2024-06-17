
USBADDR = 1;
NPasm = NET.addAssembly('C:\Program Files (x86)\New Focus\New Focus Picomotor Application\Bin\UsbDllWrap.dll'); %load UsbDllWrap.dll library (Path may change from one device to another)
    
NPASMtype = NPasm.AssemblyHandle.GetType('Newport.USBComm.USB'); %Get a handle on the USB class

NP_USB = System.Activator.CreateInstance(NPASMtype); %launch the class USB, it constructs and allows to use functions in USB.h
    
NP_USB.OpenDevices();  %Open the USB device
   
querydata = System.Text.StringBuilder(64);
NP_USB.Query(USBADDR, '*IDN?', querydata);
devInfo = char(ToString(querydata));
fprintf(['Device attached is ' devInfo '\n']); %display device ID to make sure it's recognized OK
NP_USB.Write(USBADDR,['2PR1000']);



cmd = strcat(num2str(1),'MD?');
qstatus = NP_USB.Query(USBADDR, cmd , querydata);
is_moving = str2num(char(ToString(querydata)));

while is_moving == 0
    pause(0.01)
    qstatus = NP_USB.Query(USBADDR, cmd , querydata);
    is_moving = str2num(char(ToString(querydata)));
end
%ADD COMMAND TO DO HERE -> THE MOTOR STOPPED MOVING WHEN YOU REACH THIS
%POINT
%NP_USB.Write(USBADDR,['2PR-1000']);

pause(6)

cmd2 = strcat(num2str(1),'TP?');
qstatus = NP_USB.Query(USBADDR, cmd2 , querydata);
position = str2num(char(ToString(querydata)));



fprintf(['we are testing ' num2str(position) 'this']);