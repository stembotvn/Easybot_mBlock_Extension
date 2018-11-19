// arduino.js

(function(ext) {
    var device = null;
    var _rxBuf = [];
    var sides = {"LEFT":0,"RIGHT":1};
    var tones ={"B0":31,"C1":33,"D1":37,"E1":41,"F1":44,"G1":49,"A1":55,"B1":62,
			"C2":65,"D2":73,"E2":82,"F2":87,"G2":98,"A2":110,"B2":123,
			"C3":131,"D3":147,"E3":165,"F3":175,"G3":196,"A3":220,"B3":247,
			"C4":262,"D4":294,"E4":330,"F4":349,"G4":392,"A4":440,"B4":494,
			"C5":523,"D5":587,"E5":659,"F5":698,"G5":784,"A5":880,"B5":988,
			"C6":1047,"D6":1175,"E6":1319,"F6":1397,"G6":1568,"A6":1760,"B6":1976,
			"C7":2093,"D7":2349,"E7":2637,"F7":2794,"G7":3136,"A7":3520,"B7":3951,
	"C8":4186,"D8":4699};
	var beats = {"Half":500,"Quarter":250,"Eighth":125,"Whole":1000,"Double":2000,"Zero":0};    

    // Sensor states:
   
  
    ext.resetAll = function(){};
  
    ext.runArduino = function(){
        responseValue();
    };
    ext.setAddress = function(addr){
        runPackage(80,addr);
    };
    ext.stop = function() {
        runPackage(60);
    };
    ext.setMotor = function(Lspeed,Rspeed) {
        runPackage(61,short2array(Lspeed),short2array(Rspeed));
    };
    ext.forward = function(speed) {
        runPackage(62,short2array(speed));
    };
    ext.backward = function(speed) {
        runPackage(63,short2array(speed));
    };
    ext.turnleft = function(speed) {
        runPackage(64,short2array(speed));
    };
    ext.turnright = function(speed) {
        runPackage(65,short2array(speed));
    };
    ext.setservo = function(angle) {
        runPackage(66,short2array(angle));
    };
    ext.disableServo = function() {
        runPackage(67);
    };
    ext.playmemody = function(Frequency,Duration) {
        runPackage(68,short2array(typeof Frequency=="number"?Frequency:tones[Frequency]),short2array(typeof Duration=="number"?Duration:beats[Duration]));
    };
    ext.setcolor = function(R,G,B) {
        runPackage(69,R,G,B);
    };
    ext.offcolor = function() {
        runPackage(70);
    };
  ///////////////////////////////////////////
    ext.getDistance = function(nextID) {
        var deviceId = 71;
        getPackage(nextID,deviceId);
    };
    ext.getLight = function(nextID,side) {
        var deviceId = 72;
        getPackage(nextID,deviceId,typeof side=="number"?side:sides[side]);
    }; 
    ext.getCenterLine = function(nextID,side) {
        var deviceId = 73;
        getPackage(nextID,deviceId,typeof side=="number"?side:sides[side]);
    }; 
    ext.getRightLine = function(nextID,side) {
        var deviceId = 74;
        getPackage(nextID,deviceId,typeof side=="number"?side:sides[side]);
    }; 
    ext.getLeftLine = function(nextID,side) {
        var deviceId = 75;
        getPackage(nextID,deviceId,typeof side=="number"?side:sides[side]);
    }; 
    ext.actionDone = function(nextID) {
        var deviceId = 92;
        getPackage(nextID,deviceId);
    };   
  ////////////////////////////////////////////
  
   function sendPackage(argList, type){
    var bytes = [0xff, 0x55, 0, 0, type];
    for(var i=0;i<argList.length;++i){
      var val = argList[i];
      if(val.constructor == "[class Array]"){
        bytes = bytes.concat(val);
      }else{
        bytes.push(val);
      }
    }
    bytes[2] = bytes.length - 3;
    device.send(bytes);
  }
  
  function runPackage(){
    sendPackage(arguments, 2);
  }
  function getPackage(){
    var nextID = arguments[0];
    Array.prototype.shift.call(arguments);
    sendPackage(arguments, 1);
  }

    var inputArray = [];
  var _isParseStart = false;
  var _isParseStartIndex = 0;
  
    function processData(bytes) {
    var len = bytes.length;
    if(_rxBuf.length>30){
      _rxBuf = [];
    }
    for(var index=0;index<bytes.length;index++){
      var c = bytes[index];
      _rxBuf.push(c);
      if(_rxBuf.length>=2){
        if(_rxBuf[_rxBuf.length-1]==0x55 && _rxBuf[_rxBuf.length-2]==0xff){
          _isParseStart = true;
          _isParseStartIndex = _rxBuf.length-2;
        }
        if(_rxBuf[_rxBuf.length-1]==0xa && _rxBuf[_rxBuf.length-2]==0xd&&_isParseStart){
          _isParseStart = false;
          
          var position = _isParseStartIndex+2;
          var extId = _rxBuf[position];
          position++;
          var type = _rxBuf[position];
          position++;
          //1 byte 2 float 3 short 4 len+string 5 double
          var value;
          switch(type){
            case 1:{
              value = _rxBuf[position];
              position++;
            }
              break;
            case 2:{
              value = readFloat(_rxBuf,position);
              position+=4;
              if(value<-255||value>1023){
                value = 0;
              }
            }
              break;
            case 3:{
              value = readInt(_rxBuf,position,2);
              position+=2;
            }
              break;
            case 4:{
              var l = _rxBuf[position];
              position++;
              value = readString(_rxBuf,position,l);
            }
              break;
            case 5:{
              value = readDouble(_rxBuf,position);
              position+=4;
            }
              break;
            case 6:
              value = readInt(_rxBuf,position,4);
              position+=4;
              break;
          }
          if(type<=6){
            responseValue(extId,value);
          }else{
            responseValue();
          }
          _rxBuf = [];
        }
      } 
    }
    }
  function readFloat(arr,position){
    var f= [arr[position],arr[position+1],arr[position+2],arr[position+3]];
    return parseFloat(f);
  }
  function readInt(arr,position,count){
    var result = 0;
    for(var i=0; i<count; ++i){
      result |= arr[position+i] << (i << 3);
    }
    return result;
  }
  function readDouble(arr,position){
    return readFloat(arr,position);
  }
  function readString(arr,position,len){
    var value = "";
    for(var ii=0;ii<len;ii++){
      value += String.fromCharCode(_rxBuf[ii+position]);
    }
    return value;
  }
    function appendBuffer( buffer1, buffer2 ) {
        return buffer1.concat( buffer2 );
    }

    // Extension API interactions
    var potentialDevices = [];
    ext._deviceConnected = function(dev) {
        potentialDevices.push(dev);

        if (!device) {
            tryNextDevice();
        }
    }

    function tryNextDevice() {
        // If potentialDevices is empty, device will be undefined.
        // That will get us back here next time a device is connected.
        device = potentialDevices.shift();
        if (device) {
            device.open({ stopBits: 0, bitRate: 115200, ctsFlowControl: 0 }, deviceOpened);
        }
    }

    var watchdog = null;
    function deviceOpened(dev) {
        if (!dev) {
            // Opening the port failed.
            tryNextDevice();
            return;
        }
        device.set_receive_handler('Easybot',processData);
    };

    ext._deviceRemoved = function(dev) {
        if(device != dev) return;
        device = null;
    };

    ext._shutdown = function() {
        if(device) device.close();
        device = null;
    };

    ext._getStatus = function() {
        if(!device) return {status: 1, msg: 'Arduino disconnected'};
        if(watchdog) return {status: 1, msg: 'Probing for Arduino'};
        return {status: 2, msg: 'Arduino connected'};
    }

    var descriptor = {};
  ScratchExtensions.register('Easybot', descriptor, ext, {type: 'serial'});
})({});
