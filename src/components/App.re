type heroState = {heroes: list(Hero.hero)};

type heroAction =
  | AddHero(Hero.hero);

[@react.component]
let make = () => {
  // let (heroState, heroDispatch) =
  //   React.useReducer(
  //     AppState.HeroState.heroReducer,
  //     AppState.HeroState.initHero(),
  //   );
  // let mockSubmitHero = _ => Js.log("submitting hero");
  // let submitHero = hero:Hero.hero => heroDispatch(AppState.HeroState.AddHero(hero);

  let (heroState, heroDispatch) =
    React.useReducer(
      (state: heroState, action: heroAction): heroState =>
        switch (action) {
        | AddHero(hero) => {heroes: [hero, ...state.heroes]}
        },
      {heroes: []},
    );

  let submitHero = (hero: Hero.hero) => heroDispatch(AddHero(hero));
  <div>
    <p> {React.string("This is a most basic component.")} </p>
    <HeroForm submitHero />
  </div>;
};
