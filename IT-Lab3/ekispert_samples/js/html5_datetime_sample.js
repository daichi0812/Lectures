document.addEventListener("DOMContentLoaded", () => {
  document.getElementById("submit_button").addEventListener("click", () => {
    const date = document.getElementById("date").value;
    const datetime = document.getElementById("datetime").value;
    console.log(date);
    console.log(datetime);
    const dateObj = new Date(date);
    const datetimeObj = new Date(datetime);
    console.log(dateObj);
    console.log(datetimeObj);
  });
});
