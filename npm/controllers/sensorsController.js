const app = require('../controllers/mainController');
// import { app } from '../controllers/mainController';
const Sensor = require('../models/sensors');




app.get("/sensors/getAll", async (req, res) =>{
    const sensors = await Sensor.findAll();
    res.send(sensors);
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
