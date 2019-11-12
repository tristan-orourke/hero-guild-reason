// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var Block = require("bs-platform/lib/js/block.js");
var Util$HeroGuild = require("../util/Util.bs.js");

function getId(hero) {
  return hero[/* id */0];
}

function view(hero) {
  return /* record */[
          /* id */hero[/* id */0],
          /* name */hero[/* name */1],
          /* skill */hero[/* skill */2]
        ];
}

function ofName(name) {
  return /* record */[
          /* id */Util$HeroGuild.Id[/* newId */0]("hero"),
          /* name */name,
          /* skill */0.5
        ];
}

function make(id, name, skill) {
  return /* record */[
          /* id */id,
          /* name */name,
          /* skill */skill
        ];
}

var Hero = /* module */[
  /* getId */getId,
  /* view */view,
  /* ofName */ofName,
  /* make */make
];

function makeWithValue(value) {
  return value;
}

var QuestBranchDescription = /* module */[/* makeWithValue */makeWithValue];

function gold(value) {
  return /* Gold */[value];
}

var Reward = /* module */[/* gold */gold];

function branch($staropt$star, $$default) {
  var options = $staropt$star !== undefined ? $staropt$star : /* [] */0;
  return /* Branch */Block.__(0, [
            options,
            $$default
          ]);
}

function travel(difficulty, next) {
  return /* Travel */Block.__(1, [
            difficulty,
            next
          ]);
}

function defend(difficulty, next) {
  return /* Defend */Block.__(2, [
            difficulty,
            next
          ]);
}

function attack(difficulty, next) {
  return /* Attack */Block.__(3, [
            difficulty,
            next
          ]);
}

function rest(next) {
  return /* Rest */Block.__(4, [next]);
}

function loot(rewards, next) {
  return /* Loot */Block.__(5, [
            rewards,
            next
          ]);
}

function endQuest(param) {
  return /* End */0;
}

var Quest$prime = /* module */[
  /* branch */branch,
  /* travel */travel,
  /* defend */defend,
  /* attack */attack,
  /* rest */rest,
  /* loot */loot,
  /* endQuest */endQuest
];

var r_000 = /* Gold */[5];

var r_001 = /* :: */[
  /* Gold */[10],
  /* [] */0
];

var r = /* :: */[
  r_000,
  r_001
];

var q1 = /* Loot */Block.__(5, [
    r,
    /* End */0
  ]);

var q2 = /* Defend */Block.__(2, [
    0.5,
    /* End */0
  ]);

var q_000 = /* :: */[
  /* DescribedQuest */[
    2.0,
    q1
  ],
  /* :: */[
    /* DescribedQuest */[
      0.5,
      q2
    ],
    /* [] */0
  ]
];

var q = /* Branch */Block.__(0, [
    q_000,
    q2
  ]);

var pipedQuest = /* Loot */Block.__(5, [
    r,
    /* End */0
  ]);

var bracketQuest_001 = /* Loot */Block.__(5, [
    r,
    /* End */0
  ]);

var bracketQuest = /* Defend */Block.__(2, [
    0.5,
    bracketQuest_001
  ]);

var composedQuest_001 = /* Loot */Block.__(5, [
    r,
    /* End */0
  ]);

var composedQuest = /* Defend */Block.__(2, [
    0.5,
    composedQuest_001
  ]);

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
          /* questActions : [] */0
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
          /* questActions : [] */0
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

var Quest = /* module */[
  /* dummyEncounter */dummyEncounter,
  /* generateNextEncounter */generateNextEncounter,
  /* resolveEncounter */resolveEncounter,
  /* resolveQuest */resolveQuest
];

exports.Hero = Hero;
exports.QuestBranchDescription = QuestBranchDescription;
exports.Reward = Reward;
exports.Quest$prime = Quest$prime;
exports.r = r;
exports.q1 = q1;
exports.q2 = q2;
exports.q = q;
exports.pipedQuest = pipedQuest;
exports.bracketQuest = bracketQuest;
exports.composedQuest = composedQuest;
exports.Quest = Quest;
/* No side effect */
