[@react.component]
let make = () => {
  let (heroState, heroDispatch) =
    React.useReducer(
      AppState.HeroState.heroReducer,
      AppState.HeroState.initHero(),
    );
  let mockSubmitHero = _ => Js.log("submitting hero");
  let submitHero = hero => heroDispatch(AppState.HeroState.AddHero(hero));

  <div className=Styles.flexColumn>
    <h2> {React.string("Heroes Guild")} </h2>
    <div> <HeroForm submitHero /> </div>
    <GuildInfo heroes={heroState.heroes} />
  </div>;
};
