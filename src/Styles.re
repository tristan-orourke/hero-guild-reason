open Css;

let flexColumn = style([display(flexBox), flexDirection(column)]);

let form =
  style([display(flexBox), flexDirection(column), backgroundColor(white)]);

global("input", [margin(px(10))]);
