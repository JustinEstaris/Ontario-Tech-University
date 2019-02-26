$(document).ready(() => {
    $("table th").click(function() {
        $("td").removeClass("selected");
    
        let tagType = $(this).siblings()[0].localName;
    
        //ROWS
        if (tagType == "td") {
          $(this).siblings().addClass("selected");
    
        // COLUMNS  
        } else if (tagType == "th") {
          column = $(this).index();
          $("table tr td").each(function() {
            if ($(this).index() == column) 
              $(this).addClass("selected");
          });
        }
      });
    
      // CELL
      $("table td").click(function() {
        $("td").removeClass("selected");
        $(this).addClass("selected");
    
        // Edit
        const value = $(this).text();
        $(this).html("<input type='text' value='" + value + "' onkeydown='edit();'/>");
        $("input").focus();
      });
    });
    
    const edit = () => {
        if (event.keyCode == 13)
          $(event.target).parent().html(event.target.value)
      };