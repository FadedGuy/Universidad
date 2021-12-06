/* 
Fait
  Change auteurs
  Images toggle
  List <-> Grid view
*/

'use strict';

window.addEventListener('load',go);

// SAM Design Pattern : http://sam.js.org/
let samActions, samModel, samState, samView;

function go() {
  console.info('Go!');
  
  samActions.exec({do:'init', artiPart1:artiPart1Data, artiPart2:artiPart2Data});
  
  // pour un nombre de lignes pleines d'articles quelque soit la largeur du navigateur
  window.addEventListener('resize', () => {samActions.exec({do:'updatePagination'})});
}

//----------------------------------------------------------------- Actions ---
// Actions appelées dans le code HTML quand des événements surviennent
//

samActions = {
  
  exec(data) {
    let enableAnimation = true; // pour les animations sur l'interface graphique
    let proposal;
    switch (data.do) {
      case 'init': {
        console.log('samActions.init');
        proposal = {do:data.do, artiPart1:data.artiPart1, artiPart2:data.artiPart2};
        enableAnimation = false;
      } break; 
      // Display 
      case 'filters':
        proposal = {do: 'filterUpdate', newFilter: data.e.target.value};
        break;
      case 'changeFilter':
        proposal = {do: data.do, filterName:data.filterName, name:data.name};
        break;
      case 'viewCartToggle'    :
      case 'gridListView'      : 
        proposal = {do: data.do, view: data.view};
        break;
      case 'imagesToggle'      : 
        proposal = {do: data.do};
        break;
        // Pagination
        // TODO
        // Cart
        // TODO
      case 'globalSearch': 
        proposal = {do: data.do, checked: data.check.checked};
        break;
      case 'deleteToggle':
        proposal = {do: data.do, id: data.id};
        break;
      case 'animationsToggle'  : proposal = {do: data.do}; break;
      case 'addCart' : 
        proposal = {do: data.do, id: data.id};
        break;
      case 'cartDelete':
        proposal = {do: data.do};
        break;
      case 'editQt':
        proposal = {do: data.do, id: data.id, qt: data.e.target.value};
        break;
      case 'sortCart':
        proposal = {do: data.do, property: data.property};
        break;
      // Articles
      // TODO
      case 'darkThemeToggle'   : 
        proposal = {do: data.do};
        break;
      case 'updatePagination'  : break;
      
      
      default : 
        console.error('samActions - Action non prise en compte : ', data);
        return;
    }

    // console.log(enableAnimation && samModel.model.settings.animations);
    if (samModel.model.settings.animations){ 
      setTimeout(()=>samModel.samPresent(proposal), 200);}
    else             samModel.samPresent(proposal);
  },

};
//-------------------------------------------------------------------- Model ---
// Unique source de vérité de l'application
//

const initialModel= {
  authors  : ['Baptiste GENTHON', 'Kevin ACEVES SIORDIA'],
  
  artiPart1: [],
  artiPart2: [],
  articles : {
    values : [],
    hasChanged : true,
  },
  categories: [],
  origins   : [],
  
  filters: {
    categories:{
      booleans: {}, // filtre actif ou non pour chaque catégorie
      count   : {}, // nombre d'articles de chaque catégorie
    },
    origins:{
      booleans: {},
      count   : {},
    },
    search : {
      global: false, // recherche sur tous les articles ou seulement les articles filtrés
      text  : 'a',   // texte recherché
    },
  },
  settings : {
    articleImages: true,
    animations   : true,
    darkTheme    : false,
  },
  display : {
    cartView     : true,   // panier visible ou non
    articlesView : 'grid', // affichage en 'grid' ou 'list'
  },
  pagination: {
    grid: {
      currentPage : 1,
      linesPerPage: 1,
      linesPerPageOptions: [1,2,3],
    },
    list: {
      currentPage : 1,
      linesPerPage: 6,
      linesPerPageOptions : [3,6,9],
    },
  },
  
  cartSort : {
    property  : 'name',   // tri du panier selon cette propriété
    ascending : {         // ordre du tri pour chaque propriété
      name    : true,
      quantity: true,
      total   : true,
    },  
    hasChanged: true,
  },  
};

