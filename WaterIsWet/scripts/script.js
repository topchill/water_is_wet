var myDevice = "e00fce68e30ddb5186932a5c";
var myToken = "7c8fbbaec21e491e2d9ac390e715b9fdbcde51fe";
var particle = new Particle();
var PH = 0;
var TEMP = 0;
var TDS = 0;
var TURB = 0;

beginPreparation();
// window.setInterval(checkValue, 10000);

function beginPreparation() {
    window.setInterval(checkValue, 3000);
    checkValue();
}

function checkValue(){
    particle.getVariable({ deviceId: myDevice, name: "temperature", auth: myToken }).then(function(data) {
        TEMP = data.body.result;
        TEMP = parseFloat(TEMP);
        TEMP = Math.round(TEMP);
        TEMP = TEMP.toString();
        document.getElementById("temp").innerHTML = "" + TEMP; 
        console.log("I just retrived the temperature that is : " + TEMP);
    }, function(err) {
            console.log("An error occurred retrieving data:", err);
    });
    particle.getVariable({ deviceId: myDevice, name: "phValue", auth: myToken }).then(function(data) {
        PH = data.body.result;
        PH = parseFloat(PH);
        PH = Math.round(PH);
        PH = PH.toString();
        document.getElementById("ph").innerHTML = "" + PH; 
        console.log("I just retrived the PH that is : " + PH);
    }, function(err) {
            console.log("An error occurred retrieving data:", err);
    });
    particle.getVariable({ deviceId: myDevice, name: "TDS", auth: myToken }).then(function(data) {
        TDS = data.body.result;
        TDS = parseFloat(TDS);
        TDS = Math.round(TDS);
        TDS = TDS.toString();
        document.getElementById("tds").innerHTML = "" + TDS; 
        console.log("I just retrived the TDS that is : " + TDS);
    }, function(err) {
            console.log("An error occurred retrieving data:", err);
    });
    particle.getVariable({ deviceId: myDevice, name: "turbidityValue", auth: myToken }).then(function(data) {
        TURB = data.body.result;
        TURB = parseFloat(TURB);
        TURB = Math.round(TURB);
        TURB = TURB.toString();
        document.getElementById("turb").innerHTML = "" + TURB; 
        console.log("I just retrived the turbidity that is : " + TURB);
    }, function(err) {
            console.log("An error occurred retrieving data:", err);
    });
}