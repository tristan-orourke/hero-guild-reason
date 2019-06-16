module HeroCard = {
  [@react.component]
  let make = (~hero: Hero.hero) => {
    <div>
      <p> {React.string("Name: " ++ hero.name)} </p>
      <p> {React.string("Skill: " ++ string_of_float(hero.skill))} </p>
    </div>;
  };
};

[@react.component]
let make = (~heroes: list(Hero.hero)) => {
  let heroCards =
    List.map(hero => <HeroCard hero key={hero.id} />, heroes)
    ->Array.of_list
    ->React.array;
  // {
  //   React.array(Array.of_list(List.map(hero => <HeroCard hero />, heroes)));
  // };

  <div> {React.string("Your Heroes")} <div> heroCards </div> </div>;
};
