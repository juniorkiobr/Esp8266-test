const express = require('express');
const app = express();
const Sensor = require('../models/sensors');

app.use(express.json());

app.get("/", async (req, res) => {
    res.send("Página inicial - Celke");
});

app.get("/getAll", async (req, res) =>{
    const sensors = await Sensor.findAll();

    await Sensor.get(res.body);
});

app.put("/criarAmbiente", async (req, res) => {
    //console.log(req.body);

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

app.listen(8080, () => {
    console.log("Servidor iniciado na porta 8080: http://localhost:8080");
});