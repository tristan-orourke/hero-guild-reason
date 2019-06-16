// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Party$HeroGuild = require("./Party.bs.js");
var Styles$HeroGuild = require("../Styles.bs.js");
var AppState$HeroGuild = require("../AppState.bs.js");
var HeroForm$HeroGuild = require("./HeroForm.bs.js");
var GuildInfo$HeroGuild = require("./GuildInfo.bs.js");

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
  return React.createElement("div", {
              className: Styles$HeroGuild.flexColumn
            }, React.createElement("h2", undefined, "Heroes Guild"), React.createElement("div", undefined, React.createElement(HeroForm$HeroGuild.make, {
                      submitHero: submitHero
                    })), React.createElement(GuildInfo$HeroGuild.make, {
                  heroes: heroState[/* heroes */0]
                }), React.createElement(Party$HeroGuild.make, {
                  heroes: heroState[/* heroes */0],
                  submitParty: (function (param) {
                      console.log("submitting party");
                      return /* () */0;
                    })
                }));
}

var make = App;

exports.make = make;
/* react Not a pure module */
