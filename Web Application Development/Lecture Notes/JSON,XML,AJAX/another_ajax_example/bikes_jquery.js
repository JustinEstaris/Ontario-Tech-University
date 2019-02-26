// enable cross-origin resource sharing
$.support.cors = true;

$(document).ready(function () {
  $('#download').click(function () {
    $.get('http://csci3230u.com/ajax/stations.xml', function(xmlDoc) {
      var table = $('<table class="table">');
      
      // header
      var thead = $('<thead>');
      table.append(thead);
      var headerRow = $('<tr>');
      thead.append(headerRow);
      
      var latHeader = $('<th>').text('Latitude');
      headerRow.append(latHeader)
      
      var longHeader = $('<th>').text('Longitude');
      headerRow.append(longHeader)
      
      var numHeader = $('<th>').text('# Bikes');
      headerRow.append(numHeader)
      
      var tbody = $('<tbody>');
      table.append(tbody);
      $(xmlDoc).find('station').each(function() {
        var row = $('<tr>');
        tbody.append(row);
        
        var lat = $(this).find('lat').text();
        var latCell = $('<td>').text(lat);
        row.append(latCell);

        var lon = $(this).find('long').text();
        var lonCell = $('<td>').text(lon);
        row.append(lonCell);

        var num = $(this).find('nbBikes').text();
        var numCell = $('<td>').text(num);
        row.append(numCell);
      });
      $('#bikeData').append(table);
    });
  });
});