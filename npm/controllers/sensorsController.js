const express = require('express');
const app = express();
const Sensor = require('../models/sensors');

app.use(express.json());
app.use(express.urlencoded({ extended: true }));

app.get("/", async (req, res) => {
    res.send("Página inicial - Celke");
});

app.get("/getAll", async (req, res) =>{
    const sensors = await Sensor.findAll();
    res.send(sensors);
});

app.put("/criarAmbiente", async (req, res) => {
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

app.listen(2052, () => {
    console.log("Servidor iniciado na porta 2052: http://localhost:2052");
});