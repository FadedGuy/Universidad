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
    let addDate = new Date(date.getTime() + 60000); //Ajoute 1 min a l'alarm courant
    model.samPresent({do: 'addAlarm', time: [addDate.getHours(), addDate.getMinutes(), 0]});
  },    // button "Ajouter une alarme"

  changeAlarmHoursMinutes(data) { 
    model.samPresent({do: data.hour == undefined ? 'changeMinute' : 'changeHour', value: data.hour || data.minute, index: data.index});
  },  // sélection de l'heure et des minutes

  changeAlarmDescription(data) { 
    model.samPresent({do: 'changeMessageAlarm', msg: data.e.target.value, index: data.index});
  },   // saisie d'une description

  removeAlarm(data) { 
    model.samPresent({do: 'removeAlarm', index:data.index});
  },   // button "Enlever cette alarme"

  setAlarm(data) { 
    model.samPresent({do: 'setAlarm', index:data.index});
  },      // checkbox pour enclencher une alarme

  fireAlarm(data) {
    console.log(data);
    model.samPresent({do: 'fireAlarm', value:data.data,index:data.index});
  }      // lancée par le setTimeout() de l'alarme

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
      case 'changeHour':
        this.alarms.values[data.index].time[0] = data.value;
        this.alarms.hasChanged = true;
        break;
      case 'changeMinute':
        this.alarms.values[data.index].time[1] = data.value;
        this.alarms.hasChanged = true;
        break;
      case 'changeMessageAlarm':
        this.alarms.values[data.index].message = data.msg;
        this.alarms.hasChanged = true;
        break;
      case 'removeAlarm':
        window.clearTimeout(this.alarms.values[data.index].timeoutId);
        this.alarms.values[data.index].timeoutId = null;
        this.alarms.hasChanged = true;
        break;
      case 'setAlarm':
        //Calculate actual delay
        const currentDate = new Date();
        const alarmDate = new Date();
        alarmDate.setHours(this.alarms.values[data.index].time[0], this.alarms.values[data.index].time[1],this.alarms.values[data.index].time[3], 0);
        console.log(alarmDate);
        const delay = alarmDate-currentDate;
        const timeoutId = window.setTimeout(() => {actions.fireAlarm({data: this.alarms.values[data.index], index: data.index})}, delay);
        this.alarms.values[data.index].timeoutId = timeoutId;
        this.alarms.hasChanged = true;
        break;
      case 'fireAlarm':
        alert(`Alarme !\nIl est: ${data.value.time[0]}:${data.value.time[1]}.\nmessage: ${data.value.message}`);
        window.clearInterval(data.value.timeoutId);
        this.alarms.values[data.index].timeoutId = null;
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
      console.log(model.alarms.values);
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
    let h = [...Array(24).keys()];
    let m = [...Array(60).keys()]; 
    const t_alarmes = model.alarms.values.map((alarm, index) => `
      <div class="alarme">   
        <input type="checkbox" ${alarm.timeoutId !== null ? `onchange="actions.removeAlarm({index:${index}})" checked=""`: `onchange="actions.setAlarm({index:${index}})"`}/>
        <select ${alarm.timeoutId !== null ? `disabled=""` : ''}>
          ${h.map(v => `<option value="${v}" onclick="actions.changeAlarmHoursMinutes({index: ${index}, hour:${v}})" ${v == alarm.time[0] ? "selected=\"selected\"":''}>${v}</option>`).join('')}
        </select>
        <select ${alarm.timeoutId !== null ? `disabled=""` : ''}>
          ${m.map(v => `<option value="${v}" onclick="actions.changeAlarmHoursMinutes({index: ${index}, minute:${v}})" ${v == alarm.time[1] ? "selected=\"selected\"":''}>${v}</option>`).join('')}
        </select>
        <input type="text" placeholder="Description de l'alarme" onchange="actions.changeAlarmDescription({e:event, index:${index}})" value="${alarm.message}" ${alarm.timeoutId !== null ? `disabled=""` : ''}/>
        <button class="enlever" ${alarm.timeoutId !== null ? `onclick="actions.removeAlarm({index:${index}})"`: ''}>Enlever cette alarme</button>
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
