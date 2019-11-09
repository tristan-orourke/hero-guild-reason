type submitHero = Domain.Hero.t => unit;
[@react.component]
let make = (~submitHero: submitHero) => {
  let getValue = (event): string => ReactEvent.Form.target(event)##value;
  let isFloat = (value: string): bool =>
    !value->Js.Float.fromString->Js.Float.isNaN;

  let (name, setName) = React.useState(() => "");

  let (skill, setSkill) = React.useState(() => 0.5);

  let submit = () => {
    let hero: Domain.Hero.t = Domain.Hero.make(~name, ~skill);
    submitHero(hero);
  };

  <div className="max-w-md p-2">
    <p> {React.string("Create a hero by entering values below.")} </p>
    <Forms.TextInput
      label="Hero Name"
      value=name
      onChange={event => {
        let value = getValue(event);
        setName(_ => value);
      }}
    />
    <Forms.NumberInput
      label="Skill (0-1)"
      step=0.01
      value=skill
      onChange={event => {
        let value = getValue(event);
        if (isFloat(value)) {
          let f = float_of_string(value);
          setSkill(_ => f);
        };
      }}
    />
    <button className=Styles.btnBlue type_="submit" onClick={_ => submit()}>
      {React.string("submit")}
    </button>
  </div>;
};