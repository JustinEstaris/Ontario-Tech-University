// enable cross-origin resource sharing
$.support.cors = true;

$(document).ready(function() {
	// initially, load the most popular videos
	var url = "https://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22toronto%2C%20on%22)&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys";
	
	// Get the data from the web service and process
	$.getJSON(url, function(data) {
        var sunrise = data.query.results.channel.astronomy.sunrise;
        var sunset = data.query.results.channel.astronomy.sunset;
        var humidity = data.query.results.channel.atmosphere.humidity;
        var temperature = ((data.query.results.channel.item.condition.temp - 32) * 5.0/9).toFixed(1);
        var description = data.query.results.channel.item.condition.text;
        
		$('#output').append('<li>Temperature: '+temperature+'&deg;C</li>');
		$('#output').append('<li>Description: '+description+'</li>');
		$('#output').append('<li>Humidity: '+humidity+'%</li>');
		$('#output').append('<li>Sunrise: '+sunrise+'</li>');
		$('#output').append('<li>Sunset: '+sunset+'</li>');
	});
});
