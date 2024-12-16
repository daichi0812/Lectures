document.addEventListener("DOMContentLoaded", () => {
  // 駅名入力パーツ初期化
  const stationApp = new expGuiStation(document.getElementById("station"));
  stationApp.dispStation();

  document.getElementById("submit_button").addEventListener("click", () => {
    console.log(stationApp.getStation());
  });
});
