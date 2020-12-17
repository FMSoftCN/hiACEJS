var a = new HiBusConn('cn.fmsoft.appagent', 'target0'); 

if (a.status) 
    printinfo('true'); 
else 
    printinfo('false'); 


var sss = {
    "abcd":1234,
    "xyz":"hello world"
    };

var ss = JSON.stringify(sss);
a.send(ss, ss.length);

var ssss = a.read();
if (typeof(ssss) == 'undefined')
    printinfo("read nothing or read error"); 
else
    printinfo(ssss);
