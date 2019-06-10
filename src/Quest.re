type party = {
  scout: Hero.hero,
  leader: Hero.hero,
  frontline: Hero.hero,
  support: Hero.hero,
};

type questAction =
  | GainGold(int);

type location =
  | Forest
  | Ruin;
type questType =
  | ClearMonsters
  | Guard;

type encounter = {
  description: string,
  scoutChallenge: float,
  leaderChallenge: float,
  frontlineChallenge: float,
  supportChallenge: float,
}
and encounterResult = {
  description: string,
  questActions: list(questAction),
  heroActions: list(Hero.heroAction),
};

type quest = {
  description: string,
  challenge: float,
  location,
  questType,
};

type questHistoryItem = {
  encounter,
  encounterResult,
};

type questHistory = {
  party,
  quest,
  history: list(questHistoryItem),
};

let dummyEncounter = (): encounter => {
  description: "Dummy Encounter,",
  scoutChallenge: 0.0,
  leaderChallenge: 0.0,
  frontlineChallenge: 0.0,
  supportChallenge: 0.0,
};
let generateNextEncounter =
    (seed: SeededRandom.rand, questHistory: questHistory): option(encounter) =>
  if (List.length(questHistory.history) > 5) {
    None;
  } else {
    Some(dummyEncounter());
  };

let resolveEncounter (party: party, encounter: encounter): encounterResult => 
  {description: "Dummy Result", questActions: [], heroActions: []};

let resolveQuest = (party, quest): questHistory => {
  let history = [];
  let questHistory = {party, quest, history: []};
  let rand = SeededRandom.seedRand(1); //TODO: get rand from quest or encounter
  let encounterHistory: list(questHistoryItem) = [];
  let nextEncounter = generateNextEncounter(rand, questHistory);
  while (nextEncounter !== None) {
    let resolution = resolveEncounter(party, nextEncounter);
    let encounterHistory = [{encounter: nextEncounter, encounterResult: resolution}, ...encounterHistory];
  }
  return {party, quest, history: encounterHistory};
};

// let generateQuestEncounter = (rand: rand, quest): encounter => {
//   switch(quest.questType, quest.location) {
//     | (ClearMonsters, Forest) => ;
//     | (ClearMonsters, Ruin) => ;
//     | (Guard, Forest) => ;
//     | (Guard, Ruin) => ;
//   }
// };
