type rand = {
  int: int => int,
  float: float => float,
  seed: unit => rand,
  seed2: unit => (rand, rand),
};

let seedInt = (seed, bound) => {
  Random.init(seed);
  Random.int(bound);
};

let seedFloat = (seed, bound) => {
  Random.init(seed);
  Random.float(bound);
};

let seedSeed = seed => {
  Random.init(seed);
  Random.bits();
};

let seedSeed2 = seed => {
  Random.init(seed);
  (Random.bits(), Random.bits());
};

let rec seedRand = (seed: int): rand => {
  {
    int: seedInt(seed),
    float: seedFloat(seed),
    seed: () => seedRand(seedSeed(seed)),
    seed2: () => {
      let (seed1, seed2) = seedSeed2(seed);
      (seedRand(seed1), seedRand(seed2));
    },
  };
};
