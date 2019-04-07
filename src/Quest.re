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
  thisEncounter: encounter,
  nextEncounter: option(encounter),
};

type quest = {
  description: string,
  challenge: float,
};

type questHistory = {
  party,
  quest,
  history: list(encounterResult),
};

let rec dummyEncounter = (): encounter => {
  description: "Dummy Encounter,",
  scoutChallenge: 0.0,
  leaderChallenge: 0.0,
  frontlineChallenge: 0.0,
  supportChallenge: 0.0,
  resolve: _party => {
    description: "Dummy Result",
    questActions: [],
    heroActions: [],
    thisEncounter: dummyEncounter(),
    nextEncounter: None,
  },
};

let rec resolveQuestEncounters =
        (party: party, encounter: encounter): list(encounterResult) => {
  let result = encounter.resolve(party);
  switch (result.nextEncounter) {
  | None => [result]
  | Some(encounter) => [result, ...resolveQuestEncounters(party, encounter)]
  };
};

let resolveQuest = (party, quest): questHistory => {
  //Create initial encounter
  let encounter = dummyEncounter();
  {party, quest, history: resolveQuestEncounters(party, encounter)};
};
