// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';


var lastId = /* record */[/* contents */0];

function heroId(param) {
  lastId[0] = lastId[0] + 1 | 0;
  return "hero:" + String(lastId[0]);
}

function questId(param) {
  lastId[0] = lastId[0] + 1 | 0;
  return "quest:" + String(lastId[0]);
}

exports.lastId = lastId;
exports.heroId = heroId;
exports.questId = questId;
/* No side effect */
