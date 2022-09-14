const { Sequelize } = require("sequelize")

const db = require('./db');

const Sensor = db.define('sensors',{
    id:{
        type: Sequelize.INTEGER,
        autoIncrement: true,
        alowNull: false,
        primaryKey: true
    },
    nameSensor:{
        type: Sequelize.STRING,
        alowNull: false,
    },
    Ambiente:{
        type: Sequelize.STRING,
        alowNull: false,
    },
    valor:{
        type: Sequelize.STRING,
        alowNull: false,
    }
});

//Criar a tabela
Sensor.sync();

module.exports = Sensor;