samModel = {

  model: initialModel,

  // Demande au modèle de se mettre à jour en fonction des données qu'on
  // lui présente.
  // l'argument data est un objet confectionné dans les actions.
  // Les propriétés de data désignent la modification à faire sur le modèle.
  samPresent(data) {
    switch (data.do) {
      case 'init': {
        console.log('samModel.init');
        // this.model.artiPart1 = data.artiPart1;
        // this.model.artiPart2 = data.artiPart2;
        this.modelAssign('artiPart1', data.artiPart1);
        this.modelAssign('artiPart2', data.artiPart2);
        this.createArticles();
        this.extractCategories();
        this.extractOrigins();
      } break;
      
      case 'viewCartToggle'    : this.modelToggle('display.cartView');       break;
      case 'imagesToggle'      : this.modelToggle('settings.articleImages'); break;
      case 'animationsToggle'  : this.modelToggle('settings.animations'   ); break;
      case 'darkThemeToggle'   : this.modelToggle('settings.darkTheme'    ); break;      
      case 'gridListView'      : this.modelAssign('display.articlesView', data.view); break;   
      case 'filterUpdate'      : this.model.filters.search.text = data.newFilter; this.model.articles.hasChanged = true; break;
      case 'changeFilter'      : if(data.name != "toutes") {
        this.modelToggle(`filters.${data.filterName}.booleans.${data.name}`);
      } else {
        let objChange = this.model.filters[data.filterName].booleans;
        for(let i = 0; i < Object.keys(objChange).length; i++) {
          this.modelAssign(`filters.${data.filterName}.booleans.${Object.keys(objChange)[i]}`, !this.model.filters[data.filterName].toutes);
        }
      }
      this.model.articles.hasChanged = true;
      break;
      case 'deleteToggle'      : 
        this.model.articles.values.find(art => art.id == data.id).deleteToggle = !this.model.articles.values.find(art => art.id == data.id).deleteToggle;
        this.model.articles.hasChanged = true;
        break;
      case 'cartDelete'        :
        this.model.articles.values.map(art => {if(art.deleteToggle){art.inCart = false; art.deleteToggle = false;}});
        this.model.articles.hasChanged = true;
        break;
      case 'globalSearch'      : this.model.filters.search.global = data.checked; break;
      case 'addCart'           : this.model.articles.values.find(art => art.id == data.id).inCart = true; this.model.articles.hasChanged = true; break;
      case 'editQt'            : this.model.articles.values.find(art => art.id == data.id).quantity = data.qt; this.model.articles.hasChanged = true; 
                                 if(data.qt == 0){this.model.articles.values.find(art => art.id == data.id).inCart = false} break; //Delete article from cart if qt is 0
      case 'updatePagination'  : break;
      case 'sortCart'          : this.model.cartSort.property = data.property; this.modelToggle(`cartSort.ascending.${data.property}`);this.model.cartSort.hasChanged = true; break;   
      // TODO
      
      default : 
        console.error('samPresent() - proposition non prise en compte : ', data); 
        return;
    }

    // Demande à l'état de l'application de prendre en compte la modification
    // du modèle
    samState.samUpdate(this.model);
    
    this.model.articles.hasChanged = false;
    this.model.cartSort.hasChanged = false;
  },
  
  /**
   * Cadeau : Affecte value à la propriété propertyStr
   * 
   * modelToggle('display.cartView'); 
   * est équivalent à :
   * this.model.display.cartView = !this.model.display.cartView;
   * 
   * Intérêt : plus compact et un message d'erreur est envoyé si le nom de la proprité est incorrecte
   * ou si les types sont différents.
   *
   * @param {string} propertyStr 
   * @param {any}    value 
   */
   modelToggle(propertyStr) {
    const root = 'model';
    const path = propertyStr.split('.');
    let val = this[root];
    let pathNames = ['this',root];
    path.some((v, i, a) => {
      pathNames.push(v);
      if (val[v]===undefined) {
        console.error(`modelToggle(${propertyStr}) : ${pathNames.join('.')} is undefined`);
        return true;
      }
      if (i < a.length - 1) { 
        val = val[v]; 
      } else {
        if (typeof val[v] != undefined && typeof val[v] != 'boolean') {
          console.error(`modelToggle(${propertyStr}) : ${pathNames.join('.')} is not a boolean`);
          return true;
        };
        val[v] = !val[v];
      }
    });
  },
  /**
   * Cadeau : Transforme une propriété booléenne en son opposée (true -> false, false -> true)
   * 
   * this.modelAssign('artiPart1', data.artiPart1);
   * est équivalent à :
   * this.model.artiPart1 = data.artiPart1;
   *
   * Intérêt : un message d'erreur est envoyé si le nom de la proprité est incorrecte
   * ou si elle n'est pas de type booléen.
   *
   * @param {string} propertyStr 
   */
   modelAssign(propertyStr, value) {
    const root = 'model';
    const path = propertyStr.split('.');
    let val = this[root];
    let pathNames = ['this',root];
    path.some((v, i, a) => {
      pathNames.push(v);
      if (val[v]===undefined) {
        console.error(`modelToggle(${propertyStr}) : ${pathNames.join('.')} is undefined`);
        return true;
      }
      if (i < a.length - 1) { 
        val = val[v]; 
      } else {
        if (typeof val[v] != undefined && typeof val[v] !== typeof value) {
          console.error(`modelToggle(${propertyStr}) : ${pathNames.join('.')} (${typeof val[v]}) is not of the same type of ${value} (${typeof value})`);
          return true;
        };
        val[v] = value;
      }
    });
  },
  
  /**
   * fonction à passer en paramètre à Array.sort() pour trier un tableau d'objets
   * selon leur nom, et leur prix s'ils ont le même nom.
   *
   * @param {Object} a 
   * @param {Object} b 
   * @returns -1 or 0 or 1
   */
  articlesSort(a,b) {
    if (a.name <b.name ) return -1;
    if (a.name >b.name ) return  1;
    if (a.price<b.price) return -1;
    if (a.price>b.price) return  1;
    return 0;  
    
  },
  
  /**
   * Création des articles à partir des deux fichiers de données (ArtiPart1 et ArtiPart2).
   *
   * Ce sont ces articles que l'interface graphique va représenter. 
   */
  createArticles() {
    const artiPart1 = this.model.artiPart1;
    const artiPart2 = this.model.artiPart2;
    
    let articleId = 0;
    
    const articles = artiPart1.map((a1)=>{
      
      const articlesTmp = artiPart2.filter((a) => a.id == a1.id).map((a2)=>{
        
        const article = {
          id      : articleId,  // création d'un identifiant unique pour chaque article
          // from artiPart2
          name    : a2.name,
          category: a2.category,
          pictures: a2.pictures,
          // from artiPart1
          origin  : a1.origin,
          price   : a1.price,
          unit    : a1.unit,
          quantity: a1.quantity,
          inCart  : a1.inCart,
          deleteToggle : false,
        };
        articleId++;
        
        return article; 
      });
      return articlesTmp[0];
    });
    this.model.articles.values = articles.sort(this.articlesSort);  // articles triés
    this.model.articles.hasChanged = true;
  },
  
  /**
   * Pour un tri par ordre alphabétique
   * 
   */
  alphaSort(a,b) {
      if(a<b) return -1;
      if(a>b) return 1;

    return 0;  
  },
  
  /**
   * Extraction :
   * - des catégories présentes dans la liste d'articles    --> model.categories
   * - du nombre d'articles appartenant à chaque catégories --> model.filters.categories.count
   *      model.filters.categories.count['fruits'] === 5
   * - du tableau de booléens pour l'état du filtre sur les catégories --> model.filters.categories.booleans
   *      model.filters.categories.booleans['fruits'] === true
   *
   * Les catégories sont triées par ordre alphabétique
   */

  /* 
  categories -> array of every categories of articles
  catsCount -> array with category keys that gives how many articles have this category
  orFilter -> array with category keys that returns true if there is at least 1 article with the category
  */
  
  extractCategories() {
    const articles   = this.model.articles.values;
    let categories   = [];
    let catsCount  = {
      'fruits': 0,
      'legumes': 0,
    };
    let catsFilter = {
        'fruits': false,
        'legumes': false,
    };
    
    categories = articles.map(value => value.category);
    categories = [...new Set(categories)];    
    categories.sort(this.alphaSort);

    for(let i = 0; i < articles.length; i++) {
        if(articles[i].category == "fruits") {
            catsCount.fruits++;
            catsFilter.fruits = true;
        } else {
            catsCount.legumes++;
            catsFilter.legumes = true;
        }
    }

    this.model.categories = categories;
    this.model.filters.categories.count  = catsCount;
    this.model.filters.categories.booleans = catsFilter;
  },
  
  /* 
  origins -> array of every origin of articles
  orCount -> array with country keys that gives how many articles have this origin
  orFilter -> array with country keys that returns true if there is at least 1 article with the country origin
  */
  extractOrigins() {
    const articles   = this.model.articles.values;
    let origins   = [];
    let orCount  = {
        'Pérou': 0,
        'France': 0,
        'Espagne': 0,
        'Maroc': 0,
    };
    const orFilter = {
        'Pérou': false,
        'France': false,
        'Espagne': false,
        'Maroc': false,
    };
    
    origins = articles.map(value => value.origin);
    origins = [...new Set(origins)];
    origins.sort(this.alphaSort);

    for(let i = 0; i < articles.length; i++) {
        if(articles[i].origin == "Pérou") {
            orCount.Pérou++;
            orFilter.Pérou = true;
        } else if(articles[i].origin == "France") {
            orCount.France++;
            orFilter.France = true;
        } else if(articles[i].origin == "Espagne") {
            orCount.Espagne++;
            orFilter.Espagne = true;
        } else {
            orCount.Maroc++;
            orFilter.Maroc = true;
        }
    }

    this.model.origins = origins;
    this.model.filters.origins.count  = orCount;
    this.model.filters.origins.booleans = orFilter;
  },
};
//-------------------------------------------------------------------- State ---
// État de l'application avant affichage
//

