// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var Caml_format = require("bs-platform/lib/js/caml_format.js");
var Uuid$HeroGuild = require("../Uuid.bs.js");
var Styles$HeroGuild = require("../Styles.bs.js");

function HeroForm(Props) {
  var submitHero = Props.submitHero;
  var match = React.useState((function () {
          return "";
        }));
  var setName = match[1];
  var name = match[0];
  var match$1 = React.useState((function () {
          return 0.5;
        }));
  var setSkill = match$1[1];
  var skill = match$1[0];
  return React.createElement("div", {
              className: Styles$HeroGuild.form
            }, React.createElement("p", undefined, "Create a hero by entering values below."), React.createElement("label", undefined, "Hero Name", React.createElement("input", {
                      type: "text",
                      value: name,
                      onChange: (function ($$event) {
                          var value = $$event.target.value;
                          return Curry._1(setName, (function (param) {
                                        return value;
                                      }));
                        })
                    })), React.createElement("label", undefined, "Skill (0-1)", React.createElement("input", {
                      step: 0.01,
                      type: "number",
                      value: Pervasives.string_of_float(skill),
                      onChange: (function ($$event) {
                          var value = $$event.target.value;
                          if (isNaN(Number(value))) {
                            return 0;
                          } else {
                            var f = Caml_format.caml_float_of_string(value);
                            return Curry._1(setSkill, (function (param) {
                                          return f;
                                        }));
                          }
                        })
                    })), React.createElement("button", {
                  type: "submit",
                  onClick: (function (param) {
                      return Curry._1(submitHero, /* record */[
                                  /* id */Uuid$HeroGuild.heroId(/* () */0),
                                  /* name */name,
                                  /* skill */skill,
                                  /* relationships : [] */0
                                ]);
                    })
                }, "submit"));
}

var make = HeroForm;

exports.make = make;
/* react Not a pure module */
