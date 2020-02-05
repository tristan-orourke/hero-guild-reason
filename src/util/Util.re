module Id: {
  type t = string;
  let newId: string => t;
} = {
  type t = string;
  // TODO: make this more robust, and maybe pure?
  let lastId = ref(0);
  let newId = prefix => {
    lastId := lastId^ + 1;
    prefix ++ ":" ++ string_of_int(lastId^);
  };
};

module type RandomGen = {
  type t;
  let next: t => (int, t);
  let split: t => (t, t);
  let make: int => t;
};

module ConstGen: RandomGen = {
  type t = int;
  let next = a => (a, a);
  let split = a => (a, a);
  let make = (a: int): t => a;
};

module type RandomType =
  (Gen: RandomGen) =>
   {
    let randomInt: (~min: int, ~max: int, Gen.t) => (int, Gen.t);
    let randomFloat: (~min: float, ~max: float, Gen.t) => (float, Gen.t);
    let randomIntStream: (~min: int, ~max: int, Gen.t) => Stream.t(int);
    let randomFloatStream:
      (~min: float, ~max: float, Gen.t) => Stream.t(float);
  };

module Random: RandomType =
  (Gen: RandomGen) => {
    let randomInt = (~min: int, ~max: int, g: Gen.t) => {
      let (seed, g') = Gen.next(g);
      Random.init(seed);
      let result = Random.int(max - min) + min;
      (result, g');
    };
    let randomFloat = (~min: float, ~max: float, g: Gen.t) => {
      let (seed, g') = Gen.next(g);
      Random.init(seed);
      let result = Random.float(max -. min) +. min;
      (result, g');
    };

    let generatorStream = (f, g) => {
      let state = ref(g);
      Stream.from(_ => {
        let (res, state') = f(state^);
        state := state';
        Some(res);
      });
    };
    let randomIntStream = (~min: int, ~max: int, g: Gen.t) =>
      generatorStream(randomInt(~min, ~max), g);
    let randomFloatStream = (~min: float, ~max: float, g: Gen.t) =>
      generatorStream(randomFloat(~min, ~max), g);
  };

module Strings = {
  let join = (sep: string) => List.fold_left((a, b) => a ++ sep ++ b, "");
};