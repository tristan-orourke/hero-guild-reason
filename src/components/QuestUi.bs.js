// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Uuid$HeroGuild = require("../Uuid.bs.js");
var Styles$HeroGuild = require("../Styles.bs.js");
var PartyForm$HeroGuild = require("./PartyForm.bs.js");

function QuestUi$QuestInfoCard(Props) {
  var quest = Props.quest;
  return React.createElement("div", {
              className: "max-w-xs rounded overflow-hidden shadow-lg p-2 m-2"
            }, React.createElement("p", undefined, "Description: " + quest[/* description */1]), React.createElement("p", undefined, "Challenge: " + quest[/* challenge */2].toString()), React.createElement("p", undefined, "Location: " + (
                  quest[/* location */3] ? "Ruin" : "Forest"
                )), React.createElement("p", undefined, "Quest Type: " + (
                  quest[/* questType */4] ? "Guard" : "Clear Monsters"
                )));
}

var QuestInfoCard = /* module */[/* make */QuestUi$QuestInfoCard];

function QuestUi$QuestResolver(Props) {
  var quest = Props.quest;
  var heroes = Props.heroes;
  var handleResolveQuest = Props.handleResolveQuest;
  var match = React.useState((function () {
          return false;
        }));
  var setShowParty = match[1];
  var showParty = match[0];
  var submitParty = function (party) {
    return Curry._2(handleResolveQuest, quest, party);
  };
  return React.createElement("div", undefined, React.createElement("button", {
                  className: Styles$HeroGuild.btnBlue,
                  type: "button",
                  onClick: (function (param) {
                      return Curry._1(setShowParty, (function (value) {
                                    return !value;
                                  }));
                    })
                }, showParty ? "Hide Party" : "Show Party"), showParty ? React.createElement(PartyForm$HeroGuild.make, {
                    heroes: heroes,
                    submitParty: submitParty
                  }) : null);
}

var QuestResolver = /* module */[/* make */QuestUi$QuestResolver];

function QuestUi$QuestOutcomeCard(Props) {
  var questHistory = Props.questHistory;
  List.mapi((function (index, description) {
          return React.createElement("p", {
                      key: String(index)
                    }, description);
        }), List.map((function (questHistoryItem) {
              return questHistoryItem[/* encounterResult */1][/* description */0];
            }), questHistory[/* history */2]));
  return React.createElement("div", {
              className: "rounded overflow-hidden shadow-lg p-2 m-2"
            }, React.createElement("p", undefined, "Quest complete: " + questHistory[/* quest */1][/* description */1]));
}

var QuestOutcomeCard = /* module */[/* make */QuestUi$QuestOutcomeCard];

function QuestUi$SetupQuest(Props) {
  var quest = Props.quest;
  var heroes = Props.heroes;
  var startQuest = Props.startQuest;
  return React.createElement("div", {
              className: "block"
            }, React.createElement(QuestUi$QuestInfoCard, {
                  quest: quest
                }), React.createElement(PartyForm$HeroGuild.make, {
                  heroes: heroes,
                  submitParty: (function (party) {
                      return Curry._2(startQuest, quest, party);
                    })
                }));
}

var SetupQuest = /* module */[/* make */QuestUi$SetupQuest];

function QuestUi(Props) {
  var pendingQuests = Props.pendingQuests;
  var completedQuests = Props.completedQuests;
  var heroes = Props.heroes;
  var handleAddQuest = Props.handleAddQuest;
  var handleResolveQuest = Props.handleResolveQuest;
  var generateQuest = function (param) {
    return /* record */[
            /* id */Uuid$HeroGuild.questId(/* () */0),
            /* description */"Another Dummy Quest #" + String(Uuid$HeroGuild.lastId[0]),
            /* challenge */0.5,
            /* location : Forest */0,
            /* questType : ClearMonsters */0,
            /* supplyCost */1.0
          ];
  };
  var questCards = $$Array.of_list(List.map((function (quest) {
              return React.createElement("div", {
                          key: quest[/* id */0]
                        }, React.createElement(QuestUi$QuestInfoCard, {
                              quest: quest
                            }), React.createElement(QuestUi$QuestResolver, {
                              quest: quest,
                              heroes: heroes,
                              handleResolveQuest: handleResolveQuest
                            }));
            }), pendingQuests));
  var questOutcomeCards = $$Array.of_list(List.map((function (questHistory) {
              return React.createElement(QuestUi$QuestOutcomeCard, {
                          questHistory: questHistory,
                          key: questHistory[/* quest */1][/* id */0]
                        });
            }), completedQuests));
  return React.createElement("div", {
              className: "m-2"
            }, React.createElement("button", {
                  className: Styles$HeroGuild.btnBlue,
                  type: "button",
                  onClick: (function (param) {
                      return Curry._1(handleAddQuest, generateQuest(/* () */0));
                    })
                }, "Generate Quest"), React.createElement("div", {
                  className: "flex flex-col sm:flex-row"
                }, questCards), React.createElement("p", undefined, "Completed Quests:"), React.createElement("div", {
                  className: "flex flex-col sm:flex-row"
                }, questOutcomeCards));
}

var make = QuestUi;

exports.QuestInfoCard = QuestInfoCard;
exports.QuestResolver = QuestResolver;
exports.QuestOutcomeCard = QuestOutcomeCard;
exports.SetupQuest = SetupQuest;
exports.make = make;
/* react Not a pure module */
