const { Sequelize } = require("sequelize")

const db = require('./db');

const Interaction = db.define('interactions',{
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
    Ambiente:{
        type: Sequelize.STRING,
        alowNull: false,
    },
    valor:{
        type: Sequelize.INTEGER,
        alowNull: false,
    }
});

//Criar a tabela
Interaction.sync();

module.exports = Interaction;