const initialState = {

  filteredArticles : {    // articles filtrés
    values        : [],
    hasChanged    : true,
    representation: '',   // représentation pour ne pas avoir à la recalculer si n'a pas changé
  },
  
  filters : {
    categories : {
        booleans      : {},  // avec une propriété 'toutes' en plus qui vaut true si toutes les autres sont 'true'
        hasChanged    : true,
        representation: '',
    },
    origins : {
        booleans      : {},  // avec une propriété 'toutes' aussi
        hasChanged    : true,
        representation: '',
    },
    search : {
      global        : false,
      text          : '',
      hasChanged    : true,
      representation: '',
    },
  },
  display : {
    cartView: {
      value     : true,
      hasChanged: true,
      },
    articlesView : {
      value     : '',
      hasChanged: true,
      },
  },
  pagination: {  // Toutes ces valeurs sont calculées dans updatePagination()
    grid: {
      currentPage        : undefined,
      linesPerPage       : undefined,
      linesPerPageOptions: undefined,
      
      maxArticlesPerLine: undefined,
      numberOfPages     : undefined,
      hasPrevPage       : undefined,
      hasNextPage       : undefined,
    },
    list: {
      currentPage        : undefined,
      linesPerPage       : undefined,
      linesPerPageOptions: undefined,
      
      maxArticlesPerLine: undefined,
      numberOfPages     : undefined,
      hasPrevPage       : undefined,
      hasNextPage       : undefined,
    },
  },

  cart : {
    values: [],    // le panier rassemble tous les articles dont inCart==true
    total : 0,     // valeur totale du panier
    hasChanged: true,
    representation: '',
  },
  cartSort : {     // pour le tri des articles du panier
    property  : 'name',
    ascending : {
      name    : true,
      quantity: true,
      total   : true,
    },  
    hasChanged: true,
  },

};

