open Domain;

module QuestInfoCard = {
  [@react.component]
  let make = (~context: Domain.questContext) => {
    let locationString = (location: location): string =>
      switch (location) {
      | Forest => "Forest"
      | Ruin => "Ruin"
      };
    let questTypeString = (questType: questType): string =>
      switch (questType) {
      | ClearMonsters => "Clear Monsters"
      | Guard => "Guard"
      };

    <div className="max-w-xs rounded overflow-hidden shadow-lg p-2 m-2">
      <p> {React.string("Description: " ++ context.title)} </p>
      // <p>
      //   {React.string("Challenge: " ++ Js.Float.toString(context.difficulty))}
      // </p>
      <p>
        {React.string("Location: " ++ locationString(context.location))}
      </p>
      <p>
        {React.string("Quest Type: " ++ questTypeString(context.questType))}
      </p>
    </div>;
  };
};

module QuestResolver = {
  [@react.component]
  let make =
      (
        ~quest: Domain.questContext,
        ~heroes: list(Hero.t),
        ~handleResolveQuest:
           (~quest: Domain.questContext, ~party: party) => unit,
      ) => {
    let (showParty, setShowParty) = React.useState(() => false);

    let submitParty = party => handleResolveQuest(~quest, ~party);

    <div>
      <button
        className=Styles.btnBlue
        type_="button"
        onClick={_ => setShowParty(value => !value)}>
        {React.string(showParty ? "Hide Party" : "Show Party")}
      </button>
      {showParty ? <PartyForm heroes submitParty /> : React.null}
    </div>;
  };
};

module QuestOutcomeCard = {
  [@react.component]
  let make = (~questHistory: Domain.questHistory) => {
    <div className="rounded overflow-hidden shadow-lg p-2 m-2">
      <p>
        {React.string("Quest complete: " ++ questHistory.questContext.title)}
      </p>
    </div>;
  };
};

module SetupQuest = {
  [@react.component]
  let make =
      (
        ~quest: Quest.t,
        ~questContext: Domain.questContext,
        ~heroes: list(Hero.t),
        ~startQuest: (~quest: Quest.t, ~party: Domain.party) => unit,
      ) => {
    <div className="block">
      <QuestInfoCard context=questContext />
      <PartyForm heroes submitParty={party => startQuest(~quest, ~party)} />
    </div>;
  };
};

[@react.component]
let make =
    (
      ~pendingQuests: list(Domain.questContext),
      ~completedQuests: list(Domain.questHistory),
      ~heroes: list(Hero.t),
      ~handleAddQuest: Domain.questContext => unit,
      ~handleResolveQuest:
         (~quest: Domain.questContext, ~party: Domain.party) => unit,
    ) => {
  let generateQuest = (): Domain.questContext =>
    Domain.BasicQuestGenerator.make(
      ~seed=Util.ConstGen.make(1),
      ~id=Util.Id.newId("quest"),
    );

  let questCards =
    List.map(
      (questContext: Domain.questContext) =>
        <div key={questContext.id}>
          <QuestInfoCard context=questContext />
          <QuestResolver quest=questContext heroes handleResolveQuest />
        </div>,
      pendingQuests,
    )
    ->Array.of_list
    ->React.array;

  let questOutcomeCards =
    List.map(
      questHistory =>
        <QuestOutcomeCard questHistory key={questHistory.questContext.id} />,
      completedQuests,
    )
    ->Array.of_list
    ->React.array;

  <div className="m-2">
    <button
      className=Styles.btnBlue
      type_="button"
      onClick={_ => handleAddQuest(generateQuest())}>
      {React.string("Generate Quest")}
    </button>
    <div className="flex flex-col sm:flex-row"> questCards </div>
    <p> {React.string("Completed Quests:")} </p>
    <div className="flex flex-col sm:flex-row"> questOutcomeCards </div>
  </div>;
};