open Css;

let card =
  style([
    display(flexBox),
    flexDirection(column),
    alignItems(stretch),
    backgroundColor(blue),
  ]);

let form =
  style([display(flexBox), flexDirection(column), backgroundColor(white)]);

global("input", [margin(px(10))]);
