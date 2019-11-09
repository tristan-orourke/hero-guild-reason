module Hero: {
  type t;
  type view = {
    id: Util.Id.t,
    name: string,
    skill: float,
  };
  let getId: t => Util.Id.t;
  let view: t => view;
  let ofName: string => t;
  let make: (~name: string, ~skill: float) => t;
} = {
  type t = {
    id: Util.Id.t,
    name: string,
    skill: float,
  };
  type view = {
    id: Util.Id.t,
    name: string,
    skill: float,
  };
  let getId = (hero: t) => hero.id;
  let view = (hero: t): view => {
    id: hero.id,
    name: hero.name,
    skill: hero.skill,
  };
  let ofName = (name): t => {id: Util.Id.newId("hero"), name, skill: 0.5};
  let make = (~name, ~skill): t => {id: Util.Id.newId("hero"), name, skill};
};

module Quest = {
  type party = {
    scout: Hero.t,
    leader: Hero.t,
    defence: Hero.t,
    support: Hero.t,
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
    defenceChallenge: float,
    supportChallenge: float,
  }
  and encounterResult = {
    description: string,
    questActions: list(questAction),
  };

  type quest = {
    id: string,
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
    defenceChallenge: 0.0,
    supportChallenge: 0.0,
  };
  let generateNextEncounter = (questHistory: questHistory): option(encounter) =>
    if (List.length(questHistory.history) > 5) {
      None;
    } else {
      Some(dummyEncounter());
    };

  let resolveEncounter = (party: party, encounter: encounter): encounterResult => {
    description: "Dummy Result",
    questActions: [],
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
        let resolution = resolveEncounter(party, encounter);
        let newEncounterHistory = [
          {encounter, encounterResult: resolution},
          ...encounterHistory^,
        ];
        encounterHistory := newEncounterHistory;
      | None => questComplete := true
      };
    };
    {party, quest, history: encounterHistory^};
  } /*   */;
  // let generateQuestEncounter = (rand: rand, quest): encounter => {
  //   switch(quest.questType, quest.location) {
  //     | (ClearMonsters, Forest) => ;
  //     | (ClearMonsters, Ruin) => ;
  //     | (Guard, Forest) => ;
  //     | (Guard, Ruin) => ;
};