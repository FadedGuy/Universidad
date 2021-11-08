"use strict";

// Demande le lancement de l'exécution quand toute la page Web sera chargée
window.addEventListener('load', go);

// SAM Design Pattern : http://sam.js.org/
let actions,
  model,
  state,
  view;

// Point d'entrée de l'application
function go() {
  console.log('GO !');

  // Pour tester des choses pendant le développement...
  // à commenter quand pas besoin
  // sandbox();

  actions.initAndGo({ time: ['01', '23', '45'] });
}

// Bac à sable pour faire des tests
function sandbox() {

  function actions_updateTime(data) {
    const date = new Date();
    const hh = date.getHours();
    const mm = date.getMinutes();
    const ss = date.getSeconds();
    const time = [hh, mm, ss];
    console.log(data.message + time.join(':'));
  }

  function actions_fireAlarm(data) {
    console.log(data.message);
    window.clearInterval(intervalId);  // et arrête l'horloge !
  }

  const intervalId = window.setInterval(() => { actions_updateTime({ message: 'Il est : ' }) }, 2000);

  // Lance une alarme dans 7 secondes !
  const seconds = 7;
  const currentDate = new Date();
  let alarmDate = new Date();
  alarmDate.setSeconds(alarmDate.getSeconds() + seconds);
  const delay = alarmDate - currentDate;   // durée en millisecondes
  const timeoutId = window.setTimeout(() => { actions_fireAlarm({ message: 'Alarme déclenchée !' }) }, delay);
}

//------------------------------------------------------------------ Actions ---
// Actions appelées dans le code HTML quand des événements surviennent
//
actions = {

  initAndGo(data) {
    model.samPresent({ do: 'init', time: data.time });
  },

  updateTime() {
    let date = new Date();
    model.samPresent({ do: 'updatedTime', time: [date.getHours(), date.getMinutes(), date.getSeconds()]});
  },  // bouton "Heure courante" et setInterval()

  startTime() { 
    const intervalId = window.setInterval(() => {actions.updateTime()}, 1000);
    model.samPresent({do:'startTime', intervalId: intervalId});
  },   // bouton "Démarrer"

  stopTime() { 
    model.samPresent({do:'stopTime'});
  },    // button "Arrêter"

  addAlarm() { 
    let date = new Date();
    model.samPresent({do: 'addAlarm', time: [date.getHours(), date.getMinutes(), 0]});
  },    // button "Ajouter une alarme"

  changeAlarmHoursMinutes(data) { },  // sélection de l'heure et des minutes

  changeAlarmDescription(data) { },   // saisie d'une description

  removeAlarm(data) { },   // button "Enlever cette alarme"

  setAlarm(data) { },      // checkbox pour enclencher une alarme

  fireAlarm(data) { }      // lancée par le setTimeout() de l'alarme

};

//-------------------------------------------------------------------- Model ---
// Unique source de vérité de l'application
//
model = {
  time: {
    value: ['', '', ''],   // heures, minutes, secondes
    isOn: false,        // rafraichissement récurrent de l'heure
    intervalId: null,         // ref sur le timer récurrent
    sectionId: 'time',       // identifiant de la section HTML
    hasChanged: true,         // rafraichissement de la section nécessaire ou pas
  },
  alarms: {
    values: [                 //  tableau d'objets représentants des alarmes
      // {
      //   time: [],               // heures, minutes, secondes de l'alarme
      //   message: '',            // description de l'alarme
      //   timeoutId: null,        // ref sur le timer d'alarme
      // },
    ],
    sectionId: 'alarms',   // identifiant de la section HTML
    hasChanged: true,       // rafraichissement de la section nécessaire ou pas
  },

  // Demande au modèle de se mettre à jour en fonction des données qu'on
  // lui présente.
  // l'argument data est un objet confectionné dans les actions.
  // Les propriétés de data désignent la modification à faire sur le modèle.
  samPresent(data) {

    switch (data.do) {
      case 'init':
        this.time.value = data.time;
        break;
      case 'updatedTime':
        this.time.value = data.time;
        this.time.hasChanged = true;
        break;
      case 'startTime':
        this.time.intervalId = data.intervalId;
        this.time.isOn = true;
        break;
      case 'stopTime':
        window.clearInterval(this.time.intervalId);
        this.time.intervalId = null;
        this.time.isOn = false; 
        this.time.hasChanged = true;
        break;
      case 'addAlarm':
        const newAlarm = {
          time: data.time,
          message: '',
          timeoutId: null,
        };
        this.alarms.values.push(newAlarm);
        this.alarms.hasChanged = true;
        break;
      // TODO: et les cas suivants...
    }

    // Demande à l'état de l'application de prendre en compte la modification
    // du modèle
    state.samUpdate(this);
  }
};
//-------------------------------------------------------------------- State ---
// État de l'application avant affichage
//
state = {

  samUpdate(model) {

    this.samRepresent(model);
    // this.samNap(model);
  },

  // Met à jour l'état de l'application, construit le code HTML correspondant,
  // et demande son affichage.
  samRepresent(model) {
    let representation = 'Oops, should not see this...';

    if (model.time.hasChanged) {      // alors nouvelle représentation pour l'heure
      model.time.hasChanged = false;
      representation = view.timeUI(model, this);
      view.samDisplay(model.time.sectionId, representation);
    }
    if (model.alarms.hasChanged) {    // alors nouvelle représentation pour les alarmes
      model.alarms.hasChanged = false;
      representation = view.alarmsUI(model, this);
      console.log(representation);
      view.samDisplay(model.alarms.sectionId, representation);
    }
  }
};
//--------------------------------------------------------------------- View ---
// Génération de portions en HTML et affichage
//
view = {

  // Injecte le HTML dans une balise de la page Web.
  samDisplay(sectionId, representation) {
    const section = document.getElementById(sectionId);
    section.innerHTML = representation;
  },

  // Renvoit le HTML pour l'affichage de l'heure
  timeUI(model, state) {
    return `
      <time>${model.time.value[0]}:${model.time.value[1]}:${model.time.value[2]}</time>
      <div>
        <button class="time" onclick="actions.updateTime()">Heure courante</button>
        <button class="time" onclick="actions.${model.time.isOn ? "stopTime" : "startTime"}()">${model.time.isOn ? "Arreter" : "Demarrer"}</button>
      </div>
    `;
  },

  // Renvoit le HTML pour la gestion des alarmes
  alarmsUI(model, state) {
    // ? 
    let h = [...Array(24).keys()];
    let m = [...Array(60).keys()]; 
    let time = [0,0,0]
    if(model.alarms.values.length != 0){
      time = model.alarms.values[model.alarms.values.length-1].time;
    }
    console.log(time);
    const t_alarmes = model.alarms.values.map((alarm) => `
      <div class="alarme">   
        <input type="checkbox"/>
        <select>
          ${h.map(v => `<option value="${v}"${v == time[0] ? "`selected`":''}>${v}</option>`).join('')}
        </select>
        <select>
          ${m.map(v => `<option value="${v}">${v}</option>`).join('')}
        </select>
        <input type="text" placeholder="Description de l'alarme" />
        <button class="enlever">Enlever cette alarme</button>
      </div>
    `).join('');
    return `
    <div class="alarmes">
      ${t_alarmes}
    </div>
    <button class="ajouter" onclick="actions.addAlarm()">Ajouter une alarme</button>
    `;
  },

  // TODO: et les suivantes...
};
