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
  let mockSubmitHero = _ => Js.log("submitting hero");
  let submitHero = hero => heroDispatch(AppState.HeroState.AddHero(hero));

  <div className="container object-top">
    <div className="p-2">
      <h2> {React.string("Heroes Guild")} </h2>
    </div>
    <div> <HeroForm submitHero /> </div>
    <GuildInfo heroes={heroState.heroes} />
    <Party
      heroes={heroState.heroes}
      submitParty={_ => Js.log("submitting party")}
    />
  </div>;
};
