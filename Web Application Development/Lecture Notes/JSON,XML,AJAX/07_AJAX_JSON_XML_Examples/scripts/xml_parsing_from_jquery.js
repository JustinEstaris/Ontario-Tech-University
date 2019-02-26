$(document).ready(function() {
   $('#goButton').click(function() {
      $.get('inventory.xml', function(xmlDoc) {
         // Hack:  Since $.get() automatically parses the XML
         var rawXML = '\
<inventory>\
   <computers>\
      <laptop price="499.99" cpu="i5-3570" />\
      <laptop price="549.99" cpu="i5-3570" />\
      <laptop price="999.99" cpu="i7-2600" />\
   </computers>\
</inventory>';
         var result = '<ul>';
         var xmlDoc2 = $.parseXML(rawXML);
         $(xmlDoc2).find('laptop').each(function() {
            result += '<li>' + $(this).attr('cpu') + ' (' + $(this).attr('price') + ')</li>';
         });
         result += '</ul>';
         $('#output').html(result);
      });
   });
});
