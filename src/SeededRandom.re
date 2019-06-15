type rand = {
  int: int => int,
  float: float => float,
  next: unit => rand,
  split: unit => (rand, rand),
};

type randomGen = {
  next: unit => (int, randomGen),
  split: unit => (randomGen, randomGen),
};

let rec seedRandomGen = (seed: int): randomGen => {
  Random.init(seed);
  let (nextInt, seed1, seed2) = (
    Random.bits(),
    Random.bits(),
    Random.bits(),
  );
  {
    next: () => (nextInt, seedRandomGen(seed1)),
    split: () => (seedRandomGen(seed1), seedRandomGen(seed2)),
  };
};

let seedInt = (seed: int, bound: int): int => {
  Random.init(seed);
  Random.int(bound);
};

let seedFloat = (seed: int, bound: float): float => {
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
    next: () => seedRand(seedSeed(seed)),
    split: () => {
      let (seed1, seed2) = seedSeed2(seed);
      (seedRand(seed1), seedRand(seed2));
    },
  };
};

let rec seedRandFromGen = (randomGen: randomGen): rand => {
  let (seed, _) = randomGen.next();
  {
    int: seedInt(seed),
    float: seedFloat(seed),
    next: () => {
      let (_, nextGen) = randomGen.next();
      seedRandFromGen(nextGen);
    },
    split: () => {
      let (gen1, gen2) = randomGen.split();
      (seedRandFromGen(gen1), seedRandFromGen(gen2));
    },
  };
};

// let rec randomSeriesRec(rand: rand, len: int, series: list(rand)): list(rand) =>
//   len <= 0 ?
//     series
//     :
//       randomSeriesRec(rand.seed(), length - 1, [rand.seed(), ...series]);

// let generateSeries(rand: rand, length: int): list(rand) => randomSeriesRec(rand, length, []);
