(function(ext) {

	//set Low and High values
	var LOW = 0,
	HIGH = 1;

    var connected = false;

    var hwList = new HWList();

    //set up the device
    function HWList() {
        this.devices = [];

        this.add = function(dev, pin) {
            var device = this.search(dev);
            if (!device) {
                device = {name: dev, pin: 13, val: 0};
                this.devices.push(device);
            } else {
                device.pin = 13;
                device.val = 0;
            }
        };

        this.search = function(dev) {
            for (var i=0; i<this.devices.length; i++) {
                if (this.devices[i].name === dev)
                    return this.devices[i];
            }
            return null;
        };
    }

	// Cleanup function when the extension is unloaded
    ext._shutdown = function() {};

    // Status reporting code
    // Use this to report missing hardware, plugin or unsupported browser
    ext._getStatus = function() {
        if (!connected)
            return { status: 1, msg: 'Disconnected' };
        else
            return { status: 2, msg: 'Connected' };
    };

    //connect to the device
    var potentialDevices = [];
    ext._deviceConnected = function (dev) {
        potentialDevices.push(dev);

        if (!device) {
            tryNextDevice();
        }
    }

    //code to run if the first serial port is not connected to arduino
    var poller = null;
    var watchdog = null;
    function tryNextDevice() {
        device = potentialDevices.shift();
        if (!device) return;

        device.open({ stopBits: 0, bitRate: 57600, ctsFlowControl: 0 });
        console.log('Attempting connection with ' + device.id);
        device.set_receive_handler(function(data) {
            var inputData = new Uint8Array(data);
            processInput(inputData);
        });

    //connect an led to a pin
    ext.connectHW = function(hw, pin) {
    hwList.add(hw, 13);
};

    //Code that executes when the turn led on block is used
    //set the led to 0 or 1
    ext.digitalLED = function (led, val) {
        ext.connectHW(hw, 13);
    	var hw = hwList.search(led);
    	if (!hw) return;
    	if (val == 'on') {
     		digitalWrite(hw.pin, HIGH);
      		hw.val = 255;
    	} else if (val == 'off') {
      		digitalWrite(hw.pin, LOW);
     		 hw.val = 0;
    	}
    };
	

	// Block and block menu descriptions
    var descriptor = {
        blocks: [
        	//Block type, block name, function namem param1, param2
        	[' ', 'Turn on LED', 'digitalLED', 'LED A', 'on'],
        	//[' ', 'connect %m.hwOut to pin %n', 'connectHW', 'led A', 3],
        ]
    };


	

	function setAnalogInput(pin, val) {
	    analogInputData[pin] = val;
	}

	function digitalWrite(pin, val) {
	    if (!hasCapability(pin, OUTPUT)) {
	        console.log('ERROR: valid output pins are ' + pinModes[OUTPUT].join(', '));
	        return;
	    }
	    var portNum = (pin >> 3) & 0x0F;
	    if (val == LOW)
	        digitalOutputData[portNum] &= ~(1 << (pin & 0x07));
	    else
	        digitalOutputData[portNum] |= (1 << (pin & 0x07));
	    pinMode(pin, OUTPUT);
	    var msg = new Uint8Array([
            DIGITAL_MESSAGE | portNum,
            digitalOutputData[portNum] & 0x7F,
            digitalOutputData[portNum] >> 0x07]);
	    device.send(msg.buffer);
	}

	ext.digitalWrite = function (pin, val) {
	    if (val == menus[lang]['outputs'][0])
	        digitalWrite(pin, HIGH);
	    else if (val == menus[lang]['outputs'][1])
	        digitalWrite(pin, LOW);
	};

	var serial_info = { type: 'serial' };

	// Register the extension
	ScratchExtensions.register('Arduino', descriptor, ext, serial_info);
})({});




