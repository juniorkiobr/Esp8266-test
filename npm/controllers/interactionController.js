// import { app } from '../controllers/mainController';
const app = require('../controllers/mainController');
// import { wss, arduino } from "../servertest";
// var webSocket = require('../servertest');
const WebSocketServer =  require("../controllers/webSocketController");

console.log(WebSocketServer);

var waitInterval = null;
var resInterval = null;
var bodyInterval = null;


const Interaction = require('../models/interactions');

var waitArduinoResponse = function(){
    if(WebSocketServer.getWaitArduinoResponse()){ return; }
    bodyInterval.response_arduino = WebSocketServer.getLastArduinoMessage()
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

app.get("/interactions/getAll", async (req, res) =>{
    const interactions = await Interaction.findAll();
    res.send(interactions);
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

app.put("/interactions/criarAmbiente", async (req, res) => {
    console.log(req.body);

    await Interaction.create(req.body)
    .then(() => {
        return res.json({
            erro: false,
            mensagem: "Interação criada com sucesso"
        });
    }).catch(() => {
        return res.status(400).json({
            erro: true,
            mensagem: "Erro: Erro ao cadastrar!"
        });
    });

    //res.send("Página cadastrar");
});