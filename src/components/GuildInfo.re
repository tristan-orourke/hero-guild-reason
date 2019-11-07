open DomainTypes;

module HeroCard = {
  [@react.component]
  let make = (~hero: hero) => {
    <div className="max-w-xs rounded overflow-hidden shadow-lg p-2 m-2">
      <p> {React.string("Name: " ++ hero.name)} </p>
      <p> {React.string("Skill: " ++ Js.Float.toString(hero.skill))} </p>
    </div>;
  };
};

[@react.component]
let make = (~heroes: list(hero)) => {
  let heroCards =
    List.map(hero => <HeroCard hero key={hero.id} />, heroes)
    ->Array.of_list
    ->React.array;
  // {
  //   React.array(Array.of_list(List.map(hero => <HeroCard hero />, heroes)));
  // };

  <div className="p-2">
    {React.string("Your Heroes")}
    <div className="flex flex-col sm:flex-row flex-wrap"> heroCards </div>
  </div>;
};