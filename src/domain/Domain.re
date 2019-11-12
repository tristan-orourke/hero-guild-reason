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
  type t =
    | Branch(list(describedQuest), t)
    | Travel(difficulty, t)
    | Defend(difficulty, t)
    | Attack(difficulty, t)
    | Rest(t)
    | Loot(list(Reward.t), t)
    | End
  and describedQuest =
    | DescribedQuest(QuestBranchDescription.t, t);

  let branch = (~options=[], default) => Branch(options, default);
  let travel = (difficulty, next) => Travel(difficulty, next);
  let defend = (difficulty, next) => Defend(difficulty, next);
  let attack = (difficulty, next) => Attack(difficulty, next);
  let rest = next => Rest(next);
  let loot = (rewards, next) => Loot(rewards, next);
  let endQuest = () => End;
};

let r = [Reward.gold(5), Reward.gold(10)];
let q1 = Quest'.Loot(r, Quest'.End);
let q2 = Quest'.Defend(0.5, Quest'.End);

let q =
  Quest'.Branch(
    [
      Quest'.DescribedQuest(QuestBranchDescription.makeWithValue(2.0), q1),
      Quest'.DescribedQuest(QuestBranchDescription.makeWithValue(0.5), q2),
    ],
    q2,
  );

let pipedQuest = Quest'.(endQuest() |> loot(r));
let bracketQuest = Quest'.(defend(0.5, loot(r, endQuest())));
let composedQuest = Quest'.(defend(0.5) @@ loot(r) @@ endQuest());

type party = {
  scout: Hero.t,
  leader: Hero.t,
  defence: Hero.t,
  support: Hero.t,
};

type location =
  | Forest
  | Ruin;
type questType =
  | ClearMonsters
  | Guard;

type questContext = {
  title: string,
  location,
  questType,
  seed: Util.ConstGen.t,
};

type questAction =
  | GainGold(int);

type encounterResult = {
  description: string,
  questActions: list(questAction),
};

type questHistory = {
  questContext,
  encounters: list(encounterResult),
};

module SimpleQuestRunner = {
  let basicEncounter = description => {description, questActions: []};

  let rec runRec =
          (
            ~party: party,
            ~questContext: questContext,
            ~pastEncounters: list(encounterResult),
            ~quest: Quest'.t,
          )
          : list(encounterResult) => {
    let runPartial = runRec(~party, ~questContext);
    let handleEncounter = (description, next) =>
      runPartial(
        ~pastEncounters=
          List.append(pastEncounters, [basicEncounter(description)]),
        ~quest=next,
      );
    switch (quest) {
    | Branch(_, next) =>
      handleEncounter(
        "And then they branched, but chose the default route.",
        next,
      )
    | Travel(difficulty, next) =>
      handleEncounter(
        "And then they travelled at a difficulty of "
        ++ Js.Float.toString(difficulty),
        next,
      )
    | Defend(difficulty, next) =>
      handleEncounter(
        "And then they defended at a difficulty of "
        ++ Js.Float.toString(difficulty),
        next,
      )
    | Attack(difficulty, next) =>
      handleEncounter(
        "And then they attacked at a difficulty of "
        ++ Js.Float.toString(difficulty),
        next,
      )
    | Rest(next) => handleEncounter("And then they rested.", next)
    | Loot(_, next) => handleEncounter("And then they looted.", next)
    | End => pastEncounters
    };
  };

  let run = (~party, ~questContext, ~quest: Quest'.t): questHistory => {
    questContext,
    encounters: runRec(~party, ~questContext, ~pastEncounters=[], ~quest),
  };
};

module BasicQuestGenerator = {
  module ConstRandom = Util.Random(Util.ConstGen);
  let make = (seed: Util.ConstGen.t): (questContext, Quest'.t) => {
    let context = {
      title: "A new dummy Quest",
      location: Forest,
      questType: ClearMonsters,
      seed,
    };
    let floats = ConstRandom.randomFloatStream(~min=0.0, ~max=1.0, seed);
    let quest =
      Quest'.(
        Stream.(
          travel(next(floats)) @@
          defend(next(floats)) @@
          attack(next(floats)) @@
          rest @@
          loot([]) @@
          endQuest()
        )
      );
    (context, quest);
  };
};

module Quest = {
  type questAction =
    | GainGold(int);

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

  type questHistoryItem = {
    encounter,
    encounterResult,
  };

  type quest = {
    id: string,
    description: string,
    challenge: float,
    location,
    questType,
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