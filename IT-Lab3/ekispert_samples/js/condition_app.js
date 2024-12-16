document.addEventListener("DOMContentLoaded", () => {
  // 探索条件パーツ初期化
  const conditonApp = new expGuiCondition(document.getElementById("condition"));
  conditonApp.dispCondition();

  document.getElementById("submit_button").addEventListener("click", () => {
    console.log(conditonApp.getCondition("plane"));
    console.log(conditonApp.getCondition("shinkansen"));
  });
});
