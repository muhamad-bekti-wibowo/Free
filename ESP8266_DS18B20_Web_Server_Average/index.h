const char Temp[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <script src="https://code.highcharts.com/highcharts.js"></script>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Pengukur Listrik</title>
    <style>
        .center {
            display: flex;
            align-items: center;
            justify-content: center;
            flex-direction: column;
            width: 100vw;
            height: 100vh;
        }

        td {
            font-size: 2vw;
            border: 0px solid black;
            margin: 10px;
            padding: 10px;
            box-shadow: 0px 20px 20px 0px rgba(0, 0, 0, 0.2);
            text-align: center;
            width: 300px;
            height: 50px;
        }

        button {
            padding: 10px;
            margin: 40px 10px 10px 10px;
            box-shadow: 0px 20px 20px 0px rgba(0, 0, 0, 0.2);
            width: 100px;
            height: 40px;
            border: 0px solid green;
            border-radius: 40px;
        }
    </style>
</head>

<body>
    <div class="center">
        <div id="charttemp" class="container" style="margin-top: 40px; width: 80vw;"></div>

    </div>

    <script>
        var chartA = new Highcharts.Chart({
            chart: { renderTo: 'charttemp' },
            title: { text: 'Temp' },
            series: [{
                showInLegend: false,
                data: []
            }],
            plotOptions: {
                line: {
                    animation: false,
                    dataLabels: { enabled: true }
                },
                series: { color: '#059e8a' }
            },
            xAxis: {
                type: 'datetime',
                dateTimeLabelFormats: { second: '%H'+':%M:%S' }
            },
            yAxis: {
                title: { text: 'V' }
            },
            credits: { enabled: false }
        });
    </script>
</body>
<script>
    setInterval(function () { //Load Data
        var xhttpDataLine1 = new XMLHttpRequest();
        xhttpDataLine1.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                const All_Array = this.responseText.split("~");
                var x = (new Date()).getTime(),
                    y = parseFloat(All_Array[0]);
                if (chartA.series[0].data.length > 100) {
                    chartA.series[0].addPoint([x, y], true, true, true);
                } else {
                    chartA.series[0].addPoint([x, y], true, false, true);
                }

            }
        };
        xhttpDataLine1.open("GET", "/data", true);
        xhttpDataLine1.send();
    }, 1000);
</script>

</html>
)=====";
