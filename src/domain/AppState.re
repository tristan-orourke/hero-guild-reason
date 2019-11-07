open DomainTypes;

module HeroState = {
  type heroState = {heroes: list(hero)};

  type heroAction =
    | AddHero(hero);

  let initHero = (): heroState => {heroes: []};

  let heroReducer = (state: heroState, action: heroAction): heroState =>
    switch (action) {
    | AddHero(hero) => {heroes: [hero, ...state.heroes]}
    };
};

module QuestState = {
  type questState = {
    pendingQuests: list(quest),
    completedQuests: list(questHistory),
  };

  type questAction =
    | AddQuest(quest)
    | ResolveQuest(quest, party);

  let initQuest = (): questState => {pendingQuests: [], completedQuests: []};

  let questReducer = (state: questState, action: questAction): questState =>
    switch (action) {
    | AddQuest(quest) => {
        ...state,
        pendingQuests: [quest, ...state.pendingQuests],
      }
    | ResolveQuest(quest, party) => {
        pendingQuests:
          List.filter(
            (item: quest) => item.id !== quest.id,
            state.pendingQuests,
          ),
        completedQuests: [
          Quest.resolveQuest(~party, ~quest),
          ...state.completedQuests,
        ],
      }
    };
};