samState = {

  state: initialState,

  samUpdate(model) {
    if(this.state.filters != model.filters){this.state.filters.categories.hasChanged = true; this.state.filters.origins.hasChanged = true;}
    this.state.filters.categories = this.updateFilter    (model.filters.categories, this.state.filters.categories);
    this.state.filters.origins = this.updateFilter    (model.filters.origins,    this.state.filters.origins);
    this.updateSearch    (model.filters.search);
    this.state.filters = this.filterArticles  (model.articles, this.state.filters);
    this.updateDisplay   (model.display);
    this.updatePagination(model.pagination);
    this.updateCartSort  (model.cartSort);
    this.updateCart      (model);
    
    this.samRepresent(model);
    
    // Nothing more to change
    this.state.filteredArticles.hasChanged     = false;
    this.state.filters.categories.hasChanged   = false;
    this.state.filters.origins.hasChanged      = false;
    this.state.filters.search.hasChanged       = false;
    this.state.display.cartView.hasChanged     = false;
    this.state.display.articlesView.hasChanged = false;
    this.state.cartSort.hasChanged             = false;
    this.state.cart.hasChanged                 = false;
  },
  
  /**
   * recopie les filtres du model dans le state
   * ajoute la propriété 'toutes' au tableau booleans
   */
  updateFilter(modelFilter, stateFilter) {
  
    console.log('updateFilter')
    
    let isEveryElementTrue = true;
    stateFilter = modelFilter;
    
    if(stateFilter.booleans.Espagne == false ||
      stateFilter.booleans.France == false || 
      stateFilter.booleans.Maroc == false ||
      stateFilter.booleans.Pérou == false) 
    {
      isEveryElementTrue = false;
    }

    if(stateFilter.booleans.fruits == false ||
      stateFilter.booleans.legumes == false)
      {
        isEveryElementTrue = false;
      }

    stateFilter.toutes = isEveryElementTrue;
    stateFilter.hasChanged = true;
    return stateFilter;
  },
  
  updateSearch(modelSearch) {
    const stateSearch = this.state.filters.search;
    const globalHasChanged = modelSearch.global != stateSearch.global;
    const textHasChanged   = modelSearch.text   != stateSearch.text;
    stateSearch.hasChanged = globalHasChanged || textHasChanged;
    stateSearch.global     = modelSearch.global;
    stateSearch.text       = modelSearch.text;
  },

  /*
  Works now, it filters articles correctly even if there is no search
  */
 
  filterArticles(articles, filters) {
    // filters.categories.booleans['légumes']=false;
    // filters.origins.booleans['France']=true;
    if (articles.hasChanged         || 
        filters.categories.hasChanged || 
        filters.origins.hasChanged    ||
        filters.search.hasChanged     ) {
              
      let filteredValues = [];  // TODO 
      let curFilter = filters.search.text.toUpperCase();
      
      if(curFilter.trim() == ""){
        this.state.filteredArticles.values = articles.values;
        this.state.filteredArticles.hasChanged = true;
        return;
      } 
      
      for(let i = 0; i < articles.values.length; i++) {
        if(articles.values[i].name.toUpperCase().includes(curFilter))
        {
            filteredValues.push(articles.values[i]);
        }
      }
      
      /* 
        We need to set the values of articles that were filtered out as false;
      */

      if(!filters.categories.toutes)
      {
        let e = Object.entries(filters.categories.booleans);
        console.log(e);
        filteredValues = filteredValues.filter(art => {
          return e.some(arr => art.category == arr[0] && arr[1]);
        });
      }
      if(!filters.origins.toutes)
      {
        let e = Object.entries(filters.origins.booleans);
        console.log(e);
        filteredValues = filteredValues.filter(art => {
          return e.some(arr => art.origin == arr[0] && arr[1]);
        });
      }
      

      this.state.filteredArticles.values     = filteredValues;
      this.state.filteredArticles.hasChanged = true;
    }
    return this.state.filters;
  },

  updateDisplay(display) {
    const cartView = this.state.display.cartView;
    if (cartView.value != display.cartView) {
      cartView.value = display.cartView;
      cartView.hasChanged = true;
    }
    const articlesView = this.state.display.articlesView;
    if (articlesView.value != display.articlesView) {
      articlesView.value = display.articlesView;
      articlesView.hasChanged = true;
    }
    
  },

  updatePagination(pagination) {
    const statePagination = this.state.pagination;
    
    const articleGrid        = document.getElementById('articleWidth');
    const articleWidth       = articleGrid.clientWidth;
    const minCardWidth       = 200;
    const articlesView       = this.state.display.articlesView.value;
    const maxArticlesPerLine = (articlesView == 'grid') ? Math.floor(articleWidth/minCardWidth) : 1;
    const linesPerPage       = pagination[articlesView].linesPerPage;
    const numberOfArticles   = this.state.filteredArticles.values.length;
    const numberOfPages      = Math.ceil(numberOfArticles / (maxArticlesPerLine * linesPerPage));
    
    statePagination[articlesView].currentPage         = pagination[articlesView].currentPage;
    statePagination[articlesView].linesPerPage        = linesPerPage;
    statePagination[articlesView].linesPerPageOptions = pagination[articlesView].linesPerPageOptions;
    statePagination[articlesView].maxArticlesPerLine  = maxArticlesPerLine;
    statePagination[articlesView].numberOfPages       = numberOfPages;
    statePagination[articlesView].hasPrevPage         = pagination[articlesView].currentPage > 1;
    statePagination[articlesView].hasNextPage         = pagination[articlesView].currentPage < numberOfPages;
  
    this.state.display.articlesView.hasChanged = true;
  },

  updateCartSort(cartSort) {
    if (cartSort.hasChanged) {
      this.state.cartSort.property   = cartSort.property;
      this.state.cartSort.ascending  = cartSort.ascending;
      this.state.cartSort.hasChanged = true;
    }
  },

  /**
   * Remplit le panier avec tous les articles dont inCart == true
   * et calcule le prix total du panier
   */
  updateCart(model) {
    const articles = model.articles;
    if (articles.hasChanged) {
    
      this.state.cart.values = articles.values.filter(art => art.inCart == true)
      this.state.cart.total = 0; 
      this.state.cart.values.forEach(art => {
        this.state.cart.total += (art.price*art.quantity);
      });
      this.state.cart.hasChanged = true;
    }
  },  

  // Met à jour l'état de l'application, construit le code HTML correspondant,
  // et demande son affichage.
  samRepresent(model) {
    this.updateFilterUI(model, this.state, 'categories');
    this.updateFilterUI(model, this.state, 'origins');
    this.updateSearchUI(model, this.state);
    this.updateArticlesUI(model, this.state);
    this.updateCartUI(model, this.state);
    
    //Settings
    
    const representation = samView.mainUI(model, this.state);
    
    //Appel l'affichage du HTML généré.
    samView.samDisplay(representation);
  },

  updateFilterUI(model, state, filterName) {
    const filter = state.filters[filterName];
    if (filter.hasChanged) {
      filter.representation = samView.filterUI(model, state, filterName)
      filter.hasChanged = false;
    }
  },

  updateSearchUI(model, state) {
    const filter = state.filters.search;
    if (filter.hasChanged) {
      filter.representation = samView.searchUI(model, state);
      filter.hasChanged = false;
    }
  },

  updateArticlesUI(model, state) {
    const filteredArticles = state.filteredArticles;
    const articlesView     = state.display.articlesView;
    if (filteredArticles.hasChanged || articlesView.hasChanged) {
      filteredArticles.representation = articlesView.value == 'grid' ? samView.articlesGridUI(model, state) : samView.articlesListUI(model, state);
      if(filteredArticles.values.length == 0){
        filteredArticles.representation = samView.articlesEmptyUI(model, state);
      }
      filteredArticles.hasChanged = false;
      articlesView.hasChanged     = false;
    }
  },
  
  updateCartUI(model, state) {
    const cart     = state.cart;
    const cartView = state.display.cartView;
    const cartSort = state.cartSort;
    if (cart.hasChanged || cartView.hasChanged || cartSort.hasChanged) {
      cart.representation = samView.cartUI(model, state);      
      cart.hasChanged     = false;
      cartView.hasChanged = false;
      cartSort.hasChanged = false;
    }
  },

  updateThemeUI(model, state) {
    const settings = state.settings;
    if (settings.darkThemeHasChanged) {
      samView.darkThemeUI(state);
      settings.darkThemeHasChanged = false;
    }
  },

};
//--------------------------------------------------------------------- View ---
// Génération de portions en HTML et affichage
//
samView = {

  // Injecte le HTML dans une balise de la page Web.
  samDisplay: function (representation) {
    const app = document.getElementById('app');
    app.innerHTML = representation;
  },

  // Astuce : Pour avoir la coloration syntaxique du HTML avec l'extension lit-html dans VSCode
  // https://marketplace.visualstudio.com/items?itemName=bierner.lit-html
  // utiliser this.html`<h1>Hello World</h1>` en remplacement de `<h1>Hello World</h1>`
  html([str, ...strs], ...vals) {
    return strs.reduce((acc,v,i)=> acc+vals[i]+v, str);
  },
 
  mainUI(model,state) {
    
    this.darkThemeUI(model);
    
    const cartClass = model.display.cartView ? 'border' : '';
    
    return this.html`
    <div class="row small-margin">
    <!-- ___________________________________________________________ Entête -->
    <div class="row middle-align no-margin">
      <div class="col s8 m9 l10">
        <h4 class="center-align"> Commande de fruits et légumes</h4>
      </div>
      <div class="col s4 m3 l2">
        <nav class="right-align small-margin">
          <button onclick="samActions.exec({do:'viewCartToggle'})" class="no-marin ${cartClass}">
            <i class="large">shopping_basket</i>
          </button>
          <button class="no-margin" data-ui="#dropdown3_">
            <i class="large">account_circle</i>
            <div id="dropdown3_" data-ui="#dropdown3_" class="dropdown left no-wrap">
              <a>Auteurs : <b>${model.authors[0]}</b> et <b>${model.authors[1]}</b></a>
            </div>
          </button>
        </nav>
      </div>
    </div>
    <div class="row">
      <div class="col s3 m2 l2" style="position:sticky; top: 10px;">
        <!-- ______________________________________________________ Filtres -->
      
        <aside>
          <h5>Filtres</h5>
          <h6>Catégories</h6>          
          <div>
            ${state.filters.categories.representation}
          </div>
          <div class="small-space"></div>
          <h6>Origines</h6>
          <div>
            ${state.filters.origins.representation}
          </div>
          <div class="small-space"></div>
          <h6>Recherche</h6>
          ${state.filters.search.representation}
          <div class="small-space"></div>          
          <h5>Paramètres</h5>
          ${this.settingsUI(model,state)}
          
        </aside>
      </div>
      <div class=" col s9 m10 l10">
        <!-- ___________________________________ Récap filtres et recherche -->
        
        
        <div class="row top-align no-margin">
          <nav class="col s8 wrap no-margin">
            ${this.filtersSearchTagsUI(model,state)}
            <!-- ${state.filteredArticles.representation}   -->
          </nav>
          <nav class="col s4 right-align no-margin">
            ${this.articlesViewUI(model,state)}
          </nav>
        </div>
        
        <!-- _____________________________________________________ Articles -->
        
        ${state.filteredArticles.representation}  
      
        <!-- ___________________________________________________ Pagination -->
        ${this.paginationUI(model,state)}
        
        
      </div>
    </div>
  </div>
  <!-- ______________________________________________________________Panier -->
  ${state.cart.representation}
  `;
  },
  
  darkThemeUI(model) {
    const bodyclass = document.body.classList;
    if (model.settings.darkTheme) bodyclass.add   ('is-dark');
    else                          bodyclass.remove('is-dark');
  },
  
  filterUI(model, state, filterName) {
    console.log('filterUI', filterName);
    let variable = Object.entries(model.filters).find(el => el[0] == filterName)[1];
    let booleans = Object.entries(Object.entries(variable).find(el => el[0] == "booleans")[1]);
    let counts = Object.entries(Object.entries(variable).find(el => el[0] == "count")[1]);

    return this.html`   
    <div>
      <label class="checkbox">
        <input type="checkbox" onclick="samActions.exec({do: 'changeFilter', filterName:'${filterName}', name:'toutes'})" ${model.filters[filterName].toutes? `checked="checked"` : ''}/>
        <span class="capitalize">toutes</span>  
        <a><span class="badge circle right color-2-text color-2a">${model.articles.values.length}</span></a>
      </label>
    </div>

    ${booleans.map((fil, index) => `
      <div>
        <label class="checkbox">
          <input type="checkbox" onclick="samActions.exec({do: 'changeFilter', filterName:'${filterName}', name:'${fil[0]}'})" ${fil[1]? `checked="checked"` : ''}/>
          <span class="capitalize">${fil[0]}</span>  
          <a><span class="badge circle right color-2-text color-2a">${counts[index][1]}</span></a>
        </label>
      </div>
    `).join('')}
  `;
  },
  
  searchUI(model, state) {
    
    console.log('searchUI')
    

    return this.html`
      <div class="middle-align small-margin">
        <label class="switch">
          <input type="checkbox" onchange="samActions.exec({do:'globalSearch', check:this})" ${state.filters.search.global == true ? `checked="checked"` : ''} />
          <span>globale</span>
        </label>
      </div>
      <div class="field prefix round fill border small">
        <i>search</i>
        <input type="text" class="align-middle" onchange="samActions.exec({do:'filters', e: event})" value="${state.filters.search.text}" /> 
      </div>    
    `;
  },
  
  settingsUI(model,state) {
    const withImageChecked  = model.settings.articleImages ? 'checked="checked"' : '';
    const darkThemeChecked  = model.settings.darkTheme     ? 'checked="checked"' : '';
    const animationsChecked = model.settings.animations    ? 'checked="checked"' : '';
    
    return this.html`
      <div class="middle-align small-margin">
        <label class="switch">
          <input type="checkbox" onclick="samActions.exec({do:'imagesToggle'})" ${withImageChecked} />
          <span>Articles <br />avec images</span>
        </label>
      </div>
      <div class="middle-align small-margin">
        <label class="switch">
          <input type="checkbox" onclick="samActions.exec({do:'animationsToggle'})" ${animationsChecked} />
          <span>Animations</span>
        </label>
      </div>          
      <div class="middle-align small-margin">
        <label class="switch">
          <input type="checkbox" onclick="samActions.exec({do:'darkThemeToggle'})" ${darkThemeChecked} />
          <span>Thème <br /> sombre</span>
        </label>
      </div>          
          `;
  },
  
  filtersSearchTagsUI(model, state) {
  
    console.log('filtersSearchTagsUI');
  
    // TODO working, do we want map to be cleaner?
    // Delete recherche by clicking, unable to set to empty
    
    return this.html`           
      <label  class="medium-text color-2-text">${state.filteredArticles.values.length} articles -</label>

      ${!model.filters.categories.booleans.fruits? ``:`
      <span class="chip small no-margin capitalize " onclick="samActions.exec({do: 'changeFilter', filterName: 'categories', name: 'fruits'})">
        fruits<i class="small">close</i>
      </span>   `}

      ${!model.filters.categories.booleans.legumes? ``:`
      <span class="chip small no-margin capitalize " onclick="samActions.exec({do: 'changeFilter', filterName: 'categories', name: 'legumes'})">
        légumes<i class="small">close</i>
      </span>   `}
      
      ${!model.filters.origins.booleans.Espagne? ``:`
      <span class="chip small no-margin capitalize " onclick="samActions.exec({do: 'changeFilter', filterName: 'origins', name: 'Espagne'})">
      Espagne<i class="small">close</i>
      </span>   `}

      ${!model.filters.origins.booleans.France? ``:`
      <span class="chip small no-margin capitalize " onclick="samActions.exec({do: 'changeFilter', filterName: 'origins', name: 'France'})">
      France<i class="small">close</i>
      </span>   `}
      
      ${!model.filters.origins.booleans.Maroc? ``:`
      <span class="chip small no-margin capitalize " onclick="samActions.exec({do: 'changeFilter', filterName: 'origins', name: 'Maroc'})">
      Maroc<i class="small">close</i>
      </span>   `}

      ${!model.filters.origins.booleans.Pérou? ``:`
      <span class="chip small no-margin capitalize " onclick="samActions.exec({do: 'changeFilter', filterName: 'origins', name: 'Pérou'})">
      Pérou<i class="small">close</i>
      </span>   `}
      
      
      ${state.filters.search.text.trim() == "" ? '' : `
        <span class="chip small no-margin" onclick="samActions.exec({do: 'filters', e: {target: {value: 'a'}}})">
          Rech : "${state.filters.search.text}"<i class="small">close</i>
        </span> `}       
                   
    `;
  },
  
  articlesViewUI(model, state) {
    
    const gridOn = state.display.articlesView.value == 'grid';
    const gridViewClass    = gridOn ? 'disabled' : '';
    const gridViewDisabled = gridOn ? 'disabled="disabled"' : '';
    const listViewClass    = gridOn ? '' : 'disabled';
    const listViewDisabled = gridOn ? '' : 'disabled="disabled"';
    
    return this.html`
      <button onclick="samActions.exec({do:'gridListView', view:'list'})" class="small no-margin ${listViewClass}" ${listViewDisabled}>
        <i>view_list</i></button>
      <button onclick="samActions.exec({do:'gridListView', view:'grid'})" class="small           ${gridViewClass}" ${gridViewDisabled}>
        <i>grid_view</i></button>
    `;
  },
  
  inEuro(number) {
    const numString = (number + 0.0001) + '';
    const dotIndex  = numString.indexOf('.');
    return numString.substring(0, dotIndex+3)+' €';
  },
  
  articlesGridUI(model, state) {
    
    console.log('articlesGridUI');
    
    return this.html`
      <article class="small-margin grid-view">
        ${state.filteredArticles.values.map(art => `
          <div  class="card no-padding small-margin">        
            <div class="card-image center-align">
            ${model.settings.articleImages ? `<img src="./images/${art.pictures[0]}" />` : ''}
            </div>            
            <div class="small-padding">
              <h6 class="no-margin">${art.name}</h6>
              <div class="small-margin"><label>Origine : </label>${art.origin}</div>
              <div class="chip large">
                <label>Prix: </label><span class="large-text">${art.price.toFixed(2)} € / <span class="avoidwrap">${art.unit}</span> </span>
              </div>
              <div class="row no-margin">
                <div class="col s8 field round fill border center-align">
                  <input type="text" class="center-align ${art.inCart ? '' : 'color-1a'}" value="${art.quantity == 0 ? '' : `${art.quantity}`}" onchange="samActions.exec({do:'editQt', e:event, id: ${art.id}})"/>
                  <label>Quantité</label>
                </div>
                <div class=" col s4">
                  <button ${art.quantity == 0 ? `class="circle no-margin disabled" disabled="disabled" ` : `class="circle no-margin "`} onclick="samActions.exec({do: 'addCart', id: ${art.id}})" >
                    <i>${art.inCart ? 'edit' : 'add'}</i>
                  </button>
                </div>
              </div>
            </div>
          </div>
              `).join('')}
        
        
      </article>
    `;
  },
  
  articlesListUI(model, state) {
    
    console.log('articlesListUI');
      
    return this.html`
      <article class="large-margin list-view">
        ${state.filteredArticles.values.map(art => `
          <nav  class="row card divider no-wrap">            
            <div class="col min">
              ${model.settings.articleImages ? `<img src="./images/${art.pictures[0]}" />` : ''}
            </div>
            <div class="col">
              <h6>${art.name}</h6>
              <label>${art.origin}</label>
            </div>
            <div class="col min chip no-margin">
              <label>Prix : </label><span class="large-text">${art.price.toFixed(2)} € / ${art.unit}</span>
            </div>
            <div class="col min field round fill small border center-align no-margin">
              <label>Qté : </label>
              <input type="text" class="center-align ${art.inCart ? '' : 'color-1a'}" value="${art.quantity == 0 ? '' : `${art.quantity}`}" onchange="samActions.exec({do:'editQt', e:event, id: ${art.id}})"/>
              </div>
            <div class="col min no-margin"></div>
            <div class="col min">
              <button ${art.quantity == 0 ? `class="circle no-margin disabled" disabled="disabled" ` : `class="circle no-margin "`} onclick="samActions.exec({do: 'addCart', id: ${art.id}})" >
                <i>${art.inCart ? 'edit' : 'add'}</i>
              </button>
            </div>
          </nav>
        `).join('')}
  
      </article>
    `;
  },
  
  articlesEmptyUI(model,state) {
  
    return this.html`
      <div class="row">
        <div class="col s12 medium-padding fond">
          <img src="./images/fond.png" class="responsive" />
        </div>
      </div>
    `;
  },
  
  paginationUI(model, state) {
    
    console.log('paginationUI');
    
    // TODO
    
    return this.html`
      <nav class="center-align">
        <button class="square border disabled" disabled="disabled">
          <i>navigate_before</i>
        </button>     
        <button class="square no-margin border">1</button>      
        <button class="square no-margin ">2</button>      
        <button class="square no-margin ">3</button>      
        <button class="square ">
          <i>navigate_next</i>
        </button>
        <div class="field suffix small">
          <select>
            <option value="1" selected="selected">1 ligne par page</option>
            <option value="2">2 lignes par page</option>
            <option value="3">3 lignes par page</option>
          </select>
          <i>arrow_drop_down</i>
        </div>
      </nav>
    `;
  },
  
  cartUI(model, state) {

    console.log('cartUI')

    if (!model.display.cartView) return '';
    let articlesCart = state.cart.values;
    let sortParam = state.cartSort.property;
    if(sortParam == 'name'){
      articlesCart.sort((a, b) => {
        var aN = a.name.toUpperCase();
        var bN = b.name.toUpperCase();
        if(aN < bN) return state.cartSort.ascending.name ? -1 : 1;
        if(aN > bN) return state.cartSort.ascending.name ? 1 : -1;
        return 0;
      });
    }
    else{
      if(sortParam == 'quantity'){
        articlesCart.sort((a, b) => {
          return state.cartSort.ascending.quantity ? a.quantity - b.quantity : b.quantity - a.quantity;
        });
      }
      else{
        articlesCart.sort((a, b) => {
          return state.cartSort.ascending.total ? (a.price * a.quantity) - (b.price * b.quantity) : (b.price * b.quantity) - (a.price * a.quantity);
        });
      }
    }
    // Envoyer command

    
    return this.html`
      <div class="panier row small-margin">
    <div class="col s0 m1 l2"></div>
    <section class="col s12 m10 l8">
      <div class="card ">
        <h4>Panier</h4>
        <div>
          <table border="0" class="right-align large-text">
            <thead>
              <th class="center-align"><a onclick="samActions.exec({do: 'sortCart', property: 'name'})">
                Articles <i class="small">unfold_more</i></a></th>
              <th class="center-align"><a onclick="samActions.exec({do: 'sortCart', property: 'quantity'})">
                Qté<i class="small">unfold_more</i></a></th>
              <th class="center-align">Unit</th>
              <th class="center-align">P.U.</th>
              <th class="center-align"><a onclick="samActions.exec({do: 'sortCart', property: 'total'})">
                Prix<i class="small">unfold_more</i></a></th>
              <th>
              </th>
            </thead>

            ${state.cart.values.map((art, index) => `
              <tr class="${index % 2 == 0 ? `ligne-paire` : `ligne-impaire`}">
                <td class="left-align">${art.name}</td>
                <td class="quantite">
                  <div class="field fill small">
                    <input type="text" class="right-align" value="${art.quantity}" onchange="samActions.exec({do:'editQt', e:event, id: ${art.id}})"/>
                  </div>
                </td>
                <td class="left-align">${art.unit}</td>
                <td>${art.price.toFixed(2)} €</td>
                <td>${(art.price * art.quantity).toFixed(2)} €</td>
                <td class="center-align">
                  <label class="checkbox">
                    <input type="checkbox" onclick="samActions.exec({do: 'deleteToggle', id: '${art.id}'})" ${art.deleteToggle ? `checked="cheked"` : ''}/> 
                    <span></span>
                  </label>
                </td>
              </tr>
              `).join('')}
              
            <tfoot class="orange-light-3">
              <th colspan="4">Total :</th>
              <th>${state.cart.total.toFixed(2)} €</th>
              <th class="center-align">
                <button type="button" onclick="samActions.exec({do:'cartDelete'})" 
                  ${state.cart.total ? `class="small"` : `class="small disabled" disabled="disabled"`}><i>delete</i></button>
              </th>
            </tfoot>
          </table>
        </div>
        <div class="medium-margin right-align">
          <button onclick="envoyerCommande('${model.authors[0]} et ${model.authors[1]}', samState.state.cart.values, ${state.cart.total})" ${state.cart.total ? `` : `class="disabled" disabled="disabled"`}><i class="small-margin">send</i> Envoyer la commande</button>
        </div>
      </div>
    </section>
  </div>
    `;

  },
   
};

function envoyerCommande(client, articles, total) {
    
  console.log(articles);
  let email = 'commandes@fruits-legumes.com';
  let sujet = 'Commande de ' + client;
  let corps = `
  Commande de fruits et légumes
  Voici les articles commandés pour un montant de ${samView.inEuro(total)} :
    ${articles.map(art => `
      ${art.name} (${art.quantity} ${art.unit})
    `).join('')}
    `;
  email = encodeURIComponent(email);
  sujet = encodeURIComponent(sujet);
  corps = encodeURIComponent(corps);
  const uri = "mailto:" + email + "?subject=" + sujet + "&body=" + corps;
  window.open(uri);
}
