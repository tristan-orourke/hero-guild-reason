module Hero': {
  type t;
  type view = {
    id: Util.ID.t,
    name: string,
    skill: float,
  };
  let view: t => view;
} = {
  type t = {
    id: Util.ID.t,
    name: string,
    skill: float,
  };
  type view = {
    id: Util.ID.t,
    name: string,
    skill: float,
  };
  let view = (t: t): view => {id: t.id, name: t.name, skill: t.skill};
};