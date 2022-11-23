const http = require('http');
const ws = require('ws');
const Sensor = require("./models/sensors");
const sensorsController = require("./controllers/sensorsController");

const server = http.createServer();
const wss = new ws.WebSocketServer({ server });

server.listen(2053, () => {
  console.log('Server listening on port 2053');
});

wss.on('connection', function connection(ws) {
  ws.on('message', function message(data) {
    console.log('received: %s', data);
    try{
      const parsedData = JSON.parse(""+data);
      if(parsedData.status_code === 200){
        let message = ""

        if(parsedData.id_sensor === 1){
          message = "Temperatura: " + parsedData.temperatura;
          message += " - Umidade: " + parsedData.umidade;

        }else if(parsedData.id_sensor === 2){
          message = "Presença: " + (parsedData.estado == 1 ? "Detectada" : "Não detectada");

        }

        try{
          if(parsedData.id_sensor != undefined){
            Sensor.update({valor: message }, {where: {id: parsedData.id_sensor}});

          }
        }catch(err){
          console.log(parsedData)
          

        }
      }
    } catch (e) {
      console.log("" + data)
      wss.clients.forEach(function each(client) {
        if (client.readyState === ws.OPEN && client !== ws) {
          client.send("" + data);
        }
      });

    }
    // wss.clients.forEach(function each(client) {
    //   if (client.readyState === ws.OPEN && client !== ws) {
    //     try {
    //       let jsonObj = JSON.parse(""+data);
    //       if(jsonObj.status_code == 200) {
    //         client.send(jsonObj.id_sensor == 1 ? "Temperatura/Umidade: " + jsonObj.temperatura + " / " + jsonObj.umidade : "Sensor Presença: " + (jsonObj.estado == 1 ? "Detectado" : "Ausente"));
    //       }
    //     }catch(e) {
    //       console.log(e);
    //     }
    //   }
    // })
  });


  ws.send('something');
});
