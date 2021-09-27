//Filter with regions and map

// Lance l'exécution quand tout est chargé
window.addEventListener('load', go);

// SAM Design Pattern
let actions, model, state, view;

// Point d'entrée de l'application
function go() {
  console.log('GO !');

  model.init({departments: départements, mode: 'asList_for'});
  state.samRender(model);
}

//------------------------------------------------------------------ Actions ---
// Actions lancées par des événements
//
actions = {

  changeMode: function(data) {
    let selectedMode = data.e.target.value;
    model.samPresent({mode: selectedMode});
  },

  filter: function(data) {
    let filterValue = data.e.target.value;
    model.samPresent({filter: filterValue});
  },

  filterRegions: function(data) {
    let checkValue = data.e.target.checked;
    model.samPresent({filterRegions: checkValue});
  }
};
//-------------------------------------------------------------------- Model ---
// Unique source de vérité de l'application
//
model = {
  departments: [], // tableau contenant données sur les départements
  mode: '',        // mode de rendu 'asList_for', 'asList_map', 'asTable_for'...
  depFilter: '',   // filtre à appliquer aux données sur les départements
  filterRegions: false,  // inclure les régions dans le filtrage

  init: function(data) {
    this.departments = data.departments;
    this.mode = data.mode;
  },

  samPresent: function(data) {
    const has = Object.prototype.hasOwnProperty;   // test si la propriété
                                                   // d'un objet est présente
    if (has.call(data, 'mode')) {
      this.mode = data.mode;
    }

    if (has.call(data, 'filter')) {
      this.depFilter = data.filter;
    }

    if (has.call(data, 'filterRegions')) {
      this.filterRegions = data.filterRegions;
    }
    state.samRender(this);
  }
};
//-------------------------------------------------------------------- State ---
// État de l'application avant affichage
//
state = {
  currentFilter: undefined,         // le filtre courant appliqué à departments
  currentFilterRegions: undefined,  // inclure ou pas le filtrage des régions
  depFiltered: [],                  // version filtrée de departments

  samRender: function(model) {
    this.samRepresentAndDisplay(model);
    // this.samNap(model);
  },

  samRepresentAndDisplay: function(model) {
    let representation = 'Oops, should not see this...';

    if ( this.currentFilter !== model.depFilter
      || this.currentFilterRegions !== model.filterRegions) {
      this.currentFilter = model.depFilter;
      this.currentFilterRegions = model.filterRegions;
      // TODO: Choisir ci-dessous la fonction de filtrage
      this.depFiltered = this.filterDepartments_for(model.departments);
      // this.depFiltered = this.filterDepartments_map(model.departments);
    }

    representation = view.occurences(model, this);

    switch (model.mode) {
      case "asList_for":
        representation += view.asList_for(model, this);
        break;
      case "asList_map":
        representation += view.asList_map(model, this);
        break;
      case "asTable_for":
        representation += view.asTable_for(model, this);
        break;
      case "asTable_map":
        representation += view.asTable_map(model, this);
        break;
      default:
        representation += view.error(model.mode);
    }
    view.samDisplay(representation);
  },

  // Filtrage des départements

  // version avec boucle for
  filterDepartments_for: function(depArray) {
    if (this.currentFilter == '') return depArray;
    let filtered = [];     
    for(let i = 0; i < depArray.length; i++){
      if(depArray[i][0].toUpperCase().includes(this.currentFilter.toUpperCase())){
        filtered.push(depArray[i]);
      }

    }
    return filtered;
  },
};
//--------------------------------------------------------------------- View ---
// Génération du HTML et affichage
//
view = {

  samDisplay: function(representation) {
    const app = document.getElementById('app');
    app.innerHTML = representation;
  },

  occurences: function(model, state) {
    let nbOcc = state.depFiltered.length;  // TODO: Quel est le nombre d'éléments dans le tableau filtré ?
    return `
        <p>${nbOcc} occurence</p>
    `;
  },

  asList_for: function(model, state) {
    let items = '';
    let a = state.depFiltered;
    for (let i = 0; i < a.length; i++) {
      const dep = a[i][0];
      const reg = a[i][2];
      items += `<li><b>${dep}</b> (${reg})</li>`
    }

    return `
        <ul>
          ${items}
        </ul>
      `;
  },

  asList_map: function(model, state) {
    return `
        <ul>
          ${state.depFiltered.map((v) => `<li><b>${v[0]}</b> (${v[2]})</li>`).join('')}
        </ul>
      `;
  },

  asTable_for: function(model, state) {
    // TODO: générez un tableau HTML avec les éléments filtrés
    let deps = state.depFiltered;
    let items = '';
    items += `
      <tr>
        <td><b>N°</b></td>
        <td><b>Départements</b></td>
        <td><b>Régions</b></td>
      </tr>
    `;
    for(let i = 0; i < deps.length; i++){
      items += `
        <tr>
          <td>${deps[i][1]}</td>
          <td><b>${deps[i][0]}</b></td>
          <td>${deps[i][2]}</td>
        </tr>
      `;
    }

    return `
      <table border="1">${items}</table>
    `;
  },

  asTable_map: function(model, state) {
    // TODO: générez un tableau HTML avec les éléments filtrés
    return `
      <table border="1">
        <tr>
          <td><b>N°</b></td>
          <td><b>Départements</b></td>
          <td><b>Régions</b></td>
        </tr>
        ${state.depFiltered.map((v) => `
          <tr>
            <td>${v[1]}</td>
            <td><b>${v[0]}</b></td>
            <td>${v[2]}</td>
          </tr>
        `).join(``)}
      </table>
    `;
  },

  error: function(caseValue) {
    return `
      <p>Problème : <b>state.representation(model)</b> : que faire avec "${caseValue}" ?</p>
    `;
  }
};
