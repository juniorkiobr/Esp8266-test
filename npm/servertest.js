const http = require('http');
const ws = require('ws');

const server = http.createServer();
const wss = new ws.WebSocketServer({ server });

server.listen(3000, () => {
  console.log('Server listening on port 3000');
});

wss.on('connection', function connection(ws) {
  ws.on('message', function message(data) {
    console.log('received: %s', data);
    wss.clients.forEach(function each(client) {
      if (client.readyState === ws.OPEN && client !== ws) {
        try {
          let jsonObj = JSON.parse(""+data);
          if(jsonObj.status_code == 200) {
            client.send(jsonObj.id_sensor == 1 ? "Temperatura/Umidade: " + jsonObj.temperatura + " / " + jsonObj.umidade : "Sensor Presença: " + (jsonObj.estado == 1 ? "Detectado" : "Ausente"));
          }
        }catch(e) {
          console.log(e);
        }
      }
    })
  });

  ws.send('something');
});
