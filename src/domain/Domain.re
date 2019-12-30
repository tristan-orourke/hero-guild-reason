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

module Reward: {
  type t;
  let gold: int => t;
} = {
  type t =
    | Gold(int);
  let gold = value => Gold(value);
};

module Quest = {
  module Encounter = {
    type difficulty = float;
    module SuccessMap =
      Map.Make({
        type t = float;
        let compare = compare;
      });

    type branchOutcome =
      | BranchDescription;
    type travelOutcome =
      | SupplyCost(int);
    type lootOutcome =
      | Reward(Reward.t);
    type defendOutcome =
      | DamageTaken(float);
    type attackOutcome =
      | DamageDealt(float);
    type restOutcome =
      | PotentialHeals(float);

    type t =
      | Branch(difficulty, outcomes(branchOutcome))
      | Travel(difficulty, outcomes(travelOutcome))
      | Loot(difficulty, outcomes(lootOutcome))
      | Defend(difficulty, outcomes(defendOutcome))
      | Attack(difficulty, outcomes(attackOutcome))
      | Rest(difficulty, outcomes(restOutcome))
      | End
    and encounterOutcome('a) = {
      outcomeDetails: 'a,
      nextEncounter: t,
    }
    and outcomes('a) = {
      defaultOutcome: encounterOutcome('a),
      optionalOutcomes: SuccessMap.t(encounterOutcome('a)),
    };

    let branch =
        (
          ~difficulty,
          ~defaultOutcome: branchOutcome,
          ~defaultNext: t,
          ~optionalOutcomes=SuccessMap.empty,
          (),
        )
        : t =>
      Branch(
        difficulty,
        {
          defaultOutcome: {
            outcomeDetails: defaultOutcome,
            nextEncounter: defaultNext,
          },
          optionalOutcomes,
        },
      );
    let travel =
        (
          ~difficulty,
          ~defaultOutcome: travelOutcome,
          ~defaultNext: t,
          ~optionalOutcomes=SuccessMap.empty,
          (),
        )
        : t =>
      Travel(
        difficulty,
        {
          defaultOutcome: {
            outcomeDetails: defaultOutcome,
            nextEncounter: defaultNext,
          },
          optionalOutcomes,
        },
      );
    let loot =
        (
          ~difficulty,
          ~defaultOutcome: lootOutcome,
          ~defaultNext: t,
          ~optionalOutcomes=SuccessMap.empty,
          (),
        )
        : t =>
      Loot(
        difficulty,
        {
          defaultOutcome: {
            outcomeDetails: defaultOutcome,
            nextEncounter: defaultNext,
          },
          optionalOutcomes,
        },
      );
    let defend =
        (
          ~difficulty,
          ~defaultOutcome: defendOutcome,
          ~defaultNext: t,
          ~optionalOutcomes=SuccessMap.empty,
          (),
        )
        : t =>
      Defend(
        difficulty,
        {
          defaultOutcome: {
            outcomeDetails: defaultOutcome,
            nextEncounter: defaultNext,
          },
          optionalOutcomes,
        },
      );
    let attack =
        (
          ~difficulty,
          ~defaultOutcome: attackOutcome,
          ~defaultNext: t,
          ~optionalOutcomes=SuccessMap.empty,
          (),
        )
        : t =>
      Attack(
        difficulty,
        {
          defaultOutcome: {
            outcomeDetails: defaultOutcome,
            nextEncounter: defaultNext,
          },
          optionalOutcomes,
        },
      );
    let rest =
        (
          ~difficulty,
          ~defaultOutcome: restOutcome,
          ~defaultNext: t,
          ~optionalOutcomes=SuccessMap.empty,
          (),
        )
        : t =>
      Rest(
        difficulty,
        {
          defaultOutcome: {
            outcomeDetails: defaultOutcome,
            nextEncounter: defaultNext,
          },
          optionalOutcomes,
        },
      );
    let endQuest = () => End;
  };

  type questDescription = {descriptionText: string};
  type t = {
    questDescription,
    firstEncounter: Encounter.t,
  };
};

let q1: Quest.Encounter.t =
  Quest.Encounter.loot(
    ~difficulty=0.4,
    ~defaultOutcome=Reward(Reward.gold(10)),
    ~defaultNext=Quest.Encounter.End,
    (),
  );
let q2Options =
  Quest.Encounter.(
    SuccessMap.(
      empty
      |> add(0.33, {outcomeDetails: DamageTaken(10.0), nextEncounter: q1})
      |> add(0.66, {outcomeDetails: DamageTaken(5.0), nextEncounter: q1})
      |> add(1.0, {outcomeDetails: DamageTaken(0.0), nextEncounter: q1})
    )
  );
let q2: Quest.Encounter.t =
  Quest.Encounter.defend(
    ~difficulty=0.6,
    ~defaultOutcome=DamageTaken(15.0),
    ~defaultNext=q1,
    ~optionalOutcomes=q2Options,
    (),
  );
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