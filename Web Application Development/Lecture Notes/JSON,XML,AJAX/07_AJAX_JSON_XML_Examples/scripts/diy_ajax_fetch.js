window.onload = function() {

  // AJAX
   var plainTextButton = document.getElementById('plainTextButton');
   plainTextButton.onclick = function() { //If the plainTextButton has been clicked
      fetch('test_data.txt') // Fetch AJAX
      .then((resp) => resp.text()) // Resp Object has been converted into a string object
      .then(function(data) { //Anonymous Function
          // success
          var destination = document.getElementById('plainTextDiv');
          destination.innerHTML = data;
      })
      .catch(function(error) {
        // error
        console.log(error);
      });
   };

  // CSV
   var csvButton = document.getElementById('csvButton');
   csvButton.onclick = function() {
     fetch('test_data.csv')
     .then((resp) => resp.text())
     .then(function(data) {
         // success
         var fields = data.split(',');
         var firstName = document.getElementById('csvFirstName');
         var lastName = document.getElementById('csvLastName');
         firstName.setAttribute('value', fields[0]);
         lastName.setAttribute('value', fields[1]);
     })
     .catch(function(error) {
       // error
       console.log(error);
     });
   };

   // JSON
   var jsonButton = document.getElementById('jsonButton');
   jsonButton.onclick = function() {
     fetch('test_data.json')
     .then((resp) => resp.json())
     .then(function(data) { //Using the JSON Object
         // success
         var firstName = document.getElementById('jsonFirstName');
         var lastName = document.getElementById('jsonLastName');

         firstName.setAttribute('value', data.firstName);
         lastName.setAttribute('value', data.lastName);
     })
     .catch(function(error) {
       // error
       console.log(error);
     });
   };

  // XML
   var xmlButton = document.getElementById('xmlButton');
   xmlButton.onclick = function() {
     fetch('test_data.xml')
     .then((resp) => resp.text())
     .then(function(data) {
         // success
         var xmlData = parseXML(data); // Parse XML Data

         var person = xmlData.getElementsByTagName('person')[0];
         var firstNameVal = person.getAttribute('firstName');
         var lastNameVal = person.getAttribute('lastName');
         var firstName = document.getElementById('xmlFirstName');
         var lastName = document.getElementById('xmlLastName');
         
         firstName.setAttribute('value', firstNameVal);
         lastName.setAttribute('value', lastNameVal);
     })
     .catch(function(error) {
       // error
       console.log(error);
     });
   };
};

function parseXML(rawXML) {
  var parser = new window.DOMParser() //Use the Browser's DOM Parser
  return parser.parseFromString(rawXML, "text/xml"); //Return XML Text
}
