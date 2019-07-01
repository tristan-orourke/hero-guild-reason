module QuestCard = {
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

module QuestOutcomeCard = {
  [@react.component]
  let make = (~questHistory: Quest.questHistory) => {
    <div className="rounded overflow-hidden shadow-lg p-2 m-2">
      <p> {React.string("encounter => result")} </p>
    </div>;
  };
};

module SetupQuest = {
  [@react.component]
  let make =
      (
        ~quest: Quest.quest,
        ~heroes: list(Hero.hero),
        ~startQuest: (~quest: Quest.quest, ~party: Quest.party) => unit,
      ) => {
    <div className="block">
      <QuestCard quest />
      <PartyForm heroes submitParty={party => startQuest(~quest, ~party)} />
    </div>;
  };
};

[@react.component]
let make =
    (
      ~pendingQuests: list(Quest.quest),
      ~completedQuests: list(Quest.questHistory),
      ~heroes: list(Hero.hero),
      ~handleAddQuest: Quest.quest => unit,
      ~handleResolveQuest: (~quest: Quest.quest, ~party: Quest.party) => unit,
    ) => {
  let generateQuest = (): Quest.quest => {
    id: Uuid.questId(),
    description: "Another Dummy Quest #" ++ string_of_int(Uuid.lastId^),
    challenge: 0.5,
    location: Forest,
    questType: ClearMonsters,
  };

  let questCards =
    List.map(
      quest =>
        <SetupQuest
          quest
          heroes
          startQuest=handleResolveQuest
          key={quest.id}
        />,
      pendingQuests,
    )
    ->Array.of_list
    ->React.array;

  let completedQuestCards =
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
    <h3> {React.string("Pending Quests")} </h3>
    <div className="flex flex-col"> questCards </div>
    <h3> {React.string("Completed Quests")} </h3>
    <div className="flex flex-col"> completedQuestCards </div>
  </div>;
};