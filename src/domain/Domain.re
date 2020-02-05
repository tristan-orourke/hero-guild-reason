type location =
  | Forest
  | Ruin;
type questType =
  | ClearMonsters
  | Guard;

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

    let travelDefault = (~difficulty, ~defaultOutcome, defaultNext: t): t =>
      travel(~difficulty, ~defaultOutcome, ~defaultNext, ());
    let lootDefault = (~difficulty, ~defaultOutcome, defaultNext: t): t =>
      loot(~difficulty, ~defaultOutcome, ~defaultNext, ());
    let defendDefault = (~difficulty, ~defaultOutcome, defaultNext: t): t =>
      defend(~difficulty, ~defaultOutcome, ~defaultNext, ());
    let attackDefault = (~difficulty, ~defaultOutcome, defaultNext: t): t =>
      attack(~difficulty, ~defaultOutcome, ~defaultNext, ());
    let restDefault = (~difficulty, ~defaultOutcome, defaultNext: t): t =>
      rest(~difficulty, ~defaultOutcome, ~defaultNext, ());
  };

  type questContext = {
    id: Util.Id.t,
    title: string,
    location,
    questType,
    seed: Util.ConstGen.t,
  };

  type t = {
    questContext,
    firstEncounter: Encounter.t,
  };
};

/** TESTING HOW TO CONSTRUCT ENCOUNTERS */
module TestEncounters = {
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
        |> add(
             0.33,
             {outcomeDetails: DamageTaken(10.0), nextEncounter: q1},
           )
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
    Quest.Encounter.branch(
      ~difficulty=0.0,
      ~defaultOutcome=BranchDescription,
      ~defaultNext=q2,
      ~optionalOutcomes=
        Quest.Encounter.(
          SuccessMap.(
            empty
            |> add(
                 0.1,
                 {outcomeDetails: BranchDescription, nextEncounter: q1},
               )
          )
        ),
    );

  let r = Quest.Encounter.Reward(Reward.gold(12));
  let pipedQuest =
    Quest.Encounter.(
      endQuest() |> lootDefault(~difficulty=0.4, ~defaultOutcome=r)
    );
  let bracketQuest =
    Quest.Encounter.(
      defendDefault(
        ~difficulty=0.5,
        ~defaultOutcome=DamageTaken(5.0),
        lootDefault(~difficulty=0.4, ~defaultOutcome=r, endQuest()),
      )
    );
  let composedQuest =
    Quest.Encounter.(
      defendDefault(~difficulty=0.5, ~defaultOutcome=DamageTaken(5.0)) @@
      lootDefault(~difficulty=0.4, ~defaultOutcome=r) @@
      endQuest()
    );
  ();
};

/** END OF ENCOUNTER TESTING */

type party = {
  scout: Hero.t,
  leader: Hero.t,
  defence: Hero.t,
  support: Hero.t,
};

type questAction =
  | GainGold(int)
  | TakeDamage(Util.Id.t, float);

type encounterResult = {
  descriptions: list(string),
  questActions: list(questAction),
};

type questHistory = {
  quest: Quest.t,
  encounters: list(encounterResult),
};

module SimpleQuestRunner = {
  let basicEncounter = (description: string): encounterResult => {
    descriptions: [description],
    questActions: [],
  };

  // TODO: Add logic for determining success
  let determineSuccess =
      (~party: party, encounter: Quest.Encounter.t)
      : (float, list(string), list(questAction)) => (
    0.5,
    [],
    [],
  );

  // TODO: Add logic for considering optional outcomes
  let pickBranchOutcome =
      (
        ~party: party,
        ~success: float,
        ~outcomes: Quest.Encounter.outcomes(Quest.Encounter.branchOutcome),
      ) =>
    outcomes.defaultOutcome;

  // TODO: Add logic for branch outcome
  let resolveBranchOutcome =
      (~party: party, outcome: Quest.Encounter.branchOutcome)
      : (list(string), list(questAction)) => (
    [],
    [],
  );

