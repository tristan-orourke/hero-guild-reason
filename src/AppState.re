module HeroState = {
  type heroState = {heroes: list(Hero.hero)};

  type heroAction =
    | AddHero(Hero.hero);

  let initHero = (): heroState => {heroes: []};

  let heroReducer = (state: heroState, action: heroAction): heroState =>
    switch (action) {
    | AddHero(hero) => {heroes: [hero, ...state.heroes]}
    };
};
