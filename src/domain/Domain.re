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

module Quest = {
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
let q1 = Quest.Loot(r, Quest.End);
let q2 = Quest.Defend(0.5, Quest.End);

let q =
  Quest.Branch(
    [
      Quest.DescribedQuest(QuestBranchDescription.makeWithValue(2.0), q1),
      Quest.DescribedQuest(QuestBranchDescription.makeWithValue(0.5), q2),
    ],
    q2,
  );

let pipedQuest = Quest.(endQuest() |> loot(r));
let bracketQuest = Quest.(defend(0.5, loot(r, endQuest())));
let composedQuest = Quest.(defend(0.5) @@ loot(r) @@ endQuest());

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
  id: Util.Id.t,
  title: string,
  location,
  questType,
  seed: Util.ConstGen.t,
  quest: Quest.t,
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
            ~pastEncounters: list(encounterResult),
            ~quest: Quest.t,
          )
          : list(encounterResult) => {
    let runPartial = runRec(~party);
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

  let run = (~party, ~questContext): questHistory => {
    questContext,
    encounters: runRec(~party, ~pastEncounters=[], ~quest=questContext.quest),
  };
};

module BasicQuestGenerator = {
  module ConstRandom = Util.Random(Util.ConstGen);
  let make = (~seed: Util.ConstGen.t, ~id: Util.Id.t): questContext => {
    let floats = ConstRandom.randomFloatStream(~min=0.0, ~max=1.0, seed);
    let quest =
      Quest.(
        Stream.(
          travel(next(floats)) @@
          defend(next(floats)) @@
          attack(next(floats)) @@
          rest @@
          loot([]) @@
          endQuest()
        )
      );
    {
      id,
      title: "A new dummy Quest with id = " ++ id,
      location: Forest,
      questType: ClearMonsters,
      seed,
      quest,
    };
  };
};