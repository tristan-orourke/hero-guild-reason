// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");

function dummyEncounter(param) {
  return /* record */[
          /* description */"Dummy Encounter,",
          /* scoutChallenge */0.0,
          /* leaderChallenge */0.0,
          /* defenceChallenge */0.0,
          /* supportChallenge */0.0
        ];
}

function generateNextEncounter(questHistory) {
  if (List.length(questHistory[/* history */2]) > 5) {
    return undefined;
  } else {
    return /* record */[
            /* description */"Dummy Encounter,",
            /* scoutChallenge */0.0,
            /* leaderChallenge */0.0,
            /* defenceChallenge */0.0,
            /* supportChallenge */0.0
          ];
  }
}

function resolveEncounter(party, encounter) {
  return /* record */[
          /* description */"Dummy Result",
          /* questActions : [] */0,
          /* heroActions : [] */0
        ];
}

function resolveQuest(party, quest) {
  var questComplete = false;
  var encounterHistory = /* [] */0;
  while(!questComplete) {
    var questHistory = /* record */[
      /* party */party,
      /* quest */quest,
      /* history */encounterHistory
    ];
    var nextEncounter = generateNextEncounter(questHistory);
    if (nextEncounter !== undefined) {
      var newEncounterHistory_000 = /* record */[
        /* encounter */nextEncounter,
        /* encounterResult : record */[
          /* description */"Dummy Result",
          /* questActions : [] */0,
          /* heroActions : [] */0
        ]
      ];
      var newEncounterHistory = /* :: */[
        newEncounterHistory_000,
        encounterHistory
      ];
      encounterHistory = newEncounterHistory;
    } else {
      questComplete = true;
    }
  };
  return /* record */[
          /* party */party,
          /* quest */quest,
          /* history */encounterHistory
        ];
}

exports.dummyEncounter = dummyEncounter;
exports.generateNextEncounter = generateNextEncounter;
exports.resolveEncounter = resolveEncounter;
exports.resolveQuest = resolveQuest;
/* No side effect */