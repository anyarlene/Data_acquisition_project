function loadJSON(callback) {

    var xobj = new XMLHttpRequest();
        xobj.overrideMimeType("application/json");
    xobj.open('GET', 'data.json', true); // Replace 'my_data' with the path to your file
    xobj.onreadystatechange = function () {
          if (xobj.readyState == 4 && xobj.status == "200") {
            // Required use of an anonymous callback as .open will NOT return a value but simply returns undefined in asynchronous mode
            callback(xobj.responseText);
          }
    };
    xobj.send(null);
 }

function init() {
 loadJSON(function(response) {
  // Parse JSON string into object
    var data = JSON.parse(response).data;
    console.log(data);
    var x_values = data.map((line) => line[0]);
    var y_values = data.map((line) => line[1]);
    var chartData = {
      labels : x_values,
      datasets : [
        {
          label: "My First dataset",
          fillColor : "rgba(220,220,220,0.2)",
          strokeColor : "rgba(220,220,220,1)",
          pointColor : "rgba(220,220,220,1)",
          pointStrokeColor : "#fff",
          pointHighlightFill : "#fff",
          pointHighlightStroke : "rgba(220,220,220,1)",
          data : y_values
        }
      ]
    }

    window.onload = function(){
      var chartOptions = { responsive : true };
      var chart = document.getElementById("canvas").getContext("2d");
      window.myBar = new Chart(chart).Line(chartData, chartOptions);
    }

 });
}

init();
