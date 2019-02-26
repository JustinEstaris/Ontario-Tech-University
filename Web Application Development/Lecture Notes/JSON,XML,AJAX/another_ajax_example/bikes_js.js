window.onload = function () {
  var downloadButton = 
   document.getElementById('download');
  
  downloadButton.onclick = function () {
    // post back
    var request = new XMLHttpRequest();
    request.onreadystatechange = function () {
      if (request.readyState == 4) {
        if (request.status == 200) {
          var table = document.createElement('table');
          table.className = 'table'; // Bootstrap

          // create the table header
          var thead = document.createElement('thead');
          table.appendChild(thead);
          var headerRow = document.createElement('tr');
          thead.appendChild(headerRow);
          
          var latHeader = document.createElement('th');
          var latHeaderText = document.createTextNode('Latitude');
          latHeader.appendChild(latHeaderText);
          headerRow.appendChild(latHeader);
          
          var lonHeader = document.createElement('th');
          var lonHeaderText = document.createTextNode('Longitude');
          lonHeader.appendChild(lonHeaderText);
          headerRow.appendChild(lonHeader);
          
          var numHeader = document.createElement('th');
          var numHeaderText = document.createTextNode('# Bikes');
          numHeader.appendChild(numHeaderText);
          headerRow.appendChild(numHeader);
          
          // create the table body
          var tbody = document.createElement('tbody');
          table.appendChild(tbody);
          
          var stations = request.responseXML.getElementsByTagName('station');
          for (var i = 0; i < stations.length; i++) {
            // create the row
            var dataRow = document.createElement('tr');
            tbody.appendChild(dataRow);
            
            // create the latitude cell
            var latitudes = stations[i].getElementsByTagName('lat');
            var latCell = document.createElement('td');
            dataRow.appendChild(latCell);
            var latContent = document.createTextNode(latitudes[0].textContent);
            latCell.appendChild(latContent);
            
            // create the longitude cell
            var longitudes = stations[i].getElementsByTagName('long');
            var longCell = document.createElement('td');
            dataRow.appendChild(longCell);
            var longContent = document.createTextNode(longitudes[0].textContent);
            longCell.appendChild(longContent);
            
            // create the numBikes cell
            var nbBikes = stations[i].getElementsByTagName('nbBikes');
            var numCell = document.createElement('td');
            dataRow.appendChild(numCell);
            var numContent = document.createTextNode(nbBikes[0].textContent);
            numCell.appendChild(numContent);
            
          }
          var bikeData = document.getElementById('bikeData');
          bikeData.appendChild(table);
        }
      }
    };
    request.open('GET', 'stations.xml', true);
    request.send();
  };
};