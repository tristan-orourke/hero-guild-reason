open DomainTypes;

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
  heroActions: [],
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
} /* }*/ /*   */;

// let generateQuestEncounter = (rand: rand, quest): encounter => {
//   switch(quest.questType, quest.location) {
//     | (ClearMonsters, Forest) => ;
//     | (ClearMonsters, Ruin) => ;
//     | (Guard, Forest) => ;
//     | (Guard, Ruin) => ;