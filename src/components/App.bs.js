// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Domain$HeroGuild = require("../domain/Domain.bs.js");
var QuestUi$HeroGuild = require("./QuestUi.bs.js");
var AppState$HeroGuild = require("../domain/AppState.bs.js");
var HeroForm$HeroGuild = require("./HeroForm.bs.js");
var GuildInfo$HeroGuild = require("./GuildInfo.bs.js");

function App(Props) {
  var initialHeros_000 = Domain$HeroGuild.Hero[/* make */3]("Johnny Appleseed", 0.2);
  var initialHeros_001 = /* :: */[
    Domain$HeroGuild.Hero[/* make */3]("Anny Dragonhear", 0.35),
    /* :: */[
      Domain$HeroGuild.Hero[/* make */3]("Bolton Spaltipur", 0.25),
      /* :: */[
        Domain$HeroGuild.Hero[/* make */3]("Araignia Temple", 0.30),
        /* [] */0
      ]
    ]
  ];
  var initialHeros = /* :: */[
    initialHeros_000,
    initialHeros_001
  ];
  var match = React.useReducer(AppState$HeroGuild.HeroState[/* heroReducer */1], /* record */[/* heroes */initialHeros]);
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
  var resolveQuest = function (quest, party) {
    return Curry._1(questDispatch, /* ResolveQuest */Block.__(1, [
                  quest,
                  party
                ]));
  };
  return React.createElement("div", {
              className: "container mx-auto object-top"
            }, React.createElement("div", {
                  className: "p-2"
                }, React.createElement("h2", undefined, "Heroes Guild")), React.createElement("div", undefined, React.createElement(HeroForm$HeroGuild.make, {
                      submitHero: submitHero
                    })), React.createElement(GuildInfo$HeroGuild.make, {
                  heroes: heroState[/* heroes */0]
                }), React.createElement(QuestUi$HeroGuild.make, {
                  pendingQuests: questState[/* pendingQuests */0],
                  completedQuests: questState[/* completedQuests */1],
                  heroes: heroState[/* heroes */0],
                  handleAddQuest: addQuest,
                  handleResolveQuest: resolveQuest
                }));
}

var make = App;

exports.make = make;
/* react Not a pure module */
