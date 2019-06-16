// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var React = require("react");
var Pervasives = require("bs-platform/lib/js/pervasives.js");

function GuildInfo$HeroCard(Props) {
  var hero = Props.hero;
  return React.createElement("div", undefined, React.createElement("p", undefined, "Name: " + hero[/* name */1]), React.createElement("p", undefined, "Skill: " + Pervasives.string_of_float(hero[/* skill */2])));
}

var HeroCard = /* module */[/* make */GuildInfo$HeroCard];

function GuildInfo(Props) {
  var heroes = Props.heroes;
  var heroCards = $$Array.of_list(List.map((function (hero) {
              return React.createElement(GuildInfo$HeroCard, {
                          hero: hero,
                          key: hero[/* id */0]
                        });
            }), heroes));
  return React.createElement("div", undefined, "Your Heroes", React.createElement("div", undefined, heroCards));
}

var make = GuildInfo;

exports.HeroCard = HeroCard;
exports.make = make;
/* react Not a pure module */