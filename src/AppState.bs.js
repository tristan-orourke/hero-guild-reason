// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';


function initHero(param) {
  return /* record */[/* heroes : [] */0];
}

function heroReducer(state, action) {
  return /* record */[/* heroes : :: */[
            action[0],
            state[/* heroes */0]
          ]];
}

var HeroState = /* module */[
  /* initHero */initHero,
  /* heroReducer */heroReducer
];

exports.HeroState = HeroState;
/* No side effect */