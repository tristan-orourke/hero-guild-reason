module Hero': {
  type t;
  type view = {
    id: Util.Id.t,
    name: string,
    skill: float,
  };
  let view: t => view;
  let ofName: string => t;
} = {
  type t = {
    id: Util.Id.t,
    name: string,
    skill: float,
  };
  type view = {
    id: Util.Id.t,
    name: string,
    skill: float,
  };
  let view = (t: t): view => {id: t.id, name: t.name, skill: t.skill};
  let ofName = (name): t => {id: Util.Id.newId("hero"), name, skill: 0.5};
};