chrome.browserAction.onClicked.addListener(function(tab) {
    //this function does not work when you have popup html file.
    //alert('icon clicked');
    chrome.tabs.executeScript({
        file:'select.js'
    });
});




chrome.runtime.onMessage.addListener(function(request,sender,sendResponse) {

    //alert("lalala");//this alert does not pop up when you have popup html file.
    if (request.action && request.action == 'plzdownload') {
        chrome.downloads.download({
            url: request.value,
            filename: "bluebird/"+ request.tweetID + ".jpg" // backward directory or absolute directory is not valid.
        });
        sendResponse();
    }
    if (request.action && request.action == 'openwebsite'){
        var newURL = request.value;
        chrome.tabs.create({ url: newURL });//this function does not work when you have popup html file.
    }
});





//below functions are keyboard shortcut, but does not work.
// chrome.commands.onCommand.addListener(function(command) {
//     if (command === "execute-picturedownload") {
//         picDownload();
//     }
// });

// function picDownload() {
// //    trackEvent('highlight-action', 'highlight');
//     chrome.tabs.executeScript({file: 'select.js'});
// }