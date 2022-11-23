const app = require('../controllers/mainController');
// import { app } from '../controllers/mainController';
const Sensor = require('../models/sensors');
const WebSocketServer =  require("../controllers/webSocketController");

var waitInterval = null;
var resInterval = null;
var bodyInterval = null;

var waitArduinoResponse = function(){
    if(WebSocketServer.getWaitArduinoResponse()){ return; }
    try{
        bodyInterval.response_arduino = JSON.parse(WebSocketServer.getLastArduinoMessage());

    }catch(e){
        bodyInterval.response_arduino = WebSocketServer.getLastArduinoMessage();
    }
    resInterval.send(JSON.stringify(bodyInterval));
    clearInterval(waitInterval);
    resInterval = null;
    bodyInterval = null;
}

function delayArduinoResponse(res, body){
    resInterval = res;
    bodyInterval = body;
    waitInterval = setInterval(waitArduinoResponse, 1000);
}




app.get("/sensors/getAll", async (req, res) =>{
    const sensors = await Sensor.findAll();
    res.send(sensors);
});

app.post("/interactions/writeInteraction", async (req, res) =>{
    if(WebSocketServer.sendToArduino("cmd_ard_uno:>writeInteraction:" + req.body.id + ";" + req.body.value)    ){
        console.log(req.body);
        // await Interaction.update({valor: req.body.value }, {where: {id: req.body.id}});
        let body = {
            id: req.body.id,
            value: req.body.value,
            message: "Interacao atualizada com sucesso",            
        }
        delayArduinoResponse(res, body);
    }else{
        delayArduinoResponse(res, {message: "Erro: Arduino não conectado!"});
    }

});

app.get("/sensors/readSensor", async (req, res) =>{

    if(WebSocketServer.sendToArduino("cmd_ard_uno:>readSensor:" + req.body.id)    ){
        console.log(req.body);
        // await Interaction.update({valor: req.body.value }, {where: {id: req.body.id}});
        let body = {
            id: req.body.id,
            value: req.body.value,
            message: "Leitura realizada com sucesso",            
        }
        delayArduinoResponse(res, body);
    }else{
        delayArduinoResponse(res, {message: "Erro: Arduino não conectado!"});
    }
});

app.put("/sensors/criarAmbiente", async (req, res) => {
    console.log(req.body);

    await Sensor.create(req.body)
    .then(() => {
        return res.json({
            erro: false,
            mensagem: "Ambiente criado com sucesso"
        });
    }).catch(() => {
        return res.status(400).json({
            erro: true,
            mensagem: "Erro: Erro ao cadastrar!"
        });
    });

    //res.send("Página cadastrar");
});
