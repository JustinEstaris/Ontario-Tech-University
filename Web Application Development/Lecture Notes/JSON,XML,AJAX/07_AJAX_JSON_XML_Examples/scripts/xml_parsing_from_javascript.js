window.onload = function () {
    var goButton = document.getElementById('goButton');
    goButton.onclick = function() {
      var request = new XMLHttpRequest();
      request.onreadystatechange = function() {
         if ((request.readyState == 4) && 
             (request.status == 200)) {

            var result = '<ul>';
            
            //var xmlDocument = request.responseXML;
            // ignoring request.responseXML so we can test parsing XML
            var rawXML = request.responseText;
            var parser = new DOMParser();
            var xmlDocument = parser.parseFromString(rawXML,"text/xml");
            var laptops = xmlDocument.getElementsByTagName('laptop');
            for (var i = 0; i < laptops.length; i++) {
                var cpu = laptops[i].getAttribute('cpu');
                var price = laptops[i].getAttribute('price');
                result += '<li>' + cpu + ' (' + price + ')</li>';
            }
                        
            result += '</ul>';
            var output = document.getElementById('output');
            output.innerHTML = result;
         }
      };
      request.open('GET','inventory.xml',true);
      request.send();
   };
};
