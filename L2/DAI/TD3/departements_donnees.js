const départements = [
  [
    'Ain', '1', 'Auvergne-Rhône-Alpes'
  ],
  [
    'Aisne', '2', 'Hauts-de-France'
  ],
  [
    'Allier', '3', 'Auvergne-Rhône-Alpes'
  ],
  [
    'Alpes-de-Haute-Provence', '4', 'Provence-Alpes-Côte d\'Azur'
  ],
  [
    'Hautes-Alpes', '5', 'Provence-Alpes-Côte d\'Azur'
  ],
  [
    'Alpes-Maritimes', '6', 'Provence-Alpes-Côte d\'Azur'
  ],
  [
    'Ardèche', '7', 'Auvergne-Rhône-Alpes'
  ],
  [
    'Ardennes', '8', 'Grand Est'
  ],
  [
    'Ariège', '9', 'Occitanie'
  ],
  [
    'Aube', '10', 'Grand Est'
  ],
  [
    'Aude', '11', 'Occitanie'
  ],
  [
    'Aveyron', '12', 'Occitanie'
  ],
  [
    'Bouches-du-Rhône', '13', 'Provence-Alpes-Côte d\'Azur'
  ],
  [
    'Calvados', '14', 'Normandie'
  ],
  [
    'Cantal', '15', 'Auvergne-Rhône-Alpes'
  ],
  [
    'Charente', '16', 'Nouvelle-Aquitaine'
  ],
  [
    'Charente-Maritime', '17', 'Nouvelle-Aquitaine'
  ],
  [
    'Cher', '18', 'Centre-Val de Loire'
  ],
  [
    'Corrèze', '19', 'Nouvelle-Aquitaine'
  ],
  [
    'Corse-du-Sud', '2A', 'Corse'
  ],
  [
    'Haute-Corse', '2B', 'Corse'
  ],
  [
    'Côte-d\'Or', '21', 'Bourgogne-Franche-Comté'
  ],
  [
    'Côtes-d\'Armor', '22', 'Bretagne'
  ],
  [
    'Creuse', '23', 'Nouvelle-Aquitaine'
  ],
  [
    'Dordogne', '24', 'Nouvelle-Aquitaine'
  ],
  [
    'Doubs', '25', 'Bourgogne-Franche-Comté'
  ],
  [
    'Drôme', '26', 'Auvergne-Rhône-Alpes'
  ],
  [
    'Eure', '27', 'Normandie'
  ],
  [
    'Eure-et-Loir', '28', 'Centre-Val de Loire'
  ],
  [
    'Finistère', '29', 'Bretagne'
  ],
  [
    'Gard', '30', 'Occitanie'
  ],
  [
    'Haute-Garonne', '31', 'Occitanie'
  ],
  [
    'Gers', '32', 'Occitanie'
  ],
  [
    'Gironde', '33', 'Nouvelle-Aquitaine'
  ],
  [
    'Hérault', '34', 'Occitanie'
  ],
  [
    'Ille-et-Vilaine', '35', 'Bretagne'
  ],
  [
    'Indre', '36', 'Centre-Val de Loire'
  ],
  [
    'Indre-et-Loire', '37', 'Centre-Val de Loire'
  ],
  [
    'Isère', '38', 'Auvergne-Rhône-Alpes'
  ],
  [
    'Jura', '39', 'Bourgogne-Franche-Comté'
  ],
  [
    'Landes', '40', 'Nouvelle-Aquitaine'
  ],
  [
    'Loir-et-Cher', '41', 'Centre-Val de Loire'
  ],
  [
    'Loire', '42', 'Auvergne-Rhône-Alpes'
  ],
  [
    'Haute-Loire', '43', 'Auvergne-Rhône-Alpes'
  ],
  [
    'Loire-Atlantique', '44', 'Pays de la Loire'
  ],
  [
    'Loiret', '45', 'Centre-Val de Loire'
  ],
  [
    'Lot', '46', 'Occitanie'
  ],
  [
    'Lot-et-Garonne', '47', 'Nouvelle-Aquitaine'
  ],
  [
    'Lozère', '48', 'Occitanie'
  ],
  [
    'Maine-et-Loire', '49', 'Pays de la Loire'
  ],
  [
    'Manche', '50', 'Normandie'
  ],
  [
    'Marne', '51', 'Grand Est'
  ],
  [
    'Haute-Marne', '52', 'Grand Est'
  ],
  [
    'Mayenne', '53', 'Pays de la Loire'
  ],
  [
    'Meurthe-et-Moselle', '54', 'Grand Est'
  ],
  [
    'Meuse', '55', 'Grand Est'
  ],
  [
    'Morbihan', '56', 'Bretagne'
  ],
  [
    'Moselle', '57', 'Grand Est'
  ],
  [
    'Nièvre', '58', 'Bourgogne-Franche-Comté'
  ],
  [
    'Nord', '59', 'Hauts-de-France'
  ],
  [
    'Oise', '60', 'Hauts-de-France'
  ],
  [
    'Orne', '61', 'Normandie'
  ],
  [
    'Pas-de-Calais', '62', 'Hauts-de-France'
  ],
  [
    'Puy-de-Dôme', '63', 'Auvergne-Rhône-Alpes'
  ],
  [
    'Pyrénées-Atlantiques', '64', 'Nouvelle-Aquitaine'
  ],
  [
    'Hautes-Pyrénées', '65', 'Occitanie'
  ],
  [
    'Pyrénées-Orientales', '66', 'Occitanie'
  ],
  [
    'Bas-Rhin', '67', 'Grand Est'
  ],
  [
    'Haut-Rhin', '68', 'Grand Est'
  ],
  [
    'Rhône', '69', 'Auvergne-Rhône-Alpes'
  ],
  [
    'Haute-Saône', '70', 'Bourgogne-Franche-Comté'
  ],
  [
    'Saône-et-Loire', '71', 'Bourgogne-Franche-Comté'
  ],
  [
    'Sarthe', '72', 'Pays de la Loire'
  ],
  [
    'Savoie', '73', 'Auvergne-Rhône-Alpes'
  ],
  [
    'Haute-Savoie', '74', 'Auvergne-Rhône-Alpes'
  ],
  [
    'Paris', '75', 'Île-de-France'
  ],
  [
    'Seine-Maritime', '76', 'Normandie'
  ],
  [
    'Seine-et-Marne', '77', 'Île-de-France'
  ],
  [
    'Yvelines', '78', 'Île-de-France'
  ],
  [
    'Deux-Sèvres', '79', 'Nouvelle-Aquitaine'
  ],
  [
    'Somme', '80', 'Hauts-de-France'
  ],
  [
    'Tarn', '81', 'Occitanie'
  ],
  [
    'Tarn-et-Garonne', '82', 'Occitanie'
  ],
  [
    'Var', '83', 'Provence-Alpes-Côte d\'Azur'
  ],
  [
    'Vaucluse', '84', 'Provence-Alpes-Côte d\'Azur'
  ],
  [
    'Vendée', '85', 'Pays de la Loire'
  ],
  [
    'Vienne', '86', 'Nouvelle-Aquitaine'
  ],
  [
    'Haute-Vienne', '87', 'Nouvelle-Aquitaine'
  ],
  [
    'Vosges', '88', 'Grand Est'
  ],
  [
    'Yonne', '89', 'Bourgogne-Franche-Comté'
  ],
  [
    'Territoire de Belfort', '90', 'Bourgogne-Franche-Comté'
  ],
  [
    'Essonne', '91', 'Île-de-France'
  ],
  [
    'Hauts-de-Seine', '92', 'Île-de-France'
  ],
  [
    'Seine-Saint-Denis', '93', 'Île-de-France'
  ],
  [
    'Val-de-Marne', '94', 'Île-de-France'
  ],
  [
    'Val-d\'Oise', '95', 'Île-de-France'
  ],
  [
    'Guadeloupe', '971', 'Guadeloupe'
  ],
  [
    'Martinique', '972', 'Martinique'
  ],
  [
    'Guyane', '973', 'Guyane'
  ],
  [
    'La Réunion', '974', 'La Réunion'
  ],
  ['Mayotte', '976', 'Mayotte'],
];
