module HeroSelector = {
  [@react.component]
  let make =
      (
        ~position: string,
        ~selectedHero: option(Hero.hero),
        ~heroOptions: list(Hero.hero),
        ~handleChange,
      ) => {
    <div className="inline-block relative m-2">
      <label className=Styles.formLabel>
        {React.string(position ++ ": ")}
        <select
          className=Styles.input
          name=position
          value={
            switch (selectedHero) {
            | Some(hero) => hero.id
            | None => ""
            }
          }
          onChange=handleChange>
          <option value="" disabled=true>
            {React.string("fill position")}
          </option>
          {List.map(
             (hero: Hero.hero): React.element =>
               <option value={hero.id} key={hero.id}>
                 {React.string(hero.name)}
               </option>,
             heroOptions,
           )
           ->Array.of_list
           ->React.array}
        </select>
      </label>
      <div
        className="pointer-events-none absolute inset-y-0 right-0 flex items-center px-2 text-gray-700">
        <svg
          className="fill-current h-4 w-4"
          xmlns="http://www.w3.org/2000/svg"
          viewBox="0 0 20 20">
          <path
            d="M9.293 12.95l.707.707L15.657 8l-1.414-1.414L10 10.828 5.757 6.586 4.343 8z"
          />
        </svg>
      </div>
    </div>;
  };
};

[@react.component]
let make = (~heroes: list(Hero.hero), ~submitParty: Quest.party => unit) => {
  /* States for each party position */
  let (scout: option(Hero.hero), setScout) =
    React.useState(() => (None: option(Hero.hero)));
  let (leader: option(Hero.hero), setLeader) =
    React.useState(() => (None: option(Hero.hero)));
  let (defence: option(Hero.hero), setDefence) =
    React.useState(() => (None: option(Hero.hero)));
  let (support: option(Hero.hero), setSupport) =
    React.useState(() => (None: option(Hero.hero)));

  let handleChange = (heroSetter, event) => {
    let selectedId = ReactEvent.Form.target(event)##value;
    let hasId = (id, item: Hero.hero) => item.id === id;
    let selectedHero = List.find(hasId(selectedId), heroes);
    heroSetter(_ => Some(selectedHero));
  };

  let selectedHeros = (): list(Hero.hero) =>
    Belt.List.keepMap([scout, leader, defence, support], hero => hero);
  let isAlreadySelected = (hero: Hero.hero) =>
    List.exists(h => h === hero, selectedHeros());

  let availableOptions = (~forceAllow: option(Hero.hero)): list(Hero.hero) => {
    let heroFilter: Hero.hero => bool =
      switch (forceAllow) {
      | Some(forceHero) => (
          hero => hero === forceHero || !isAlreadySelected(hero)
        )
      | None => (hero => !isAlreadySelected(hero))
      };
    List.filter(heroFilter, heroes);
  };

  let validateAndSubmit = () =>
    switch (scout, leader, defence, support) {
    | (
        Some(scoutVal),
        Some(leaderVal),
        Some(defenceVal),
        Some(supportVal),
      ) =>
      submitParty({
        scout: scoutVal,
        leader: leaderVal,
        defence: defenceVal,
        support: supportVal,
      })
    | (_, _, _, _) =>
      Js.log("Cannot submit party until all positions filled") // TODO: do something when more need to be selected
    };

  <div className="p-2">
    <h3> {React.string("Select your pary")} </h3>
    <div className="block">
      <HeroSelector
        position="scout"
        selectedHero=scout
        heroOptions={availableOptions(~forceAllow=scout)}
        handleChange={handleChange(setScout)}
      />
      <HeroSelector
        position="leader"
        selectedHero=leader
        heroOptions={availableOptions(~forceAllow=leader)}
        handleChange={handleChange(setLeader)}
      />
      <HeroSelector
        position="defence"
        selectedHero=defence
        heroOptions={availableOptions(~forceAllow=defence)}
        handleChange={handleChange(setDefence)}
      />
      <HeroSelector
        position="support"
        selectedHero=support
        heroOptions={availableOptions(~forceAllow=support)}
        handleChange={handleChange(setSupport)}
      />
    </div>
    <button
      className=Styles.btnBlue
      type_="submit"
      onClick={_ => validateAndSubmit()}>
      {React.string("Submit Party")}
    </button>
  </div>;
};