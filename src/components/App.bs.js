// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var QuestUi$HeroGuild = require("./QuestUi.bs.js");
var AppState$HeroGuild = require("../AppState.bs.js");
var HeroForm$HeroGuild = require("./HeroForm.bs.js");
var GuildInfo$HeroGuild = require("./GuildInfo.bs.js");
var PartyForm$HeroGuild = require("./PartyForm.bs.js");

function App(Props) {
  var match = React.useReducer(AppState$HeroGuild.HeroState[/* heroReducer */1], /* record */[/* heroes : :: */[
          /* record */[
            /* id */"hero:-1",
            /* name */"Johnny Appleseed",
            /* skill */0.2,
            /* relationships : [] */0
          ],
          /* :: */[
            /* record */[
              /* id */"hero:-2",
              /* name */"Anny Dragonhear",
              /* skill */0.35,
              /* relationships : [] */0
            ],
            /* :: */[
              /* record */[
                /* id */"hero:-3",
                /* name */"Bolton Spaltipur",
                /* skill */0.25,
                /* relationships : [] */0
              ],
              /* :: */[
                /* record */[
                  /* id */"hero:-4",
                  /* name */"Araignia Temple",
                  /* skill */0.30,
                  /* relationships : [] */0
                ],
                /* [] */0
              ]
            ]
          ]
        ]]);
  var heroDispatch = match[1];
  var heroState = match[0];
  var submitHero = function (hero) {
    return Curry._1(heroDispatch, /* AddHero */[hero]);
  };
  var match$1 = React.useReducer(AppState$HeroGuild.QuestState[/* questReducer */1], AppState$HeroGuild.QuestState[/* initQuest */0](/* () */0));
  var questDispatch = match$1[1];
  var questState = match$1[0];
  var addQuest = function (quest) {
    return Curry._1(questDispatch, /* AddQuest */Block.__(0, [quest]));
  };
  return React.createElement("div", {
              className: "container mx-auto object-top"
            }, React.createElement("div", {
                  className: "p-2"
                }, React.createElement("h2", undefined, "Heroes Guild")), React.createElement("div", undefined, React.createElement(HeroForm$HeroGuild.make, {
                      submitHero: submitHero
                    })), React.createElement(GuildInfo$HeroGuild.make, {
                  heroes: heroState[/* heroes */0]
                }), React.createElement(PartyForm$HeroGuild.make, {
                  heroes: heroState[/* heroes */0],
                  submitParty: (function (param) {
                      console.log("submitting party");
                      return /* () */0;
                    })
                }), React.createElement(QuestUi$HeroGuild.make, {
                  pendingQuests: questState[/* pendingQuests */0],
                  completedQuests: questState[/* completedQuests */1],
                  handleAddQuest: addQuest,
                  heroes: heroState[/* heroes */0],
                  handleResolveQuest: (function (quest, party) {
                      console.log("resolving quest");
                      return /* () */0;
                    })
                }));
}

var make = App;

exports.make = make;
/* react Not a pure module */
