(function(t){var e={};function n(i){if(e[i]){return e[i].exports}var s=e[i]={i:i,l:false,exports:{}};t[i].call(s.exports,s,s.exports,n);s.l=true;return s.exports}n.m=t;n.c=e;n.d=function(t,e,i){if(!n.o(t,e)){Object.defineProperty(t,e,{enumerable:true,get:i})}};n.r=function(t){if(typeof Symbol!=="undefined"&&Symbol.toStringTag){Object.defineProperty(t,Symbol.toStringTag,{value:"Module"})}Object.defineProperty(t,"__esModule",{value:true})};n.t=function(t,e){if(e&1)t=n(t);if(e&8)return t;if(e&4&&typeof t==="object"&&t&&t.__esModule)return t;var i=Object.create(null);n.r(i);Object.defineProperty(i,"default",{enumerable:true,value:t});if(e&2&&typeof t!="string")for(var s in t)n.d(i,s,function(e){return t[e]}.bind(null,s));return i};n.n=function(t){var e=t&&t.__esModule?function e(){return t["default"]}:function e(){return t};n.d(e,"a",e);return e};n.o=function(t,e){return Object.prototype.hasOwnProperty.call(t,e)};n.p="";return n(n.s=16)})({16:function(t,e,n){var i=n(17);var s=n(18);var r=n(19);var c=r;if(r.__esModule){c=r.default}c.styleSheet=s;c.render=i;t.exports=new ViewModel(c)},17:function(t,e){t.exports=function(t){var e=t||this;return _c("stack",{staticClass:["stackcontainer"],dynamicStyle:{width:function(){return e.width},height:function(){return e.height}}},[_c("image",{attrs:{src:"/common/home/bg_960.jpg"},dynamicStyle:{width:function(){return e.width},height:function(){return e.height}}}),_c("div",{staticClass:["row"],dynamicStyle:{width:function(){return e.width},height:function(){return e.height}}},[_c("div",{staticClass:["row"],staticStyle:{height:110,backgroundColor:"#19f5f5f5"},dynamicStyle:{width:function(){return e.width}}},[_c("div",{staticClass:["acenterstyle","trans"],staticStyle:{height:46,backgroundColor:"#0000ff00"},dynamicStyle:{width:function(){return e.width}}},[_c("image",{attrs:{src:"/common/home/ic_weather_white.png"},staticClass:["systemstatusbar_tempicon"]}),_c("text",{attrs:{value:"22 C |"},staticClass:["systemstatusbar_temp"]}),_c("text",{attrs:{value:"空气质量: 优"},staticClass:["systemstatusbar_air"]}),_c("text",{attrs:{value:"2020年12月20 星期三 19:50"},staticClass:["systemstatusbar_date"]})]),_c("div",{staticClass:["trans"],staticStyle:{height:64},dynamicStyle:{width:function(){return e.width}}},[_c("stack",{staticClass:["trans","systemstatusbar_backicon"]},[_c("input",{attrs:{type:"button"},staticClass:["btn","myapp_iconsize","common_btn"],on:{click:e.onBack}}),_c("image",{attrs:{src:"/common/image/ic_back.png"},staticClass:["systemstatusbar_backicon"]})]),_c("text",{attrs:{value:"音乐"},staticClass:["systemstatusbar_text"]})])]),_c("div",{staticClass:["centerstyle"],staticStyle:{height:260,marginTop:0},dynamicStyle:{width:function(){return e.width}}},[_c("div",{staticClass:["trans"],staticStyle:{height:260},dynamicStyle:{width:function(){return e.width/4}}}),_c("div",{staticClass:["centerstyle","row","musicdetail_albumcontainer"]},[_c("image",{attrs:{src:"/common/music/ic_music_album_art.jpg"},staticClass:["trans","musicdetail_albumpic"]}),_c("text",{attrs:{value:function(){return e.songInfo.title}},staticClass:["musicdetail_albumtitle"]}),_c("text",{attrs:{value:function(){return e.songInfo.singer}},staticClass:["musicdetail_albumsinger"]})]),_c("div",{staticClass:["trans"],staticStyle:{height:260},dynamicStyle:{width:function(){return e.width/5}}}),_c("list",{attrs:{id:"list1",ref:"listObj"},staticClass:["centerstyle","musicdetail_lyrics_list"]},[_l((function(){return e.songInfo.lyrics}),(function(t,n){return _c("list-item",{staticClass:["centerstyle","musicdetail_lyrics_listitem"]},[_i((function(){return n==e.currentLyricsIndex}),(function(){return _c("text",{attrs:{value:function(){return t}},staticClass:["musicdetail_lyrics_text"]})})),_i((function(){return n!=e.currentLyricsIndex}),(function(){return _c("text",{attrs:{value:function(){return t}},staticClass:["musicdetail_lyrics_currenttext"]})}))])}))]),_c("div",{staticClass:["trans"],staticStyle:{height:220},dynamicStyle:{width:function(){return e.width/4}}})]),_c("div",{staticClass:["row"],staticStyle:{height:120,backgroundColor:"#19f9f9f9",justifyContent:"center"},dynamicStyle:{width:function(){return e.width}}},[_c("div",{staticClass:["centerstyle"],staticStyle:{height:60},dynamicStyle:{width:function(){return e.width}}},[_c("text",{attrs:{value:function(){return e.songInfo.current}}}),_c("stack",{staticClass:["centerstyle"],staticStyle:{width:600,height:20,justifyContent:"center",alignItems:"center"}},[_c("slider",{attrs:{value:function(){return e.songInfo.percent}},staticClass:["musicdetail_progress"],staticStyle:{top:10},on:{change:e.onSliderChange,click:e.onSliderClick}}),_c("image",{attrs:{src:"/common/music/music_circle_progress_bar.png"},staticStyle:{width:20,height:20,top:0},dynamicStyle:{left:function(){return e.songInfo.musicLeft}}})]),_c("text",{attrs:{value:function(){return e.songInfo.end}}})]),_c("div",{staticClass:["centerstyle"],staticStyle:{height:60,backgroundColor:"#0000ff00"},dynamicStyle:{width:function(){return e.width}}},[_i((function(){return!e.isShuffleMode}),(function(){return _c("input",{attrs:{type:"button"},staticClass:["btn","music_playicon_first","music_controlbtn_shufflemode"],on:{click:e.onChangeMode}})})),_i((function(){return e.isShuffleMode}),(function(){return _c("input",{attrs:{type:"button"},staticClass:["btn","music_playicon_first","music_controlbtn_singlemode"],on:{click:e.onChangeMode}})})),_c("input",{attrs:{type:"button"},staticClass:["btn","music_playicon","music_controlbtn_preview"],on:{click:e.onPreview}}),_i((function(){return!e.musicPlaying}),(function(){return _c("input",{attrs:{type:"button"},staticClass:["btn","music_playicon","music_controlbtn_play"],on:{click:e.onPlay}})})),_i((function(){return e.musicPlaying}),(function(){return _c("input",{attrs:{type:"button"},staticClass:["btn","music_playicon","music_controlbtn_pause"],on:{click:e.onPause}})})),_c("input",{attrs:{type:"button"},staticClass:["btn","music_playicon","music_controlbtn_next"],on:{click:e.onNext}}),_c("input",{attrs:{type:"button"},staticClass:["btn","music_playicon","music_controlbtn_love"],on:{click:e.onAddLove}})])])])])}},18:function(t,e){t.exports={classSelectors:{trans:{backgroundColor:"#00000000"},btn:{borderRadius:5,borderTopColor:"#00000000",borderRightColor:"#00000000",borderBottomColor:"#00000000",borderLeftColor:"#00000000",backgroundColor:"#00000000"},jcenterstyle:{justifyContent:"center",backgroundColor:"#000000ff"},acenterstyle:{alignItems:"center",backgroundColor:"#000000ff"},centerstyle:{justifyContent:"center",alignItems:"center",backgroundColor:"#000000ff"},leftstyle:{backgroundColor:"#000000ff"},rightstyle:{backgroundColor:"#000000ff"},jcenterstyle_bg:{justifyContent:"center"},acenterstyle_bg:{alignItems:"center"},centerstyle_bg:{justifyContent:"center",alignItems:"center"},row:{flexDirection:"column",backgroundColor:"#000000ff"},col:{flexDirection:"row",backgroundColor:"#00ff0000"},row_bg:{flexDirection:"column"},col_bg:{flexDirection:"row"},stackcontainer:{width:960,height:480},workspace_container:{backgroundColor:"#19f9f9f9",borderRadius:18,height:160,width:720,paddingLeft:10,paddingRight:10},common_btn:{backgroundColor:"#00f5f5f5","backgroundColor:active":"#49f5f5f5"},systemstatusbar_tempicon:{marginLeft:36,width:28,height:28},systemstatusbar_temp:{fontSize:24,marginLeft:6},systemstatusbar_air:{fontSize:24,marginLeft:6},systemstatusbar_date:{fontSize:24,marginLeft:280},systemstatusbar_selected_title:{fontSize:30,marginLeft:20,color:"#fffafafa"},systemstatusbar_title:{fontSize:24,marginLeft:50,color:"#ffd9d9d9"},systemstatusbar_backicon:{marginTop:15,marginLeft:36,width:36,height:36},systemstatusbar_text:{marginTop:15,marginLeft:16,fontSize:32,height:64},music_playstatus:{width:96,height:96},music_playicon:{width:48,height:48,marginLeft:60},music_playicon_first:{width:48,height:48,marginLeft:0},music_songtitle:{fontSize:36},music_songsinger:{fontSize:24},music_controlbtn_play:{backgroundImage:"url(common/music/ic_music_play.png)","backgroundImage:active":"url(common/music/ic_music_play_pressed.png)"},music_controlbtn_pause:{backgroundImage:"url(common/music/ic_music_pause.png)","backgroundImage:active":"url(common/music/ic_music_pause_pressed.png)"},music_controlbtn_love:{backgroundImage:"url(common/music/ic_music_i_like_default.png)","backgroundImage:active":"url(common/music/ic_music_i_like_checked.png)"},music_controlbtn_shufflemode:{backgroundImage:"url(common/music/ic_music_shuffle_play.png)"},music_controlbtn_singlemode:{backgroundImage:"url(common/music/ic_music_single_cycle.png)"},music_controlbtn_next:{backgroundImage:"url(common/music/ic_music_next.png)","backgroundImage:active":"url(common/music/ic_music_next_pressed.png)"},music_controlbtn_preview:{backgroundImage:"url(common/music/ic_music_last.png)","backgroundImage:active":"url(common/music/ic_music_last_pressed.png)"},musicdetail_progress:{width:600,height:6,color:"#fffafafa",selectedColor:"#ffff0000",blockColor:"#00ffffff",borderRadius:5,marginLeft:15,marginRight:15},musicdetail_lyrics:{width:218,height:220},musicdetail_albumcontainer:{width:188,height:260},musicdetail_albumtitle:{fontSize:28,marginTop:5,marginBottom:5},musicdetail_albumsinger:{fontSize:22},musicdetail_albumpic:{width:188,height:188},musicdetail_lyrics_list:{width:220,height:240},musicdetail_lyrics_listitem:{width:220,height:40},musicdetail_lyrics_text:{fontSize:24,color:16777215},musicdetail_lyrics_currenttext:{fontSize:24,color:"#99fafafa"}}}},19:function(t,e,n){"use strict";Object.defineProperty(e,"__esModule",{value:true});e["default"]=void 0;var i=r(requireNative("system.device"));var s=n(7);function r(t){return t&&t.__esModule?t:{default:t}}function c(t,e){if(t!==e){throw new TypeError("Cannot instantiate an arrow function")}}var o={data:{songLyrics:["我劝你早点归去","你说你不想归去","只叫我抱着你","悠悠海风轻轻吹","冷却了野火堆","我看见伤心的你","你叫我怎舍得去","哭态也绝美","如何止哭","只得轻吻你发边","让风继续吹","不忍远离","心里极渴望","希望留下伴着你","风继续吹","不忍远离","心里亦有泪不愿流泪望着你","过去多少快乐记忆","何妨与你一起去追","要将忧郁苦痛洗去","柔情蜜意我愿记取","要强忍离情泪"],songLyrics2:["明白到爱失去 一切都不对","我却为何偏偏喜欢你","爱已是负累","相爱似受罪","心底如今满苦泪","旧日情如醉","此际怕再追","偏偏痴心想见你","为何我心分秒想着过去","为何你一点都不记起","情义已失去 恩爱都失去"],songDatas:[{title:"风继续吹",singer:"张国荣",duration:320,lyrics:null},{title:"偏偏喜欢你",singer:"陈百强",duration:330,lyrics:null},{title:"红茶馆",singer:"陈慧娴",duration:430,lyrics:null},{title:"真的爱你",singer:"黄家驹",duration:350,lyrics:null},{title:"我的眼里只有你",singer:"蔡国庆",duration:310,lyrics:null},{title:"茶山情歌",singer:"杨钰莹",duration:300,lyrics:null}],width:960,height:480,currentIndex:0,currentLyricsIndex:2,intervalId:0,musicPlaying:false,isShuffleMode:false,songInfo:{title:"茶山情歌",singer:"杨钰莹",duration:300,currentValue:0,current:"00:00",end:"04:01",percent:0,musicLeft:0,lyrics:null},backPage:""},scrollTo:function t(){var e=this.currentLyricsIndex;if(e>3)e-=2;this.$refs.listObj.scrollTo({index:e})},initSongs:function t(){var e=this;var n=0;var i=this;this.songDatas.forEach(function(t){c(this,e);if(n%2==0)t.lyrics=i.songLyrics;else t.lyrics=i.songLyrics2;n+=1}.bind(this))},initSongInfo:function t(e){this.songInfo.title=this.songDatas[e].title;this.songInfo.singer=this.songDatas[e].singer;this.songInfo.duration=this.songDatas[e].duration;this.songInfo.lyrics=this.songDatas[e].lyrics;this.songInfo.end=(0,s.getMusicTime)(this.songInfo.duration);this.songInfo.currentValue=0},onInit:function t(){var e=this;var n=this;this.currentIndex=this.currentIndex;this.backPage=this.backPage;this.musicPlaying=this.musicPlaying;i["default"].getInfo({success:function t(n){c(this,e);this.width=n.windowWidth;this.height=n.windowHeight;console.log("Resolution: ".concat(this.width,"*").concat(this.height))}.bind(this)});this.initSongs();this.initSongInfo(this.currentIndex);this.intervalId=setInterval((function(){if(n.currentLyricsIndex<n.songLyrics.length){n.currentLyricsIndex+=1}else{n.currentLyricsIndex=0}n.scrollTo();n.songInfo.currentValue+=1;if(n.songInfo.currentValue>=n.songInfo.duration||n.songInfo.currentValue>2){}n.updateSlide()}),1e3*1)},updateSlide:function t(){var e=this;e.songInfo.current=(0,s.getMusicTime)(e.songInfo.currentValue);e.songInfo.percent=Math.floor(e.songInfo.currentValue*100/e.songInfo.duration);e.songInfo.musicLeft=Math.floor(e.songInfo.currentValue*600/e.songInfo.duration)},onSliderClick:function t(){console.log("onSliderClick")},onSliderChange:function t(e){this.songInfo.currentValue=Math.floor(e.progress*this.songInfo.duration/100);console.log("onSliderChange "+e+" "+this.songInfo.currentValue);this.updateSlide()},onPlay:function t(){this.music_playing=true},onPause:function t(){this.music_playing=false},onNext:function t(){if(this.isShuffleMode==false){if(this.currentIndex>this.songDatas.length-1){this.currentIndex=0;return}this.currentIndex+=1}else{this.currentIndex=(0,s.getMyRnd)(0,this.songDatas.length-1)}this.initSongInfo(this.currentIndex);this.updateSlide()},onPreview:function t(){if(this.isShuffleMode){if(this.currentIndex<=0){this.currentIndex=this.songDatas.length-1;return}this.currentIndex-=1}else{this.currentIndex=(0,s.getMyRnd)(0,this.songDatas.length-1)}this.initSongInfo(this.currentIndex);this.updateSlide()},onChangeMode:function t(){},onBack:function t(){if(this.backPage==undefined||this.backPage.length==0)(0,s.backHome)();else(0,s.goPage)(this.backPage)},onDestroy:function t(){if(this.intervalId!=0)clearInterval(this.intervalId)}};e["default"]=o},7:function(t,e,n){"use strict";Object.defineProperty(e,"__esModule",{value:true});e.readSettingInfo=e.getMyRnd=e.getMusicTime=e.getTime=e.getTimeDetail=e.goSetting=e.goPage=e.backHome=e.openSetting=e.SettingPage=e.KEYS=void 0;var i=r(requireNative("system.router"));var s=r(requireNative("system.storage"));function r(t){return t&&t.__esModule?t:{default:t}}var c={WASHCOUNT:"setting_washingcount_key",SETTINGPAGE:"pages/setting/index",HOMEPAGE:"pages/index/index",SCREENSAVEPAGE:"pages/screensave/index",PICTUREPAGE:"pages/picture/index",VOICEPAGE:"pages/voice/index",MYAPPPAGE:"pages/myapp/index",VIDEOPAGE:"pages/video/index",MUSICPAGE:"pages/music/index",MUSICDETAILPAGE:"pages/musicdetail/index"};e.KEYS=c;var o={};e.SettingPage=o;var a=function t(){i["default"].replace({uri:c.SETTINGPAGE,params:{}})};e.openSetting=a;var u=function t(){i["default"].replace({uri:c.HOMEPAGE,params:{}})};e.backHome=u;var l=function t(e){try{i["default"].replace({uri:e,params:{}})}catch(t){console.log("goPage() "+t)}};e.goPage=l;var g=function t(e,n,s){i["default"].replace({uri:c.COMMONSETTING,params:{settingInfo:e,settingValues:n,backPage:s}})};e.goSetting=g;var f=function t(){var e="",n="";var i=new Date;var s=i.getFullYear(),r=i.getMonth()+1,c=i.getDate();if(r<10)n="0";if(c<10)e="0";var o=new Array("星期日","星期一","星期二","星期三","星期四","星期五","星期六");var a=o[i.getDay()];return s+"年"+n+r+"月"+e+c+"日 "+a};e.getTimeDetail=f;var d=function t(){var e=new Date;var n=e.getMinutes(),i=e.getHours();var s="",r="";if(i<10)r="0";if(n<10)s="0";return r+i+":"+s+n};e.getTime=d;var m=function t(e){var n=Math.floor(e/60),i=e%60;var s="",r="";if(i<10)r="0";if(n<10)s="0";return s+n+":"+r+i};e.getMusicTime=m;var h=function t(e,n){return Math.floor(Math.random()*(n-e+1)+e)};e.getMyRnd=h;var _=function t(e){s["default"].get({key:c.WASHINGMODE,success:function t(n){if(n!=""&&n!="String")e.washingmode=n;console.log("call storage.get success setting_washingmode_key: ",n+" ",e.washingmode)}})};e.readSettingInfo=_}});