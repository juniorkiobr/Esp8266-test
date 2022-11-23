const express = require('express');
const app = express();

app.use(express.json());
app.use(express.urlencoded({ extended: true }));

app.get("/", async (req, res) => {
    res.send("Página inicial - Celke");
});

app.listen(80, () => {
    console.log("Servidor web iniciado na porta 80: http://localhost");
});
module.exports = app;