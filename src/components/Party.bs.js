// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Styles$HeroGuild = require("../Styles.bs.js");

function Party$HeroSelector(Props) {
  var position = Props.position;
  var selectedHero = Props.selectedHero;
  var heroOptions = Props.heroOptions;
  var handleChange = Props.handleChange;
  return React.createElement("label", {
              className: Styles$HeroGuild.formLabel
            }, position + ": ", React.createElement("select", {
                  className: Styles$HeroGuild.input,
                  name: position,
                  value: selectedHero !== undefined ? selectedHero[/* id */0] : "",
                  onChange: handleChange
                }, React.createElement("option", {
                      disabled: true,
                      value: ""
                    }, "fill position"), $$Array.of_list(List.map((function (hero) {
                            return React.createElement("option", {
                                        key: hero[/* id */0],
                                        value: hero[/* id */0]
                                      }, hero[/* name */1]);
                          }), heroOptions))));
}

var HeroSelector = /* module */[/* make */Party$HeroSelector];

function Party(Props) {
  var heroes = Props.heroes;
  var submitParty = Props.submitParty;
  var match = React.useState((function () {
          return undefined;
        }));
  var setScout = match[1];
  var scout = match[0];
  var match$1 = React.useState((function () {
          return undefined;
        }));
  var setLeader = match$1[1];
  var leader = match$1[0];
  var match$2 = React.useState((function () {
          return undefined;
        }));
  var setDefence = match$2[1];
  var defence = match$2[0];
  var match$3 = React.useState((function () {
          return undefined;
        }));
  var setSupport = match$3[1];
  var support = match$3[0];
  var handleChange = function (heroSetter, $$event) {
    var selectedId = $$event.target.value;
    var selectedHero = List.find((function (param) {
            return param[/* id */0] === selectedId;
          }), heroes);
    return Curry._1(heroSetter, (function (param) {
                  return selectedHero;
                }));
  };
  var selectedHeros = function (param) {
    return Belt_List.keepMap(/* :: */[
                scout,
                /* :: */[
                  leader,
                  /* :: */[
                    defence,
                    /* :: */[
                      support,
                      /* [] */0
                    ]
                  ]
                ]
              ], (function (hero) {
                  return hero;
                }));
  };
  var isAlreadySelected = function (hero) {
    return List.exists((function (h) {
                  return h === hero;
                }), selectedHeros(/* () */0));
  };
  var availableOptions = function (forceAllow) {
    var heroFilter;
    if (forceAllow !== undefined) {
      var forceHero = forceAllow;
      heroFilter = (function (hero) {
          if (hero === forceHero) {
            return true;
          } else {
            return !isAlreadySelected(hero);
          }
        });
    } else {
      heroFilter = (function (hero) {
          return !isAlreadySelected(hero);
        });
    }
    return List.filter(heroFilter)(heroes);
  };
  return React.createElement("div", {
              className: "p-2"
            }, React.createElement("h3", undefined, "Select your pary"), React.createElement(Party$HeroSelector, {
                  position: "scout",
                  selectedHero: scout,
                  heroOptions: availableOptions(scout),
                  handleChange: (function (param) {
                      return handleChange(setScout, param);
                    })
                }), React.createElement(Party$HeroSelector, {
                  position: "leader",
                  selectedHero: leader,
                  heroOptions: availableOptions(leader),
                  handleChange: (function (param) {
                      return handleChange(setLeader, param);
                    })
                }), React.createElement(Party$HeroSelector, {
                  position: "defence",
                  selectedHero: defence,
                  heroOptions: availableOptions(defence),
                  handleChange: (function (param) {
                      return handleChange(setDefence, param);
                    })
                }), React.createElement(Party$HeroSelector, {
                  position: "support",
                  selectedHero: support,
                  heroOptions: availableOptions(support),
                  handleChange: (function (param) {
                      return handleChange(setSupport, param);
                    })
                }), React.createElement("button", {
                  className: Styles$HeroGuild.btnBlue,
                  type: "submit",
                  onClick: (function (param) {
                      if (scout !== undefined && leader !== undefined && defence !== undefined && support !== undefined) {
                        return Curry._1(submitParty, /* record */[
                                    /* scout */scout,
                                    /* leader */leader,
                                    /* defence */defence,
                                    /* support */support
                                  ]);
                      } else {
                        console.log("Cannot submit party until all positions filled");
                        return /* () */0;
                      }
                    })
                }, "Submit Party"));
}

var make = Party;

exports.HeroSelector = HeroSelector;
exports.make = make;
/* react Not a pure module */
