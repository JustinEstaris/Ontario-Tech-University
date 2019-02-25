document.addEventListener("DOMContentLoaded", function(event) {
  const table = document.getElementsByTagName("table")[0];
  const rows = table.rows;

  // COLUMNS
  rows[0].addEventListener("click", e => {
    if (e.target.cellIndex !== 0) {
      resetTable();
      for (let j = 1; j < table.rows.length; j++)
        document
          .getElementsByTagName("tr")
          [j].cells[e.target.cellIndex].classList.add("selected");
    }
  });

  // ROWS
  document.getElementsByTagName("tbody")[0].addEventListener("click", e => {
    if (e.target.tagName === "TH" && e.target.parentElement.rowIndex !== 0) {
      resetTable();
      for (let j = 1; j < table.rows.length; j++)
        document
          .getElementsByTagName("tr")
          [e.target.parentElement.rowIndex].cells[j].classList.add("selected");
    }
  });

  // CELLS
  document.getElementsByTagName("tbody")[0].addEventListener("click", e => {
    if (e.target.tagName === "TD") {
      const current = document.getElementsByTagName("tr")[
        e.target.parentElement.rowIndex
      ].cells[e.target.cellIndex];
      resetTable();
      current.classList.toggle("selected");

      // Updating cells logic (lab 5)
      const value = current.innerHTML;
      current.innerHTML = "<input type='text' value='" + value + "' onkeydown='edit();'/>";
    }
  });
});


function edit() {
  if(event.keyCode == 13){
    const newVal = event.target.value;
    event.target.parentElement.innerHTML = newVal;
  }
}

const resetTable = () =>
  Array.from(document.querySelectorAll("td")).forEach(td =>
    td.classList.remove("selected")
);