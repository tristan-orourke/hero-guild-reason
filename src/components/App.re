[@react.component]
let make = () => {
  let initialHeros: list(Domain.Hero.t) = [
    Domain.Hero.make(
      ~id=Util.Id.newId("hero"),
      ~name="Johnny Appleseed",
      ~skill=0.2,
    ),
    Domain.Hero.make(
      ~id=Util.Id.newId("hero"),
      ~name="Anny Dragonhear",
      ~skill=0.35,
    ),
    Domain.Hero.make(
      ~id=Util.Id.newId("hero"),
      ~name="Bolton Spaltipur",
      ~skill=0.25,
    ),
    Domain.Hero.make(
      ~id=Util.Id.newId("hero"),
      ~name="Araignia Temple",
      ~skill=0.30,
    ),
  ];

  let (heroState, heroDispatch) =
    React.useReducer(
      AppState.HeroState.heroReducer,
      // AppState.HeroState.initHero(),
      {heroes: initialHeros},
    );
  let submitHero = hero => heroDispatch(AppState.HeroState.AddHero(hero));

  let (questState, questDispatch) =
    React.useReducer(
      AppState.QuestState.questReducer,
      AppState.QuestState.initQuest(),
    );
  let addQuest = quest => questDispatch(AppState.QuestState.AddQuest(quest));
  let resolveQuest = (~quest, ~party) =>
    questDispatch(AppState.QuestState.ResolveQuest(quest, party));

  <div className="container mx-auto object-top">
    <div className="p-2"> <h2> {React.string("Heroes Guild")} </h2> </div>
    <div> <HeroForm submitHero /> </div>
    <GuildInfo heroes={heroState.heroes} />
    <QuestUi
      pendingQuests={questState.pendingQuests}
      completedQuests={questState.completedQuests}
      handleAddQuest=addQuest
      heroes={heroState.heroes}
      handleResolveQuest=resolveQuest
    />
  </div>;
};