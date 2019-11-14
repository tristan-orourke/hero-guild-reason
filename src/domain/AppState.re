open Domain;

module HeroState = {
  type heroState = {heroes: list(Hero.t)};

  type heroAction =
    | AddHero(Hero.t);

  let initHero = (): heroState => {heroes: []};

  let heroReducer = (state: heroState, action: heroAction): heroState =>
    switch (action) {
    | AddHero(hero) => {heroes: [hero, ...state.heroes]}
    };
};

module QuestState = {
  type questState = {
    pendingQuests: list(Domain.questContext),
    completedQuests: list(Domain.questHistory),
  };

  type questAction =
    | AddQuest(Domain.questContext)
    | ResolveQuest(Domain.questContext, Domain.party);

  let initQuest = (): questState => {pendingQuests: [], completedQuests: []};

  let questReducer = (state: questState, action: questAction): questState =>
    switch (action) {
    | AddQuest(quest) => {
        ...state,
        pendingQuests: [quest, ...state.pendingQuests],
      }
    | ResolveQuest(questContext, party) => {
        pendingQuests:
          List.filter(
            (item: Domain.questContext) => item.id !== questContext.id,
            state.pendingQuests,
          ),
        completedQuests: [
          Domain.SimpleQuestRunner.run(~party, ~questContext),
          ...state.completedQuests,
        ],
      }
    };
};