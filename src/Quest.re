type party = {
  scout: Hero.hero,
  leader: Hero.hero,
  defence: Hero.hero,
  support: Hero.hero,
};

type questAction =
  | GainGold(float)
  | SpendSupplies(float);

type location =
  | Forest
  | Ruin;
type questType =
  | ClearMonsters
  | Guard;

type encounterType =
  | Supply
  | Reward;
type challengeWeights = {
  scoutChallenge: float,
  leaderChallenge: float,
  defenceChallenge: float,
  supportChallenge: float,
};
type encounter = {
  description: string,
  encounterType,
  challenge: float,
  challengeWeights,
}
and encounterResult = {
  description: string,
  questActions: list(questAction),
  heroActions: list(Hero.heroAction),
};

type quest = {
  id: string,
  description: string,
  challenge: float,
  location,
  questType,
  supplyCost: float,
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

module Encounters = {
  /**
   * Caculate the degree of success agains an encounter, expressed as a float.
   * 1.0 suggest just meeting the requirements for success.
  */
  let calculateSuccess = (~totalChallenge, ~challengeWeights, ~party): float => {
    let totalWeight: float =
      challengeWeights.leaderChallenge
      +. challengeWeights.scoutChallenge
      +. challengeWeights.supportChallenge
      +. challengeWeights.defenceChallenge;

    let leaderSuccess: float =
      challengeWeights.leaderChallenge /. totalWeight *. party.leader.skill;
    let scoutSuccess: float =
      challengeWeights.scoutChallenge /. totalWeight *. party.scout.skill;
    let supportSuccess: float =
      challengeWeights.supportChallenge /. totalWeight *. party.support.skill;
    let defenceSuccess: float =
      challengeWeights.defenceChallenge /. totalWeight *. party.defence.skill;

    (leaderSuccess +. scoutSuccess +. supportSuccess +. defenceSuccess)
    /. totalChallenge;
  };

  let newSupplyEncounter = (questHistory): encounter => {
    description: "How many supplies will be spent and how will it affect hero comfort?",
    encounterType: Supply,
    challenge: questHistory.quest.challenge,
    challengeWeights: {
      leaderChallenge: 0.0,
      scoutChallenge: 1.0,
      supportChallenge: 1.0,
      defenceChallenge: 0.0,
    },
  };

  let resolveSupplyEncounter =
      (~encounter: encounter, ~questHistory: questHistory): encounterResult => {
    let degreeSuccess =
      calculateSuccess(
        ~totalChallenge=encounter.challenge,
        ~challengeWeights=encounter.challengeWeights,
        ~party=questHistory.party,
      );
    // if success > 1.0, use less supplies
    let suppliesSpent =
      degreeSuccess > 1.0
        ? 1.0 /. degreeSuccess *. questHistory.quest.supplyCost
        : questHistory.quest.supplyCost;
    {
      description:
        "The party had a degree of success = "
        ++ Js.Float.toString(degreeSuccess)
        ++ " and spent "
        ++ Js.Float.toString(suppliesSpent)
        ++ " supplies",
      questActions: [SpendSupplies(suppliesSpent)],
      heroActions: [],
    };
  };

  let newRewardEncounter = (questHistory): encounter => {
    description: "How much gold will be discovered by the Leader and Scout?",
    encounterType: Reward,
    challenge: questHistory.quest.challenge,
    challengeWeights: {
      leaderChallenge: 1.0,
      scoutChallenge: 1.0,
      supportChallenge: 0.0,
      defenceChallenge: 0.0,
    },
  };

  let resolveRewardEncounter =
      (~encounter: encounter, ~questHistory: questHistory): encounterResult => {
    let degreeSuccess =
      calculateSuccess(
        ~totalChallenge=encounter.challenge,
        ~challengeWeights=encounter.challengeWeights,
        ~party=questHistory.party,
      );
    // choose base gold for quest type
    let baseGold =
      switch (questHistory.quest.questType) {
      | ClearMonsters => 10
      | Guard => 15
      };
    let goldGained = float(baseGold) *. degreeSuccess;
    {
      description:
        "The party had a degree of success = "
        ++ Js.Float.toString(degreeSuccess)
        ++ " and gained "
        ++ Js.Float.toString(goldGained)
        ++ " gold",
      questActions: [GainGold(goldGained)],
      heroActions: [],
    };
  };
};

let generateNextEncounter = (questHistory: questHistory): option(encounter) =>
  switch (List.length(questHistory.history)) {
  | 0 => Some(Encounters.newSupplyEncounter(questHistory))
  | 1 => Some(Encounters.newRewardEncounter(questHistory))
  | _ => None
  };

let resolveEncounter =
    (~questHistory: questHistory, ~encounter: encounter): encounterResult =>
  switch (encounter.encounterType) {
  | Supply => Encounters.resolveSupplyEncounter(~encounter, ~questHistory)
  | Reward => Encounters.resolveRewardEncounter(~encounter, ~questHistory)
  };

let resolveQuest = (~party, ~quest): questHistory => {
  // let rand = SeededRandom.seedRand(1); //TODO: get rand from quest or encounter
  let questComplete = ref(false);
  let encounterHistory: ref(list(questHistoryItem)) = ref([]);
  while (! questComplete^) {
    let questHistory: questHistory = {
      party,
      quest,
      history: encounterHistory^,
    };
    let nextEncounter = generateNextEncounter(questHistory);
    switch (nextEncounter) {
    | Some(encounter) =>
      let resolution = resolveEncounter(~questHistory, ~encounter);
      let newEncounterHistory = [
        {encounter, encounterResult: resolution},
        ...encounterHistory^,
      ];
      encounterHistory := newEncounterHistory;
    | None => questComplete := true
    };
  };
  {party, quest, history: encounterHistory^};
} /* }*/ /*   switch(quest.questType, quest.location) */ /*     | (ClearMonsters, Ruin) => */ /*     | (Guard, Ruin) => */ /*   */ /*     | (Guard, Forest) => */ /*     | (ClearMonsters, Forest) => */ /* let generateQuestEncounter = (rand: rand, quest): encounter => */;