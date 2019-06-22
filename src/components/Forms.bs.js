// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var Styles$HeroGuild = require("../Styles.bs.js");

function Forms$TextInput(Props) {
  var label = Props.label;
  var value = Props.value;
  var onChange = Props.onChange;
  return React.createElement("label", {
              className: Styles$HeroGuild.formLabel
            }, label, React.createElement("input", {
                  className: Styles$HeroGuild.input,
                  type: "text",
                  value: value,
                  onChange: onChange
                }));
}

var TextInput = /* module */[/* make */Forms$TextInput];

function Forms$NumberInput(Props) {
  var label = Props.label;
  var value = Props.value;
  var match = Props.step;
  var step = match !== undefined ? match : 1.0;
  var onChange = Props.onChange;
  return React.createElement("label", {
              className: Styles$HeroGuild.formLabel
            }, label, React.createElement("input", {
                  className: Styles$HeroGuild.input,
                  step: step,
                  type: "number",
                  value: Pervasives.string_of_float(value),
                  onChange: onChange
                }));
}

var NumberInput = /* module */[/* make */Forms$NumberInput];

exports.TextInput = TextInput;
exports.NumberInput = NumberInput;
/* react Not a pure module */
