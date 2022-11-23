const http = require('http');
const ws = require('ws');
const Sensor = require("../models/sensors");
const Interaction = require("../models/interactions");

const server = http.createServer();
const wss = new ws.WebSocketServer({ server });
var arduino = null;
var lastArduinoMessage = 'start';
var lock_resp_arduino = false;

function sendToArduino(message, wait_response = false){
    if(arduino && arduino.readyState === ws.OPEN){
        arduino.send(message);
        if(wait_response){
            lock_resp_arduino = true;
        }
        return true;
    }else{
      return false;
    }
}

function sendToAll(message){
    wss.clients.forEach(function each(client) {
        if (client.readyState === ws.OPEN) {
            client.send(message);
        }
    });
}

function sendToAllExcept(message, ws){
    wss.clients.forEach(function each(client) {
        if (client.readyState === ws.OPEN && client !== ws) {
            client.send(message);
        }
    });
}

var arduinoOnMessage = function(data){
    lastArduinoMessage = ""+data;
    console.log("Arduino on message: " + lastArduinoMessage);


    try{
        const parsedData = JSON.parse(""+data);
        if(parsedData.status_code === 200){
          let message = ""
  
          if(parsedData.id_sensor){
            console.log("Sensor: " + parsedData.id_sensor + " - " + parsedData.value);
            if(parsedData.id_sensor == "1"){
              message = "Temperatura: " + parsedData.temperatura;
              message += " - Umidade: " + parsedData.umidade;
    
            }else if(parsedData.id_sensor == "2"){
              message = "Presença: " + (parsedData.estado == 1 ? "Detectada" : "Não detectada");
    
            }
            Sensor.update({valor: message }, {where: {id: parsedData.id_sensor}});
  
          } else if(parsedData.id_interacao){
            Interaction.update({valor: parsedData.value }, {where: {id: parsedData.id_interacao}});
  
          }
          if(lock_resp_arduino){
            lock_resp_arduino = false;
          }
        }
    } catch (e) {
      console.log("" + data)     
      
    }

}

var getLastArduinoMessage = function(){
    return lastArduinoMessage;
}

function getWaitArduinoResponse(){
    return lock_resp_arduino;
}
wss.getUniqueID = function () {
    function s4() {
        return Math.floor((1 + Math.random()) * 0x10000).toString(16).substring(1);
    }
    return s4() + s4() + '-' + s4();
};

wss.on('connection', function connection(ws, req) {
  ws.id = wss.getUniqueID();

  if(req.headers['sec-websocket-key'] === "MDEyMzQ1Njc4OWFiY2RlZg=="){
    console.log("Arduino connected", req.headers['sec-websocket-key']);
    ws.on('message', arduinoOnMessage);
    arduino = ws;
  }else{
    ws.on('message', function message(data) {
        wss.clients.forEach(function each(client) {
            if (client.readyState === ws.OPEN && client !== ws) {
                client.send("" + data);
            }
        });
      });
  }

  


  ws.send('something');
});

server.listen(2053, () => {
    console.log('WebSocket Server listening on port 2053');
  });
module.exports = {sendToArduino, sendToAll, sendToAllExcept, arduinoOnMessage, getLastArduinoMessage, getWaitArduinoResponse};
