{
    function HiBus(appName, runnerName, pathSocket)
    {
        HiBus.SYNCREMOTECALL = 0;
        HiBus.ASYNCREMOTECALL = 1;

        var ret = true;

        // step 1: check validation
        if (typeof(appName) != "string")
            ret = false;
        else
            this.appName = appName;

        if (typeof(runnerName) != "string")
            ret = false;
        else
            this.runnerName = runnerName;

        // do not check the existence of pathSocket, C code will do it.
        if (typeof(pathSocket) != "string")
            this.pathSocket = "/var/tmp/hibus.sock";
        else
            this.pathSocket = pathSocket;

        if (ret)
        {
            // step 2: create hiBus connection
            // this.hiBusConn will be undefined, if any error occurs in new process
            this.hiBusConn = new HiBusConn(this.appName, this.runnerName, this.pathSocket);

            // step 3: create msg and callback array;
            this.eventArray = new Array();
            this.procedureArray = new Array();
        }
    }

    HiBus.prototype.genID = function(length) {
        return Number(Math.random().toString().substr(3, length) + Date.now()).toString(36);
    }

    HiBus.prototype.subscribeEvent = function(appName, runnerName, eventName, funcName)
    {
        var findEvent = false;
        var emptyPosition;

        // step 1: check validation
        if (typeof(appName) != "string")
            return false;

        if (typeof(runnerName) != "string")
            return false;

        if (typeof(eventName) != "string")
            return false;

        if (typeof(funcName) != "function") 
            return false;

        // check whether in eventArray
        for (var i = 0, len = this.eventArray.length; i < len; i++)
        {
            if (!this.eventArray[i])
            {
                emptyPosition = i;
                continue;
            }

            // delete it. if find, do not break the loop.
            // because runner can subscribe one event with different functions
            if (this.eventArray[i].appName == appName &&
                    this.eventArray[i].runnerName == runnerName &&
                    this.eventArray[i].eventName == eventName &&
                    this.eventArray[i].funcName == funcName)
            {
                findEvent = true;
                break;
            }
        }

        // set in eventArray
        if(!findEvent)
        {
            if (typeof(emptyPosition) == "undefined")
                this.eventArray.push({
                        "appName":appName, 
                        "runnerName":runnerName, 
                        "eventName":eventName, 
                        "funcName":funcName
                        });
            else
                this.eventArray[emptyPosition] = {
                    "appName":appName, 
                    "runnerName":runnerName, 
                    "eventName":eventName, 
                    "funcName":funcName
                };
        }

        // send to hiBus
//                var sendJson = {
//                            "packetType":"call",
//                            "callId":callId,
//                            "toEndpoint":endpoint,
//                            "toMethod":methodName,
//                            "expectedTime":timeout,
//                            "authenInfo":{},
//                            "parameter":param
//                            };
//                if (this.hiBusConn.status) {
//                    this.hiBusConn.hiBusWrite(JSON.stringify(sendJson));
//                }

        return true;
    }


    HiBus.prototype.unsubscribeEvent = function(appName, runnerName, eventName)
    {
        // step 1: check validation
        if (typeof(appName) != "string")
            return false;

        if (typeof(runnerName) != "string")
            return false;

        if (typeof(eventName) != "string")
            return false;

        // check whether in eventArray
        for (var i = 0, len = this.eventArray.length; i < len; i++)
        {
            if(!this.eventArray[i])
                continue;

            // If find the node, do not break the loop.
            // Because runner can subscribe one event with different functions.
            if(this.eventArray[i].appName == appName &&
                    this.eventArray[i].runnerName == runnerName &&
                    this.eventArray[i].eventName == eventName) {
                delete this.eventArray[i];
            }
        }

        // send to hiBus
//                var sendJson = {
//                            "packetType":"call",
//                            "callId":callId,
//                            "toEndpoint":endpoint,
//                            "toMethod":methodName,
//                            "expectedTime":timeout,
//                            "authenInfo":{},
//                            "parameter":param
//                            };
//                if (this.hiBusConn.status) {
//                    this.hiBusConn.hiBusWrite(JSON.stringify(sendJson));
//                }

        return true;
    }

    HiBus.prototype.callProcedure = function(endpoint, methodName, param, timeout, callback)
    {
        var emptyPosition;
        var callType = HiBus.ASYNCREMOTECALL;
        var successFunc;
        var errorFunc;
        var callId = this.genID(36);

        // step 1: check validation
        if (typeof(endpoint) != "string")
            return false;

        if (typeof(methodName) != "string")
            return false;

        if (typeof(callback) != "object")
            return false;

        if (timeout === "" || timeout == null)
            timeout = 0;
        if (isNaN(timeout))
            timeout = 0;


        if (callback == null)
        {
            // send request to hihus directly, do not push it to procedure array. 
        }
        else
        {
            callType = callback.type;
            if(callType == null)
                callType = HiBus.ASYNCREMOTECALL;

            if (timeout == 0)
                callType = HiBus.ASYNCREMOTECALL;

            successFunc = callback.success;
            errorFunc = callback.error;

            // check empty position in eventArray
            for (var i = 0, len = this.procedureArray.length; i < len; i++)
            {
                if (!this.eventArray[i])
                {
                    emptyPosition = i;
                    break;
                }

            }

            if (typeof(emptyPosition) == "undefined")
                this.procedureArray.push({
                        "callId":callId,
                        "toEndpoint":endpoint,
                        "toMethod":methodName,
                        "expectedTime":timeout,
                        "callback":callback
                        });
            else
                this.procedureArray[emptyPosition] = {
                    "callId":callId,
                    "toEndpoint":endpoint,
                    "toMethod":methodName,
                    "expectedTime":timeout,
                    "callback":callback
                };
        }

        // send to hiBus
        var sendJson = {
            "packetType":"call",
            "callId":callId,
            "toEndpoint":endpoint,
            "toMethod":methodName,
            "expectedTime":timeout,
            "authenInfo":{},
            "parameter":param
        };
//                if (this.hiBusConn.status) {
//                    this.hiBusConn.hiBusWrite(JSON.stringify(sendJson));
//                }


        // if sync, wait for result
        if (callType == HiBus.SYNCREMOTECALL) {
            this.checkPackets(timeout + 1);
        }

        return true;
    }

    HiBus.prototype.checkOnePacket = function(packetStr)
    {
        var packetJson;
//                var packetStr = '{' + 
//                        '"packetType": "result",' + 
//                        '"resultId": "<hased_event_identifier>",' +
//                        '"callId": "123456",' + 
//                        '"fromEndpoint": "@localhost/cn.fmsoft.hybridos.appagent/target0",' +
//                        '"fromMethod": "getUrl",' +
//                        '"timeConsumed": 0.123456,' +
//                        '"timeDiff": 0.123456,' +
//                        '"retCode": 200,' +
//                        '"retMsg": "OK",' +
//                        '"retValue":' +
//                            '{' +
//                            '"url":"http://www.sina.com", "gender":"male"' +
//                            '}' + 
//                    '}';

        try {
            packetJson = JSON.parse(packetStr);
        } catch (e) {
            console.log(e.message);
            return;
        }

        if (packetJson.packetType == "event") {
            console.log("get the event");

            // check whether in eventArray
            for (var i = 0, len = this.eventArray.length; i < len; i++) {
                if(!this.eventArray[i])
                    continue;

                // If find the node, do not break the loop.
                // Because runner can subscribe one event with different functions.
                if(this.eventArray[i].appName == packetJson.fromApp && this.eventArray[i].runnerName == packetJson.fromRunner &&
                        this.eventArray[i].eventName == packetJson.bubbleName) {
                    this.eventArray[i].funcName(packetJson.bubbleData);
                }
            }
        }
        else if (packetJson.packetType == "result") {
            console.log("get the result of procedure");

            // check whether in eventArray
            for (var i = 0, len = this.procedureArray.length; i < len; i++) {
                if(!this.procedureArray[i])
                    continue;
                if(this.procedureArray[i].callId == packetJson.callId && this.procedureArray[i].toEndpoint == packetJson.fromEndpoint &&
                        this.procedureArray[i].toMethod == packetJson.fromMethod) {
                    if(packetJson.retCode == "200" && typeof(this.procedureArray[i].callback.success) == "function")
                        this.procedureArray[i].callback.success(packetJson.retValue);
                    else {
                        if(typeof(this.procedureArray[i].callback.error) == "function")
                            this.procedureArray[i].callback.error(packetJson.retCode);
                    }
                    delete this.procedureArray[i];
                }
            }
        }
    }

    // check all packets in socket buffer. when timeout is 0, read packet without waiting.
    HiBus.prototype.checkPackets = function(timeout)
    {
        // step 1: check validation
        if (timeout === "" || timeout == null)
            timeout = 0;
        if (isNaN(timeout))
            timeout = 0;

        if (!this.hiBusConn.status) 
            return;

        // step 2: read packet from sockets. once a time. 
        var startTime = (new Date()).valueOf(); 
        var nowTime;

        var packet = this.hiBusConn.readPacket(timeout);
        while (typeof(packet) != "undefined") {
            this.checkOnePacket(packet);
            nowTime = (new Date()).valueOf(); 
            if(timeout != 0) {
                timeout = timeout - (nowTime - startTime); 
                if (timeout < 0)
                    timeout = 0;
            }

            packet = this.hiBusConn.readPacket(timeout);
        }
    }
}
