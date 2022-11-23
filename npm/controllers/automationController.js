const app = require('../controllers/mainController');
const WebSocketServer =  require("../controllers/webSocketController");
const Automation = require('../models/automations');
var cron = require('node-cron');

var schedules = [];

app.get("/automations/getAll", async (req, res) =>{
    const automations = await automations.findAll();
    res.send(automations);
});

function programSchedule(automation){
    console.log(automation);
    // console.log(automation.dateAutomation);
    let dateFormat = {
        day: automation.dateAutomation.getDate(),
        month: automation.dateAutomation.getMonth() + 1,

        hour: automation.dateAutomation.getUTCHours(),
        minute: automation.dateAutomation.getUTCMinutes(),
    }

    function callbackSchedule(){
        // let id_schedule = schedules.length + 1;
        console.log("callbackSchedule");
        // console.log('running a task every minute');
        if(WebSocketServer.sendToArduino("cmd_ard_uno:>writeInteraction:" + automation.idInteraction + ";" + automation.value)    ){
            console.log("Interacao programada enviada para o arduino");
        }else{
            console.log("Erro: Arduino não conectado!");
        }
        
        // (schedules.pop(id_schedule)).stop();
    }

    let schedule  = cron.schedule('0 '+dateFormat.minute+' ' + dateFormat.hour + ' ' + dateFormat.day + ' ' + dateFormat.month + ' *', callbackSchedule);
    // schedules.push(schedule);
}

function programAutomations(){
    Automation.findAll().then(automations => {
        automations.forEach(automation => {
            if(automation.dateAutomation){
                programSchedule(automation);
            }
        });
    });
}

app.put("/automations/criarAutomacao", async (req, res) => {
    console.log(req.body);
    req.body.dateAutomation = DateTime.fromISO(req.body.dateAutomation, {zone: 'utc'}).toJSDate();

    await Automation.create(req.body)
    .then(() => {
        try{
            Automation.findAll({where: {idInteraction: req.body.idInteraction}}).then(automations => {
                automations.forEach(automation => {
                    if(automation.dateAutomation){
                        programSchedule(automation);
                    }
                });
            });
            return res.json({
                erro: false,
                mensagem: "Automacao criada com sucesso"
            });
        }catch(err){
            console.log(err);
            return res.json({
                erro: true,
                mensagem: "Erro: Automacao nao criada"
            });
        }
    }).catch((err) => {
        return res.status(400).json({
            erro: true,
            mensagem: "Erro: Erro ao cadastrar!",
            err: err
        });
    });

    //res.send("Página cadastrar");
});

// programAutomations();
