$("table th").click(function() {
    $("td").removeClass("selected");
    let tagType = $(this).siblings()[0].localName;
    if(tagType == "td"){
      $(this).siblings().addClass("selected");
    }else if(tagType == "th"){
      column = $(this).index()
      $('table tr td').each(function() {
        if($(this).index() == column){
          $(this).addClass("selected")
        }
     });
    } 
  });
  $("table td").click(function() {
    $("td").removeClass("selected");
    $(this).addClass("selected");
  });