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

module QuestState = {
  type questState = {
    pendingQuests: list(Quest.quest),
    completedQuests: list(Quest.questHistory),
  };

  type questAction =
    | AddQuest(Quest.quest)
    | ResolveQuest(Quest.quest, Quest.party);

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
            (item: Quest.quest) => item.id !== quest.id,
            state.pendingQuests,
          ),
        completedQuests: [
          Quest.resolveQuest(~party, ~quest),
          ...state.completedQuests,
        ],
      }
    };
};