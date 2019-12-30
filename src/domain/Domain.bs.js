// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var $$Map = require("bs-platform/lib/js/map.js");
var List = require("bs-platform/lib/js/list.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Stream = require("bs-platform/lib/js/stream.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
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

var compare = Caml_obj.caml_compare;

var SuccessMap = $$Map.Make(/* module */[/* compare */compare]);

function branch($staropt$star, difficulty, defaultOutcome, defaultNext) {
  var optionalOutcomes = $staropt$star !== undefined ? Caml_option.valFromOption($staropt$star) : SuccessMap[/* empty */0];
  return /* Branch */Block.__(0, [
            difficulty,
            /* record */[
              /* defaultOutcome : record */[
                /* outcomeDetails */defaultOutcome,
                /* nextEncounter */defaultNext
              ],
              /* optionalOutcomes */optionalOutcomes
            ]
          ]);
}

function travel($staropt$star, difficulty, defaultOutcome, defaultNext) {
  var optionalOutcomes = $staropt$star !== undefined ? Caml_option.valFromOption($staropt$star) : SuccessMap[/* empty */0];
  return /* Travel */Block.__(1, [
            difficulty,
            /* record */[
              /* defaultOutcome : record */[
                /* outcomeDetails */defaultOutcome,
                /* nextEncounter */defaultNext
              ],
              /* optionalOutcomes */optionalOutcomes
            ]
          ]);
}

function loot($staropt$star, difficulty, defaultOutcome, defaultNext) {
  var optionalOutcomes = $staropt$star !== undefined ? Caml_option.valFromOption($staropt$star) : SuccessMap[/* empty */0];
  return /* Loot */Block.__(2, [
            difficulty,
            /* record */[
              /* defaultOutcome : record */[
                /* outcomeDetails */defaultOutcome,
                /* nextEncounter */defaultNext
              ],
              /* optionalOutcomes */optionalOutcomes
            ]
          ]);
}

function defend($staropt$star, difficulty, defaultOutcome, defaultNext) {
  var optionalOutcomes = $staropt$star !== undefined ? Caml_option.valFromOption($staropt$star) : SuccessMap[/* empty */0];
  return /* Defend */Block.__(3, [
            difficulty,
            /* record */[
              /* defaultOutcome : record */[
                /* outcomeDetails */defaultOutcome,
                /* nextEncounter */defaultNext
              ],
              /* optionalOutcomes */optionalOutcomes
            ]
          ]);
}

function attack($staropt$star, difficulty, defaultOutcome, defaultNext) {
  var optionalOutcomes = $staropt$star !== undefined ? Caml_option.valFromOption($staropt$star) : SuccessMap[/* empty */0];
  return /* Attack */Block.__(4, [
            difficulty,
            /* record */[
              /* defaultOutcome : record */[
                /* outcomeDetails */defaultOutcome,
                /* nextEncounter */defaultNext
              ],
              /* optionalOutcomes */optionalOutcomes
            ]
          ]);
}

function rest($staropt$star, difficulty, defaultOutcome, defaultNext) {
  var optionalOutcomes = $staropt$star !== undefined ? Caml_option.valFromOption($staropt$star) : SuccessMap[/* empty */0];
  return /* Rest */Block.__(5, [
            difficulty,
            /* record */[
              /* defaultOutcome : record */[
                /* outcomeDetails */defaultOutcome,
                /* nextEncounter */defaultNext
              ],
              /* optionalOutcomes */optionalOutcomes
            ]
          ]);
}

function endQuest(param) {
  return /* End */0;
}

var Encounter = /* module */[
  /* SuccessMap */SuccessMap,
  /* branch */branch,
  /* travel */travel,
  /* loot */loot,
  /* defend */defend,
  /* attack */attack,
  /* rest */rest,
  /* endQuest */endQuest
];

function branch$1($staropt$star, $$default) {
  var options = $staropt$star !== undefined ? $staropt$star : /* [] */0;
  return /* Branch */Block.__(0, [
            options,
            $$default
          ]);
}

function travel$1(difficulty, next) {
  return /* Travel */Block.__(1, [
            difficulty,
            next
          ]);
}

function defend$1(difficulty, next) {
  return /* Defend */Block.__(2, [
            difficulty,
            next
          ]);
}

function attack$1(difficulty, next) {
  return /* Attack */Block.__(3, [
            difficulty,
            next
          ]);
}

function rest$1(next) {
  return /* Rest */Block.__(4, [next]);
}

function loot$1(rewards, next) {
  return /* Loot */Block.__(5, [
            rewards,
            next
          ]);
}

function endQuest$1(param) {
  return /* End */0;
}

var Quest = /* module */[
  /* Encounter */Encounter,
  /* branch */branch$1,
  /* travel */travel$1,
  /* defend */defend$1,
  /* attack */attack$1,
  /* rest */rest$1,
  /* loot */loot$1,
  /* endQuest */endQuest$1
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

function basicEncounter(description) {
  return /* record */[
          /* description */description,
          /* questActions : [] */0
        ];
}

function runRec(party, pastEncounters, quest) {
  var handleEncounter = function (description, next) {
    return runRec(party, List.append(pastEncounters, /* :: */[
                    /* record */[
                      /* description */description,
                      /* questActions : [] */0
                    ],
                    /* [] */0
                  ]), next);
  };
  if (typeof quest === "number") {
    return pastEncounters;
  } else {
    switch (quest.tag | 0) {
      case 0 : 
          return handleEncounter("And then they branched, but chose the default route.", quest[1]);
      case 1 : 
          return handleEncounter("And then they travelled at a difficulty of " + quest[0].toString(), quest[1]);
      case 2 : 
          return handleEncounter("And then they defended at a difficulty of " + quest[0].toString(), quest[1]);
      case 3 : 
          return handleEncounter("And then they attacked at a difficulty of " + quest[0].toString(), quest[1]);
      case 4 : 
          return handleEncounter("And then they rested.", quest[0]);
      case 5 : 
          return handleEncounter("And then they looted.", quest[1]);
      
    }
  }
}

function run(party, questContext) {
  return /* record */[
          /* questContext */questContext,
          /* encounters */runRec(party, /* [] */0, questContext[/* quest */5])
        ];
}

var SimpleQuestRunner = /* module */[
  /* basicEncounter */basicEncounter,
  /* runRec */runRec,
  /* run */run
];

var ConstRandom = Util$HeroGuild.Random(Util$HeroGuild.ConstGen);

function make$1(seed, id) {
  var floats = Curry._3(ConstRandom[/* randomFloatStream */3], 0.0, 1.0, seed);
  var quest_000 = Stream.next(floats);
  var quest_001 = /* Defend */Block.__(2, [
      Stream.next(floats),
      /* Attack */Block.__(3, [
          Stream.next(floats),
          /* Rest */Block.__(4, [/* Loot */Block.__(5, [
                  /* [] */0,
                  /* End */0
                ])])
        ])
    ]);
  var quest = /* Travel */Block.__(1, [
      quest_000,
      quest_001
    ]);
  return /* record */[
          /* id */id,
          /* title */"A new dummy Quest with id = " + id,
          /* location : Forest */0,
          /* questType : ClearMonsters */0,
          /* seed */seed,
          /* quest */quest
        ];
}

var BasicQuestGenerator = /* module */[
  /* ConstRandom */ConstRandom,
  /* make */make$1
];

exports.Hero = Hero;
exports.QuestBranchDescription = QuestBranchDescription;
exports.Reward = Reward;
exports.Quest = Quest;
exports.r = r;
exports.q1 = q1;
exports.q2 = q2;
exports.q = q;
exports.pipedQuest = pipedQuest;
exports.bracketQuest = bracketQuest;
exports.composedQuest = composedQuest;
exports.SimpleQuestRunner = SimpleQuestRunner;
exports.BasicQuestGenerator = BasicQuestGenerator;
/* SuccessMap Not a pure module */
