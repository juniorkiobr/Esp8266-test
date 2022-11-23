const { Sequelize, DATE } = require("sequelize")
const Interaction = require("../models/interactions");
const Sensor = require("../models/sensors");


const db = require('./db');

const Automation = db.define('automations',{
    id:{
        type: Sequelize.INTEGER,
        autoIncrement: true,
        alowNull: false,
        primaryKey: true
    },
    nameInteraction:{
        type: Sequelize.STRING,
        alowNull: false,
    },
    idSensor:{
        type: Sequelize.INTEGER,
        alowNull: true,
    },
    idInteraction:{
        type: Sequelize.INTEGER,
        alowNull: true,
    },
    typeAutomation:{
        type: Sequelize.INTEGER,
        alowNull: false,
    },
    dateAutomation:{
        type: "TIMESTAMP",
        alowNull: true,
    },
    value:{
        type: Sequelize.INTEGER,
        alowNull: true,
    }
});

//Criar a tabela
Automation.sync();

// Automation.hasMany(Interaction, {foreignKey: 'idInteraction'});
// Automation.hasMany(Sensor, {foreignKey: 'idSensor'});

module.exports = Automation;