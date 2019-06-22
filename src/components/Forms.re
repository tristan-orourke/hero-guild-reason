module TextInput = {
  [@react.component]
  let make = (~label: string, ~value: string, ~onChange) => {
   
    <label className=Styles.formLabel>
        {React.string(label)}
        <input className={Styles.input} type_="text" value onChange />
    </label>;
  };
};
module NumberInput = {
  [@react.component]
  let make = (~label: string, ~value: float, ~step=1.0, ~onChange) => {


    <label className=Styles.formLabel>
        {React.string(label)}
        <input className=Styles.input
            type_="number"
            step 
            value={string_of_float(value)} 
            onChange />
    </label>;
  };
};
