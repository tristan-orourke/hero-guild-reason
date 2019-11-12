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
  let make: (~id: Util.Id.t, ~name: string, ~skill: float) => t;
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
  /**TODO: remove impurity of newId. Maybe just take a string? */
  let ofName = (name): t => {id: Util.Id.newId("hero"), name, skill: 0.5};
  let make = (~id, ~name, ~skill): t => {id, name, skill};
};

module QuestBranchDescription: {
  type t;
  let makeWithValue: float => t;
} = {
  type t = float;
  let makeWithValue = value => value;
};

module Reward: {
  type t;
  let gold: int => t;
} = {
  type t =
    | Gold(int);
  let gold = value => Gold(value);
};

module Quest' = {
  type difficulty = float;
  type encounterDescription = string;
  type t =
    | Branch(encounterDescription, list(describedQuest), t)
    | Travel(encounterDescription, difficulty, t)
    | Defend(encounterDescription, difficulty, t)
    | Attack(encounterDescription, difficulty, t)
    | Rest(encounterDescription, t)
    | Loot(encounterDescription, list(Reward.t), t)
    | End
  and describedQuest =
    | DescribedQuest(QuestBranchDescription.t, t);

  let branch = (description, ~options=[], default) =>
    Branch(description, options, default);
  let travel = (description, difficulty, next) =>
    Travel(description, difficulty, next);
  let defend = (description, difficulty, next) =>
    Defend(description, difficulty, next);
  let attack = (description, difficulty, next) =>
    Attack(description, difficulty, next);
  let rest = (description, next) => Rest(description, next);
  let loot = (description, rewards, next) =>
    Loot(description, rewards, next);
  let endQuest = () => End;
};

let r = [Reward.gold(5), Reward.gold(10)];
let q1 = Quest'.Loot("Found some jewels", r, Quest'.End);
let q2 = Quest'.Defend("Defend the castle", 0.5, Quest'.End);

let q =
  Quest'.Branch(
    "Choose which one",
    [
      Quest'.DescribedQuest(QuestBranchDescription.makeWithValue(2.0), q1),
      Quest'.DescribedQuest(QuestBranchDescription.makeWithValue(0.5), q2),
    ],
    q2,
  );

let pipedQuest = Quest'.(endQuest() |> loot("Pipe the loot", r));
let bracketQuest =
  Quest'.(
    defend("Keep your fort", 0.5, loot("Bracket the loot", r, endQuest()))
  );
let composedQuest =
  Quest'.(
    defend("Keep your house safe", 0.5) @@
    loot("Compose your loot", r) @@
    endQuest()
  );

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