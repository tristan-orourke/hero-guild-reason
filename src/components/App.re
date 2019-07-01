[@react.component]
let make = () => {
  let initialHeros: list(Hero.hero) = [
    {id: "hero:-1", name: "Johnny Appleseed", skill: 0.2, relationships: []},
    {id: "hero:-2", name: "Anny Dragonhear", skill: 0.35, relationships: []},
    {id: "hero:-3", name: "Bolton Spaltipur", skill: 0.25, relationships: []},
    {id: "hero:-4", name: "Araignia Temple", skill: 0.30, relationships: []},
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

  <div className="container mx-auto object-top">
    <div className="p-2"> <h2> {React.string("Heroes Guild")} </h2> </div>
    <div> <HeroForm submitHero /> </div>
    <GuildInfo heroes={heroState.heroes} />
    <PartyForm
      heroes={heroState.heroes}
      submitParty={_ => Js.log("submitting party")}
    />
    <QuestUi
      pendingQuests=questState.pendingQuests
      completedQuests=questState.completedQuests
      handleAddQuest=addQuest
      handleResolveQuest={(~quest, ~party) => Js.log("resolving quest")}
    />
  </div>;
};