  let runEncounter =
      (
        ~party,
        ~pastEncounters: list(encounterResult),
        ~questContext: Quest.questContext,
        encounter: Quest.Encounter.t,
      )
      : (encounterResult, option(Quest.Encounter.t)) => {
    switch (encounter) {
    | End => ({descriptions: [], questActions: []}, None)
    | Branch(difficulty, outcomes) =>
      let (success, challengeDescriptions, challengeActions) =
        determineSuccess(~party, encounter);
      let outcome = pickBranchOutcome(~party, ~success, ~outcomes);
      let (outcomeDescriptions, outcomeActions) =
        resolveBranchOutcome(~party, outcome.outcomeDetails);
      (
        {
          descriptions:
            List.concat([challengeDescriptions, outcomeDescriptions]),
          questActions: List.concat([challengeActions, outcomeActions]),
        },
        Some(outcome.nextEncounter),
      );
    | Travel(difficulty, outcomes) => (
        {descriptions: [], questActions: []},
        Some(outcomes.defaultOutcome.nextEncounter),
      )
    | Loot(difficulty, outcomes) => (
        {descriptions: [], questActions: []},
        Some(outcomes.defaultOutcome.nextEncounter),
      )
    | Defend(difficulty, outcomes) => (
        {descriptions: [], questActions: []},
        Some(outcomes.defaultOutcome.nextEncounter),
      )
    | Attack(difficulty, outcomes) => (
        {descriptions: [], questActions: []},
        Some(outcomes.defaultOutcome.nextEncounter),
      )
    | Rest(difficulty, outcomes) => (
        {descriptions: [], questActions: []},
        Some(outcomes.defaultOutcome.nextEncounter),
      )
    };
  };

  let rec runRec =
          (
            ~party: party,
            ~pastEncounters: list(encounterResult),
            ~questContext: Quest.questContext,
            encounter: Quest.Encounter.t,
          )
          : list(encounterResult) => {
    let (result, nextEncounter) =
      runEncounter(~party, ~pastEncounters, ~questContext, encounter);
    let encounterList = List.append(pastEncounters, [result]);
    switch (nextEncounter) {
    | None => encounterList
    | Some(x) =>
      runRec(~party, ~pastEncounters=encounterList, ~questContext, x)
    };
  };

  let run = (~party, ~quest: Quest.t): questHistory => {
    quest,
    encounters:
      runRec(
        ~party,
        ~pastEncounters=[],
        ~questContext=quest.questContext,
        quest.firstEncounter,
      ),
  };
};

module BasicQuestGenerator = {
  module ConstRandom = Util.Random(Util.ConstGen);
  let make = (~seed: Util.ConstGen.t, ~id: Util.Id.t): Quest.t => {
    let floats = ConstRandom.randomFloatStream(~min=0.0, ~max=1.0, seed);
    let firstEncounter =
      Quest.Encounter.(
        Stream.(
          travelDefault(
            ~difficulty=next(floats),
            ~defaultOutcome=SupplyCost(10),
          ) @@
          defendDefault(
            ~difficulty=next(floats),
            ~defaultOutcome=DamageTaken(5.0),
          ) @@
          attackDefault(
            ~difficulty=next(floats),
            ~defaultOutcome=DamageDealt(10.0),
          ) @@
          restDefault(
            ~difficulty=next(floats),
            ~defaultOutcome=PotentialHeals(5.0),
          ) @@
          lootDefault(
            ~difficulty=next(floats),
            ~defaultOutcome=Reward(Reward.gold(10)),
          ) @@
          endQuest()
        )
      );
    {
      questContext: {
        id,
        title: "A new dummy Quest with id = " ++ id,
        location: Forest,
        questType: ClearMonsters,
        seed,
      },
      firstEncounter,
    };
  };
};