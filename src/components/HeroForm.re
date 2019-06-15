type submitHero = Hero.hero => unit;
[@react.component]
let make = (~submitHero: submitHero) => {
  let getValue = (event): string => ReactEvent.Form.target(event)##value;
  let isFloat = (value: string): bool =>
    !value->Js.Float.fromString->Js.Float.isNaN;

  let (name, setName) = React.useState(() => "");

  let (skill, setSkill) = React.useState(() => 0.5);

  let submit = () => {
    let hero: Hero.hero = {id: Uuid.heroId(), name, skill, relationships: []};
    submitHero(hero);
  };

  <div>
    <p> {React.string("Create a hero by entering values below.")} </p>
    <label>
      {React.string("Hero Name")}
      <input
        type_="text"
        value=name
        onChange={event => {
          let value = getValue(event);
          setName(_ => value);
        }}
      />
    </label>
    <label>
      {React.string("Skill (0-1)")}
      <input
        type_="number"
        step=0.01
        value={string_of_float(skill)}
        onChange={event => {
          let value = getValue(event);
          if (isFloat(value)) {
            let f = float_of_string(value);
            setSkill(_ => f);
          };
        }}
      />
    </label>
    <button type_="submit" onClick={_ => submit()}>
      {React.string("submit")}
    </button>
  </div>;
};
