/*
Randy's API Key
key = 'AIzaSyA2rJ3kuns7kM0B-qLeGl6-BLpM_9whQr0';
url = 'https://www.googleapis.com/youtube/v3/search?part=id%2Csnippet&q=NASA&key=';
*/

// enable cross-origin resource sharing
$.support.cors = true;

$(document).ready(function() {
    key = 'AIzaSyA2rJ3kuns7kM0B-qLeGl6-BLpM_9whQr0';
   

	// handler for searching by keyword
	$('#searchByKeywordButton').click(function() {
        var keyword = $('#keyword').val();
        url = 'https://www.googleapis.com/youtube/v3/search?part=id%2Csnippet&q=' + keyword + '&key=' + key;
        var max_videos = 5;

    //OLD CODE: var searchURL = 'https://www.googleapis.com/youtube/v3/search?part=id%2Csnippet&q=' + escape(keyword) + '&key=AIzaSyBKl-NXWdXHsj6dCYrNRqgU5k5h_bH6Ua8';

		// clear any previous search results
		$('#output ol').html(''); //Set InnerHTML to nothing
		$('#videos').html('');

		// Perform a fresh query : Get the data from the web service and process
    $.getJSON(url, function(data) { //Data is a diciontary(JSON)
        $.each(data.items, function(index,item) { //for loop and call a function for each one of those
            $('#output ol').append(renderSearchResultItem(item)); //Add  new item by calling the renderSearchResultItem function
            $('#videos').append(renderVideoPlayback(item.id));
        });
    });
  });
});

function renderSearchResultItem(item) {
    if (item.id.kind === 'youtube#video') { // if the query is a Youtube Video

        //PROPER WAY - No need for Browser to Parse XML
        li = $('<li />'); //Create Li Tag
        a = $('<a/>'); // Create Anchor Tag 
        a.attr('href', 'http://www.youtube.com/watch?v=' +  item.id.videoId +'">');
        li.text(item.snippet.title);
        li.append(a)
        return li;

       // return '<li><a href="http://www.youtube.com/watch?v=' + item.videoId + '">' + item.snippet.title + '</a></li>';
    } else {
        // Likely a channel, ignore
        return '';
    }
}

function renderVideoPlayback(id) {
    if (id.kind == 'youtube#video') {
       var text = '<div>' +
                  '    <embed width="420" height="345" ' +
                  '       src="http://www.youtube.com/watch/v/' + item.id.videoId + '"' +
                  '       type="application/x-shockwave-flash">' +
                  '    </embed>' +
                  '</div>'
        return text;
    } else {
        return '';
    }
}
