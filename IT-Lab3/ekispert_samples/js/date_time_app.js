document.addEventListener("DOMContentLoaded", () => {
  // 日付入力パーツ初期化
  const dateTimeApp = new expGuiDateTime(document.getElementById("dateTime"));
  dateTimeApp.dispDateTime();

  document.getElementById("submit_button").addEventListener("click", () => {
    console.log(dateTimeApp.getDate());
    console.log(dateTimeApp.getTime());
  });
});
