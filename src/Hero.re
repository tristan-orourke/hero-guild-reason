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

let heroToJs = hero => {
  "id": hero.id,
  "name": hero.name,
  "skill": hero.skill,
  "relationships": List.map(relationshipToJs, hero.relationships),
};