module QuestCard = {
  [@react.component]
  let make = (~quest: Quest.quest) => {
    let locationString = (location: Quest.location): string =>
      switch (location) {
      | Forest => "Forest"
      | Ruin => "Ruin"
      };

    // let locationString = "dummy";

    <div className="max-w-xs rounded overflow-hidden shadow-lg p-2 m-2">
      <p> {React.string("Description: " ++ quest.description)} </p>
      <p>
        {React.string("Challenge: " ++ Js.Float.toString(quest.challenge))}
      </p>
      <p> {React.string("Location: " ++ locationString(quest.location))} </p>
    </div>;
  };
};