type bond =
  | Basic
  | Friend
  | Rival
  | Mentor
  | Student;

/**
  Note: if I am myId, bond=Mentor means I think of THEM as my Mentor.
 */
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
