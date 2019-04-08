type bond =
  | Basic
  | Friend
  | Rival
  | Mentor
  | Student;

/**
  Note: if I am myId, bond=Mentor means I think of THEM as my Mentor.
 */
type relationship = {
  myId: int,
  towardsId: int,
  value: float,
  bond,
};

type hero = {
  id: int,
  name: string,
  skill: float,
  relationships: list(relationship),
};

type heroAction =
  | SetSkill(float)
  | SetRelationship(relationship);

type party = {
  scout: hero,
  leader: hero,
  frontline: hero,
  support: hero,
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
  resolve: party => encounterResult,
}
and encounterResult = {
  description: string,
  questActions: list(questAction),
  heroActions: list(heroAction),
  nextEncounter: option(encounter),
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
  resolve: _party => {
    description: "Dummy Result",
    questActions: [],
    heroActions: [],
    nextEncounter: None,
  },
};

let rec resolveQuestEncounters =
        (party: party, encounter: encounter): list(questHistoryItem) => {
  let encounterResult = encounter.resolve(party);
  let questHistoryItem = {encounter, encounterResult};
  switch (encounterResult.nextEncounter) {
  | None => [questHistoryItem]
  | Some(encounter) => [
      questHistoryItem,
      ...resolveQuestEncounters(party, encounter),
    ]
  };
};

let resolveQuest = (party, quest): questHistory => {
  //Create initial encounter
  let encounter = dummyEncounter();
  {party, quest, history: resolveQuestEncounters(party, encounter)};
};

let generateQuestEncounter = (rand: rand, quest): encounter => {
  switch(quest.questType, quest.location) {
    | (ClearMonsters, Forest) => ;
    | (ClearMonsters, Ruin) => ;
    | (Guard, Forest) => ;
    | (Guard, Ruin) => ;
  }
};
