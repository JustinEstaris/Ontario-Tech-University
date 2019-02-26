window.onload = function() {
   var plainTextButton = document.getElementById('plainTextButton');
   plainTextButton.onclick = function() {
      var xmlHttpRequest = new XMLHttpRequest();
      xmlHttpRequest.onreadystatechange = function() {
         if ((xmlHttpRequest.readyState == 4) &&
             (xmlHttpRequest.status == 200)) {
            var destination = document.getElementById('plainTextDiv');
            destination.innerHTML = xmlHttpRequest.responseText;
         }
      };
      xmlHttpRequest.open('GET','test_data.txt',true);
      xmlHttpRequest.send();
   };

   var csvButton = document.getElementById('csvButton');
   csvButton.onclick = function() {
      var xmlHttpRequest = new XMLHttpRequest();
      xmlHttpRequest.onreadystatechange = function() {
         if ((xmlHttpRequest.readyState == 4) &&
             (xmlHttpRequest.status == 200)) {
            var data = xmlHttpRequest.responseText.split(',');
            var firstName = document.getElementById('csvFirstName');
            var lastName = document.getElementById('csvLastName');
            firstName.setAttribute('value', data[0]);
            lastName.setAttribute('value', data[1]);
         }
      };
      xmlHttpRequest.open('GET', 'test_data.csv', true);
      xmlHttpRequest.send();
   };

   var jsonButton = document.getElementById('jsonButton');
   jsonButton.onclick = function() {
      var xmlHttpRequest = new XMLHttpRequest();
      xmlHttpRequest.onreadystatechange = function() {
         if ((xmlHttpRequest.readyState == 4) &&
             (xmlHttpRequest.status == 200)) {
            var rawData = xmlHttpRequest.responseText;
            var person = JSON.parse(rawData);
            var firstName = document.getElementById('jsonFirstName');
            var lastName = document.getElementById('jsonLastName');
            firstName.setAttribute('value', person['firstName']);
            lastName.setAttribute('value', person['lastName']);
         }
      };
      xmlHttpRequest.open('GET', 'test_data.json', true);
      xmlHttpRequest.send();
   };

   var xmlButton = document.getElementById('xmlButton');
   xmlButton.onclick = function() {
      var xmlHttpRequest = new XMLHttpRequest();
      xmlHttpRequest.onreadystatechange = function() {
         if ((xmlHttpRequest.readyState == 4) &&
             (xmlHttpRequest.status == 200)) {
            var xmlData = xmlHttpRequest.responseXML;
            var person = xmlData.getElementsByTagName('person')[0];
            var firstNameVal = person.getAttribute('firstName');
            var lastNameVal = person.getAttribute('lastName');
            var firstName = document.getElementById('xmlFirstName');
            var lastName = document.getElementById('xmlLastName');
            firstName.setAttribute('value', firstNameVal);
            lastName.setAttribute('value', lastNameVal);
         }
      };

      xmlHttpRequest.open('GET', 'test_data.xml', true);
      xmlHttpRequest.send();
   };
};
