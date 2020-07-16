
var image = document.elementFromPoint(window.screenX+window.innerWidth/2, window.screenY+window.innerHeight/2);
var PictureContainer = image.closest(".r-1p0dtai.r-1pi2tsx.r-1d2f490.r-u8s1d.r-ipm5af.r-13qz1uu");
var PicList = PictureContainer.getElementsByClassName("css-9pa8cd");//Return all pictures in the container

var wholetweet = image.closest(".css-1dbjc4n.r-my5ep6.r-qklmqi.r-1adg3ll");
if(wholetweet == null)
{
	var wholetweet = image.closest(".css-1dbjc4n.r-1j3t67a");
}
var tweeterIDContainer = wholetweet.getElementsByClassName("css-1dbjc4n r-1awozwy r-18u37iz r-1wtj0ep");//Return List of one element(Container of ID and NickName).
var tweeterID = tweeterIDContainer[0].getElementsByClassName("css-901oao css-16my406 r-1qd0xha r-ad9z0x r-bcqeeo r-qvutc0");//Return List
//var tweeterID = wholetweet.getElementsByClassName("css-901oao css-16my406 r-1qd0xha r-ad9z0x r-bcqeeo r-qvutc0");
//console.log(tweeterID);

for(var i=0; i < PicList.length; i++)
{
	var str1 = PicList[i].getAttribute('src');
	//if it is gif
	if(str1.indexOf("https://pbs.twimg.com/tweet_video_thumb/") != -1)
	{
		str1 = str1.replace(/tweet_video_thumb/, 'tweet_video');
		str1 = str1.replace(/pbs.twimg.com/,'video.twimg.com');
		str1 = str1.replace(/\?format\S+/,'.mp4');
		var gifWebsite = "https://ezgif.com/video-to-gif?url="+ str1;
		chrome.extension.sendMessage({action:'openwebsite',value:gifWebsite});
		//alert(gifWebsite);
	}
	else
	{
		str2 = str1.replace(/name=small|name=360x360/g,"name=large");
		//console.log(str2);
		//Does the tweet has date(time) next to the nickname?
		NicknameIndex = (tweeterID[tweeterID.length-1].textContent == '·' )? tweeterID.length-2 : tweeterID.length-1;
		chrome.extension.sendMessage({action:'plzdownload', value: str2, tweetID: tweeterID[NicknameIndex].textContent});
		//tweeterID[0].textContent is nickname and [2] is usually ID when nickname does not have emoji.
		//[-2] is better than [2]. but negative is not defined in javascript. then [length-2].
	}
}