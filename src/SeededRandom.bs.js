// Generated by BUCKLESCRIPT VERSION 5.0.0, PLEASE EDIT WITH CARE
'use strict';

var Random = require("bs-platform/lib/js/random.js");

function seedInt(seed, bound) {
  Random.init(seed);
  return Random.$$int(bound);
}

function seedFloat(seed, bound) {
  Random.init(seed);
  return Random.$$float(bound);
}

function seedSeed(seed) {
  Random.init(seed);
  return Random.bits(/* () */0);
}

function seedSeed2(seed) {
  Random.init(seed);
  return /* tuple */[
          Random.bits(/* () */0),
          Random.bits(/* () */0)
        ];
}

function seedRand(seed) {
  return /* record */[
          /* int */(function (param) {
              Random.init(seed);
              return Random.$$int(param);
            }),
          /* float */(function (param) {
              Random.init(seed);
              return Random.$$float(param);
            }),
          /* seed */(function (param) {
              return seedRand((Random.init(seed), Random.bits(/* () */0)));
            }),
          /* seed2 */(function (param) {
              var match = seedSeed2(seed);
              return /* tuple */[
                      seedRand(match[0]),
                      seedRand(match[1])
                    ];
            })
        ];
}

exports.seedInt = seedInt;
exports.seedFloat = seedFloat;
exports.seedSeed = seedSeed;
exports.seedSeed2 = seedSeed2;
exports.seedRand = seedRand;
/* No side effect */
