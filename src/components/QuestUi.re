module QuestInfoCard = {
  [@react.component]
  let make = (~quest: Quest.quest) => {
    let locationString = (location: Quest.location): string =>
      switch (location) {
      | Forest => "Forest"
      | Ruin => "Ruin"
      };
    let questTypeString = (questType: Quest.questType): string =>
      switch (questType) {
      | ClearMonsters => "Clear Monsters"
      | Guard => "Guard"
      };

    <div className="max-w-xs rounded overflow-hidden shadow-lg p-2 m-2">
      <p> {React.string("Description: " ++ quest.description)} </p>
      <p>
        {React.string("Challenge: " ++ Js.Float.toString(quest.challenge))}
      </p>
      <p> {React.string("Location: " ++ locationString(quest.location))} </p>
      <p>
        {React.string("Quest Type: " ++ questTypeString(quest.questType))}
      </p>
    </div>;
  };
};

module QuestResolver = {
  [@react.component]
  let make =
      (
        ~quest: Quest.quest,
        ~heroes: list(Hero.hero),
        ~handleResolveQuest:
           (~quest: Quest.quest, ~party: Quest.party) => unit,
      ) => {
    let (showParty, setShowParty) = React.useState(() => false);

    let submitParty = party => handleResolveQuest(quest, party);

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
  let make = (~questHistory: Quest.questHistory) => {
    let questDescriptions =
      List.map(
        (questHistoryItem: Quest.questHistoryItem): string =>
          questHistoryItem.encounterResult.description,
        questHistory.history,
      )
      |> List.mapi((index: int, description: string) =>
           <p key={string_of_int(index)}> {React.string(description)} </p>
         );

    <div className="rounded overflow-hidden shadow-lg p-2 m-2">
      {Array.of_list(questDescriptions)->React.array}
    </div>;
  };
};

[@react.component]
let make =
    (
      ~pendingQuests: list(Quest.quest),
      ~completedQuests: list(Quest.questHistory),
      ~handleAddQuest: Quest.quest => unit,
      ~heroes: list(Hero.hero),
      ~handleResolveQuest: (~quest: Quest.quest, ~party: Quest.party) => unit,
    ) => {
  let generateQuest = (): Quest.quest => {
    id: Uuid.questId(),
    description: "Another Dummy Quest",
    challenge: 0.5,
    location: Forest,
    questType: ClearMonsters,
    supplyCost: 1.0,
  };

  let questCards =
    List.map(
      (quest: Quest.quest) =>
        <div key={quest.id}>
          <QuestInfoCard quest />
          <QuestResolver quest heroes handleResolveQuest />
        </div>,
      pendingQuests,
    )
    ->Array.of_list
    ->React.array;

  let questOutcomeCards =
    List.map(
      questHistory =>
        <QuestOutcomeCard questHistory key={questHistory.quest.id} />,
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