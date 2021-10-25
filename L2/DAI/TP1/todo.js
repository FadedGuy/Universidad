"use strict";  // le mode strict impose une version plus exigente de Javascript

// Demande le lancement de l'exécution quand toute la page Web sera chargée
window.addEventListener('load', go);

// SAM Design Pattern : http://sam.js.org/
let actions, model, state, view;

// Point d'entrée de l'application
function go() {
  console.log('GO !');

  // liste de tâches initiales
  const initialTodos = [{ text: `À faire hier`       , done: true  },
                        { text: `À faire aujourd'hui`, done: false },
                        { text: `À faire demain`     , done: false }];

  // Initialise le modèle avec une liste de tâches
  actions.initAndGo({ items: initialTodos });
}

//------------------------------------------------------------------ Actions ---
// Actions appelées dans le code HTML quand des événements surviennent
//
actions = {

  initAndGo(data) {
    model.samPresent({do: 'init', items: data.items})
  },

  // Demande au modèle d'ajouter un item à son tableau de tâches à faire.
  // Lui envoit pour cela un objet avec une propriété 'inputField' qui
  // désigne l'id de l'élément qui contient le texte à ajouter.
  addItem(data) {
    const item = document.getElementById(data.inputField).value;
    if (item == '') return; // ne rien faire si l'item est vide
    model.samPresent({do: 'addItem', item: item});
  },

  doneItem(data){
      model.samPresent({do: 'doneItem', index: data.index});
  },

  removeDoneItems(){
    model.samPresent({do: 'removeDoneItems'});
  },

  toggleEditMode(){
    model.samPresent({do:'toggleEditMode'});
  },

  editItem(data){
    const text = data.e.target.value;
    model.samPresent({do: 'editItem', text: text, index: data.index});
  }
  //TODO: Ajouter les autres actions ici
};
//-------------------------------------------------------------------- Model ---
// Unique source de vérité de l'application
//
model = {
  items: [],
  isEditMode: false,

  // Demande au modèle de se mettre à jour en fonction des données qu'on
  // lui présente.
  // l'argument data est un objet confectionné dans les actions.
  // Les propriétés de data désignent la modification à faire sur le modèle.
  samPresent(data) {
    switch (data.do) {
      case 'init': 
        this.items = data.items || []; // Astuce : si data.items est undefined, renvoie []
        break;
      case 'addItem':
        this.items.push({text:data.item, done:false});
        break;
      case 'doneItem':
        this.items[data.index].done = !this.items[data.index].done;
        break;
      case 'removeDoneItems':
        this.items = this.items.filter(v => !v.done);
        break;
      case 'toggleEditMode':
        this.isEditMode = !this.isEditMode;
        break;
      case 'editItem':
        this.items[data.index].text = data.text;
        break;
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
  hasDoneItems: true,

  samUpdate(model) {
    this.hasDoneItems = (model.items.find(v => v.done) == undefined ? false : true)
    this.samRepresent(model);
    // this.samNap(model);
  },

  // Met à jour l'état de l'application, construit le code HTML correspondant,
  // et demande son affichage.
  samRepresent(model) {
    let representation = 'Oops, should not see this...';

    representation = view.todoUI(model, this);

    // Appel l'affichage du HTML généré.
    view.samDisplay(representation);
  }
};
//--------------------------------------------------------------------- View ---
// Génération de portions en HTML et affichage
//
view = {

  // Injecte le HTML dans une balise de la page Web.
  samDisplay(representation) {
    const app = document.getElementById('app');
    app.innerHTML = representation;
  },

  // Renvoit le HTML
  todoUI(model, state) {

    //TODO: compléter l'interface afin qu'elle affiche les tâches et qu'on puisse les gérer

    const li_items = model.isEditMode ? this.editItemsUI(model, state) : this.listItemsUI(model,state);

    return `
      <h2> Todo List </h2>
      <input id="inputText" type="text" />
      <button onclick="actions.addItem( {e: event, inputField:'inputText'} )">Todo</button>
      <ul>
      	${li_items}
      </ul>
      <button onclick="actions.removeDoneItems()" ${!state.hasDoneItems? `disabled="disabled"` : ''}>Remove done items</button>
      <button onclick="actions.toggleEditMode()" ${model.items.length > 0 ? '' : `disabled="disabled"`}>${model.isEditMode ? "Todo Mode" : "Edit Mode"}</button>
      `;
  },

  listItemsUI(model, state) {
    const li_items = `${model.items.map((v, index) => 
                      `<li onclick="actions.doneItem({index:${index}})" ${v.done ? `class="done"` : ''}> 
                        ${v.text} 
                      </li>`)
                      .join('')}`; // TODO: remplir avec les éléments de model.items
    return li_items;
  },

  editItemsUI(model, state){
    const li_items = `${model.items.map((v, index) => `<li><input value="${v.text}" 
                                                      onchange="actions.editItem({e:event, index:${index}})"/>
                                                      </li>`).join('')}`
    return li_items;
  },

};
