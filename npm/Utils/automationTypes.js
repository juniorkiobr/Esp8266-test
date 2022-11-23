const automationTypes = {
    "1": "Date",
    "2": "SensorActive",
    "3": "SensorInactive",
};

function getAutomationType(type) {
    return automationTypes[type];
}

module.exports = getAutomationType;