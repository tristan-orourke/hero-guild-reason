type bond =
  | Basic
  | Friend
  | Rival
  | Mentor
  | Student;

/**
  Note: if I am myId, bond=Mentor means I think of THEM as my Mentor.
 */
[@bs.deriving jsConverter]
type relationship = {
  myId: string,
  towardsId: int,
  value: float,
  bond,
};

type hero = {
  id: string,
  name: string,
  skill: float,
  relationships: list(relationship),
};

type heroAction =
  | SetSkill(float)
  | SetRelationship(relationship);

type party = {
  scout: hero,
  leader: hero,
  defence: hero,
  support: hero,
};

type questAction =
  | GainGold(int);

type location =
  | Forest
  | Ruin;
type questType =
  | ClearMonsters
  | Guard;

type encounter = {
  description: string,
  scoutChallenge: float,
  leaderChallenge: float,
  defenceChallenge: float,
  supportChallenge: float,
}
and encounterResult = {
  description: string,
  questActions: list(questAction),
  heroActions: list(heroAction),
};

type quest = {
  id: string,
  description: string,
  challenge: float,
  location,
  questType,
};

type questHistoryItem = {
  encounter,
  encounterResult,
};

type questHistory = {
  party,
  quest,
  history: list(questHistoryItem),
};