window.onload = function() {
    //Select Tables and Rows
  var table = document.getElementsByTagName("table")[0];
  var rows = table.rows;

  initializeTableEventListeners(table, rows);


}

//Initializing cell event listeners
function initializeTableEventListeners(table, rows) {
  //Add Column Event Listeners
  var assignmentRow = rows[0].cells;
  for (let columnIndex = 1; columnIndex < assignmentRow.length; columnIndex++) {
    assignmentRow[columnIndex].addEventListener("click", function(event) {
      columnSelected(columnIndex, table);
    });
  }

  // Add Row Event Listeners
  for (let columnIndex = 1; columnIndex < rows.length; columnIndex++) {
    let studentIDRow = rows[columnIndex].getElementsByTagName("th")[0];
    
    studentIDRow.addEventListener("click", function(event) {
      rowSelected(columnIndex, table)
    });
  }

  //Add Cell Event Listeners
  for (let columnIndex = 1; columnIndex < rows.length; columnIndex++) {
    let cells = rows[columnIndex].getElementsByTagName("td");

    for (let rowIndex = 0; rowIndex < cells.length; rowIndex++) {
        cells[rowIndex].addEventListener("click", function(event) {
          cellSelected (rowIndex,cells);
      });
    }
  } 
};

// Add a CSS class for the entire column when a assignment cell is selected
function columnSelected(columnIndex, table) {
  for (let rowIndex = 1; rowIndex < table.rows.length; rowIndex++){
    document.getElementsByTagName("tr")[rowIndex].cells[columnIndex].className = "selected";
  }
};

// Add a CSS class for the entire row when a student cell is selected
function rowSelected(columnIndex, table){
 for (let rowIndex = 1; rowIndex < table.rows.length; rowIndex++){
        document.getElementsByTagName("tr")[columnIndex].cells[rowIndex].className = "selected";
    }
};

// Add a CSS class when a cell is selected
function cellSelected(rowIndex,cells){
  cells [rowIndex].style.backgroundColor = "lightBlue";
};