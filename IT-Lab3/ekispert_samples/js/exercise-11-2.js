document.addEventListener("DOMContentLoaded", () => {
    // 駅名入力パーツ初期化
    const departureStation = new expGuiStation(document.getElementById("departureStation"));
    departureStation.dispStation();
    const arrivalStation = new expGuiStation(document.getElementById("arrivalStation"));
    arrivalStation.dispStation();

    // 経路表示パーツ初期化
    const resultApp = new expGuiCourse(document.getElementById("result"));

    // 日付入力パーツ初期化
    const dateTimeApp = new expGuiDateTime(document.getElementById("dateTime"));  
    dateTimeApp.dispDateTime();  
    



    // 探索実行時のコールバック関数
    function result(isSuccess) {
        if (isSuccess) {
            console.log("運賃：" + resultApp.getFarePrice());
            console.log("路線リスト：" + resultApp.getLineList());
            console.log("地点リスト：" + resultApp.getPointList());
            console.log("出発日時：" + resultApp.getDepartureDate());
            console.log("到着日時：" + resultApp.getArrivalDate());
            console.log(resultApp.getResultString());
        } else {
            alert("探索結果が取得できませんでした");
        }
    }

    // 経路を表示するための処理
    document.getElementById("submit_button").addEventListener("click", () => {
        // 発着地リスト
        let searchWord = `viaList=${departureStation.getStation()}:${arrivalStation.getStation()}`;
        // 列車運行日
        searchWord += `&date=${dateTimeApp.getDate()}`;
        // 列車の発着時刻
        searchWord += `&time=${dateTimeApp.getTime()}`;
        // 探索結果数
        searchWord += "&answerCount=" + String(3);

        // 片道料金
        let price = resultApp.PRICE_ONEWAY;
        console.log(searchWord);
        // 探索を実行
        resultApp.search(searchWord, price, result);
    });

});
