(function(t){var e={};function n(i){if(e[i]){return e[i].exports}var s=e[i]={i:i,l:false,exports:{}};t[i].call(s.exports,s,s.exports,n);s.l=true;return s.exports}n.m=t;n.c=e;n.d=function(t,e,i){if(!n.o(t,e)){Object.defineProperty(t,e,{enumerable:true,get:i})}};n.r=function(t){if(typeof Symbol!=="undefined"&&Symbol.toStringTag){Object.defineProperty(t,Symbol.toStringTag,{value:"Module"})}Object.defineProperty(t,"__esModule",{value:true})};n.t=function(t,e){if(e&1)t=n(t);if(e&8)return t;if(e&4&&typeof t==="object"&&t&&t.__esModule)return t;var i=Object.create(null);n.r(i);Object.defineProperty(i,"default",{enumerable:true,value:t});if(e&2&&typeof t!="string")for(var s in t)n.d(i,s,function(e){return t[e]}.bind(null,s));return i};n.n=function(t){var e=t&&t.__esModule?function e(){return t["default"]}:function e(){return t};n.d(e,"a",e);return e};n.o=function(t,e){return Object.prototype.hasOwnProperty.call(t,e)};n.p="";return n(n.s=16)})({16:function(t,e,n){var i=n(17);var s=n(18);var a=n(19);var r=a;if(a.__esModule){r=a.default}r.styleSheet=s;r.render=i;t.exports=new ViewModel(r)},17:function(t,e){t.exports=function(t){var e=t||this;return _c("stack",{staticClass:["stackcontainer"],dynamicStyle:{width:function(){return e.width},height:function(){return e.height}}},[_i((function(){return e.settingValues.isDayMode}),(function(){return _c("image",{attrs:{src:"/common/image/bg_daytime_mode.jpg"},dynamicStyle:{width:function(){return e.width},height:function(){return e.height}}})})),_i((function(){return!e.settingValues.isDayMode}),(function(){return _c("image",{attrs:{src:"/common/image/bg_night_mode.jpg"},dynamicStyle:{width:function(){return e.width},height:function(){return e.height}}})})),_c("div",{staticClass:["row"],dynamicStyle:{width:function(){return e.width},height:function(){return e.height}}},[_c("div",{staticClass:["sysstatusbar"],staticStyle:{height:70},dynamicStyle:{width:function(){return e.width}}},[_c("stack",{staticClass:["centerstyle","sysstatusbar_stack"],staticStyle:{width:80,height:70}},[_c("input",{attrs:{type:"button"},staticClass:["btn","sysstatusbar_icon","sysstatusbar_setting"],on:{click:e.onBack}}),_c("image",{attrs:{src:"/common/image/ic_back.png"},staticClass:["sysstatusbar_icon","sysstatusbar_back"]})]),_c("div",{staticClass:["centerstyle","sysstatusbar_center"]},[_c("text",{attrs:{value:function(){return e.settingInfo.title}},staticClass:["sysstatusbar_text"]})]),_c("text",{attrs:{value:function(){return e.currentTime}},staticClass:["sysstatusbar_time"]}),_c("stack",{staticClass:["centerstyle","sysstatusbar_stack"],staticStyle:{width:80,height:70}},[_c("input",{attrs:{type:"button"},staticClass:["btn","sysstatusbar_icon","sysstatusbar_setting"],on:{click:e.onOpenSetting}}),_c("image",{attrs:{src:"/common/image/ic_setting.png"},staticClass:["sysstatusbar_icon","sysstatusbar_setting"]})])]),_c("div",{staticClass:["workspace"],staticStyle:{height:280},dynamicStyle:{width:function(){return e.width}}},[_c("list",{staticClass:["trans","settinglist"],staticStyle:{height:410},dynamicStyle:{width:function(){return e.width}}},[_l((function(){return e.listData[e.settingInfo.mode]}),(function(t,n){return _c("list-item",{staticClass:["trans","settinglistitem"],on:{click:function(t){e.onListItemClick(n,t)}}},[_c("stack",{staticClass:["trans","settinglistitem"]},[_i((function(){return n==e.currentIndex}),(function(){return _c("image",{attrs:{src:"/common/image/set_checked_bg.png"},staticStyle:{height:58},dynamicStyle:{width:function(){return e.width}}})})),_i((function(){return n==e.currentIndex}),(function(){return _c("text",{attrs:{value:function(){return e.settingInfo.unit}},staticClass:["titleunit"]})})),_c("div",{staticClass:["centerstyle","settinglistitem"]},[_c("text",{attrs:{value:function(){return t}},staticClass:["titleitem"]})])])])}))])]),_c("div",{staticClass:["centerstyle_bg","workspace"],staticStyle:{height:120},dynamicStyle:{width:function(){return e.width}}},[_c("input",{attrs:{type:"button"},staticClass:["btn","workspace_okbtn"],on:{click:e.onOK}})])])])}},18:function(t,e){t.exports={classSelectors:{sysstatusbar:{flexDirection:"row",backgroundColor:"#19f5f5f5"},sysstatusbar_icon:{width:50,height:50,marginTop:15},sysstatusbar_back:{marginLeft:20},sysstatusbar_home:{marginLeft:0},sysstatusbar_text:{marginLeft:50,marginTop:3},sysstatusbar_center:{marginTop:3,marginLeft:50,width:600,height:70},sysstatusbar_time:{marginTop:15,marginLeft:30},sysstatusbar_stack:{marginTop:10,marginLeft:15,backgroundColor:"#00ff0000"},sysstatusbar_setting:{marginLeft:30,backgroundColor:"#00f5f5f5","marginLeft:active":30,"backgroundColor:active":"#29f5f5f5"},trans:{backgroundColor:"#00000000"},btn:{borderRadius:0,borderTopColor:"#00000000",borderRightColor:"#00000000",borderBottomColor:"#00000000",borderLeftColor:"#00000000",backgroundColor:"#00000000"},centerstyle:{justifyContent:"center",alignItems:"center",backgroundColor:"#000000ff"},leftstyle:{backgroundColor:"#000000ff"},rightstyle:{backgroundColor:"#000000ff"},centerstyle_bg:{justifyContent:"center",alignItems:"center"},row:{flexDirection:"column",backgroundColor:"#000000ff"},col:{flexDirection:"row",backgroundColor:"#00ff0000"},row_bg:{flexDirection:"column"},col_bg:{flexDirection:"row"},stackcontainer:{width:960,height:480},container:{justifyContent:"space-around"},workspace:{flexDirection:"row",backgroundColor:"#0000ff00"},bgimage:{width:960,height:480},titleitem:{fontSize:30,textAlign:"center",height:58},titleunit:{fontSize:30,textAlign:"center",width:1100,height:58},settinglistitem:{width:960,height:58},settinglistitemtest:{width:160,height:58},workspace_okbtn:{width:165,height:65,marginTop:20,backgroundImage:"url(common/image/but_ok_normal.png)","width:active":165,"height:active":65,"marginTop:active":20,"backgroundImage:active":"url(common/image/but_ok_pressed.png)"}}}},19:function(t,e,n){"use strict";Object.defineProperty(e,"__esModule",{value:true});e["default"]=void 0;var i=c(requireNative("system.device"));var s=c(requireNative("system.router"));var a=c(requireNative("system.storage"));var r=c(requireNative("system.app"));var o=n(7);function c(t){return t&&t.__esModule?t:{default:t}}function u(t,e){if(t!==e){throw new TypeError("Cannot instantiate an arrow function")}}var l={data:{listData:[["1","2","3","4","5"],["1","2","3","4","5"],["10","15","20","25","30","35","40","45","50","55","60","65","70","75","80","85","90","95","100"],["1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","18","20","22","24","26","28","30"],["1","2","3","4","5","10","15","20","25","30","40","50","60","70","120"]],settingInfo:o.SettingPage.washingCountInfo,width:960,height:480,currentTime:0,currentIndex:-1,intervalID:0,settingValues:o.SettingPage.defaultSettingInfo,backPage:""},onInit:function t(){var e=this;var n=this;this.settingInfo=this.settingInfo;this.backPage=this.backPage;console.log("open common setting page..."+this.settingValues.isDayMode);this.currentTime=(0,o.getTime)();this.intervalID=setInterval((function(){n.currentTime=(0,o.getTime)()}),1e3*50);i["default"].getInfo({success:function t(n){u(this,e);this.width=n.windowWidth;this.height=n.windowHeight;console.log("Resolution: ".concat(this.width,"*").concat(this.height))}.bind(this)});a["default"].get({key:n.settingInfo.key,success:function t(e){if(e!="String"){n.currentIndex=-1;var i=n.listData[n.settingInfo.mode];for(var s in i){if(i[s]==e){n.currentIndex=s;break}}}else n.currentIndex=-1;console.log("setting "+n.settingInfo+n.currentIndex)}});(0,o.readSettingInfo)(this.settingValues)},onChangeDayNight:function t(){this.settingValues.isDayMode=!this.settingValues.isDayMode},onOpenSetting:function t(){(0,o.openSetting)()},onBack:function t(){if(this.backPage!="")(0,o.goPage)(this.backPage);else(0,o.backHome)()},onOK:function t(){var e=this;var n=this.listData[this.settingInfo.mode][this.currentIndex];a["default"].set({key:e.settingInfo.key,value:""+n,success:function t(){console.log("call storage.set success. value:"+n)}});this.onBack()},onListItemClick:function t(e){this.currentIndex=e},onDestroy:function t(){if(this.intervalID!=0){clearInterval(this.intervalID)}}};e["default"]=l},7:function(t,e,n){"use strict";Object.defineProperty(e,"__esModule",{value:true});e.readSettingInfo=e.getTime=e.goSetting=e.goPage=e.backHome=e.openSetting=e.SettingPage=e.KEYS=void 0;var i=a(requireNative("system.router"));var s=a(requireNative("system.storage"));function a(t){return t&&t.__esModule?t:{default:t}}var r={WASHCOUNT:"setting_washingcount_key",WATERLEVEL:"setting_waterlevel_key",WATERTEMP:"setting_watertemp_key",WATERLEAVE_TIME:"setting_waterleavetime_key",WASHINGMODE:"setting_washingmode_key",WASHINGPREPARE_H_TIME:"setting_washingprepare_hour_key",WASHINGPREPARE_M_TIME:"setting_washingprepare_MIN_key",ISDAYMODE:"setting_isdaymode",ISCHILDRENLOCKON:"setting_ischildrenlockon",SETTINGPAGE:"pages/setting/index",HOMEPAGE:"pages/index/index",COMMONSETTING:"pages/commonsetting/index"};e.KEYS=r;var o={defaultSettingInfo:{watertemp:"40",waterlevel:"30",washingcount:"2",waterleavetime:"10",washingmode:"标准",preparetime:"2",isDayMode:false,childrenLock:true},washingCountInfo:{unit:"次",title:"漂洗次数",mode:0,key:r.WASHCOUNT},waterLeaveInfo:{unit:"分钟",title:"脱水",mode:4,key:r.WATERLEAVE_TIME},waterTempInfo:{unit:"度",title:"水温",mode:2,key:r.WATERTEMP},waterLevelInfo:{unit:"升",title:"水位",mode:3,key:r.WATERLEVEL}};e.SettingPage=o;var c=function t(){i["default"].replace({uri:r.SETTINGPAGE,params:{}})};e.openSetting=c;var u=function t(){i["default"].replace({uri:r.HOMEPAGE,params:{}})};e.backHome=u;var l=function t(e){i["default"].replace({uri:e,params:{}})};e.goPage=l;var g=function t(e,n,s){i["default"].replace({uri:r.COMMONSETTING,params:{settingInfo:e,backPage:s}})};e.goSetting=g;var f=function t(){var e=new Date;var n=e.getMinutes(),i=e.getHours();var s="",a="";if(i<10)a="0";if(n<10)s="0";return a+i+":"+s+n};e.getTime=f;var d=function t(e){s["default"].get({key:r.WASHINGMODE,success:function t(n){if(n!=""&&n!="String")e.washingmode=n;console.log("call storage.get success setting_washingmode_key: ",n+" ",e.washingmode)}});s["default"].get({key:r.WASHCOUNT,success:function t(n){console.log("call storage.get success setting_washingcount_key: "+n);if(n!=""&&n!="String")e.washingcount=n}});s["default"].get({key:r.WATERLEAVE_TIME,success:function t(n){console.log("call storage.get success setting_waterleavetime_key: "+n);if(n!=""&&n!="String")e.waterleavetime=n}});s["default"].get({key:r.WATERLEVEL,success:function t(n){console.log("call storage.get success setting_waterlevel_key: "+n);if(n!=""&&n!="String")e.waterlevel=n}});s["default"].get({key:r.ISDAYMODE,success:function t(n){if(n=="true")e.isDayMode=true;else e.isDayMode=false;console.log("isDayMode "+e.isDayMode)}});s["default"].get({key:r.ISCHILDRENLOCKON,success:function t(n){console.log("call storage.get success: "+n);if(n=="true")e.childrenLock=true;else e.childrenLock=false}});s["default"].get({key:r.WASHINGPREPARE_H_TIME,success:function t(n){console.log("call storage.get success setting_washingprepare_hour_key: "+n);if(n!=""&&n!="String")e.preparetime=n}})};e.readSettingInfo=d}});